#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

struct BorrowedBook {
    int bookId;
    std::string bookTitle;
    std::time_t borrowDate;
    std::time_t dueDate;
    bool returned;
    double fine;
};

class Student {
private:
    std::string name;
    std::string studentId;
    std::string password;
    std::vector<BorrowedBook> borrowedBooks;
    static int nextStudentId;

public:
    // Constructors
    Student();
    Student(const std::string& name, const std::string& password);
    
    // Getters
    std::string getName() const;
    std::string getStudentId() const;
    std::string getPassword() const;
    const std::vector<BorrowedBook>& getBorrowedBooks() const;
    
    // Setters
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    
    // Book operations
    bool borrowBook(int bookId, const std::string& bookTitle);
    bool returnBook(int bookId);
    bool hasBook(int bookId) const;
    
    // Fine calculation
    double calculateFines() const;
    void updateFines();
    
    // Display methods
    void display() const;
    void displayBorrowedBooks() const;
    
    // File operations
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
    
    // Utility methods
    static std::string generateStudentId();
};

#endif
