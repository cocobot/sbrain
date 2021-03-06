#include <cocobot.h>
#include "strat_hut.h"

typedef enum
{
  STRAT_HUT_VIOLET_LEFT,
  STRAT_HUT_VIOLET_RIGHT,
  STRAT_HUT_GREEN_LEFT,
  STRAT_HUT_GREEN_RIGHT,
} strat_hut_t;

static unsigned int strat_hut_get_score(int hut)
{
  (void)hut; //each hut is equal
  return 10;
}

static float strat_hut_get_x(strat_hut_t hut)
{
  switch(hut)
  {
    case STRAT_HUT_VIOLET_LEFT:
      return -1200;

    case STRAT_HUT_VIOLET_RIGHT:
      return -900;

    case STRAT_HUT_GREEN_LEFT:
      return 900;

    case STRAT_HUT_GREEN_RIGHT:
      return 1200;
  }

  return 10000; //unvalid hut has been requested.
}

static float strat_hut_get_y(strat_hut_t hut)
{
  (void)hut; //each hut is equal
  return 700;
}

static float strat_hut_get_a(strat_hut_t hut)
{
  (void)hut; //each hut is equal
  return -90; //we want to hit the door with our back
}

static void strat_hut_pos(void *arg, float *x, float *y, float *a)
{
  strat_hut_t hut = (strat_hut_t)arg;
  *x = strat_hut_get_x(hut);
  *y = strat_hut_get_y(hut);
  *a = strat_hut_get_a(hut);
}

static float strat_hut_get_exec_time(strat_hut_t hut)
{
  (void)hut; //each hut is equal
  return 3000; //in ms
}

static float strat_hut_get_success_proba(strat_hut_t hut)
{
  (void)hut; //each hut is equal
  return 0.01; //very low. Main robot should have already done the action before us !
}

static cocobot_action_callback_result_t strat_hut_action(void * arg)
{
  (void)arg; //each hut is equal

  cocobot_trajectory_goto_d(-10400, 2000);
  cocobot_trajectory_goto_d(300, COCOBOT_TRAJECTORY_UNLIMITED_TIME);
  cocobot_trajectory_wait();

  return COCOBOT_RETURN_ACTION_SUCCESS;
}

void strat_hut_register(void)
{
  if(cocobot_game_state_get_color() == COCOBOT_GAME_STATE_COLOR_NEG)
  {
    cocobot_action_scheduler_add_action(
                                        "hut_0",
                                        strat_hut_get_score(STRAT_HUT_VIOLET_LEFT),
                                        strat_hut_pos,
                                        strat_hut_get_exec_time(STRAT_HUT_VIOLET_LEFT),
                                        strat_hut_get_success_proba(STRAT_HUT_VIOLET_LEFT),
                                        NULL,
                                        strat_hut_action,
                                        NULL,
                                        (void *)STRAT_HUT_VIOLET_LEFT,
                                        NULL);

    cocobot_action_scheduler_add_action(
                                        "hut_1",
                                        strat_hut_get_score(STRAT_HUT_VIOLET_RIGHT),
                                        strat_hut_pos,
                                        strat_hut_get_exec_time(STRAT_HUT_VIOLET_RIGHT),
                                        strat_hut_get_success_proba(STRAT_HUT_VIOLET_RIGHT),
                                        NULL,
                                        strat_hut_action,
                                        NULL,
                                        (void *)STRAT_HUT_VIOLET_RIGHT,
                                        NULL);
  }

  if(cocobot_game_state_get_color() == COCOBOT_GAME_STATE_COLOR_POS)
  {
    cocobot_action_scheduler_add_action(
                                        "hut_2",
                                        strat_hut_get_score(STRAT_HUT_GREEN_LEFT),
                                        strat_hut_pos,
                                        strat_hut_get_exec_time(STRAT_HUT_GREEN_LEFT),
                                        strat_hut_get_success_proba(STRAT_HUT_GREEN_LEFT),
                                        NULL,
                                        strat_hut_action,
                                        NULL,
                                        (void *)STRAT_HUT_GREEN_LEFT,
                                        NULL);

    cocobot_action_scheduler_add_action(
                                        "hut_3",
                                        strat_hut_get_score(STRAT_HUT_GREEN_RIGHT),
                                        strat_hut_pos,
                                        strat_hut_get_exec_time(STRAT_HUT_GREEN_RIGHT),
                                        strat_hut_get_success_proba(STRAT_HUT_GREEN_RIGHT),
                                        NULL,
                                        strat_hut_action,
                                        NULL,
                                        (void *)STRAT_HUT_GREEN_RIGHT,
                                        NULL);
  }
}
