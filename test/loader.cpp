#include <dynalo/dynalo.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>

// usage: loader "path/to/shared/lib/dir"
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "No path for a dynamic library was provided.\nUsage: ./loader path_to_dyn_lib" << std::endl;
    }
    try
    {
        dynalo::library lib(argv[1]);

        auto add_integers  = lib.get_function<int32_t(const int32_t, const int32_t)>("add_integers");
        auto print_message = lib.get_function<void(const char*)>("print_message");

        std::ostringstream oss;
        oss << "it works: " << add_integers(1, 2);
        print_message(oss.str().c_str());

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Test failed: " << error.what() << std::endl;
    }

    return -1;
}
