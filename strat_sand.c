#include <cocobot.h>
#include <stdio.h>
#include <math.h>
#include "strat_sand.h"

static float strat_sand_get_x(void)
{
  float target = 850 + 300;

  if(cocobot_game_state_get_color() == COCOBOT_GAME_STATE_COLOR_NEG)
  {
    return -target;
  }
  return target;
}

static float strat_sand_get_y(void)
{
  return 90;
}

static float strat_sand_get_a(void)
{
  if(cocobot_game_state_get_color() == COCOBOT_GAME_STATE_COLOR_NEG)
  {
    return 180;
  }
  return 0;
}

static void strat_sand_pos(void * arg, float *x, float *y, float *a)
{
  (void)arg;
  *x = strat_sand_get_x();
  *y = strat_sand_get_y();
  *a = strat_sand_get_a();
}

static float strat_sand_get_exec_time(void)
{
  return 5000;
}

float strat_sand_get_success_proba(void)
{
  return 1;
}

float strat_sand_get_score(void)
{
  return 16;
}

static cocobot_action_callback_result_t strat_sand_preexec(void * arg)
{
  (void)arg;

  cocobot_trajetory_set_xy_default(COCOBOT_TRAJECTORY_BACKWARD);

  return COCOBOT_RETURN_ACTION_SUCCESS;
}

static cocobot_action_callback_result_t strat_sand_cleanup(void * arg)
{
  (void)arg;

  cocobot_trajetory_set_xy_default(COCOBOT_TRAJECTORY_FORWARD);
  
  return COCOBOT_RETURN_ACTION_SUCCESS;
}

static cocobot_action_callback_result_t strat_sand_exec(void * arg)
{
  (void)arg;

  int x_k = 1;
  if(cocobot_game_state_get_color() == COCOBOT_GAME_STATE_COLOR_NEG)
  {
    x_k = -1;
  }

  cocobot_trajectory_goto_xy(x_k * 500, strat_sand_get_y(), 10000);

  cocobot_trajectory_wait();

  //cocobot_trajectory_set_opponent_detection(0);
  //cocobot_trajectory_goto_xy(x_k * 200, 100, 10000);

  //cocobot_trajectory_wait();
  //cocobot_trajectory_set_opponent_detection(1);


  //cocobot_trajectory_goto_d(150, 2500);
  //cocobot_trajectory_goto_xy_forward(x_k * (1500 - 400), strat_sand_get_y(), 10000);

  cocobot_trajectory_wait();

  return COCOBOT_RETURN_ACTION_SUCCESS;
}

void strat_sand_register(void)
{
  cocobot_action_scheduler_add_action(
                                    "sand",
                                    strat_sand_get_score(),
                                    strat_sand_pos,
                                    strat_sand_get_exec_time(),
                                    strat_sand_get_success_proba(),
                                    strat_sand_preexec,
                                    strat_sand_exec,
                                    strat_sand_cleanup,
                                    NULL,
                                    NULL);
}
