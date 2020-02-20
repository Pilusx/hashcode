#include <algorithm>
#include <iostream>
#include <vector>

#include "io.h"
#include "structs.h"

struct BookIt {
    std::vector<Book>::iterator m_it;
};

struct LibraryIt {
    std::vector<Library>::iterator m_it;
};

void A_strategy() {

}

void B_strategy() {

}

void C_strategy() {
    auto cmp = [](LibraryIt& lhs, LibraryIt& rhs) { return lhs.m_it->m_signup_time < rhs.m_it->m_signup_time; };
    std::vector<LibraryIt> libraries;
    for(std::vector<Library>::iterator it = g_libraries.begin(); it != g_libraries.end(); it++) {
        libraries.push_back({it});
    }
    std::sort(libraries.begin(), libraries.end(), cmp);

    OUT << libraries.size() << std::endl;
    for(auto& selected_library : libraries) {
        LibraryId id = selected_library.m_it - g_libraries.begin();
        Library& library = g_libraries[id];
        OUT << id << " " << library.m_books.size() << std::endl;
        for(auto& book_id : library.m_books) {
            OUT << book_id << " ";
        }
        OUT << std::endl;
    }
}

void D_strategy() {

}

void E_strategy() {

}

void F_strategy() {

}

void default_strategy() {
    OUT << g_libraries.size() << std::endl;
    for(LibraryId id = 0; id < g_libraries.size(); id++) {
        OUT << id << " " << g_libraries[id].m_books.size() << std::endl;
        for(auto& book_id : g_libraries[id].m_books) {
            OUT << book_id << " ";
        }
        OUT << std::endl;
    }
}

void real_main() {
    get_input();

    case_A = (D == 7);
    case_B = (D == 1000);
    case_C = (D == 100000);
    case_D = (D == 30001);
    case_E = (D == 200);
    case_F = (D == 700);

    if(case_C) {
        C_strategy();
    } else {
        default_strategy();
    }
}