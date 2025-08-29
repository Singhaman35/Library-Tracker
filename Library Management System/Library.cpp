#include "Library.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <iomanip>

// Constructor
Library::Library(const std::string& booksFile, const std::string& studentsFile, const std::string& adminPassword)
    : booksFile(booksFile), studentsFile(studentsFile), adminPassword(adminPassword) {
    loadData();
}

// Book management
bool Library::addBook(const std::string& title, const std::string& author, const std::string& isbn, int quantity) {
    // Check if book with same ISBN already exists
    if (findBookByIsbn(isbn) != nullptr) {
        std::cout << "Book with ISBN " << isbn << " already exists!" << std::endl;
        return false;
    }
    
    Book newBook(title, author, isbn, quantity);
    books.push_back(newBook);
    std::cout << "Book added successfully! Book ID: " << newBook.getBookId() << std::endl;
    return true;
}

bool Library::deleteBook(int bookId) {
    auto it = std::find_if(books.begin(), books.end(), 
                          [bookId](const Book& book) { return book.getBookId() == bookId; });
    
    if (it != books.end()) {
        books.erase(it);
        std::cout << "Book deleted successfully!" << std::endl;
        return true;
    }
    
    std::cout << "Book not found!" << std::endl;
    return false;
}

bool Library::updateBook(int bookId, const std::string& title, const std::string& author, 
                        const std::string& isbn, int quantity) {
    Book* book = findBook(bookId);
    if (book != nullptr) {
        book->setTitle(title);
        book->setAuthor(author);
        book->setIsbn(isbn);
        book->setQuantity(quantity);
        std::cout << "Book updated successfully!" << std::endl;
        return true;
    }
    
    std::cout << "Book not found!" << std::endl;
    return false;
}

Book* Library::findBook(int bookId) {
    for (auto& book : books) {
        if (book.getBookId() == bookId) {
            return &book;
        }
    }
    return nullptr;
}

Book* Library::findBookByIsbn(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

std::vector<Book> Library::searchBooks(const std::string& query) {
    std::vector<Book> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    
    for (const auto& book : books) {
        std::string title = book.getTitle();
        std::string author = book.getAuthor();
        std::string isbn = book.getIsbn();
        
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);
        std::transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        
        if (title.find(lowerQuery) != std::string::npos ||
            author.find(lowerQuery) != std::string::npos ||
            isbn.find(lowerQuery) != std::string::npos) {
            results.push_back(book);
        }
    }
    
    return results;
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "\nNo books in the library." << std::endl;
        return;
    }
    
    std::cout << "\n=== All Books in Library ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(25) << "Title" 
              << std::setw(20) << "Author" 
              << std::setw(15) << "ISBN" 
              << std::setw(10) << "Available" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (const auto& book : books) {
        book.displayShort();
    }
}

// Student management
bool Library::addStudent(const std::string& name, const std::string& password) {
    Student newStudent(name, password);
    students[newStudent.getStudentId()] = newStudent;
    std::cout << "Student added successfully!" << std::endl;
    std::cout << "Your Student ID: " << newStudent.getStudentId() << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Please save this information for login!" << std::endl;
    return true;
}

bool Library::deleteStudent(const std::string& studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        students.erase(it);
        std::cout << "Student deleted successfully!" << std::endl;
        return true;
    }
    
    std::cout << "Student not found!" << std::endl;
    return false;
}

Student* Library::findStudent(const std::string& studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        return &(it->second);
    }
    return nullptr;
}

Student* Library::findStudentByName(const std::string& name) {
    for (auto& pair : students) {
        if (pair.second.getName() == name) {
            return &(pair.second);
        }
    }
    return nullptr;
}

Student* Library::authenticateStudent(const std::string& studentId, const std::string& password) {
    Student* student = findStudent(studentId);
    if (student != nullptr && student->getPassword() == password) {
        return student;
    }
    return nullptr;
}

bool Library::authenticateAdmin(const std::string& password) {
    return password == adminPassword;
}

void Library::displayAllStudents() const {
    if (students.empty()) {
        std::cout << "\nNo students registered." << std::endl;
        return;
    }
    
    std::cout << "\n=== All Students ===" << std::endl;
    for (const auto& pair : students) {
        pair.second.display();
        std::cout << std::endl;
    }
}

