#include "shared.hpp"

#include <iostream>

DYNALO_EXPORT int32_t DYNALO_CALL add_integers(const int32_t a, const int32_t b)
{
    return a + b;
}

DYNALO_EXPORT void DYNALO_CALL print_message(const char* str)
{
    std::cout << "Hello [" << str << "]" << std::endl;
}
