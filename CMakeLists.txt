cmake_minimum_required(VERSION 3.16)

project(LibraryManagementSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

set(PROJECT_SOURCES
    src/main.cpp
    src/core/Book.h
    src/core/User.h
    src/core/DatabaseManager.h
    src/core/DatabaseManager.cpp
    src/core/LibraryService.h
    src/core/LibraryService.cpp
    src/ui/MainWindow.h
    src/ui/MainWindow.cpp
    src/ui/LoginWidget.h
    src/ui/LoginWidget.cpp
    src/ui/DashboardWidget.h
    src/ui/DashboardWidget.cpp
    src/ui/AddBookDialog.h
    src/ui/AddBookDialog.cpp
)

add_executable(LibraryManagementSystem ${PROJECT_SOURCES})

target_link_libraries(LibraryManagementSystem PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)

# Set up include directories
target_include_directories(LibraryManagementSystem PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Handle resources if needed later
# qt_add_resources(LibraryManagementSystem "resources"
#     PREFIX "/"
#     FILES resources/style.qss
# )
