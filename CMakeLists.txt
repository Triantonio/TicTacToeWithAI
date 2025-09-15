cmake_minimum_required(VERSION 3.16)

project(TicTacToeWithAI LANGUAGES CXX)

# --- C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sets the default installation directory within the project folder.
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "Default installation path")


# --- Enable automoc, autouic, and autorcc (handle Q_OBJECT, .ui, and .qrc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- Search for Qt (first Qt6, if not Qt5)
find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia QUIET)
if (Qt6_FOUND)
    set(QT_LIBS Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
else()
    find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)
    set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)
endif()

# --- Sources
set(SOURCES
    GameConfiguration.cpp
    MainWindow.cpp
    main.cpp
    tictactoewidget.cpp
)

set(HEADERS
    GameConfiguration.hpp
    MainWindow.hpp
    tictactoewidget.h
)

set(FORMS
    GameConfiguration.ui
    MainWindow.ui
)

set(RESOURCES
    resources.qrc
)

# --- Executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

# --- Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBS})

# --- Installation (equivalent to target.path in qmake)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# (Optional) If you want to copy assets, sounds, images, etc.:
install(FILES resources/sound.wav DESTINATION resources)

# Informative message
message(STATUS "Configuring ${PROJECT_NAME} with Qt libraries: ${QT_LIBS}")

# --- Automatically locate windeployqt based on the Qt kit
get_target_property(_qt5_qmake_location Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt5_bin_dir "${_qt5_qmake_location}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt5_bin_dir}")

# --- Automatically copy Qt dependencies
if(WIN32 AND WINDEPLOYQT_EXECUTABLE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_custom_command(TARGET TicTacToeWithAI POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E chdir "$<TARGET_FILE_DIR:TicTacToeWithAI>"
             "${WINDEPLOYQT_EXECUTABLE}" --no-compiler-runtime .
    COMMENT "Ejecutando windeployqt en la carpeta del ejecutable para la configuración Release"
    )
endif()