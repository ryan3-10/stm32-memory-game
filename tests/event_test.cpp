#include <gtest/gtest.h>

extern "C" {
#include <event.h>
}

TEST(EventTest, EqPushPop) {
    eq_clear();
    ASSERT_TRUE(eq_is_empty());

    EVENT e = { 
        .type = EVENT_BUTTON,
        .button = BUTTON_WHITE,
        .timestamp = 100
    };

    eq_push(e);
    EVENT p = eq_pop();
    EXPECT_TRUE(
        e.type == p.type &&
        e.button == p.button &&
        e.timestamp == p.timestamp
    );

    eq_push(e);
    eq_push({ .timestamp = 1 });
    eq_push({ .timestamp = 0 });
    eq_push({ .timestamp = 0 });
    p = eq_pop();

    EXPECT_TRUE(
        e.type == p.type &&
        e.button == p.button &&
        e.timestamp == p.timestamp
    );

    p = eq_pop();
    EXPECT_EQ(p.timestamp, 1);
}

TEST(EventTest, EqEmptyFullClear) {
    eq_clear();

    for (size_t i = 0; i < EVENT_QUEUE_SIZE - 1; ++i) {
        eq_push({});
    }

    eq_clear();
    EXPECT_TRUE(eq_is_empty());

    // Push until almost full
    for (size_t i = 0; i < EVENT_QUEUE_SIZE - 2; ++i) {
        eq_push({});
        EXPECT_FALSE(eq_is_full());
        EXPECT_FALSE(eq_is_empty());
    }

    // Final push to make full
    eq_push({});
    EXPECT_TRUE(eq_is_full());

    for (size_t i = 0; i < EVENT_QUEUE_SIZE - 1; ++i) {
        eq_pop();
    }

    EXPECT_TRUE(eq_is_empty());
    EXPECT_FALSE(eq_is_full());
}