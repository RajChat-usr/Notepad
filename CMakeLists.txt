cmake_minimum_required(VERSION 3.5)
project(Notepad)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Qt setup
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source and header files
set(SOURCES
    BudgetQt.cpp
    BudgetPlanner.cpp
)
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/BudgetPlanner.hpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
