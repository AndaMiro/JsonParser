#pragma once
#include <variant>
#include <memory>
#include <string>

namespace andamiro
{
    using mixed = std::variant<std::nullptr_t, std::string, bool, int, double>; // TODO JsonSerializable 추가해야됨 지금 오류떠서 뺌

    class JsonSerializable
    {
    public:
        virtual mixed jsonSerialize() const = 0;
    };
}