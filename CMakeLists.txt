cmake_minimum_required(VERSION 3.16)

project(AudioPlayerTutorial VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appAudioPlayerTutorial
    main.cpp
    resources.qrc
    PlayerController.h PlayerController.cpp
)

set_target_properties(appAudioPlayerTutorial PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAudioPlayerTutorial
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAudioPlayerTutorial
    PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Multimedia
)
target_link_libraries(appAudioPlayerTutorial PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appAudioPlayerTutorial
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
