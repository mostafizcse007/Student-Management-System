# Student Management System

A console-based Student Management System written in C++ as a lab project. It provides admin and student portals for managing student records stored in a CSV file.

## Features

- **Admin Portal**
  - Add, remove, and modify student accounts
  - Search students by ID, name, email, gender, or average marks range
  - Sort students by average marks
  - Restore deleted student records
  - View student statistics (active/deleted counts)
  - Change admin credentials at runtime

- **Student Portal**
  - View personal details and performance analysis
  - Update personal information
  - Change password

- **Data Persistence** — records are saved to `students.csv` automatically

## How to Compile and Run

### Using Make

```bash
make
./student_management
```

### Manual Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o student_management LabProject.cpp
./student_management
```

## Usage

### Admin Login
- **Username:** `admin`
- **Password:** `admin123`

> ⚠️ **Security Note:** Change the default admin credentials immediately after the first login using the *Change Admin Password* option in the admin menu.

### Student Login
Students log in with the ID and password set by the admin when the account was created.

## Project Structure

```
Student-Management-System/
├── LabProject.cpp      # Single-file C++ source code
├── Makefile            # Build configuration
├── README.md           # This file
└── .gitignore          # Git ignore rules
```

Runtime-generated files (not tracked by git):
- `students.csv` — active student records
- `deleted_students.txt` — soft-deleted student records
- `input.txt` — optional subject/marks input file

## Authors

- Mostafizur Rahman Antu
- Shanita Shafi Mugdha
- Shanita Shafi Mugdha
- Md. Waliullah
- Maruf Hossain
