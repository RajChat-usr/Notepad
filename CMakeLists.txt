cmake_minimum_required(VERSION 3.5)
project(BudgetPlannerApp)

# Set the required Qt modules
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Add source and header files
set(SOURCES
    BudgetQt.cpp
    BudgetPlanner.cpp
)
set(HEADERS
    BudgetPlanner.hpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
