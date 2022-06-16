#ifndef DESIGN__H__
#define DESIGN__H__

#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

template <class T>
class Singleton
{
public:
    static T *createInstance()
    {
        if (nullptr == instance_)
        {
            instance_ = new T();
        }
        return instance_;
    };

private:
    Singleton() {}
    ~Singleton() {}
    static T *instance_;
};

template <class T>
T *Singleton<T>::instance_ = nullptr;

template <class AbstractClass,
          typename TypeName,
          typename... Args>
class AbstractFactory
{
public:
    typedef typename std::function<std::shared_ptr<AbstractClass>(Args...)> ObjectCreator;
    template <class T>
    friend class Sington;
    AbstractFactory() {}
    ~AbstractFactory() {}
    bool registClass(const TypeName &name, ObjectCreator creator)
    {
        if (obj_.find(name) != obj_.end())
        {
            return false;
        }
        obj_[name] = creator;
        return true;
    }

    bool unregistClass(const TypeName &name)
    {
        if (obj_.find(name) != obj_.end())
        {
            obj_.erase(name);
            return true;
        }
        return false;
    }

    std::shared_ptr<AbstractClass> createObject(const TypeName &name, Args... args)
    {
        if (obj_.find(name) != obj_.end())
        {
            return obj_[name](args...);
        }
        return nullptr;
    }

private:
    std::map<TypeName, ObjectCreator> obj_;
};

template <class AbstractClass,
          typename TypeName,
          typename... Args>
class CAbstractFactory
{
public:
    typedef typename std::function<AbstractClass *(Args...)> ObjectCreator;
    template <class T>
    friend class Sington;
    CAbstractFactory() {}
    ~CAbstractFactory() {}
    bool registClass(const TypeName &name, ObjectCreator creator)
    {
        if (obj_.find(name) != obj_.end())
        {
            return false;
        }
        obj_[name] = creator;
        return true;
    }

    bool unregistClass(const TypeName &name)
    {
        if (obj_.find(name) != obj_.end())
        {
            obj_.erase(name);
            return true;
        }
        return false;
    }

    AbstractClass *createObject(const TypeName &name, Args... args)
    {
        if (obj_.find(name) != obj_.end())
        {
            return obj_[name](args...);
        }
        return nullptr;
    }

private:
    std::map<TypeName, ObjectCreator> obj_;
};

template <class TypeName,
          typename... Args>
class Reactor
{
public:
    typedef typename std::function<void(Args...)> HandleObj;

    void registHandle(const TypeName &name, HandleObj obj)
    {
        objHandle_[name].emplace_back(obj);
    }

    void dispatchMsg(const TypeName &name, Args... args)
    {
        if (objHandle_.find(name) != objHandle_.end())
        {
            std::for_each(
                objHandle_[name].begin(), objHandle_[name].end(),
                [&](const HandleObj &obj)
                {
                    obj(args...);
                });
        }
    }

private:
    std::map<TypeName, std::vector<HandleObj>> objHandle_;
};

/*
template <class TypeName>
class LIBRARY_EXPORT_TEMPLATE TestVar
{
public:
    template <class... Args>
    void Print(const TypeName &name, Args... args)
    {
        std::cout << sizeof...(args) << std::endl;
    }
};
*/

#endif //# DESIGN__H__