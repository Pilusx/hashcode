#pragma once
#include <set>
#include <vector>

int B, L, D;
int A, Y, K;

typedef int BookId;
typedef int LibraryId;

struct Book {
    int m_score;
};

std::vector<Book> g_books;

struct Library {
    std::set<BookId> m_books;
    int m_signup_time;
    int m_book_scanned_per_day;
};

std::vector<Library> g_libraries;

void get_input() {
    IN >> B >> L >> D;
    g_books.resize(B);
    for(auto& book : g_books) {
        IN >> book.m_score;
    }

    g_libraries.resize(L);
    for(auto& library : g_libraries) {
        int number_of_books;
        BookId book_number;
        IN >> number_of_books >> library.m_signup_time >> library.m_book_scanned_per_day;
        for(int i = 0; i < number_of_books; i++) {
            IN >> book_number;
            library.m_books.insert(book_number);
        }
    }
}