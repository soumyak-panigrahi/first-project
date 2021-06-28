#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <memory>

struct queueNode;
class queue;

using wPtrQueueNode = std::weak_ptr<queueNode>;
using sPtrQueueNode = std::shared_ptr<queueNode>;

struct queueNode
{
    void* data;
    sPtrQueueNode link;
};

class queue
{
    sPtrQueueNode top;
    size_t size;
public:
    queue() : top{ nullptr }, size{ 0 } { }
    bool push(void*);
    void* pop() noexcept;
};

#endif 