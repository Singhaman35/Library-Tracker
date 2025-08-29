#include "Library.h"
#include <iostream>
#include <cassert>

void testLibrarySystem() {
    std::cout << "Testing Library Management System..." << std::endl;
    
    // Create a library instance
    Library library("test_books.txt", "test_students.txt", "test123");
    
    // Test 1: Add books
    std::cout << "\nTest 1: Adding books..." << std::endl;
    assert(library.addBook("The Great Gatsby", "F. Scott Fitzgerald", "978-0743273565", 3));
    assert(library.addBook("To Kill a Mockingbird", "Harper Lee", "978-0446310789", 2));
    assert(library.addBook("1984", "George Orwell", "978-0451524935", 4));
    std::cout << "✓ Books added successfully" << std::endl;
    
    // Test 2: Add students
    std::cout << "\nTest 2: Adding students..." << std::endl;
    assert(library.addStudent("John Doe", "password123"));
    assert(library.addStudent("Jane Smith", "password456"));
    std::cout << "✓ Students added successfully" << std::endl;
    
    // Test 3: Search books
    std::cout << "\nTest 3: Searching books..." << std::endl;
    auto results = library.searchBooks("Gatsby");
    assert(!results.empty());
    std::cout << "✓ Book search working" << std::endl;
    
    // Test 4: Issue book
    std::cout << "\nTest 4: Issuing books..." << std::endl;
    // Find a student
    Student* student = library.findStudent("STU1001");
    if (student) {
        assert(library.issueBook(student->getStudentId(), 1));
        std::cout << "✓ Book issued successfully" << std::endl;
    }
    
    // Test 5: Display functions
    std::cout << "\nTest 5: Display functions..." << std::endl;
    library.displayAllBooks();
    library.displayAllStudents();
    std::cout << "✓ Display functions working" << std::endl;
    
    std::cout << "\nAll tests passed! Library system is working correctly." << std::endl;
}

int main() {
    try {
        testLibrarySystem();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
