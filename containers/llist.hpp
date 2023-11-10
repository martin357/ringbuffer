#pragma once

#include <cassert>

#ifdef USE_ITERATORS
    #include <iterator>
    #include <initializer_list>
#endif


template<class T>
class LList {
    struct Node {
        T value;
        Node * prev{nullptr};
        Node * next{nullptr};
    };
    Node * head{nullptr};
    Node * tail{nullptr};
public:

#ifdef USE_ITERATORS 
    class iterator : public std::iterator<
                                std::bidirectional_iterator_tag,
                                T,
                                size_t,
                                T*,
                                T> {
        Node * node{nullptr};
        iterator(Node * node) { this->node = node; }
        friend class LList;
    public:
        inline T & operator*() { assert(node); return node->value; }
        inline iterator & operator++() { assert(node); node = node->next; return *this; } // pre
        inline iterator & operator--() { assert(node); node = node->prev; return *this; } // pre
        inline iterator operator++(int) { 
            assert(node); 
            auto tmp = iterator(*this); 
            node = node->next; 
            return tmp; 
        } // post
        inline iterator operator--(int) {
            assert(node);
            auto tmp = iterator(*this); 
            node = node->prev; 
            return tmp; 
        } // post
        inline bool operator==(const iterator & other) const { return this->node == other.node; }
        inline bool operator!=(const iterator & other) const { return !(*this == other); }
    };

    class const_iterator : public iterator {
    public:
        inline const T & operator*() { assert(this->node); return this->node->value; }
    };

    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(nullptr); }
    const_iterator const_begin() const { return const_iterator(head); }
    const_iterator const_end() const { return const_iterator(nullptr); }
#endif // USE_ITERATORS

    LList(const LList &) = delete;
    LList & operator=(const LList &) = delete;
    LList() {}
    LList(std::initializer_list<T> list) {
        for(auto value : list) push_back(value);
    }

    void push_front(const T & item) {
        Node * node = new Node{item, nullptr, nullptr};
        if( ! head ) { head = tail = node; }
        else { head->prev = node; node->next = head; head = node; }
        assert(head == node);
    }

    void push_back(const T & item) {
        Node * node = new Node{item, nullptr, nullptr};
        if( ! tail ) { head = tail = node; }
        else { tail->next = node; node->prev = tail; tail = node; }
        assert(tail == node);
    }
        
    void pop_front() {
        assert(head);
        Node * tmp = head;
        head = head->next;
        if( !head ) tail = nullptr;
        delete tmp;
    }

    void pop_back() {
        assert(tail);
        Node * tmp = tail;
        tail = tail->prev;
        if( !tail ) head = nullptr;
        delete tmp;
    }

    bool empty() {
        assert( (!head) == (!tail) );
        return head == nullptr;
    }

    const T & front() const { return head->value; }
    const T & back() const { return tail->value; }

    void clear() {
        while(!empty()) pop_back();
    }

    ~LList() {
        clear();
    }
};
