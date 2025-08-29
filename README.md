# Library Management System

A comprehensive C++ library management system that simulates a real library with two user roles: Administrator and Student. The system provides complete book and student management capabilities with persistent data storage.

## Features

### Administrator Features
- **Book Management**
  - Add new books (title, author, ISBN, quantity)
  - Delete books
  - Update book details
  - View all books in the library
- **Student Management**
  - Add new students
  - Delete students
  - View all registered students
- **Tracking**
  - View all issued books (who borrowed which book)
  - Monitor library inventory

### Student Features
- **Book Operations**
  - Search for books (by title, author, or ISBN)
  - Issue books (only if available)
  - Return books
  - View borrowing history
- **Account Management**
  - View personal details
  - Track fines for overdue books
  - View due dates

### System Features
- **Data Persistence**
  - Automatic saving to text files
  - Data recovery on program restart
- **Security**
  - Password-protected admin login
  - Student authentication
- **Fine Calculation**
  - Automatic fine calculation for overdue books
  - $0.50 per day for overdue books
- **Unique IDs**
  - Auto-generated book IDs
  - Auto-generated student IDs (STU0001, STU0002, etc.)

## File Structure

```
Library Management System/
├── Book.h              # Book class header
├── Book.cpp            # Book class implementation
├── Student.h           # Student class header
├── Student.cpp         # Student class implementation
├── Library.h           # Library management class header
├── Library.cpp         # Library management class implementation
├── main.cpp            # Main program with menu system
├── Makefile            # Build configuration
├── README.md           # This file
├── books.txt           # Book data storage (auto-generated)
└── students.txt        # Student data storage (auto-generated)
```

## Compilation and Installation

### Prerequisites
- C++ compiler (GCC/G++ 4.8 or higher)
- Make utility

### Installation

#### Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install g++ make
```

#### CentOS/RHEL/Fedora:
```bash
sudo yum install gcc-c++ make
```

#### macOS:
```bash
brew install gcc make
```

### Compilation
```bash
# Build the project
make

# Or build and run directly
make run

# Clean build files
make clean
```

### Manual Compilation
```bash
g++ -std=c++11 -Wall -Wextra -g main.cpp Book.cpp Student.cpp Library.cpp -o library_system
```

## Usage

### Running the Program
```bash
./library_system
```

### Default Credentials
- **Admin Password**: `admin123`

### Getting Started

1. **First Time Setup**:
   - Run the program
   - Login as administrator using password: `admin123`
   - Add some books to the library
   - Add students or let them register themselves

2. **Student Registration**:
   - Choose option 3 from main menu
   - Enter name and password
   - **Important**: Note down the generated Student ID that appears on screen
   - The Student ID will be in format: STU1001, STU1002, etc.

3. **Student Login**:
   - Choose option 2 from main menu
   - Enter Student ID and password

4. **Forgot Student ID?**:
   - Choose option 4 from main menu
   - Enter your registered name and password
   - Your Student ID will be displayed

## Data Storage

The system uses two text files for data persistence:

- **books.txt**: Stores all book information
- **students.txt**: Stores all student information and borrowing records

Data is automatically saved when:
- Books are added, updated, or deleted
- Students are added or deleted
- Books are issued or returned
- Program exits normally

## Technical Details

### Classes and Structure

#### Book Class
- Manages individual book information
- Handles book availability
- Provides file I/O operations

#### Student Class
- Manages student information and borrowing history
- Calculates fines for overdue books
- Tracks borrowed books with dates

#### Library Class
- Central management class
- Handles all operations between books and students
- Manages authentication and authorization
- Provides search and display functionality

### Data Format

#### Book Data Format
```
bookId|title|author|isbn|quantity|available
```

#### Student Data Format
```
studentId|name|password|numBorrowedBooks
bookId|bookTitle|borrowDate|dueDate|returned|fine
```

## Error Handling

The system includes comprehensive error handling for:
- Invalid user input
- File I/O errors
- Authentication failures
- Book availability checks
- Student validation

## Future Enhancements

Potential improvements for the system:
- Database integration (SQLite/MySQL)
- GUI interface using Qt or wxWidgets
- Email notifications for due dates
- Advanced search with filters
- Book categories and genres
- Reservation system
- Multiple admin accounts
- Activity logging

## Contributing

Feel free to contribute to this project by:
- Reporting bugs
- Suggesting new features
- Submitting pull requests
- Improving documentation

## License

This project is open source and available under the MIT License.

## Support

For support or questions, please create an issue in the project repository.
