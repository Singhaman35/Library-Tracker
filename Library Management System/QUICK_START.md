# Quick Start Guide - Library Management System

## Prerequisites
- Windows with MinGW or Visual Studio
- Or Linux/macOS with GCC

## Quick Setup (Windows)

1. **Install MinGW** (if not already installed):
   - Download from: https://sourceforge.net/projects/mingw/
   - Add MinGW bin directory to PATH

2. **Compile the program**:
   ```cmd
   compile.bat
   ```
   Or manually:
   ```cmd
   g++ -std=c++11 -Wall -Wextra -g main.cpp Book.cpp Student.cpp Library.cpp -o library_system.exe
   ```

3. **Run the program**:
   ```cmd
   library_system.exe
   ```

## Quick Setup (Linux/macOS)

1. **Install GCC** (if not already installed):
   ```bash
   # Ubuntu/Debian
   sudo apt-get install g++ make
   
   # macOS
   brew install gcc make
   ```

2. **Compile the program**:
   ```bash
   make
   ```
   Or manually:
   ```bash
   g++ -std=c++11 -Wall -Wextra -g main.cpp Book.cpp Student.cpp Library.cpp -o library_system
   ```

3. **Run the program**:
   ```bash
   ./library_system
   ```

## First Time Setup

1. **Login as Administrator**:
   - Choose option 1
   - Password: `admin123`

2. **Add some books**:
   - Choose option 1 (Add Book)
   - Enter book details (title, author, ISBN, quantity)

3. **Add students or let them register**:
   - Choose option 5 (Add Student) from admin menu
   - Or let students register themselves (option 3 from main menu)

## Student Registration & Login

1. **Register as Student**:
   - Choose option 3 from main menu
   - Enter name and password
   - **Save the Student ID** that appears (e.g., STU1001)

2. **Login as Student**:
   - Choose option 2 from main menu
   - Enter Student ID and password

3. **Forgot Student ID?**:
   - Choose option 4 from main menu
   - Enter name and password to retrieve your Student ID

## Default Credentials

- **Admin Password**: `admin123`
- **Student IDs**: Auto-generated (STU1001, STU1002, etc.)

## Sample Data

Here are some sample books you can add:

| Title | Author | ISBN | Quantity |
|-------|--------|------|----------|
| The Great Gatsby | F. Scott Fitzgerald | 978-0743273565 | 3 |
| To Kill a Mockingbird | Harper Lee | 978-0446310789 | 2 |
| 1984 | George Orwell | 978-0451524935 | 4 |
| Pride and Prejudice | Jane Austen | 978-0141439518 | 3 |
| The Hobbit | J.R.R. Tolkien | 978-0547928241 | 5 |

## Common Operations

### For Administrators:
- Add/Delete/Update books
- Manage students
- View all issued books
- Monitor library inventory

### For Students:
- Search for books
- Issue/Return books
- View borrowing history
- Check fines

## Data Files

The system automatically creates:
- `books.txt` - Stores all book information
- `students.txt` - Stores student data and borrowing records

## Troubleshooting

### Compilation Errors:
- Ensure you have a C++11 compatible compiler
- Check that all files are in the same directory
- Verify GCC/G++ is properly installed

### Runtime Errors:
- Check file permissions for data files
- Ensure sufficient disk space
- Verify input format (no special characters in names)

### Data Loss:
- Data is automatically saved
- Backup `books.txt` and `students.txt` regularly
- Don't manually edit data files while program is running

## Support

If you encounter issues:
1. Check the README.md for detailed documentation
2. Verify your compiler version: `g++ --version`
3. Try the test program: `g++ test_system.cpp Book.cpp Student.cpp Library.cpp -o test && ./test`
