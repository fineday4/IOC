#ifndef __ANY_H__
#define __ANY_H__

#include <memory>
#include <typeindex>

class Any {

private:
    struct Base;
    typedef std::unique_ptr<Base> BasePtr;

    struct Base {
        virtual ~Base() {}
        virtual BasePtr Clone() = 0;
    };

    template<typename T>
    struct Deriver: Base {
        T m_value;

        template<typename U>
        Deriver(U&& value): m_value(std::forward(value)) {};

        BasePtr Clone() const {
            return BasePtr(new Deriver(m_value));
        }
    };

public:

Any(void): m_ptr(nullptr), m_tpIndex(std::type_index(typeid(void))) {}

template<typename U>
Any(U&& value): m_ptr(new Deriver<std::decay<U>::type>(std::forward<std::decay<U>>(value))), m_tpIndex(std::type_index<typeid(std::decay<U>::type)>) {}

Any(Any&& that): m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}

Any(Any& that): m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}

BasePtr Clone() const {
    if(nullptr == m_ptr) {
        return nullptr;
    }
    return m_ptr->Clone();
}

template<typename U>
bool Is()
{
    return m_tpIndex == std::type_index(typeid(std::decay<U>::type));
}

bool IsNull()
{
    return nullptr == m_ptr;
}

template<typename U>
U&& AnyCast()
{
    if(!Is<U>() || IsNull()) {
        throw std::bad_typeid("ERROR type!!!");
    }
    auto& ptr = dynamic_cast<Deriver<std::decay<U>::type>*>(m_ptr.get());
    return ptr->m_value;
}

Any& operator=(const Any& that) {
    if(m_ptr == that.m_ptr) {
        return *this;
    }
    m_ptr = that.Clone();
    m_tpIndex = that.m_tpIndex;
    return *this;
}

private:
    BasePtr m_ptr;
    std::type_index m_tpIndex;
};


#endif