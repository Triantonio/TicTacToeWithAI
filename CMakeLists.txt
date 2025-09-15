cmake_minimum_required(VERSION 3.16)

project(TicTacToeWithAI LANGUAGES CXX)

# --- C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Force the installation path.
set(CMAKE_INSTALL_PREFIX "C:/Users/azamora/Desktop/Antonio Zamora Saiz/TicTacToe/TicTacToeWithAI" CACHE PATH "Install path" FORCE)

# --- Activar automoc, autouic y autorcc (manejan Q_OBJECT, .ui y .qrc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# --- Buscar Qt (primero Qt6, si no Qt5)
find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia QUIET)
if (Qt6_FOUND)
    set(QT_LIBS Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
else()
    find_package(Qt5 COMPONENTS Core Gui Widgets Multimedia REQUIRED)
    set(QT_LIBS Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)
endif()

# --- Fuentes
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

# --- Ejecutable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)

# --- Vincular librerías
target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBS})

# --- Instalación (equivalente a target.path en qmake)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# (Opcional) Si quieres copiar assets, sonidos, imágenes, etc.:
install(FILES resources/sound.wav DESTINATION resources)

# Mensaje informativo
message(STATUS "Configuring ${PROJECT_NAME} with Qt libraries: ${QT_LIBS}")

# --- Localiza automáticamente windeployqt según el kit de Qt
get_target_property(_qt5_qmake_location Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt5_bin_dir "${_qt5_qmake_location}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt5_bin_dir}")

# --- Copiar dependencias Qt automáticamente
if(WIN32 AND WINDEPLOYQT_EXECUTABLE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_custom_command(TARGET TicTacToeWithAI POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E chdir "$<TARGET_FILE_DIR:TicTacToeWithAI>"
             "${WINDEPLOYQT_EXECUTABLE}" --no-compiler-runtime .
    COMMENT "Ejecutando windeployqt en la carpeta del ejecutable para la configuración Release"
    )
endif()