#ifndef __STACK_H__
#define __STACK_H__

#include <memory>

struct stackNode;
class stack;

using wPtrStackNode = std::weak_ptr<stackNode>;
using sPtrStackNode = std::shared_ptr<stackNode>;

struct stackNode
{
    void* data;
    sPtrStackNode link;
};

class stack
{
    sPtrStackNode top;
    size_t size;
public:
    stack() : top{ nullptr }, size{ 0 } { }
    bool push(void*);
    void* pop();
};

#endif 