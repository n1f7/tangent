cmake_minimum_required(VERSION 3.5.2)
project(TANGENT VERSION 0.0.0 LANGUAGES CXX C)

set(TANGENT_SOURCE_DIR ${TANGENT_SOURCE_DIR}/../)
set(CMAKE_MODULE_PATH ${TANGENT_SOURCE_DIR}/cmake)

option(BUILD_DEBUG "build with debug codepaths" ON)

set(OUT_NAME tangent)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Quick Core)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_executable(${OUT_NAME} ${RCC_SOURCES}
	${TANGENT_SOURCE_DIR}/src/tangent.cpp
	${TANGENT_SOURCE_DIR}/src/native_to_qt.cpp
	${TANGENT_SOURCE_DIR}/res/resources.qrc)
qt5_use_modules(${OUT_NAME} Quick)
