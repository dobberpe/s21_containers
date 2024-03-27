#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../list/s21_list.h"

namespace s21 {

template <typename Key>
class Queue {
private:
    List<Key> list;

public:
    using value_type = Key;
    using reference = Key&;
    using const_reference = const Key&;
    using size_type = size_t;

    Queue() = default;
    Queue(Queue& other) = default;
    Queue(Queue&& other) = default;
    Queue(std::initializer_list<Key> const &items);
    ~Queue() = default;

    Queue& operator=(Queue& other) = default;
    Queue& operator=(Queue&& other) = default;

    void push(const_reference value);
    void pop();
    const_reference front() const;
    const_reference back() const;
    bool empty() const;
    size_type size() const;
    void swap(Queue& other);
};

template class Queue<int>;
}



#endif