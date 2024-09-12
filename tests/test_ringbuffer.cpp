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

#include <gtest/gtest.h>
#define USE_ITERATORS
#include "ringbuffer.hpp"

TEST(Ringbuffer, RingIndex_operations) {
    Ringbuffer<size_t, 3>::Index idx(0);
    Ringbuffer<size_t, 3>::Index idx2(1);
    EXPECT_EQ((size_t)idx, 0);
    EXPECT_EQ((size_t)idx--, 0);
    EXPECT_EQ((size_t)idx, 2);
    EXPECT_EQ((size_t)++idx, 0);
    EXPECT_NE(idx, idx2);
    EXPECT_EQ((size_t)(idx - idx2), 2);
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

TEST(Ringbuffer, indexing) {
    Ringbuffer<int, 5> ring;
    for(int i = 0; i < 4; ++i) {
        ring.push_back(i);
        EXPECT_EQ(ring[0], 0);
        EXPECT_EQ(ring[-1], i);
    }
    EXPECT_EQ(ring[-2], 2);
}

struct Leaky {
    static int counter;
    Leaky() { counter++; }
    ~Leaky() { counter--; }
};
int Leaky::counter = 0;

TEST(Ringbuffer, destructor_for_each_item) {
    auto ring = new Ringbuffer<Leaky, 3>;
    for(int i = 0; i < 6; i++) {
        ring->push_front(Leaky());
    }
    delete ring;
    EXPECT_EQ(Leaky::counter, 0);
}

TEST(Ringbuffer, initializer_list_constructor) {
    Ringbuffer<int, 10> ring = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Buffer may contain only 9 values, than circles back
    EXPECT_EQ(ring[0], 2);
    EXPECT_EQ(ring[-1], 10);
}

TEST(Ringbuffer, contained_size) {
    // Over-filled buffer
    Ringbuffer<int, 10> ring = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    EXPECT_EQ(ring.size(), (size_t) 9);
    ring.pop_back();
    EXPECT_EQ(ring.size(), (size_t) 8);
}

TEST(Ringbuffer, zero_size) {
    Ringbuffer<int, 16> ring;
    EXPECT_EQ(ring.size(), (size_t) 0);
}
