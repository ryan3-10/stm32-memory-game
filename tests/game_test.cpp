#include <gtest/gtest.h>

extern "C" {
#include <game.h>
}

TEST(GameTest, ResetInitializesGameWaitStart) {
    game_reset();
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);
}

