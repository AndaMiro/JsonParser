#include <Array.hpp>

using namespace andamiro::array;

bool Array::isset(const Proxy &proxy) const
{
    return proxy.keies_.size() == 1;
}

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

Proxy &Proxy::operator=(const Value &value)
{

    // if (parent_->isVector())
    // {
    //     auto &vec = std::get<std::vector<Value>>(*parent_->data_);
    //     if (isStringKey())
    //     {
    //         parent_->toMap();
    //         parent_->getMap()[getStringKey()] = value;
    //     }
    //     else
    //     {
    //         size_t idx = getIndexKey();
    //         if (idx < vec.size())
    //             vec[idx] = value;
    //         else if (idx == vec.size())
    //             vec.push_back(value);
    //         else
    //         {
    //             parent_->toMap();
    //             parent_->getMap()[std::to_string(idx)] = value;
    //         }
    //     }
    // }
    // else
    // {
    //     auto &map = parent_->getMap();
    //     if (isStringKey())
    //         map[getStringKey()] = value;
    //     else
    //         map[std::to_string(getIndexKey())] = value;
    // }
    // return *this;
}

Array::Proxy &Array::Proxy::operator=(const Proxy &proxy)
{
    // 근데 여기서 만약 other 가 존재하지 않는 인덱스를 가진 프록시라면?? 그거 예외 처리 해야함 아니면 걍 Value 로 변환해서 받던가
    // 이 배열에 프록시를 배열로 전환해서 집어넣기
}

Array::Value &Array::Proxy::get() const
{
    // if (parent_->isVector())
    // {
    //     auto &vec = parent_->getVector();
    //     if (isStringKey())
    //         throw std::out_of_range("Not exists value ~ in this."); // 이거 문구 수정좀 해야할듯 ~ 인덱스는 존재하지 않습니다~~ 이렇게 PHP 참고해서 ㄱㄱ
    //     size_t idx = getIndexKey();
    //     if (idx < vec.size())
    //         return vec[idx];
    //     throw std::out_of_range("Not exists value ~ in this."); // 이거 문구 수정좀 해야할듯 ~ 인덱스는 존재하지 않습니다~~ 이렇게 PHP 참고해서 ㄱㄱ
    // }
    // auto &map = parent_->getMap();
    // return map.at(isStringKey() ? getStringKey() : std::to_string(getIndexKey()));
}

Proxy &Proxy::operator[](const Key &key)
{
    if (parent_->isMap())
    {
        auto &map = parent_->asMap();
        try
        {
            Value &value = map.at(key);
            if (std::holds_alternative<Array>(value))
            {
                
            }
        }
    }
}

bool Key::operator==(const Key &other) const
{
    // 0 == "0"
    // 11 == "11"
    // 1 !== "001"
}
