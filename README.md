# Qt_MusicPlayer

![Dashboard Screenshot](assets/view_0.png)

Qt_MusicPlayer is a simple music player application built with Qt 6.
The backend is implemented in C++, while the user interface is created using QML.

## Purpose

This project was developed while following the YouTube tutorial:
"Qt QML Tutorial #0: Introduction to Qt/QML" by Somco Software.

The main goal was to learn and understand:
- Integration between C++ and QML
- Qt 6 project structure
- Signals and slots communication
- Basic media handling in Qt
- QML UI components and layouts

# Table of Contents

-   Features
-   Technologies
-   Installation and building
-   Running
-   Project structure
-   Future plans
-   License

# Features

-   Loading audio files (e.g., MP3, WAV)
-   Play, pause, resume
-   Skip to next/previous track
-   Display basic audio file information (e.g., title, artist)
-   Simple, responsive interface layer with QML

# Technologies

- C++ (backend)
- QML (UI)
- Qt 6 framework
- CMake as the build system
- (Optional) Qt multimedia components

# Installation and building

1. Clone the repository:
```
git clone https://github.com/r‑lapins/Qt_MusicPlayer.git
cd Qt_MusicPlayer
```
2.  Create a build directory and configure the CMake project:
```    mkdir build && cd build
cmake ..
```
3.  Build the project:
```
cmake –build .
```

# Running

Once the build is complete, run the generated binary file (e.g.,
Qt_MusicPlayer).

# Project structure
```
/assets/            # Application resources (icons, images, etc.)
/qml/               # QML user interface files

AudioInfo.h/.cpp    # Class responsible for handling audio metadata
PlayerController.h/.cpp  # Core player logic and playback control

main.cpp            # Application entry point
CMakeLists.txt      # CMake build configuration
.gitignore
README.md
```
# Future plans

-   Playlists
-   Shuffle / repeat
-   Music library
-   More formats
-   UI improvement

# License

MIT (or no license)
