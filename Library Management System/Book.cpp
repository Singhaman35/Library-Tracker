#include "Book.h"
#include <fstream>
#include <iomanip>

// Initialize static member
int Book::nextBookId = 1;

// Constructors
Book::Book() : title(""), author(""), isbn(""), quantity(0), available(0), bookId(0) {}

Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int quantity)
    : title(title), author(author), isbn(isbn), quantity(quantity), available(quantity), bookId(nextBookId++) {}

// Getters
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getIsbn() const { return isbn; }
int Book::getQuantity() const { return quantity; }
int Book::getAvailable() const { return available; }
int Book::getBookId() const { return bookId; }

// Setters
void Book::setTitle(const std::string& title) { this->title = title; }
void Book::setAuthor(const std::string& author) { this->author = author; }
void Book::setIsbn(const std::string& isbn) { this->isbn = isbn; }
void Book::setQuantity(int quantity) { 
    this->quantity = quantity; 
    if (available > quantity) available = quantity;
}
void Book::setAvailable(int available) { this->available = available; }

// Book operations
bool Book::issueBook() {
    if (available > 0) {
        available--;
        return true;
    }
    return false;
}

bool Book::returnBook() {
    if (available < quantity) {
        available++;
        return true;
    }
    return false;
}

bool Book::isAvailable() const {
    return available > 0;
}

// Display methods
void Book::display() const {
    std::cout << "\n=== Book Details ===" << std::endl;
    std::cout << "ID: " << bookId << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Total Quantity: " << quantity << std::endl;
    std::cout << "Available: " << available << std::endl;
    std::cout << "Status: " << (isAvailable() ? "Available" : "Not Available") << std::endl;
}

void Book::displayShort() const {
    std::cout << std::left << std::setw(5) << bookId 
              << std::setw(25) << title 
              << std::setw(20) << author 
              << std::setw(15) << isbn 
              << std::setw(10) << available << "/" << quantity << std::endl;
}

// File operations
void Book::saveToFile(std::ofstream& file) const {
    file << bookId << "|" << title << "|" << author << "|" << isbn << "|" << quantity << "|" << available << std::endl;
}

void Book::loadFromFile(std::ifstream& file) {
    std::string line;
    if (std::getline(file, line)) {
        size_t pos = 0;
        std::string token;
        
        // Parse bookId
        pos = line.find('|');
        if (pos != std::string::npos) {
            bookId = std::stoi(line.substr(0, pos));
            if (bookId >= nextBookId) nextBookId = bookId + 1;
            line.erase(0, pos + 1);
        }
        
        // Parse title
        pos = line.find('|');
        if (pos != std::string::npos) {
            title = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        
        // Parse author
        pos = line.find('|');
        if (pos != std::string::npos) {
            author = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        
        // Parse isbn
        pos = line.find('|');
        if (pos != std::string::npos) {
            isbn = line.substr(0, pos);
            line.erase(0, pos + 1);
        }
        
        // Parse quantity
        pos = line.find('|');
        if (pos != std::string::npos) {
            quantity = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        
        // Parse available
        available = std::stoi(line);
    }
}
