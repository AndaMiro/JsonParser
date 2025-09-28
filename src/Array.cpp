#include <Array.hpp>

using namespace andamiro::array;

void Array::toMap()
{
    detach();
    if (isVector())
    {
        auto &vec = asVector();
        std::unordered_map<Key, Value> map;
        for (size_t i = 0; i < vec.size(); ++i)
            map[std::to_string(i)] = vec[i];
        *data_ = std::move(map);
    }
}

Proxy &Proxy::operator[](const Key &key)
{
    if (parent_->isMap())
    {
        auto &map = parent_->asMap();
        try
        {
            Value &value = map.at(key);
            if (auto *arr = std::get_if<Array*>(&value))
            {
                parent_ = *arr;
                keies_ = {key};
            } else{
                
            }
        }
    }
}

bool Proxy::isset() const
{
    return
}

bool Key::operator==(const Key &other) const
{
    // 0 == "0"
    // 11 == "11"
    // 1 !== "001"
}
