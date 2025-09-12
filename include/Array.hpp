#pragma once
#include <JsonSerializable.hpp>
#include <cstddef>
#include <unordered_map>

namespace andamiro
{
    static inline constexpr auto append = std::monostate{};

    struct Array : public JsonSerializable
    {
    private:
        struct Appender;
        struct Proxy;

    public:
        mixed &operator[](size_t index);
        mixed &operator[](const std::string &key);
        Appender operator[](std::monostate);

        Array &operator=(const Array &other);
        Array &operator=(const mixed &other);

        mixed jsonSerialize() const;

    private:
        size_t nextIdx_ = 0;
        std::unordered_map<std::string, mixed> value_; // index 접근할 땐 string으로 변환해서 접근

        struct Appender
        {
            friend Array;

        public:
            Appender &operator=(const mixed &other)
            {
                parent_[parent_.nextIdx_++] = other;
                return *this;
            }

        private:
            Array &parent_;

            explicit Appender(Array &parent) : parent_(parent) {}
            Appender() = delete;
            Appender(const Appender &) = delete;
            Appender(Appender &&) = delete;

            Appender &operator=(const Appender &) = delete;
            Appender &operator=(Appender &&) = delete;
        };

        struct Proxy
        {
            friend Array;
        };
    };
}