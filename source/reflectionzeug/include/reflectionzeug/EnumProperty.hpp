
#pragma once

#include <cassert>

#include <reflectionzeug/PropertyVisitor.h>

namespace reflectionzeug
{

template <typename Enum>
template <typename... Arguments>
EnumProperty<Enum>::EnumProperty(Arguments&&... args)
:   ValueProperty<Enum>(std::forward<Arguments>(args)...)
{
    this->setStrings(EnumDefaultStrings<Enum>()());
}

template <typename Enum>
EnumProperty<Enum>::~EnumProperty()
{
}
    
template <typename Type>
void EnumProperty<Type>::accept(AbstractPropertyVisitor * visitor, bool warn)
{
    auto * typedVisitor = dynamic_cast<PropertyVisitor<Type> *>(visitor);
    
    if (typedVisitor == nullptr)
    {
        EnumPropertyInterface::accept(visitor, warn);
        return;
    }
    
    typedVisitor->visit(reinterpret_cast<Property<Type> *>(this));
}

template <typename Enum>
std::string EnumProperty<Enum>::toString() const
{
    assert(m_stringMap.count(this->value()) > 0);

    return m_stringMap.at(this->value());
}

template <typename Enum>
bool EnumProperty<Enum>::fromString(const std::string & string)
{
    auto it = m_enumMap.find(string);

    if (it == m_enumMap.end())
        return false;

    this->setValue((*it).second);
    return true;
}
    
template <typename Enum>
std::vector<std::string> EnumProperty<Enum>::strings() const
{
    std::vector<std::string> strings;
    for (const std::pair<Enum, std::string> & pair : m_stringMap)
    {
        strings.push_back(pair.second);
    }
    
    return strings;
}
    
template <typename Enum>
void EnumProperty<Enum>::setStrings(const std::map<Enum, std::string> & pairs)
{
    m_stringMap = pairs;

    m_enumMap.clear();
    
    for (const std::pair<Enum, std::string> & pair : pairs)
    {        
        assert(m_enumMap.count(pair.second) == 0);
        m_enumMap.emplace(pair.second, pair.first);
    }
}

} // namespace reflectionzeug