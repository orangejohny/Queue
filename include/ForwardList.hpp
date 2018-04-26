// class ForwardList header file

#include <string>
#include <initializer_list>
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
};

template <typename T>
class ForwardList {
    Node<T>* start;
public:
    ForwardList() : start{nullptr} {};
    ForwardList(std::initializer_list<T>);
    ~ForwardList();
    auto insert(T) -> void;
    auto remove(T) -> int;
    auto print(std::ostream&) -> std::ostream&;
    auto search(T) const -> int;
    auto change(T, int) -> int;
    auto sort() const -> int;
    auto get() const -> Node<T>*; 
};


template <typename T>
auto ForwardList<T>::insert(T val) -> void {
    if (!start) {
        start = new Node<T>{val, nullptr};
        return;
    }

    Node<T>* curr = start;

    while (curr -> next != nullptr)
        curr = curr -> next;

    curr -> next = new Node<T>{val, nullptr};
}

template <typename T>
auto ForwardList<T>::remove(T val) -> int {
    if (!start) {
        return -1;
    }

    Node<T>* curr = start;
    Node<T>* prev = curr;

    if (curr -> data == val) {
        curr = start -> next;
        delete start;
        start = curr;
        return 0;
    }

    curr = curr -> next;

    while (curr != nullptr) {
        if (curr -> data == val) {
            prev -> next = curr -> next;
            delete curr;
            curr = prev -> next;
            return 0;
        } else {
            curr = curr -> next;
            prev = prev -> next;
        }
    }

    return 1;
}

template <typename T>
auto ForwardList<T>::print(std::ostream& out) -> std::ostream& {
    if (!start) {
        return out;
    }

    Node<T>* curr = start;
    out << start -> data;
    curr = curr -> next;

    while (curr != nullptr) {
        out << " " << curr -> data;
        curr = curr -> next;
    }

    return out;
}

template <typename T>
ForwardList<T>::~ForwardList() {
    Node<T>* curr = start;

    while (curr != nullptr) {
        curr = curr -> next;
        delete start;          // if there is a complex object in start => memory leak(?)
        start = curr;
    }
}

template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> in) {
    start = nullptr;
    for (T elem : in) {
        insert(elem);
    }
}

template <typename T>
auto ForwardList<T>::search(T val) const -> int {
    if (!start) {
        return -1;
    }

    Node<T>* curr = start;
    int pos = 0;
    bool found = false;

    while (curr != nullptr) {
        if ((curr -> data) == val) {
            return 0;
        }

        curr = curr -> next;
        pos++;
    }   

    return 1;
}

template <typename T>
auto ForwardList<T>::change(T val, int pos) -> int {
    if (!start) {
        return -1;
    }

    Node<T>* curr = start;
    int curr_pos = 0;

    while (curr != nullptr) {
        if (pos == curr_pos) {
            curr -> data = val;
            return 0;
        }

        curr = curr -> next;
        curr_pos++;
    }

    return 1;
}

template <typename T>
auto ForwardList<T>::sort() const -> int {
    if (!start) {
        return -1;
    }

    Node<T>* curr = start;
    Node<T>* follow;

    for (Node<T>* i = start; i -> next != nullptr; i = i -> next) {
        for (Node<T>* j = i -> next; j != nullptr; j = j -> next) {
            if ((i -> data) > (j -> data)) {
                std::swap(i -> data, j -> data);
            }
        }
    }

    return 0;
}

template <typename T>
auto ForwardList<T>::get() const -> Node<T>* {
    return start;
} 