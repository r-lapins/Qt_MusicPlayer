cmake_minimum_required(VERSION 3.16)

project(AudioPlayerTutorial VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core Gui Qml Quick Multimedia
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_standard_project_setup()

qt_add_executable(appAudioPlayerTutorial
    main.cpp
    PlayerController.h PlayerController.cpp
)

qt_add_resources(appAudioPlayerTutorial
    PREFIX "/"
    FILES
    assets/icons/app_icon.png
)

file(GLOB_RECURSE QML_SRC
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    qml/*.qml)

file(GLOB_RECURSE ASSETS_SRC
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    assets/*.*
)

qt_add_qml_module(appAudioPlayerTutorial
    URI AudioPlayer
    VERSION 1.0
    RESOURCE_PREFIX "/"

    QML_FILES ${QML_SRC}

    RESOURCES ${ASSETS_SRC}
)

target_link_libraries(appAudioPlayerTutorial
    PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appAudioPlayerTutorial
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
