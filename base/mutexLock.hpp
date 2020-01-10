#pragma once
#include "nocopyable.hpp"
#include <pthread.h>
#include <cstdio>

//继承noncopyable类，则默认的拷贝构造和赋值重载函数是删除的，不重写这些函数，就不能进行拷贝构造和赋值
class MutexLock: noncopyable//用RAII手法，封装互斥器的创建于销毁
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex, NULL);
    }
    ~MutexLock()
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }

	pthread_mutex_t *getlock()
	{
		return &mutex;
	}
private:
    pthread_mutex_t mutex;
};


class MutexLockGuard: noncopyable//用RAII手法，封装临界区的进入和退出，即加锁和解锁
{
public:
    explicit MutexLockGuard(MutexLock &_mutex):
    mutex(_mutex)
    {
        mutex.lock();
    }
    ~MutexLockGuard()
    {
        mutex.unlock();
    }
private:
    MutexLock &mutex;
};
