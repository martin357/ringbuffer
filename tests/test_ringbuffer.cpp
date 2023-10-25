#include <gtest/gtest.h>
#include "ringbuffer.hpp"

TEST(Ringbuffer, RingIndex_operations) {
    Ringbuffer<int, 3>::Index idx(0);
    Ringbuffer<int, 3>::Index idx2(1);
    EXPECT_EQ((int)idx, 0);
    EXPECT_EQ((int)idx--, 0);
    EXPECT_EQ((int)idx, 2);
    EXPECT_EQ((int)++idx, 0);
    EXPECT_NE(idx, idx2);
    EXPECT_EQ((int)(idx - idx2), 2);
    EXPECT_EQ((idx-idx2) + (idx-idx2), idx2);
    EXPECT_NE(idx, idx2);
    EXPECT_EQ(idx, idx2-1);
    EXPECT_LE(idx, idx2);
    
}

TEST(Ringbuffer, push_back_pop_back_behaviour) {
    Ringbuffer<int, 10> ring;
    ring.push_back(1);
    ring.push_back(2);
    ring.push_back(3);
    EXPECT_EQ(ring.front(), 1);
    EXPECT_EQ(ring.back(), 3);
    EXPECT_EQ(ring.empty(), false);
    ring.pop_back();
    EXPECT_EQ(ring.front(), 1);
    EXPECT_EQ(ring.back(), 2);
    EXPECT_EQ(ring.empty(), false);
    ring.pop_back();
    EXPECT_EQ(ring.front(), 1);
    EXPECT_EQ(ring.back(), 1);
    EXPECT_EQ(ring.empty(), false);
    ring.pop_back();
    EXPECT_EQ(ring.empty(), true);
}

TEST(Ringbuffer, push_front_pop_front_behaviour) {
    Ringbuffer<int, 10> ring;
    ring.push_front(1);
    ring.push_front(2);
    ring.push_front(3);
    EXPECT_EQ(ring.front(), 3);
    EXPECT_EQ(ring.back(), 1);
    EXPECT_EQ(ring.empty(), false);
    ring.pop_front();
    EXPECT_EQ(ring.front(), 2);
    EXPECT_EQ(ring.back(), 1);
    EXPECT_EQ(ring.empty(), false);
    ring.pop_front();
    EXPECT_EQ(ring.front(), 1);
    EXPECT_EQ(ring.back(), 1);
    EXPECT_EQ(ring.empty(), false);
    ring.pop_front();
    EXPECT_EQ(ring.empty(), true);
}

TEST(Ringbuffer, Iterators) {
    Ringbuffer<int, 10> ring;
    for(int i = 0; i < 9; ++i) {
        ring.push_back(i);
        EXPECT_EQ(ring.front(), 0);
        EXPECT_EQ(ring.back(), i);
        int j = 0;
        for(auto it = ring.begin(); it != ring.end(); ++it) {
            EXPECT_EQ(*it, j++);
        }
        j = 0;
        for(auto it = ring.begin(); it != ring.end(); it++) {
            EXPECT_EQ(*it, j++);
        }
    }
}

TEST(Ringbuffer, round_and_round) {
    Ringbuffer<int, 5> ring;
    for(int i = 0; i < 4; ++i) ring.push_back(i);
    EXPECT_TRUE(ring.full());
    ring.push_back(4);
    EXPECT_TRUE(ring.full());
    EXPECT_EQ(1, ring.front());
    EXPECT_EQ(4, ring.back());
}

TEST(Ringbuffer, pushing_head) {
    Ringbuffer<int, 3> ring;
    for(int i = 0; i < 6; i++) {
        ring.push_back(i);
    }
    EXPECT_EQ(ring.front(), 5-1);
    EXPECT_EQ(ring.back(), 5);
    EXPECT_TRUE(ring.full());
    EXPECT_FALSE(ring.empty());
}

TEST(Ringbuffer, pushing_tail) {
    Ringbuffer<int, 3> ring;
    for(int i = 0; i < 6; i++) {
        ring.push_front(i);
    }
    EXPECT_EQ(ring.back(), 5-1);
    EXPECT_EQ(ring.front(), 5);
    EXPECT_TRUE(ring.full());
    EXPECT_FALSE(ring.empty());
}


