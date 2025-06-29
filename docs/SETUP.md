**Let’s set everything up in six bite-sized missions.
Do them in order and you’ll be coding your robot car in no time!**

---

### Mission 1 – Open your Fedora terminal

Press <kbd>Super</kbd> (Windows/⌘ key) → type **“terminal”** → press <kbd>Enter</kbd>.
Keep this window open for every mission.

---

### Mission 2 – Install & test the GitHub CLI (`gh`)

1. **Do I already have it?**

   ```bash
   gh --version
   ```

   If you see a version number (for example `gh version 2.50.0`) you’re good – skip to Mission 3.
   If you get “command not found”, install it:

2. **Add the official repo and install:**

   ```bash
   sudo dnf config-manager --add-repo https://cli.github.com/packages/rpm/gh-cli.repo
   sudo dnf install gh
   ```

3. **Check again:**

   ```bash
   gh --version
   ```

   Now you should see that version number.

---

### Mission 3 – Log in to GitHub from the terminal

```bash
gh auth login
```

* Pick **GitHub.com** → **HTTPS** → **Login with a web browser**.
* Your browser pops up; click **“Authorize”**, then return to the terminal.
* Verify:

  ```bash
  gh auth status
  ```

  It should show your username and “✓ Logged in”. ([cli.github.com][1])

---

### Mission 4 – Create your project folder & GitHub repo

1. **Make a place for your code and go inside it:**

   ```bash
   mkdir ~/elegoo-car
   cd ~/elegoo-car
   ```

2. **Turn it into a Git repo and push it to GitHub in one shot:**

   ```bash
   gh repo create elegoo-car \
     --public --source=. --remote=origin --push
   ```

   (Change `elegoo-car` to any name you like.)

3. **Add a starter README and project structure:**

   ```bash
   echo "# Elegoo Uno R3 Car Kit V4 Projects" > README.md
   mkdir sketches docs
   echo "*.bin\n*.hex\nbuild/" > .gitignore     # keeps compiled stuff out of Git
   git add .
   git commit -m "Initial project structure"
   git push
   ```

Now your brand-new repo lives on GitHub and has neat folders ready for code.

---

### Mission 5 – Install the Arduino IDE the Fedora-easy way

1. **Enable Flathub (one-time step):**

   ```bash
   flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
   ```

2. **Install Arduino IDE 2.x:**

   ```bash
   flatpak install flathub cc.arduino.arduinoide
   ```

3. **Launch it:**
   *GUI:* Press <kbd>Super</kbd> → type “**arduino**” → click the blue icon.
   *OR* from terminal:

   ```bash
   flatpak run cc.arduino.arduinoide
   ```

---

### Mission 6 – First-time IDE setup for your Uno R3 car kit

1. **Select board:** *Tools ▸ Board ▸ Arduino AVR Boards ▸ Arduino Uno*
2. **Plug in the USB cable.** Wait a few seconds.
3. **Pick the serial port:** *Tools ▸ Port* → choose something like `/dev/ttyACM0`.
4. **Test upload:** In the IDE open `File ▸ Examples ▸ 01.Basics ▸ Blink` → click the **➡️ Upload** arrow.
   The little LED on the Uno should start blinking -- success!

> **Tip:** If the IDE can’t see the port, unplug/re-plug the USB or reboot once; Flatpak adds the needed udev rules automatically.

---

## Victory! 🎉

You now have:

* **GitHub CLI** installed & authenticated
* A **GitHub repo** with README, `sketches/`, and `docs/` folders
* **Arduino IDE 2** installed, launchable from your menu or terminal
* Your Elegoo Uno R3 talking to Fedora

Happy hacking, future systems wizard!

[1]: https://cli.github.com/manual/gh_auth_login?utm_source=chatgpt.com "gh auth login - GitHub CLI"