#include <gtest/gtest.h>

extern "C" {
#include <event.h>
#include <event_handlers.h>
#include <game.h>
}

TEST(EventHandlersTest, WaitStartHandler) {
    // All events in this state are ignored except for a green 
    // button press
    game_set_state(GAME_WAIT_START);

    // display done is ignored
    handle_event({ .type = EVENT_DISPLAY_DONE });
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);

    // timeout is ignored
    handle_event({ .type = EVENT_TIMEOUT });
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);

    // blue button press is ignored
    handle_event({ .type = EVENT_BUTTON, .button = BUTTON_BLUE });
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);

    // green button press changes the state to GAME_SEQUENCE
    handle_event({ .type = EVENT_BUTTON, .button = BUTTON_GREEN });
    EXPECT_EQ(game_get_state(), GAME_SEQUENCE);
}

TEST(EventHandlersTest, SequenceHandler) {
    game_set_state(GAME_SEQUENCE);

    // display done changes the state to GAME_USER_ATTMEMPT
    handle_event({ .type = EVENT_DISPLAY_DONE });
    EXPECT_EQ(game_get_state(), GAME_USER_ATTEMPT);
    game_set_state(GAME_SEQUENCE);

    // event timeout is ignored
    handle_event({ .type = EVENT_TIMEOUT });
    EXPECT_EQ(game_get_state(), GAME_SEQUENCE);

    // button press changes the state to GAME_OVER
    handle_event({ .type = EVENT_BUTTON });
    EXPECT_EQ(game_get_state(), GAME_OVER);
}

TEST(EventHandlersTest, UserAttemptHandler) {
    game_reset(); // reset the game so we know we are on round 1
    game_set_state(GAME_USER_ATTEMPT);

    // display done changes the state to GAME_USER_ATTEMPT
    handle_event({ .type = EVENT_DISPLAY_DONE });
    EXPECT_EQ(game_get_state(), GAME_USER_ATTEMPT);

    // timeout changes the state to GAME_OVER
    handle_event({ .type = EVENT_TIMEOUT });
    EXPECT_EQ(game_get_state(), GAME_OVER);
    game_set_state(GAME_USER_ATTEMPT);

    // correct button press changes state to GAME_SEQUENCE (assuming round is complete)
    handle_event({
        .type = EVENT_BUTTON, 
        .button = static_cast<BUTTON>(game_get_sequence()[0])
    });
    EXPECT_EQ(game_get_state(), GAME_SEQUENCE);
    game_set_state(GAME_USER_ATTEMPT);

    // incorrect button press changes the state to GAME_OVER
    handle_event({
        .type = EVENT_BUTTON, 
        .button = static_cast<BUTTON>(!game_get_sequence()[0])
    });
    EXPECT_EQ(game_get_state(), GAME_OVER);
}

// GAME_VICTORY and GAME_OVER states behave the exact same, so they will use this
// helper for testing
void end_game_test_helper(GAME_STATE state) {
    ASSERT_TRUE(state == GAME_VICTORY || state == GAME_OVER);
    game_set_state(state);

    // display done changes the state to GAME_DISPLAY_SCORE
    handle_event( { .type = EVENT_DISPLAY_DONE });
    EXPECT_EQ(game_get_state(), GAME_DISPLAY_SCORE);
    game_set_state(state);

    // timeout is ignored
    handle_event( { .type = EVENT_TIMEOUT });
    EXPECT_EQ(game_get_state(), state);

    // button press ends the animation and changes the state to GAME_DISPLAY_SCORE
    handle_event( {.type = EVENT_BUTTON });
    EXPECT_EQ(game_get_state(), GAME_DISPLAY_SCORE);
}

TEST(EventHandlersTest, GameOverHandler) {
    end_game_test_helper(GAME_OVER);
}

TEST(EventHandlersTest, VictoryHandler) {
    end_game_test_helper(GAME_VICTORY);
}

TEST(EventHandlerTest, DisplayScoreHandler) {
    game_set_state(GAME_DISPLAY_SCORE);
    
    // display done is ignored
    handle_event({ .type = EVENT_DISPLAY_DONE });
    EXPECT_EQ(game_get_state(), GAME_DISPLAY_SCORE);

    // timeout is ignored
    handle_event( { .type = EVENT_TIMEOUT });
    EXPECT_EQ(game_get_state(), GAME_DISPLAY_SCORE);

    // button press changes the state to GAME_WAIT_START
    handle_event( { .type = EVENT_BUTTON });
    EXPECT_EQ(game_get_state(), GAME_WAIT_START);
}