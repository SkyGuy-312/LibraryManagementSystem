# Library Management System

A desktop application for managing library books, built with **C++** and **Qt 5**. This application demonstrates a clean **MVC architecture**, role-based access control, and JSON-based persistence.

## Features

- **Role-Based Access Control (RBAC)**:
  - **Admin**: Full access. Can searching, viewing, **adding**, and **removing** books.
  - **User**: Read-only access. Can only search and view books.
- **Search Functionality**:
  - Filter by **Title**, **Author**, or **Category**.
  - Supports multiple active filters simultaneously.
- **Persistent Storage**:
  - Data is automatically saved to `books.json` and `users.json` in the application directory.
  - No external database server required.
- **Modern UI**:
  - Clean Qt Widgets interface with a dedicated Login screen and Dashboard.

## Prerequisites

To build and run this project, you need:

- **C++ Compiler** (GCC, Clang, or MSVC) supporting C++17.
- **CMake** (Version 3.16 or higher).
- **Qt 5** (Core, Gui, Widgets modules).
  - *Ubuntu/Debian*: `sudo apt-get install qt5-default`

## Build Instructions

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/SkyGuy-312/LibraryManagementSystem.git
    cd LibraryManagementSystem
    ```

2.  **Create a build directory**:
    ```bash
    mkdir build && cd build
    ```

3.  **Run CMake**:
    ```bash
    cmake ..
    ```

4.  **Build the application**:
    ```bash
    make
    ```

## Usage

1.  Run the executable from the build directory:
    ```bash
    ./LibraryManagementSystem
    ```

2.  **Log in** using the default credentials:
    - **Username**: `admin`
    - **Password**: `admin`

    *Note: The first time you run the app, the admin account is automatically created.*

3.  **Dashboard**:
    - Use the **Search bar** to find books.
    - Check the boxes to filter by specific fields.
    - (Admin only) Click **"Add Book"** to open the creation dialog.
    - (Admin only) Select a row and click **"Remove Selected"** to delete a book.

## Project Structure

- `src/core`: Backend logic and data models (`Book`, `User`, `DatabaseManager`).
- `src/ui`: Qt Widget classes (`LoginWidget`, `DashboardWidget`, `MainWindow`).
- `src/main.cpp`: Application entry point.

