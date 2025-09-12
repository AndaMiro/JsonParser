#include <Array.hpp>

namespace andamiro
{
    mixed &Array::operator[](size_t index)
    {
        return value_[std::to_string(index)];
    }

    mixed &Array::operator[](const std::string &key)
    {
        return value_[key];
    }

    Array::Appender Array::operator[](std::monostate)
    {
        return Appender{*this};
    }

    Array &Array::operator=(const Array &other)
    {
        if (this != &other)
            value_ = other.value_;
        return *this;
    }

    mixed Array::jsonSerialize() const{
        return 1;
    }
}