// Book operations
bool Library::issueBook(const std::string& studentId, int bookId) {
    Student* student = findStudent(studentId);
    Book* book = findBook(bookId);
    
    if (student == nullptr) {
        std::cout << "Student not found!" << std::endl;
        return false;
    }
    
    if (book == nullptr) {
        std::cout << "Book not found!" << std::endl;
        return false;
    }
    
    if (!book->isAvailable()) {
        std::cout << "Book is not available!" << std::endl;
        return false;
    }
    
    if (student->hasBook(bookId)) {
        std::cout << "Student already has this book!" << std::endl;
        return false;
    }
    
    if (student->borrowBook(bookId, book->getTitle()) && book->issueBook()) {
        std::cout << "Book issued successfully!" << std::endl;
        return true;
    }
    
    std::cout << "Failed to issue book!" << std::endl;
    return false;
}

bool Library::returnBook(const std::string& studentId, int bookId) {
    Student* student = findStudent(studentId);
    Book* book = findBook(bookId);
    
    if (student == nullptr) {
        std::cout << "Student not found!" << std::endl;
        return false;
    }
    
    if (book == nullptr) {
        std::cout << "Book not found!" << std::endl;
        return false;
    }
    
    if (student->returnBook(bookId) && book->returnBook()) {
        std::cout << "Book returned successfully!" << std::endl;
        return true;
    }
    
    std::cout << "Failed to return book!" << std::endl;
    return false;
}

void Library::displayIssuedBooks() const {
    std::cout << "\n=== Issued Books ===" << std::endl;
    bool hasIssuedBooks = false;
    
    for (const auto& pair : students) {
        const Student& student = pair.second;
        const auto& borrowedBooks = student.getBorrowedBooks();
        
        for (const auto& borrowedBook : borrowedBooks) {
            if (!borrowedBook.returned) {
                if (!hasIssuedBooks) {
                    std::cout << std::left << std::setw(15) << "Student ID" 
                              << std::setw(20) << "Student Name" 
                              << std::setw(5) << "Book ID" 
                              << std::setw(30) << "Book Title" << std::endl;
                    std::cout << std::string(70, '-') << std::endl;
                    hasIssuedBooks = true;
                }
                
                std::cout << std::left << std::setw(15) << student.getStudentId()
                          << std::setw(20) << student.getName()
                          << std::setw(5) << borrowedBook.bookId
                          << std::setw(30) << borrowedBook.bookTitle << std::endl;
            }
        }
    }
    
    if (!hasIssuedBooks) {
        std::cout << "No books are currently issued." << std::endl;
    }
}

// File operations
void Library::loadData() {
    loadBooks();
    loadStudents();
}

void Library::saveData() {
    saveBooks();
    saveStudents();
}

void Library::loadBooks() {
    std::ifstream file(booksFile);
    if (file.is_open()) {
        books.clear();
        Book book;
        while (file.good()) {
            book.loadFromFile(file);
            if (book.getBookId() != 0) {
                books.push_back(book);
            }
        }
        file.close();
    }
}

void Library::saveBooks() {
    std::ofstream file(booksFile);
    if (file.is_open()) {
        for (const auto& book : books) {
            book.saveToFile(file);
        }
        file.close();
    }
}

void Library::loadStudents() {
    std::ifstream file(studentsFile);
    if (file.is_open()) {
        students.clear();
        Student student;
        while (file.good()) {
            student.loadFromFile(file);
            if (!student.getStudentId().empty()) {
                students[student.getStudentId()] = student;
            }
        }
        file.close();
    }
}

void Library::saveStudents() {
    std::ofstream file(studentsFile);
    if (file.is_open()) {
        for (const auto& pair : students) {
            pair.second.saveToFile(file);
        }
        file.close();
    }
}

// Utility methods
void Library::displayMenu() const {
    std::cout << "\n=== Library Management System ===" << std::endl;
    std::cout << "1. Login as Administrator" << std::endl;
    std::cout << "2. Login as Student" << std::endl;
    std::cout << "3. Register as Student" << std::endl;
    std::cout << "4. Forgot Student ID?" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void Library::displayAdminMenu() const {
    std::cout << "\n=== Administrator Menu ===" << std::endl;
    std::cout << "1. Add Book" << std::endl;
    std::cout << "2. Delete Book" << std::endl;
    std::cout << "3. Update Book" << std::endl;
    std::cout << "4. View All Books" << std::endl;
    std::cout << "5. Add Student" << std::endl;
    std::cout << "6. Delete Student" << std::endl;
    std::cout << "7. View All Students" << std::endl;
    std::cout << "8. View Issued Books" << std::endl;
    std::cout << "9. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

void Library::displayStudentMenu() const {
    std::cout << "\n=== Student Menu ===" << std::endl;
    std::cout << "1. Search Books" << std::endl;
    std::cout << "2. Issue Book" << std::endl;
    std::cout << "3. Return Book" << std::endl;
    std::cout << "4. View My Borrowed Books" << std::endl;
    std::cout << "5. View My Details" << std::endl;
    std::cout << "6. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

void Library::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Library::pause() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
