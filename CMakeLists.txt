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

# --- Search for Qt5
find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets REQUIRED)
set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets)

# --- Project sources
set(PROJECT_SOURCES
    src/GameConfiguration.cpp
    src/MainWindow.cpp
    src/main.cpp
    src/tictactoewidget.cpp
)

set(PROJECT_HEADERS
    include/GameConfiguration.hpp
    include/MainWindow.hpp
    include/tictactoewidget.h
)

set(PROJECT_FORMS
    resources/ui/GameConfiguration.ui
    resources/ui/MainWindow.ui
)

set(PROJECT_RESOURCES
    resources/resources.qrc
)

# --- Executable
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_FORMS}
        ${PROJECT_RESOURCES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/resources/ui"
)

# --- ExecutableIcon
if (WIN32)
    target_sources(${PROJECT_NAME} PRIVATE resources/app_icon.rc)
endif()

# --- Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
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
find_program(WINDEPLOYQT_EXECUTABLE windeployqt)

# --- Automatically copy Qt dependencies
if(WIN32 AND WINDEPLOYQT_EXECUTABLE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_custom_command(TARGET TicTacToeWithAI POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E chdir "$<TARGET_FILE_DIR:TicTacToeWithAI>"
             "${WINDEPLOYQT_EXECUTABLE}" --no-compiler-runtime .
    COMMENT "Ejecutando windeployqt en la carpeta del ejecutable para la configuración Release"
    )
endif()
