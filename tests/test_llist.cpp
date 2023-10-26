#include <gtest/gtest.h>
#include "llist.hpp"

TEST(push_back_pop_back_behaviour, BasicAssertions) {
    LList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.empty(), false);
    list.pop_back();
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.empty(), false);
    list.pop_back();
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.empty(), false);
    list.pop_back();
    EXPECT_EQ(list.empty(), true);
}

TEST(push_front_pop_front_behaviour, BasicAssertions) {
    LList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.empty(), false);
    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.empty(), false);
    list.pop_front();
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.empty(), false);
    list.pop_front();
    EXPECT_EQ(list.empty(), true);
}

TEST(iterators, BasicAssertions) {
    LList<int> list;
    for(int i = 0; i < 10; ++i) {
        list.push_back(i);
        EXPECT_EQ(list.front(), 0);
        EXPECT_EQ(list.back(), i);
        int j = 0;
        for(auto it = list.begin(); it != list.end(); ++it) {
            EXPECT_EQ(*it, j++);
        }
        j = 0;
        for(auto it = list.begin(); it != list.end(); it++) {
            EXPECT_EQ(*it, j++);
        }
    }
}

TEST(const_iterators, BasicAssertions) {
    LList<int> list;
    for(int i = 0; i < 10; ++i) {
        list.push_back(i);
        EXPECT_EQ(list.front(), 0);
        EXPECT_EQ(list.back(), i);
        int j = 0;
        for(auto it = list.const_begin(); it != list.const_end(); ++it) {
            EXPECT_EQ(*it, j++);
        }
        j = 0;
        for(auto it = list.const_begin(); it != list.const_end(); it++) {
            EXPECT_EQ(*it, j++);
        }
    }
}

struct LeakingCanary {
    static int i;
    LeakingCanary() {
        i++;
    }
    ~LeakingCanary() {
        i--;
    }
    static bool is_leaking() { return 0 == i; }
};
int LeakingCanary::i = 0;

TEST(destructor, BasicAssertions) {
    {
        LList<LeakingCanary> list;
        for(int i = 0; i < 10; i++) {
            list.push_back(LeakingCanary());
        }
    }
    EXPECT_EQ(false, LeakingCanary::is_leaking());

}