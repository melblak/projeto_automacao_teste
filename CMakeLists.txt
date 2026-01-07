cmake_minimum_required(VERSION 3.16)

project(projeto_automacao_teste LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core SerialPort Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialPort Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(projeto_automacao_teste
  main.cpp
  placa.h placa.cpp

)
target_link_libraries(projeto_automacao_teste PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::SerialPort
  Qt${QT_VERSION_MAJOR}::Widgets
)
target_link_libraries(projeto_automacao_teste PRIVATE Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS projeto_automacao_teste
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
