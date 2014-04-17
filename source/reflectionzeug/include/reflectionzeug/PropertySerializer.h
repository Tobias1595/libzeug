
#pragma once

#include <fstream>


namespace reflectionzeug
{

class AbstractValueProperty;
class PropertyGroup;
    
/** @brief
 * Saves values of a property hierachy to a specified file.
 */
    
class REFLECTIONZEUG_API PropertySerializer
{
public:
    PropertySerializer();
    virtual ~PropertySerializer();

    bool serialize(PropertyGroup & group, std::string filePath);
    
protected:
    void serializeValue(const AbstractValueProperty & property);
    void serializeGroup(const PropertyGroup & group);
    void pushGroupToPath(const PropertyGroup & group);
    void popGroupFromPath();

protected:
    std::fstream m_fstream;
    std::string m_currentPath;
    std::string m_previousPath;
};
    
} // namespace reflectionzeug
