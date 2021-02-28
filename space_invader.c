#include <stdint.h>

#include "space_invader.h"

/* TODO: Refactor code so that .state is a part of the PlayerLaser and PlayerShip structs */

#define MAX_PLAYER_LASERS 3
#define MAX_ENEMY_LASERS 3

struct PlayerLaser {
  boolean_t active;
  struct DrawableImage laser;
};

struct PlayerShip {
  boolean_t alive;
  struct DrawableImage ship;
  struct DrawableImage explosion;
};

const uint8_t spaceship_frame_0[24] = {
  0x01, 0x00, 0x00,
  0x01, 0x80, 0x00,
  0x41, 0xC1, 0xC0,
  0x6F, 0xFF, 0xFF,
  0x0F, 0xFF, 0xFF,
  0x81, 0xC1, 0xC0,
  0x11, 0x80, 0x00,
  0x41, 0x00, 0x00
};
const uint8_t spaceship_frame_1[24] = {
  0x01, 0x00, 0x00,
  0xC1, 0x80, 0x00,
  0x01, 0xC1, 0xC0,
  0x8F, 0xFF, 0xFF,
  0x2F, 0xFF, 0xFF,
  0x21, 0xC1, 0xC0,
  0x11, 0x80, 0x00,
  0x11, 0x00, 0x00
};
const uint8_t spaceship_frame_2[24] = {
  0x21, 0x00, 0x00,
  0x41, 0x80, 0x00,
  0x21, 0xC1, 0xC0,
  0x8F, 0xFF, 0xFF,
  0x0F, 0xFF, 0xFF,
  0x81, 0xC1, 0xC0,
  0x41, 0x80, 0x00,
  0x61, 0x00, 0x00
};

const uint8_t player_laser_frame_0[2] = { 0x3F, 0xDF };
const uint8_t player_laser_frame_1[2] = { 0xDF, 0xBF };
const uint8_t player_laser_frame_2[2] = { 0x7F, 0x1F };
const uint8_t player_laser_frame_3[2] = { 0x9F, 0x3F };


const struct Image spaceship_image_0 = {.width = 24, .height = 8, .pixels = spaceship_frame_0};
const struct Image spaceship_image_1 = {.width = 24, .height = 8, .pixels = spaceship_frame_1};
const struct Image spaceship_image_2 = {.width = 24, .height = 8, .pixels = spaceship_frame_2};

const struct Image player_laser_image_0 = {.width = 8, .height = 2, .pixels = player_laser_frame_0};
const struct Image player_laser_image_1 = {.width = 8, .height = 2, .pixels = player_laser_frame_1};
const struct Image player_laser_image_2 = {.width = 8, .height = 2, .pixels = player_laser_frame_2};
const struct Image player_laser_image_3 = {.width = 8, .height = 2, .pixels = player_laser_frame_3};


static struct PlayerShip  player_ship;
static struct PlayerLaser player_lasers[MAX_PLAYER_LASERS];

signed char check_collisions() {

  return 0;
}

signed char game_tick(struct InvaderCommands commands) {
  
  return 0;
}

signed char game_setup() {
  /* Initialize player ship */
  player_ship = (struct PlayerShip){.alive = TRUE, .ship = (struct DrawableImage){.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0, .images = {&spaceship_image_0, &spaceship_image_1, &spaceship_image_2}} };
  
  /* Initialize player laser structs */
  for (int i = 0; i < MAX_PLAYER_LASERS; i++) {
    player_lasers[i].active = FALSE;
    // struct DrawableImage player_laser_init =
    player_lasers[i].laser = (struct DrawableImage){.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0,
      .images = {&player_laser_image_0, &player_laser_image_1, &player_laser_image_2, &player_laser_image_3}};
  }

  
  return 0;
}
