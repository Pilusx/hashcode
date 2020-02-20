#include <iostream>

#include "io.h"
#include "structs.h"

int64_t real_eval() {
    // IN
    get_input();

    // IN2
    int registration_time = 0;
    int score = 0;
    std::set<BookId> scanned_books;
    IN2 >> A;
    for(int i = 0; (i < A) && (registration_time < D); i++) {
        BookId book_id;
        LibraryId library_id;
        std::vector<int> books;
        int number_of_books;
        IN2 >> library_id >> number_of_books;
        Library& library = g_libraries[library_id];
        registration_time += library.m_signup_time;
        for(int j = 0; j < number_of_books; j++) {
            IN2 >> book_id;
            if((registration_time + (j / library.m_book_scanned_per_day) <= D) && scanned_books.find(book_id) == scanned_books.end()) {
                scanned_books.insert(book_id);
                score += g_books[book_id].m_score;
            }
        }
    }

    return score;
}
