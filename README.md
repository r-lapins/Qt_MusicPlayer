# Qt_MusicPlayer

![Dashboard Screenshot](assets/view_0.png)

Qt_MusicPlayer is a simple music player created using C++
(backend) and QML (interface). The project is based on a tutorial and serves as
a good starting point for learning Qt 6 + QML + C++ integration.

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
-   Display basic audio file information (e.g., title,
    artist)
-   Simple, responsive interface layer with QML

# Technologies

-   C++ (backend)
-   QML (UI)
- Qt 6 framework
- CMake as the build system
- (Optional) Qt multimedia components

# Installation and building

1. Clone the repository:
  git clone https://github.com/r‑lapins/Qt_MusicPlayer.git
  cd Qt_MusicPlayer
2.  Create a build directory and configure the CMake project:
    mkdir build && cd build
    cmake ..
3.  Build the project:
    cmake –build .

# Running

Once the build is complete, run the generated binary file (e.g.,
Qt_MusicPlayer).

# Project structure

/assets/ – assets
/qml/ – QML interface
AudioInfo.cpp/.h – audio metadata
PlayerController.cpp/.h – player logic
main.cpp – entry point
CMakeLists.txt – configuration
.gitignore
README.md

# Future plans

-   Playlists
-   Shuffle / repeat
-   Music library
-   More formats
-   UI improvement

# License

MIT (or no license).


Translated with DeepL.com (free version)
