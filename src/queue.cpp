#include "queue.h"

bool queue::push(void* data)
{
    if (data) {
        auto temp = std::make_shared<queueNode>();
        if (temp) {
            temp->data = data;
            tail->link = temp;
            tail = temp;
            if (!head)
                head = temp;
            return true;
        }
    }
    return false;
}

void* queue::pop() noexcept
{
    if (head) {
        auto temp{ head };
        if (!head->link)
            tail = head->link;
        head = temp->link;
        return temp->data;
    }
    return nullptr;
}