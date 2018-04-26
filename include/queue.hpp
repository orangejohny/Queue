// queue.hpp

#include <initializer_list>
#include <iostream>
#include <ForwardList.hpp>

template <typename T>
class Queue {
public:
    typedef T type;
    Queue() : list{new ForwardList<T>()} {};
    Queue(std::initializer_list<type> list);
    Queue(const Queue& q);

    auto swap(Queue& q) -> void;
    auto empty() const -> bool;
    auto size() const -> std::size_t;
    auto push(type) -> void;
    auto pop() -> void;
    auto front() const -> type&;
    auto back() const -> type&;

    auto operator=(const Queue& q);
    bool operator==(const Queue& q) const;
    template <typename type> friend
    auto operator<<(std::ostream&, Queue<type>&) -> std::ostream&;
    template <typename type> friend
    auto operator>>(std::istream&, Queue<type>&) -> std::istream&;

    ~Queue();
private:
    ForwardList<type>* list;
};


template <typename T>
Queue<T>::Queue(std::initializer_list<T> in) {
    list = new ForwardList<T>;

    for (T elem : in) {
        push(elem);
    }
}

template <typename T>
Queue<T>::Queue(const Queue& q) {
    list = new ForwardList<T>;

    Node<T>* curr = q.list->get();
    if (!curr) {
        return;
    }

    while(curr != nullptr) {
        push(curr->data);
        curr = curr->next;
    }
}

template <typename T>
auto Queue<T>::push(T val) -> void {
    list->insert(val);
}

template <typename T>
auto Queue<T>::size() const -> std::size_t {
    Node<T>* curr = list->get();
    std::size_t size = 0;
    while (curr != nullptr) {
        size++;
        curr = curr->next;
    }

    return size;
}

template <typename T>
auto Queue<T>::empty() const -> bool {
    if (size() == 0) return true;
    else return false;
}

template <typename T>
auto Queue<T>::pop() -> void {
    list->remove(front());
}

template <typename T>
auto Queue<T>::front() const -> T& {
    if (empty()) {
        throw std::length_error("Empty queue");
    }

    return list->get()->data;
}

template <typename T>
auto Queue<T>::back() const -> T& {
    if (empty()) {
        throw std::length_error("Empty queue");    
    }

    Node<T>* curr = list->get();
    
    while (curr->next != nullptr) {
        curr = curr->next;
    }

    return curr->data;
}

template <typename T>
Queue<T>::~Queue() {
    list->~ForwardList();
}

template <typename T>
auto Queue<T>::swap(Queue& q) -> void {
    std::swap(list, q.list);
}

template <typename T>
auto Queue<T>::operator=(const Queue& q) {
    Queue<T> tmp{q};
    swap(tmp);
}

template <typename T>
bool Queue<T>::operator==(const Queue& q) const {
    std::size_t size1 = size();
    std::size_t size2 = q.size();

    if (size1 == 0 && size2 == 0) return true;
    if (size1 != size2) return false;

    Node<T>* curr1 = list->get();
    Node<T>* curr2 = q.list->get();

    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return true;
}

template <typename T>
auto operator<<(std::ostream& out, Queue<T>& q) -> std::ostream& {
    return q.list->print(out);
}

template <typename T>
auto operator>>(std::istream& in, Queue<T>& q) -> std::istream& {
    T tmp;
    in >> tmp;
    q.push(tmp);
    return in;
}