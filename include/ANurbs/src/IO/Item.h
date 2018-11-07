#pragma once

#include <string>
#include <memory>
#include <map>

namespace ANurbs {
namespace IO {

class Model;

struct Item {
    std::string m_key;
    Model& m_model;

    Item(
        Model& model,
        const std::string& key)
    : m_key(key)
    , m_model(model)
    {
    }

    virtual const std::string&
    Type() const = 0;
};

template <typename T>
struct ItemBase : public Item {
    using Item::Item;

    const std::string&
    Type() const override
    {
        return T::Type();
    }
};

} // namespace IO
} // namespace ANurbs