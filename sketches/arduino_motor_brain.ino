// Arduino Motor Brain Code for Elegoo Uno R3 Car Kit V4
#define PWMA 5  // Right motor speed
#define PWMB 6  // Left motor speed
#define AIN1 7  // Right motor direction
#define BIN1 8  // Left motor direction
#define STBY 3  // Motor driver standby

void setup() {
    Serial.begin(115200);
    // Set up motor pins
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(STBY, OUTPUT);
    // Turn on motor driver
    digitalWrite(STBY, HIGH);
    Serial.println("Arduino ready!");
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        char cmd = command.charAt(0);
        if (cmd == 'L' || cmd == 'R') {
            int speed = command.substring(1).toInt();
            setMotorSpeed(cmd, speed);
        } else if (cmd == 'S') {
            executeSpin();
        } else if (cmd == 'D') {
            performDance();
        }
    }
}

void setMotorSpeed(char motor, int speed) {
    speed = constrain(speed, -255, 255);
    if (motor == 'L') {
        if (speed >= 0) {
            digitalWrite(BIN1, HIGH);
            analogWrite(PWMB, speed);
        } else {
            digitalWrite(BIN1, LOW);
            analogWrite(PWMB, abs(speed));
        }
    } else if (motor == 'R') {
        if (speed >= 0) {
            digitalWrite(AIN1, HIGH);
            analogWrite(PWMA, speed);
        } else {
            digitalWrite(AIN1, LOW);
            analogWrite(PWMA, abs(speed));
        }
    }
}

void executeSpin() {
    setMotorSpeed('L', 255);
    setMotorSpeed('R', -255);
    delay(1000);
    setMotorSpeed('L', 0);
    setMotorSpeed('R', 0);
}

void performDance() {
    setMotorSpeed('L', 200);
    setMotorSpeed('R', 200);
    delay(500);
    setMotorSpeed('L', -200);
    setMotorSpeed('R', -200);
    delay(500);
    setMotorSpeed('L', -255);
    setMotorSpeed('R', 255);
    delay(750);
    setMotorSpeed('L', 0);
    setMotorSpeed('R', 0);
}