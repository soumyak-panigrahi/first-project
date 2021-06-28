#include "stack.h"

bool stack::push(void* data)
{
    if (data) {
        auto temp = std::make_shared<stackNode>();
        if (temp) {
            temp->data = data;
            temp->link = top;
            top = temp;
            size++;
        }
    }
    return false;
}

void* stack::pop() noexcept
{
    if (top) {
        auto data{ top->data };
        top = top->link;
        return data;
    }
    return nullptr;
}