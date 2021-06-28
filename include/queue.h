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
    queueNode() : data{ nullptr }, link{ nullptr } { }
};

class queue
{
    sPtrQueueNode head, tail;
    size_t size;
public:
    queue() : head{ nullptr }, tail{ nullptr }, size{ 0 } { }
    bool push(void*);
    void* pop();
};

#endif 