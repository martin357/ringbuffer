/*
Copyright 2023, Martin Kopecky (martin.kopecky357@gmail.com)

This file is part of Containers.

Containers is free software: you can redistribute it and/or modify it under the terms of
the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

Containers is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
Containers. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef USE_ITERATORS
    #include <iterator>
    #include <initializer_list>
#endif



template<class T, size_t N>
class Ringbuffer {
    T m_data[N];
public:
    class Index {
        size_t m_index{0};
    public:
        constexpr Index(size_t _index) : m_index(_index) {}
        explicit constexpr operator size_t() const { return m_index; }
        constexpr Index operator+(const Index & other) const {
            return (this->m_index + other.m_index) % N;
        }
        constexpr Index operator-(const Index & other) const {
            return ( N + this->m_index - other.m_index) % N;
        }
        constexpr const Index & operator+=(const Index & other) {
            m_index = (m_index + other.m_index) % N;
            return * this;
        }
        constexpr const Index & operator-=(const Index & other) {
            m_index = (N + m_index - other.m_index) % N;
            return * this;
        }
        constexpr Index operator++(int) { // post
            auto tmp = Index(*this);
            m_index = (m_index + 1) % N;
            return tmp;
        }
        constexpr Index operator--(int) { // post
            auto tmp = Index(*this);
            m_index = (N + m_index - 1) % N;
            return tmp;
        }
        constexpr Index operator++() { // pre
            m_index = (m_index + 1) % N;
            return * this;
        }
        constexpr Index operator--() { // pre
            m_index = (N + m_index - 1) % N;
            return * this;
        }
        constexpr auto operator<=>(const Index & other) const = default;
    };
#ifdef USE_ITERATORS
    class iterator : public std::iterator<
                                std::random_access_iterator_tag,
                                T,
                                size_t,
                                T*,
                                T> {
        Ringbuffer *m_buf{nullptr};
        Index m_idx;
        friend class Ringbuffer;
        constexpr iterator(Ringbuffer * _buf, Index _idx) : m_buf(_buf), m_idx(_idx) {}
    public:
        explicit constexpr iterator() = delete;
        constexpr iterator& operator++() { m_idx++; return *this; }
        constexpr iterator operator++(int) { auto tmp = *this; m_idx++; return tmp; }
        constexpr bool operator==(iterator other) const { return m_idx == other.m_idx; }
        constexpr bool operator!=(iterator other) const { return !(*this == other); }
        constexpr T& operator*() const { return m_buf->m_data[(size_t)m_idx]; }
    };
#endif
protected:

    Index m_head, m_tail;

public:
    constexpr Ringbuffer() : m_head(0), m_tail(0) {}
    Ringbuffer(const Ringbuffer &) = delete;
    Ringbuffer & operator=(const Ringbuffer &) = delete;

    constexpr void push_front(const T & item) {
        m_data[(size_t)--m_head] = item;
        if(m_head == m_tail) m_tail--;
    }
    constexpr void push_back(const T & item) {
        m_data[(size_t)m_tail++] = item;
        if(m_head == m_tail) m_head++;
    }
    constexpr const T & front() const {
        return m_data[(size_t)m_head];
    }
    constexpr const T & back() const {
        return m_data[(size_t)(m_tail-1)];
    }
    constexpr void pop_front() {
        m_head++;
    }
    constexpr void pop_back() {
        m_tail--;
    }
    constexpr bool full() const { return m_head == m_tail + 1; }
    constexpr bool empty() const { return m_head == m_tail; }
    constexpr size_t size() const { return m_tail - m_head; }
    constexpr size_t capacity() const { return N - 1; }
    constexpr T & operator[](int idx) {
        return idx >= 0 ?
            m_data[(size_t)(m_head + (Index(idx)))]
            : m_data[(size_t)(m_tail + (Index(idx)))];
    }
#ifdef USE_ITERATORS
    constexpr iterator begin() { return iterator(this, m_head); }
    constexpr iterator end() { return iterator(this, m_tail); }
    constexpr Ringbuffer(std::initializer_list<T> init) : m_head(0), m_tail(0) {
        for(T value : init) {
            push_back(value);
        }
    }
#endif
};
