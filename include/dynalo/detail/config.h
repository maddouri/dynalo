#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux) || defined(_LINUX)
    #define DYNALO_HAS_LINUX
#elif defined(_WIN32) || defined(_WIN64)
    #define DYNALO_HAS_WINDOWS
#else
    #error "dynalo/detail/config.hpp OS Not Supported"
#endif
