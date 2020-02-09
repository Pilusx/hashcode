#include <iostream>
#include <string>

namespace io {
std::istream* ifstr;
std::istream* ifstr2;
std::ostream* ofstr;

#define IN (*io::ifstr)
#define IN2 (*io::ifstr2)
#define OUT (*io::ofstr)

} // namespace io
