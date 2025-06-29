# Codex AI Assistant Instructions (AGENTS)

This file provides instructions to AI assistants (Codex CLI) about the scope and guidelines
for the Elegoo Uno R3 Car Kit V4 Projects repository.

## Project Overview

- **Name**: Elegoo Uno R3 Car Kit V4 Projects
- **Purpose**: Arduino and ESP32-based robot car control examples, setup tutorials, and guides
- **Languages**: C/C++ (Arduino .ino), Markdown documentation
- **Key directories**:
  - `docs/SETUP.md`: Quick-start six-mission setup guide
  - `docs/SETUP-FEDORA-41.md`: Fedora 41 advanced IDE & CLI setup
  - `docs/uploading-code.md`: Detailed code-uploading instructions
  - `docs/xbox-control-steps.md`: Xbox controller integration guide
  - `sketches/esp32_xbox_controller.ino`: ESP32 Xbox controller sketch
  - `sketches/arduino_motor_brain.ino`: Arduino motor control sketch

## Toolchain & Dependencies

- Arduino IDE 2.x (Flatpak or AppImage)
- arduino-cli (via install script or Snap)
- avr-gcc, avr-libc, avrdude for AVR builds
- Bluepad32 library for ESP32 Xbox controller support

## Coding & Documentation Guidelines

- Use 2-space indentation for C/C++ code
- Sketches must compile in Arduino IDE and arduino-cli without errors
- Document new features in Markdown under `docs/`
- Reference existing code paths and docs in any responses or new content

## Commit & Patch Style

- Use `apply_patch` for edits; provide concise commit messages prefixed by area scope,
  e.g., `docs: add new setup guide` or `sketches: implement braking feature`
- Do NOT add or remove license headers
- Keep changes atomic and focused; update docs if behavior changes

## AI Assistant Behavior

- Always read relevant docs before suggesting code changes
- Ask clarifying questions if user requirements are ambiguous
- Preserve repository structure and style