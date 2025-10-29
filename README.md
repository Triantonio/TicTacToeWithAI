# TicTacToeWithAI

TicTacToeWithAI is a Qt-based desktop application that lets you play the
classic tic-tac-toe game either against another person or against a computer
controlled opponent. The project leverages Qt widgets for the graphical user
interface and the framework's multimedia stack to provide an interactive
experience with animations and sound effects.

## Key features

- **Modern graphical interface** built on top of `QMainWindow` and forms
  created with Qt Designer (`resources/ui`).
- **Local multiplayer mode** with automatic turn switching and highlighting of
  the active player.
- **Two AI difficulty levels** (normal and easy) that execute their moves after
  a short, configurable delay.
- **Configurable board size** that can be adjusted between 3x3 and 10x10 before
  each match.
- **Multimedia feedback** with sounds for moves and victories, plus an
  introductory video displayed in the main window whenever the board is idle.

## Requirements

- CMake >= 3.16
- A compiler with C++17 support
- Qt 5 with the following modules: `Core`, `Gui`, `Widgets`, `Multimedia`, and
  `MultimediaWidgets`

On Debian/Ubuntu-based systems you can install a minimal toolchain with:

```bash
sudo apt install qtbase5-dev qtmultimedia5-dev qttools5-dev-tools build-essential cmake
```

## Build and run

1. Create an out-of-source build directory:

   ```bash
   cmake -S . -B build
   ```

2. Compile the project:

   ```bash
   cmake --build build
   ```

3. Launch the resulting application:

   ```bash
   ./build/TicTacToeWithAI
   ```

On Windows, consider generating the project from the "Qt Developer Command
Prompt" to ensure `windeployqt` is available and to copy the Qt libraries next
to the executable when producing a **Release** build.

## Project structure

- `src/`: application source code (main window, board logic, and initialization).
- `include/`: public headers with each component's API.
- `resources/`: icons, sounds, videos, `.ui` files, and the Qt resource file
  (`resources.qrc`).
- `doc/`: Doxygen configurations for generating API documentation.
- `CHANGELOG.md`: project change log.

## Generate documentation (optional)

The `doc/doxygen` directory contains a ready-to-use `Doxyfile`. To produce the
API documentation run:

```bash
cd doc/doxygen
doxygen Doxyfile
```

Make sure `doxygen` and `graphviz` are installed if you want collaboration
graphs.

## License

This repository does not include an explicit license. Confirm with the original
author before distributing the software or reusing its code.
