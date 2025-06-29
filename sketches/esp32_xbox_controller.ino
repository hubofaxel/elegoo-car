// ESP32 Xbox Controller Code for Elegoo Uno R3 Car Kit V4
#include <Bluepad32.h>

// This will hold our controller
ControllerPtr myController;

// Called when a controller connects
void onConnectedController(ControllerPtr ctl) {
    Serial.println("YES! Controller connected!");
    myController = ctl;
}

// Called when a controller disconnects
void onDisconnectedController(ControllerPtr ctl) {
    Serial.println("Oh no! Controller disconnected!");
    myController = nullptr;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Robot starting up...");

    // Set up Bluepad32
    BP32.setup(&onConnectedController, &onDisconnectedController);

    // Forget old controllers (clean slate!)
    BP32.forgetBluetoothKeys();

    Serial.println("Ready to pair with Xbox controller!");
}

void loop() {
    BP32.update();
    if (myController && myController->isConnected()) {
        processGamepad();
    }
    delay(20);
}

void processGamepad() {
    int leftY = myController->axisY();
    int rightY = myController->axisRY();

    int leftSpeed = map(leftY, -1023, 1023, -255, 255);
    int rightSpeed = map(rightY, -1023, 1023, -255, 255);

    // Dead zone - ignore tiny movements
    if (abs(leftSpeed) < 20) leftSpeed = 0;
    if (abs(rightSpeed) < 20) rightSpeed = 0;

    // Send commands to Arduino
    Serial.print("L"); Serial.println(leftSpeed);
    Serial.print("R"); Serial.println(rightSpeed);

    // Special moves with buttons!
    if (myController->a()) {
        Serial.println("S");
    }
    if (myController->b()) {
        Serial.println("D");
    }
}