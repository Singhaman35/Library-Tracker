#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Student.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>

class Library {
private:
    std::vector<Book> books;
    std::map<std::string, Student> students; // studentId -> Student
    std::string booksFile;
    std::string studentsFile;
    std::string adminPassword;

public:
    // Constructor
    Library(const std::string& booksFile = "books.txt", 
            const std::string& studentsFile = "students.txt",
            const std::string& adminPassword = "admin123");
    
    // Book management
    bool addBook(const std::string& title, const std::string& author, 
                 const std::string& isbn, int quantity);
    bool deleteBook(int bookId);
    bool updateBook(int bookId, const std::string& title, const std::string& author, 
                   const std::string& isbn, int quantity);
    Book* findBook(int bookId);
    Book* findBookByIsbn(const std::string& isbn);
    std::vector<Book> searchBooks(const std::string& query);
    void displayAllBooks() const;
    
    // Student management
    bool addStudent(const std::string& name, const std::string& password);
    bool deleteStudent(const std::string& studentId);
    Student* findStudent(const std::string& studentId);
    Student* findStudentByName(const std::string& name);
    Student* authenticateStudent(const std::string& studentId, const std::string& password);
    bool authenticateAdmin(const std::string& password);
    void displayAllStudents() const;
    
    // Book operations
    bool issueBook(const std::string& studentId, int bookId);
    bool returnBook(const std::string& studentId, int bookId);
    void displayIssuedBooks() const;
    
    // File operations
    void loadData();
    void saveData();
    void loadBooks();
    void saveBooks();
    void loadStudents();
    void saveStudents();
    
    // Utility methods
    void displayMenu() const;
    void displayAdminMenu() const;
    void displayStudentMenu() const;
    void clearScreen() const;
    void pause() const;
};

#endif
