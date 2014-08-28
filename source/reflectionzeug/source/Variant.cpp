
#include <reflectionzeug/Variant.h>


namespace reflectionzeug
{

Variant::Variant()
:   m_content(nullptr)
{
}

Variant::Variant(const std::string & value)
:   m_content(new VariantHolder<std::string>(value))
{
}

Variant::Variant(float value)
:   m_content(new VariantHolder<float>(value))
{
}
Variant::Variant(double value)
:   m_content(new VariantHolder<double>(value))
{
}

Variant::Variant(char value)
:   m_content(new VariantHolder<char>(value))
{
}

Variant::Variant(unsigned char value)
:   m_content(new VariantHolder<unsigned char>(value))
{
}

Variant::Variant(short value)
:   m_content(new VariantHolder<short>(value))
{
}

Variant::Variant(unsigned short value)
:   m_content(new VariantHolder<unsigned short>(value))
{
}

Variant::Variant(int value)
:   m_content(new VariantHolder<int>(value))
{
}

Variant::Variant(unsigned int value)
:   m_content(new VariantHolder<unsigned int>(value))
{
}

Variant::Variant(long value)
:   m_content(new VariantHolder<long>(value))
{
}

Variant::Variant(unsigned long value)
:   m_content(new VariantHolder<unsigned long>(value))
{
}

Variant::Variant(long long value)
:   m_content(new VariantHolder<long long>(value))
{
}

Variant::Variant(unsigned long long value)
:   m_content(new VariantHolder<unsigned long long>(value))
{
}

Variant::Variant(const VariantArray & array)
:   m_content(new VariantHolder<VariantArray>(array))
{
}

Variant::Variant(const VariantMap & map)
:   m_content(new VariantHolder<VariantMap>(map))
{
}

Variant::Variant(const Variant & variant)
:   m_content(variant.isNull() ? nullptr : variant.m_content->clone())
{
}

Variant & Variant::operator=(const Variant & variant)
{
    if (!isNull())
        delete m_content;
        
    m_content = variant.isNull() ? nullptr : variant.m_content->clone();
    return *this;
}

Variant::~Variant()
{
    if (m_content)
        delete m_content;
}

bool Variant::isNull() const
{
    return !m_content;
}

} // namespace reflectionzeug
