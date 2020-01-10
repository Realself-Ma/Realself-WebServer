#pragma once
class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}
private:	//不允许拷贝构造和赋值
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};