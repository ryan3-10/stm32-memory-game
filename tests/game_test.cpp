#include <gtest/gtest.h>

extern "C" {
#include <game.h>
}

TEST(GameTest, GameInitialization) {
    game_reset();
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);
    EXPECT_EQ(game_get_round(), 1);
    EXPECT_TRUE(game_in_new_state());
}

TEST(GameTest, GameSetState) {
    game_set_state(GAME_SEQUENCE);
    EXPECT_EQ(game_get_state(), GAME_SEQUENCE);

    game_set_state(GAME_USER_ATTEMPT);
    EXPECT_EQ(game_get_state(), GAME_USER_ATTEMPT);

    game_set_state(GAME_VICTORY);
    EXPECT_EQ(game_get_state(), GAME_VICTORY);

    game_set_state(GAME_OVER);
    EXPECT_EQ(game_get_state(), GAME_OVER);

    game_set_state(GAME_DISPLAY_SCORE);
    EXPECT_EQ(game_get_state(), GAME_DISPLAY_SCORE);

    game_set_state(GAME_WAIT_START);
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);
}

TEST(GameTest, GameLevelUp) {
    game_reset();
    EXPECT_EQ(game_get_round(), 1);

    for (size_t i = 2; i <= 15; ++i) {
        game_level_up();
        EXPECT_EQ(game_get_round(), i);
    }
}
