#include "Student.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

// Initialize static member
int Student::nextStudentId = 1001;

// Constructors
Student::Student() : name(""), studentId(""), password("") {}

Student::Student(const std::string& name, const std::string& password)
    : name(name), password(password) {
    studentId = generateStudentId();
}

// Getters
std::string Student::getName() const { return name; }
std::string Student::getStudentId() const { return studentId; }
std::string Student::getPassword() const { return password; }
const std::vector<BorrowedBook>& Student::getBorrowedBooks() const { return borrowedBooks; }

// Setters
void Student::setName(const std::string& name) { this->name = name; }
void Student::setPassword(const std::string& password) { this->password = password; }

// Book operations
bool Student::borrowBook(int bookId, const std::string& bookTitle) {
    // Check if student already has this book
    for (const auto& book : borrowedBooks) {
        if (book.bookId == bookId && !book.returned) {
            return false; // Already borrowed
        }
    }
    
    BorrowedBook newBook;
    newBook.bookId = bookId;
    newBook.bookTitle = bookTitle;
    newBook.borrowDate = std::time(nullptr);
    newBook.dueDate = newBook.borrowDate + (14 * 24 * 60 * 60); // 14 days from now
    newBook.returned = false;
    newBook.fine = 0.0;
    
    borrowedBooks.push_back(newBook);
    return true;
}

bool Student::returnBook(int bookId) {
    for (auto& book : borrowedBooks) {
        if (book.bookId == bookId && !book.returned) {
            book.returned = true;
            book.fine = calculateFines();
            return true;
        }
    }
    return false;
}

bool Student::hasBook(int bookId) const {
    for (const auto& book : borrowedBooks) {
        if (book.bookId == bookId && !book.returned) {
            return true;
        }
    }
    return false;
}

// Fine calculation
double Student::calculateFines() const {
    double totalFine = 0.0;
    std::time_t currentTime = std::time(nullptr);
    
    for (const auto& book : borrowedBooks) {
        if (!book.returned && currentTime > book.dueDate) {
            // Calculate days overdue
            double daysOverdue = std::difftime(currentTime, book.dueDate) / (24 * 60 * 60);
            totalFine += daysOverdue * 0.50; // $0.50 per day
        }
    }
    
    return totalFine;
}

void Student::updateFines() {
    for (auto& book : borrowedBooks) {
        if (!book.returned) {
            book.fine = 0.0;
            std::time_t currentTime = std::time(nullptr);
            if (currentTime > book.dueDate) {
                double daysOverdue = std::difftime(currentTime, book.dueDate) / (24 * 60 * 60);
                book.fine = daysOverdue * 0.50;
            }
        }
    }
}

// Display methods
void Student::display() const {
    std::cout << "\n=== Student Details ===" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Student ID: " << studentId << std::endl;
    std::cout << "Total Books Borrowed: " << borrowedBooks.size() << std::endl;
    std::cout << "Current Fine: $" << std::fixed << std::setprecision(2) << calculateFines() << std::endl;
}

void Student::displayBorrowedBooks() const {
    if (borrowedBooks.empty()) {
        std::cout << "\nNo books borrowed." << std::endl;
        return;
    }
    
    std::cout << "\n=== Borrowed Books ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(30) << "Title" 
              << std::setw(15) << "Borrow Date" 
              << std::setw(15) << "Due Date" 
              << std::setw(10) << "Status" 
              << std::setw(10) << "Fine" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
    
    for (const auto& book : borrowedBooks) {
        std::cout << std::left << std::setw(5) << book.bookId 
                  << std::setw(30) << book.bookTitle;
        
        // Format dates
        std::string borrowDate = std::ctime(&book.borrowDate);
        borrowDate = borrowDate.substr(0, borrowDate.length() - 1); // Remove newline
        std::cout << std::setw(15) << borrowDate;
        
        std::string dueDate = std::ctime(&book.dueDate);
        dueDate = dueDate.substr(0, dueDate.length() - 1);
        std::cout << std::setw(15) << dueDate;
        
        std::cout << std::setw(10) << (book.returned ? "Returned" : "Borrowed");
        std::cout << "$" << std::fixed << std::setprecision(2) << book.fine << std::endl;
    }
}

// File operations
void Student::saveToFile(std::ofstream& file) const {
    file << studentId << "|" << name << "|" << password << "|" << borrowedBooks.size() << std::endl;
    
    for (const auto& book : borrowedBooks) {
        file << book.bookId << "|" << book.bookTitle << "|" 
             << book.borrowDate << "|" << book.dueDate << "|" 
             << book.returned << "|" << book.fine << std::endl;
    }
}

void Student::loadFromFile(std::ifstream& file) {
    std::string line;
    if (std::getline(file, line)) {
        size_t pos = 0;
        
        // Parse studentId
        pos = line.find('|');
        if (pos != std::string::npos) {
            studentId = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        
        // Parse name
        pos = line.find('|');
        if (pos != std::string::npos) {
            name = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        
        // Parse password
        pos = line.find('|');
        if (pos != std::string::npos) {
            password = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        
        // Parse number of borrowed books
        int numBooks = std::stoi(line);
        borrowedBooks.clear();
        
        // Load borrowed books
        for (int i = 0; i < numBooks; i++) {
            if (std::getline(file, line)) {
                BorrowedBook book;
                pos = 0;
                
                // Parse bookId
                pos = line.find('|');
                if (pos != std::string::npos) {
                    book.bookId = std::stoi(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                
                // Parse bookTitle
                pos = line.find('|');
                if (pos != std::string::npos) {
                    book.bookTitle = line.substr(0, pos);
                    line.erase(0, pos + 1);
                }
                
                // Parse borrowDate
                pos = line.find('|');
                if (pos != std::string::npos) {
                    book.borrowDate = std::stol(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                
                // Parse dueDate
                pos = line.find('|');
                if (pos != std::string::npos) {
                    book.dueDate = std::stol(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                
                // Parse returned
                pos = line.find('|');
                if (pos != std::string::npos) {
                    book.returned = (line.substr(0, pos) == "1");
                    line.erase(0, pos + 1);
                }
                
                // Parse fine
                book.fine = std::stod(line);
                
                borrowedBooks.push_back(book);
            }
        }
    }
}

// Utility methods
std::string Student::generateStudentId() {
    std::ostringstream oss;
    oss << "STU" << std::setfill('0') << std::setw(4) << nextStudentId++;
    return oss.str();
}
