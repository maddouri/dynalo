#pragma once

#include "detail/config.h"

#if defined(DYNALO_HAS_LINUX)
    #include "detail/linux/dynalo.hpp"
#elif defined(DYNALO_HAS_WINDOWS)
    #include "detail/windows/dynalo.hpp"
#endif

namespace dynalo
{

namespace native
{
using handle = detail::native::handle;

inline
handle invalid_handle()
{
    return detail::native::invalid_handle();
}

namespace name
{

inline
std::string prefix()
{
    return detail::native::name::prefix();
}

inline
std::string suffix()
{
    return detail::native::name::suffix();
}

inline
std::string extension()
{
    return detail::native::name::extension();
}

}

}

inline
std::string to_native_name(const std::string& lib_name)
{
    using namespace native::name;
    if (!extension().empty())
    {
        return prefix() + lib_name + suffix() + std::string(".") + extension();
    }
    else
    {
        return prefix() + lib_name + suffix();
    }
}

inline
native::handle open(const std::string& dyn_lib_path)
{
    return detail::open(dyn_lib_path);
}

inline
void close(native::handle lib_handle)
{
    detail::close(lib_handle);
}

template <typename FunctionSignature>
inline
FunctionSignature* get_function(native::handle lib_handle, const std::string& func_name)
{
    return detail::get_function<FunctionSignature>(lib_handle, func_name);
}

class library
{
private:
    native::handle m_handle;

public:
    library()                          = delete;
    library(const library&)            = delete;
    library& operator=(const library&) = delete;

    library(library&& other)
    : m_handle(other.m_handle)
    {
        other.m_handle = native::invalid_handle();
    }

    library& operator=(library&& other)
    {
        m_handle       = other.m_handle;
        other.m_handle = native::invalid_handle();
        return *this;
    }

    ~library()
    {
        if (m_handle != native::invalid_handle())
        {
            dynalo::close(m_handle);
        }
    }

    explicit library(const std::string& dyn_lib_path)
    : m_handle(dynalo::open(dyn_lib_path))
    {}

    template <typename FunctionSignature>
    FunctionSignature* get_function(const std::string& func_name)
    {
        return dynalo::get_function<FunctionSignature>(m_handle, func_name);
    }

    native::handle get_native_handle()
    {
        return m_handle;
    }
};

}
