#include "timer.h"
#include "epoll.h"
#include <unordered_map>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <deque>
#include <queue>

#include <iostream>
using namespace std;


TimerNode::TimerNode(SP_ReqData _request_data, int timeout): 
    deleted(false), 
    request_data(_request_data)
{
    //cout << "TimerNode()" << endl;
    struct timeval now;
    gettimeofday(&now, NULL);
    // 以毫秒计
    expired_time = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimerNode::~TimerNode()
{
    //cout << "~TimerNode()" << endl;
    if (request_data)
    {
        Epoll::epoll_del(request_data->getFd());
    }
    //request_data.reset();
    // if (request_data)
    // {
    //     cout << "request_data=" << request_data << endl;
    //     delete request_data;
    //     request_data = NULL;
    // }
}
void TimerNode::update(int timeout)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    expired_time = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool TimerNode::isvalid()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t temp = ((now.tv_sec * 1000) + (now.tv_usec / 1000));
    if (temp < expired_time)
    {
        return true;
    }
    else
    {
        this->setDeleted();
        return false;
    }
}

void TimerNode::clearReq()
{
    request_data.reset();
    this->setDeleted();
}

void TimerNode::setDeleted()
{
    deleted = true;
}

bool TimerNode::isDeleted() const
{
    return deleted;
}

size_t TimerNode::getExpTime() const
{
    return expired_time;
}

TimerManager::TimerManager()
{
}

TimerManager::~TimerManager()
{
}

void TimerManager::addTimer(SP_ReqData request_data, int timeout)
{
    SP_TimerNode new_node(new TimerNode(request_data, timeout));
    {
        MutexLockGuard locker(lock);
        TimerNodeQueue.push(new_node);
    }
    request_data->linkTimer(new_node);
}

void TimerManager::addTimer(SP_TimerNode timer_node)
{

}

void TimerManager::handle_expired_event()
{
    MutexLockGuard locker(lock);
    while (!TimerNodeQueue.empty())
    {
        SP_TimerNode ptimer_now = TimerNodeQueue.top();
        if (ptimer_now->isDeleted())
        {
            TimerNodeQueue.pop();
            //delete ptimer_now;
        }
        else if (ptimer_now->isvalid() == false)
        {
            TimerNodeQueue.pop();
            //delete ptimer_now;
        }
        else
        {
            break;
        }
    }
}
