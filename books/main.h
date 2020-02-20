#include <iostream>

#include "io.h"
#include "structs.h"

void real_main() {
    get_input();

    OUT << g_libraries.size() << std::endl;
    for(LibraryId id = 0; id < g_libraries.size(); id++) {
        OUT << id << " " << g_libraries[id].m_books.size() << std::endl;
        for(auto& book_id : g_libraries[id].m_books) {
            OUT << book_id << " ";
        }
        OUT << std::endl;
    }
}