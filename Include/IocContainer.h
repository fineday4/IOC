#ifndef __IOCCONTAINER_H__
#define __IOCCONTAINER_H__

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

using namespace std;

#include "Any.h"
#include <boost/utility.hpp>


class IocContainer :private boost::noncopyable{
public:
    template<typename T, typename Depend, typename... Args>
    typename std::enable_if<!is_base_of<T, Depend>::value>::type
    Register(const string strKey) {
        function<T* (Args...)> func = [](Args... args) {
            return new T(new Depend(args...));
        };
        Register(strKey, func);
    }

    template<typename T, typename Depend, typename... Args>
    typename std::enable_if<std::is_base_of<T, Depend>::value>::type
    Register(const string strKey) {
        function<Depend* (Args...)> func = [](Args... args) {
            return new Depend(args...);
        };
        Register(strKey, func);
    }

    template<typename T, typename... Args>
    void RegisterNormal(const string& strKey) {
        function<T* (Args...)> func = [](Args... args) {
            return new T(args...);
        };
        Register(strKey, func);
    }

    template<typename T, typename... Args>
    shared_ptr<T> ResolveShared(const string strKey, Args... args) {
        T* ptr = Resolve<T, Args...>(strKey, args...);
        return shared_ptr<T>(ptr);
    }

private:
    void Register(const string strKey, Any constructor) {
        if(m_creatorMap.find(strKey) != m_creatorMap.end()) {
            throw std::invalid_argument("strKey is already register!!!");
            return ;
        }
        m_creatorMap.emplace(strKey, constructor);
    }

    template<typename T, typename... Args>
    T* Resolve(const string strKey, Args... args) {
        if(m_creatorMap.find(strKey) == m_creatorMap.end()) {
            throw std::invalid_argument("strKey is NOT register!!!");
            return nullptr;
        }
        Any functionHandler = m_creatorMap[strKey];
        function<T* (Args...)> func = functionHandler.AnyCast<function<T* (Args...)>>();
        return func(args...);
    }
private:
    unordered_map<string, Any> m_creatorMap; 
};

#endif