#include "Library.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

void handleAdminMenu(Library& library);
void handleStudentMenu(Library& library, Student* currentStudent);
void handleStudentRegistration(Library& library);
void handleForgotStudentId(Library& library);

int main() {
    Library library;
    int choice;
    
    std::cout << "Welcome to Library Management System!" << std::endl;
    
    while (true) {
        library.displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Login as Administrator
                std::string password;
                std::cout << "Enter admin password: ";
                std::cin >> password;
                
                if (library.authenticateAdmin(password)) {
                    std::cout << "Login successful!" << std::endl;
                    handleAdminMenu(library);
                } else {
                    std::cout << "Invalid password!" << std::endl;
                    library.pause();
                }
                break;
            }
            
            case 2: { // Login as Student
                std::string studentId, password;
                std::cout << "Enter Student ID: ";
                std::cin >> studentId;
                std::cout << "Enter password: ";
                std::cin >> password;
                
                Student* student = library.authenticateStudent(studentId, password);
                if (student != nullptr) {
                    std::cout << "Login successful! Welcome, " << student->getName() << std::endl;
                    handleStudentMenu(library, student);
                } else {
                    std::cout << "Invalid credentials!" << std::endl;
                    library.pause();
                }
                break;
            }
            
            case 3: // Register as Student
                handleStudentRegistration(library);
                break;
                
            case 4: // Forgot Student ID
                handleForgotStudentId(library);
                break;
                
            case 5: // Exit
                std::cout << "Thank you for using Library Management System!" << std::endl;
                library.saveData();
                return 0;
                
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                library.pause();
        }
        
        library.clearScreen();
    }
    
    return 0;
}

void handleAdminMenu(Library& library) {
    int choice;
    
    while (true) {
        library.displayAdminMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Add Book
                std::string title, author, isbn;
                int quantity;
                
                std::cin.ignore();
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author name: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                
                library.addBook(title, author, isbn, quantity);
                library.pause();
                break;
            }
            
            case 2: { // Delete Book
                int bookId;
                std::cout << "Enter book ID to delete: ";
                std::cin >> bookId;
                library.deleteBook(bookId);
                library.pause();
                break;
            }
            
            case 3: { // Update Book
                int bookId;
                std::string title, author, isbn;
                int quantity;
                
                std::cout << "Enter book ID to update: ";
                std::cin >> bookId;
                
                std::cin.ignore();
                std::cout << "Enter new title: ";
                std::getline(std::cin, title);
                std::cout << "Enter new author: ";
                std::getline(std::cin, author);
                std::cout << "Enter new ISBN: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter new quantity: ";
                std::cin >> quantity;
                
                library.updateBook(bookId, title, author, isbn, quantity);
                library.pause();
                break;
            }
            
            case 4: // View All Books
                library.displayAllBooks();
                library.pause();
                break;
                
            case 5: { // Add Student
                std::string name, password;
                
                std::cin.ignore();
                std::cout << "Enter student name: ";
                std::getline(std::cin, name);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);
                
                library.addStudent(name, password);
                library.pause();
                break;
            }
            
            case 6: { // Delete Student
                std::string studentId;
                std::cout << "Enter student ID to delete: ";
                std::cin >> studentId;
                library.deleteStudent(studentId);
                library.pause();
                break;
            }
            
            case 7: // View All Students
                library.displayAllStudents();
                library.pause();
                break;
                
            case 8: // View Issued Books
                library.displayIssuedBooks();
                library.pause();
                break;
                
            case 9: // Logout
                std::cout << "Logged out successfully!" << std::endl;
                library.pause();
                return;
                
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                library.pause();
        }
    }
}

void handleStudentMenu(Library& library, Student* currentStudent) {
    int choice;
    
    while (true) {
        library.displayStudentMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: { // Search Books
                std::string query;
                std::cin.ignore();
                std::cout << "Enter search query (title, author, or ISBN): ";
                std::getline(std::cin, query);
                
                std::vector<Book> results = library.searchBooks(query);
                if (results.empty()) {
                    std::cout << "No books found matching your query." << std::endl;
                } else {
                    std::cout << "\n=== Search Results ===" << std::endl;
                    std::cout << std::left << std::setw(5) << "ID" 
                              << std::setw(25) << "Title" 
                              << std::setw(20) << "Author" 
                              << std::setw(15) << "ISBN" 
                              << std::setw(10) << "Available" << std::endl;
                    std::cout << std::string(75, '-') << std::endl;
                    
                    for (const auto& book : results) {
                        book.displayShort();
                    }
                }
                library.pause();
                break;
            }
            
            case 2: { // Issue Book
                int bookId;
                std::cout << "Enter book ID to issue: ";
                std::cin >> bookId;
                library.issueBook(currentStudent->getStudentId(), bookId);
                library.pause();
                break;
            }
            
            case 3: { // Return Book
                int bookId;
                std::cout << "Enter book ID to return: ";
                std::cin >> bookId;
                library.returnBook(currentStudent->getStudentId(), bookId);
                library.pause();
                break;
            }
            
            case 4: // View My Borrowed Books
                currentStudent->displayBorrowedBooks();
                library.pause();
                break;
                
            case 5: // View My Details
                currentStudent->display();
                library.pause();
                break;
                
            case 6: // Logout
                std::cout << "Logged out successfully!" << std::endl;
                library.pause();
                return;
                
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                library.pause();
        }
    }
}

void handleStudentRegistration(Library& library) {
    std::string name, password;
    
    std::cin.ignore();
    std::cout << "\n=== Student Registration ===" << std::endl;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    
    if (library.addStudent(name, password)) {
        std::cout << "\n=== Registration Successful! ===" << std::endl;
        std::cout << "Your Student ID has been generated above." << std::endl;
        std::cout << "Please note down your Student ID for future login." << std::endl;
        std::cout << "You can now login using option 2 from the main menu." << std::endl;
    } else {
        std::cout << "Registration failed!" << std::endl;
    }
    
    library.pause();
}

void handleForgotStudentId(Library& library) {
    std::string name, password;
    
    std::cin.ignore();
    std::cout << "\n=== Forgot Student ID? ===" << std::endl;
    std::cout << "Enter your registered name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    
    Student* student = library.findStudentByName(name);
    if (student != nullptr && student->getPassword() == password) {
        std::cout << "\n✅ Found your account!" << std::endl;
        std::cout << "📋 Your Student ID: " << student->getStudentId() << std::endl;
        std::cout << "👤 Name: " << student->getName() << std::endl;
        std::cout << "You can now login using option 2 from the main menu." << std::endl;
    } else {
        std::cout << "\n❌ No account found with the provided name and password." << std::endl;
        std::cout << "Please check your name and password, or register as a new student." << std::endl;
    }
    
    library.pause();
}
