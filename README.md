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
- **Polished desktop integration** thanks to dedicated icon resources and a
  reorganized asset pipeline that keeps images, sounds, and videos bundled with
  the executable.

## Introductory video

Get a preview of the application's look and feel with the intro clip that
ships with the repository:

- [Watch the intro video](resources/video/TitleIntro.wmv)

If your browser cannot play WMV files directly, download the video and open it
with any multimedia player that supports the Windows Media Video format.

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

3. (Optional, but recommended for Release builds) Install the compiled
   application so that the runtime directory mirrors the packaged layout:

   ```bash
   cmake --install build
   ```

4. Launch the resulting application:

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

## Git workflow

To keep the project history organized, we follow a Gitflow-inspired branching
model:

- **Default branch:** all new work starts from `develop`. Create feature or fix
  branches from it and open pull requests back into `develop` when the work is
  ready for review.
- **Protected `main`:** the `main` branch stays deployment-ready. It is
  protected in GitHub so only merges coming from reviewed pull requests are
  allowed, and Triantonio must approve every merge request before it is
  completed.
- **Promotion to production:** when the code in `develop` is stable, open a pull
  request from `develop` into `main`, obtain the mandatory approval, and merge.
Optionally tag the merge commit to mark the release.

![Gitflow branching model](https://nvie.com/img/git-model@2x.png)

## Automated Windows release workflow

When you create a Git tag whose name starts with `v` (for example, `v1.0.0`),
GitHub Actions runs the workflow defined in `.github/workflows/release.yml` to
produce a ready-to-use Windows build:

1. **Runner setup.** The job executes on `windows-latest`, checks out the
   repository, pins Python 3.10 to keep the Qt installer tooling compatible, and
   installs Qt 5.15.2 with the optional modules required by the application
   (`qtmultimedia` for audio/video support and `qttools` for `windeployqt`). It
   also installs Ninja, the fast build tool used by CMake on Windows runners.
   installs Qt 5.15.2 with the modules required by the application (`qtbase`,
   `qtmultimedia`, and `qttools`). It also installs Ninja, the fast build tool
   used by CMake on Windows runners.
   repository, and installs Qt 5.15.2 with the modules required by the
   application (`qtbase`, `qtmultimedia`, and `qttools`). It also installs Ninja,
   the fast build tool used by CMake on Windows runners.
2. **Configure and build.** CMake configures the project in Release mode and
   compiles it, generating the `TicTacToeWithAI.exe` executable inside the
   temporary build directory.
3. **Install step.** `cmake --install` copies the executable and resources to an
   `install` folder so that the layout matches what end users need.
4. **Bundle Qt dependencies.** The workflow invokes `windeployqt` on the
   executable to gather all the Qt DLLs and plugins required to run the
   application outside the development environment.
5. **Package and publish.** The contents of the `install` directory are zipped
   into `TicTacToeWithAI-<tag>-windows.zip`. The archive is uploaded both as a
   workflow artifact and as an asset attached to the tag's GitHub Release, so
   you can download the executable without building it locally.

You can adjust the workflow (for example, to add more Qt modules or include
additional packaging steps) by editing `.github/workflows/release.yml`.

## Developer resources

- The new `include/` directory exposes public headers so other components can
  depend on the game's API without navigating the implementation sources.
- `doc/doxygen/Doxyfile` configures Doxygen to generate browsable API
  documentation. Run it after building to refresh the HTML pages referenced in
  the repository documentation.
- All runtime assets now live under `resources/`, simplifying Qt resource
  management and making it easier to bundle everything with release builds or
  installers.

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
