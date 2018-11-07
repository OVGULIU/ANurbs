#pragma once

#include "Item.h"

#include <string>
#include <memory>
#include <map>

namespace ANurbs {
namespace IO {

class Model {
private:
    std::map<std::string, std::unique_ptr<Item>> m_items;

public:
    template <typename TItem, class... TArgs>
    void
    Add(
        const std::string& key,
        TArgs&&... args)
    {
        auto it = m_items.find(key);

        if (it != m_items.end()) {
            throw std::runtime_error("Element already exists!");
        }

        m_items[key] = std::make_unique<TItem>(*this, key, std::forward<TArgs>(args)...);
    }

    template <typename T>
    T&
    Get(
        const std::string& key)
    {
        auto it = m_items.find(key);

        if (it == m_items.end()) {
            throw std::runtime_error("Element does not exist!");
        } else {
            return *(dynamic_cast<T*>(it->second.get()));
        }
    }
};

} // namespace IO
} // namespace ANurbs