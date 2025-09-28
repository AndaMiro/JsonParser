#pragma once
#include <memory>
#include <variant>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>

namespace andamiro::array
{
    struct Array;
    struct Proxy;
    struct Key;

    using Value = std::variant<std::nullptr_t, std::string, bool, int64_t, double, Array *>;
    using MultiValue = std::variant<std::unordered_map<Key, Value>, std::vector<Value>>;

    struct Array
    {
        friend struct Proxy;

    private:
        std::shared_ptr<MultiValue> data_;
        size_t nextIdx_ = 0;

        bool isMap() const { return std::holds_alternative<std::unordered_map<Key, Value>>(*data_); }
        bool isVector() const { return std::holds_alternative<std::vector<Value>>(*data_); }

        std::unordered_map<Key, Value> &asMap() const { return std::get<std::unordered_map<Key, Value>>(*data_); }
        std::vector<Value> &asVector() const { return std::get<std::vector<Value>>(*data_); }

        void toMap();

        void detach();

    public:
        Array() : data_(std::make_shared<MultiValue>(std::vector<Value>{})) {}
        Array(const Array &other) = default; // 빼애애애액ㄱ 얘는 왜 noexcept 안 붙여줘요???? : 얘는 data_에 메모리 할당 후 other.data_를 복사해서 집어넣는데 아래에 있는 생성자는 std::move 로 이미 할당된 메모리를 옮기는 거라 오류날 일이 없음 오히려 이 생성자가 메모리를 새로 할당해야해서 예외를 던질 확률이 존재.
        Array(Array &&other) noexcept = default;

        Array &operator=(const Array &other) = default;
        Array &operator=(Array &&) noexcept = default;

        Proxy operator[](const Key &key) { return Proxy(this, key); }
    };

    struct Proxy
    {
        friend struct Array;

    private:
        Array *parent_;
        std::vector<Key> keies_;

        Proxy() = delete;
        Proxy(const Proxy &) = delete;
        Proxy(Proxy &&) = delete;
        Proxy(Array *parent, const Key &key) : parent_(parent), keies_{key} {}
        Proxy(Array *parent, Key &&key) : parent_(parent), keies_{std::move(key)} {}

    public:
        Proxy &operator=(const Proxy &other);
        Proxy &operator=(const Value &value);

        Proxy &operator[](const Key &key);

        Value &get() const;

        operator Value &() const { return get(); }
        operator Array &() const { return *std::get<Array *>(get()); }
        operator std::string &() const { return std::get<std::string>(get()); }
        operator bool() const { return std::get<bool>(get()); }
        operator int64_t() const { return std::get<int64_t>(get()); }
        operator double() const { return std::get<double>(get()); }

        bool isset() const;
    };

    struct Key
    {
    private:
        std::variant<std::string, size_t> value_;

    public:
        Key() = delete;
        Key(const std::string &key) : value_(key) {}
        Key(std::string &&key) noexcept : value_(std::move(key)) {}
        Key(size_t key) : value_(key) {}

        bool operator==(const Key &other) const;

        bool isString() const { return std::holds_alternative<std::string>(value_); }
        bool isNumber() const { return std::holds_alternative<size_t>(value_); }

        operator const std::string &() const { return std::get<std::string>(value_); }
        operator size_t() const { return std::get<size_t>(value_); }
    };
}

namespace std
{
    template <>
    struct hash<andamiro::array::Key>
    {
        std::size_t operator()(const andamiro::array::Key &k) const noexcept
        {
            if (k.isNumber())
                return std::hash<size_t>{}(size_t(k));
            else
                return std::hash<std::string>{}(std::string(k));
        }
    };
}