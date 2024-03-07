#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <QMutex>
#include <QScopedPointer>

namespace st_utils
{

    template <typename T>
    class Singleton
    {
    public:
        static T* getInstance();

        Singleton(const Singleton& other) = delete;
        Singleton<T>& operator=(const Singleton& other) = delete;

    private:
        static QMutex mutex;
        static T* instance;
    };

    template <typename T> QMutex Singleton<T>::mutex;
    template <typename T> T* Singleton<T>::instance;
    template <typename T>
    T* Singleton<T>::getInstance()
    {
        if (instance == nullptr)
        {
            QMutexLocker lock_(&mutex);
            if (instance == nullptr)
            {
                instance = new T();
            }
        }
        return instance;
    }

#define SINGLETON(Class)                               \
private:                                                \
    friend class  st_utils::Singleton<Class>;              \
    friend struct QScopedPointerDeleter<Class>;         \
public:                                                 \
    static Class* getInstance() {                       \
        return st_utils::Singleton<Class>::getInstance();  \
    }

#define HIDE_CONSTRUCTOR(Class)                         \
private:                                                \
    Class() = default;                                  \
    Class(const Class &other) = delete;                 \
    Class& operator=(const Class &other) = delete;      \

}

#endif // SINGLETON_H
