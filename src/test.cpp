#include <iostream>
#include <variant>
#include <string>

struct Key
{
    std::variant<std::string, size_t> value_;

    Key(const std::string &key) : value_(key) {}
    Key(std::string &&key) noexcept : value_(std::move(key)) {}
    Key(size_t key) : value_(key) {}

    bool isNumber() const { return std::holds_alternative<size_t>(value_); }
    const std::string &asString() const { return std::get<std::string>(value_); }
    int asNumber() const { return std::get<size_t>(value_); }
};

struct KeyHolder
{
    Key key_;

    KeyHolder(Key &key) : key_(key) {}
    KeyHolder(Key &&key) noexcept : key_(std::move(key)) {}
};

main(void)
{
    KeyHolder holder(1123);

    std::cout << holder.key_.asNumber();
    return 0;
}