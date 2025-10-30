# 📜 Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).

---

## [Unreleased]
### 🚧 Planned for v1.2.0
- Integration of Continuous Integration workflows (build & test automation).
- Add unit tests for AI logic.
- Improve documentation with Doxygen.
- Further UI/UX improvements.

---

## [v1.1.1] - 2025-10-30
### ✨ Highlights
- Migrated the project from qmake to CMake, enabling automatic Qt code
  generation (moc/uic/rcc), a predictable install layout, and Windows packaging
  via `windeployqt`.
- Reorganized headers and runtime assets into dedicated `include/` and
  `resources/` directories and added application icons for a polished desktop
  experience.
- Bundled the introductory video with release artifacts so the multimedia intro
  plays out-of-the-box on fresh installations.

### 📦 Continuous Delivery
- Added a Windows release workflow that compiles the app on GitHub Actions,
  collects Qt dependencies, and publishes a ready-to-use ZIP archive whenever a
  version tag is created.
- Documented the Gitflow process, branch protection requirements, and release
  automation so contributors understand how to promote builds to production.

### 📚 Documentation
- Expanded the README with the intro video link, developer resources, and
  guidance on building and packaging the project.
- Introduced a full Doxygen configuration and richer inline comments so the API
  reference can be generated directly from the source tree.

---

## [v1.1.0] - 2025-09-10
### ✨ New Features
- **AI Opponent Added:**
  - Easy Mode: random moves.
  - Hard Mode: nearby move algorithm.
- **Sound Effects:** play when winning, drawing, or ending a game.
- **Game Modes:** Human vs Human, Human vs AI (easy or hard).

### 🛠 Enhancements
- Refactored game logic to integrate AI while keeping core stability.
- Updated UI to allow mode selection and show AI status.

---

## [v1.0.0] - 2025-08-26
### 🚀 Initial Stable Release
This release marks the official launch of the application with a fully functional TicTacToe board for two players.

#### ✨ Features
- Initial stable version.
- Functional TicTacToe game without AI.
- Ready-to-use interface.
- Complete game logic implemented.

#### 🛠 Next Steps
- Implement AI opponent using **Minimax** algorithm.
- Add difficulty levels.
- Improve UI/UX experience.
