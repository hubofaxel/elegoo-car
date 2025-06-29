# Fedora 41 Advanced Setup & Arduino IDE Configuration

Below is the Fedora-41–specific workflow that matches the **current (29 June 2025)**
recommendations from Fedora’s own developer portal and the latest Arduino documentation.
Follow it top-to-bottom and you’ll have both the graphical IDE **and** a fully-functional
tool-chain (CLI, compilers, uploaders) ready for AVR-based boards such as the Elegoo Uno R3.

---

## 1 — Prep your system once

```bash
sudo dnf update                          # keep 41 fully patched
sudo dnf groupinstall "Development Tools"  # gcc-base, make, gdb, etc.
```

---

## 2 — Install the core AVR tool-chain (native RPMs)

Fedora 41 ships current cross-compilers and uploader tools in the official repos:

```bash
sudo dnf install \
  avr-gcc avr-gcc-c++ avr-libc avrdude \
  dfu-programmer pic32prog \
  arm-none-eabi-gcc-cs arm-none-eabi-newlib openocd
```

* `avr-gcc` 14.2.0-1.fc41 provides the C compiler for ATmega/ATtiny chips ([packages.fedoraproject.org][1])
* `avrdude` 8.0-4.fc41 handles flashing over USB/serial/ISP ([bodhi.fedoraproject.org][2])

That’s enough to compile and upload sketches from either the GUI or the CLI.

---

## 3 — Graphical Arduino IDE 2 (Flatpak – Fedora-recommended)

Fedora’s official “Work with Arduino” page now points to Flathub as the canonical install path ([developer.fedoraproject.org][3]):

```bash
# one-time: add the Flathub repo
flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo

# install the current IDE (v2.x)
flatpak install cc.arduino.arduinoide

# run it
flatpak run cc.arduino.arduinoide
```

*The Flatpak updates automatically via `flatpak update` and stays sandboxed from the rest of your system.*

---

### Alternate GUI route (official AppImage)

If you dislike Flatpak, Arduino’s upstream guide offers an AppImage you can drop anywhere:
download the `arduino-ide_*_Linux_64bit.AppImage`, `chmod +x`, and double-click or run
it from the shell ([docs.arduino.cc][4]).

---

## 4 — Command-line workflow (arduino-cli)

The CLI is ideal for scripted builds or headless servers.

#### a) Fast install via the upstream script (always grabs the latest release):

```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
# move it to your PATH, e.g.:
sudo mv bin/arduino-cli /usr/local/bin
arduino-cli version
```

(Installation script documented by Arduino CLI maintainers) ([docs.arduino.cc][5])

#### b) Snap alternative (if you already use snapd):

```bash
sudo dnf install snapd
sudo ln -s /var/lib/snapd/snap /snap   # classic confinement link
sudo snap install arduino-cli
```

([snapcraft.io][6])

After installing, initialise your environment and grab the AVR core once:

```bash
arduino-cli config init                    # creates ~/.arduino15
arduino-cli core update-index
arduino-cli core install arduino:avr       # Uno / Nano / Mega boards
```

---

## 5 — USB & udev (only needed once)

The IDE and CLI can access serial ports out of the box if your user is in the `dialout` group:

```bash
sudo usermod -aG dialout $USER
newgrp dialout   # or log out/in
```

Most Elegoo Uno clones use the CH340 or ATmega16U2 USB–serial chips, both supported by
Fedora’s kernel. If uploads fail, confirm the device node:

```bash
ls -l /dev/ttyACM* /dev/ttyUSB*
```

---

## 6 — Test the full round-trip

1. **Launch the IDE** → select **Tools ▸ Board ▸ Arduino AVR Boards ▸ Uno**.
2. **Open File ▸ Examples ▸ 01.Basics ▸ Blink**.
3. Click **Verify → Upload**. The on-board LED should blink.

From the CLI the same build/upload looks like:

```bash
arduino-cli compile -b arduino:avr:uno Blink
arduino-cli upload  -b arduino:avr:uno -p /dev/ttyACM0 Blink
```

---

### Quick recap

| Component          | Package / Command                       | Source                                                 |
| ------------------ | --------------------------------------- | ------------------------------------------------------ |
| AVR cross-compiler | `avr-gcc`, `avr-libc`                   | Fedora 41 RPMs ([packages.fedoraproject.org][1])       |
| Flasher            | `avrdude`                               | Fedora 41 RPM ([bodhi.fedoraproject.org][2])           |
| GUI IDE 2.x        | `flatpak install cc.arduino.arduinoide` | Fedora Dev Portal ([developer.fedoraproject.org][3])   |
| CLI                | install script or Snap                  | Arduino docs ([docs.arduino.cc][5], [snapcraft.io][6]) |
| Upstream AppImage  | manual download                         | Arduino IDE docs ([docs.arduino.cc][4])                |

That’s it—Fedora 41 now has every piece you need to write, build, and flash Arduino sketches
either graphically or from the command line. Happy hacking!

[1]: https://packages.fedoraproject.org/pkgs/avr-gcc/avr-gcc/fedora-40.html?utm_source=chatgpt.com "avr-gcc-13.2.0-3.fc40 - Fedora Packages"
[2]: https://bodhi.fedoraproject.org/updates/?packages=avrdude&utm_source=chatgpt.com "Fedora Updates System"
[3]: https://developer.fedoraproject.org/start/hw/arduino/about.html?utm_source=chatgpt.com "Work with Arduino - Fedora Developer Portal"
[4]: https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing?utm_source=chatgpt.com "Downloading and installing the Arduino IDE 2"
[5]: https://docs.arduino.cc/arduino-cli/installation?utm_source=chatgpt.com "Installation | Arduino Documentation"
[6]: https://snapcraft.io/install/arduino-cli/fedora?utm_source=chatgpt.com "Install arduino-cli on Fedora using the Snap Store - Snapcraft"