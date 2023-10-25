
#include <iterator>

template<class T, int N>
class Ringbuffer {
    T m_data[N];
public:
    class Index {
        int m_index{0};
    public:
        constexpr Index(int _index) : m_index(_index) {}
        explicit constexpr operator int() const { return m_index; }
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

    class iterator : public std::iterator<
                                std::random_access_iterator_tag,
                                T,
                                int,
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
        constexpr T& operator*() const { return m_buf->m_data[(int)m_idx]; }
    };

protected:

    Index m_head, m_tail;

public:
    constexpr Ringbuffer() : m_head(0), m_tail(0) {}

    constexpr void push_front(const T & item) {
        m_data[(int)--m_head] = item;
        if(m_head == m_tail) m_tail--;
    }
    constexpr void push_back(const T & item) {
        m_data[(int)m_tail++] = item;
        if(m_head == m_tail) m_head++;
    }
    constexpr const T & front() const {
        return m_data[(int)m_head];
    }
    constexpr const T & back() const {
        return m_data[(int)(m_tail-1)];
    }
    constexpr void pop_front() {
        m_head++;
    }
    constexpr void pop_back() {
        m_tail--;
    }
    constexpr bool full() const { return m_head == m_tail + 1; }
    constexpr bool empty() const { return m_head == m_tail; }
    constexpr int size() const { return m_tail - m_head; }
    constexpr int capacity() const { return N - 1; }
    constexpr iterator begin() { return iterator(this, m_head); }
    constexpr iterator end() { return iterator(this, m_tail); }
};
