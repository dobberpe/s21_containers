#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list.h" // Подключаем вашу реализацию двустороннего связанного списка

template <typename T>
class Queue {
private:
    List<T> list; // Используем ваш класс list внутри очереди

public:
    // Конструкторы и деструктор
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;
    ~Queue() = default;

    // Операторы присваивания
    Queue& operator=(const Queue& other) = default;
    Queue& operator=(Queue&& other) = default;

    // Методы очереди
    void push(const T& value) {
        list.push_back(value); // Добавляем элемент в конец списка
    }

    void pop() {
        if (!empty()) {
            list.pop_front(); // Удаляем первый элемент списка
        }
    }

    T& front() {
        return list.front(); // Возвращаем ссылку на первый элемент списка
    }

    const T& front() const {
        return list.front(); // Возвращаем константную ссылку на первый элемент списка
    }

    T& back() {
        return list.back(); // Возвращаем ссылку на последний элемент списка
    }

    const T& back() const {
        return list.back(); // Возвращаем константную ссылку на последний элемент списка
    }

    bool empty() const {
        return list.empty(); // Проверяем, пуст ли список
    }

    size_t size() const {
        return list.size(); // Возвращаем размер списка
    }
};

#endif