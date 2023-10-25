
#include <iterator>

template<class T, int N>
class Ringbuffer {
    class Index {
        int m_index{0};
    public:
        Index(int _index) : m_index(_index) {}
        constexpr inline Index operator+(const Index & other) const {
            return (this->m_index + other.m_index) % N;
        }
        constexpr inline Index operator-(const Index & other) const {
            return (this->m_index - other.m_index) % N;
        }
        constexpr inline const & Index operator+=(const Index & other) {
            m_index = (m_index + other.m_index) % N;
            return * this;
        }
        constexpr inline const & Index operator-=(const Index & other) {
            m_index = (N + m_index - other.m_index) % N;
            return * this;
        }
        constexpr inline Index operator++() { // pre
            auto tmp = Index(*this);
            m_index = (m_index + 1) % N;
            return tmp;
        }
        constexpr Index operator--() { // pre
            auto tmp = Index(*this);
            m_index = (N + m_index - 1) % N;
            return tmp
        }
        constexpr Index operator++(int) { // post
            m_index = (m_index + 1) & N;
            return * this;
        }
        constexpr Index operator--(int) { // post
            m_index = (N + m_index - 1);
            return * this;
        }
        constexpr 
    };

    class iterator : public std::iterator<
                                random_access_iterator_tag,
                                T,
                                int,
                                T*,
                                T> {
        const Ringbuffer *m_buf{nullptr};
        Index m_idx;
        iterator(const Ringbuf * _buf, Index _idx) : m_buf(_buf), m_idx(_idx) {}
    public:
        explicit iterator() = delete;
        iterator& operator++() { num = TO >= FROM ? num + 1: num - 1; return *this; }
        iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return num == other.num; }
        bool operator!=(iterator other) const { return !(*this == other); }
        reference operator*() const { return num; }
    }

    Index head, tail;


};
