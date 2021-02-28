#include <stdint.h>

#include "space_invader.h"
#include "baseline.h"
#include "uart.h"               /* debugging remove */

/* TODO: Refactor code so that .state is a part of the PlayerLaser and PlayerShip structs */

/* TODO: Find safe way to calculate this */
#define NUM_SHIP_FRAMES         (3)
#define NUM_PLAYER_LASER_FRAMES (4)

#define MAX_PLAYER_LASERS (3)
#define MAX_ENEMY_LASERS  (3)

#define PLAYER_LASER_VELOCITY (game_width / 32)
#define ENEMY_LASER_VELOCITY (game_width / 32)

#define MAX_VELOCITY      (game_height / 8)
#define VELOCITY_GAIN_PER_TICK (2)
#define VELOCITY_LOSS_PER_TICK (3)

struct PlayerLaser {
  boolean_t active;
  struct DrawableImage laser;
};

struct PlayerShip {
  boolean_t alive;
  signed char velocity;
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

static unsigned char game_width, game_height;


signed char ship_tick(invader_movecmd_t movement) {
  /* Change speed based on direction, also decrease mag so it stops naturally */
  if (movement == UP) player_ship.velocity -= VELOCITY_GAIN_PER_TICK;
  if (movement == DOWN) player_ship.velocity += VELOCITY_GAIN_PER_TICK;
  if (movement == NOP) player_ship.velocity = math_mag_decrease(player_ship.velocity, VELOCITY_LOSS_PER_TICK);
  /* Ensure |velocity| <= MAX_VELOCITY */
  if (math_absolute(player_ship.velocity) > MAX_VELOCITY) player_ship.velocity = math_mag_set(player_ship.velocity, MAX_VELOCITY);

  /* Change y position based on speed */
  player_ship.ship.y += player_ship.velocity;
  /* Ensure the ship stays on screen */
  char ship_height = player_ship.ship.images[player_ship.ship.state]->height;
  if (player_ship.ship.y < 0) player_ship.ship.y = 0;
  if (player_ship.ship.y + ship_height > game_height) player_ship.ship.y = game_height - ship_height;

  /* Adjust state so ship is animated */
  if (player_ship.ship.state < NUM_SHIP_FRAMES - 1) {
    player_ship.ship.state++;
  } else {
    player_ship.ship.state = 0;
  }

  return 0;
}

/* Mark first empty laser as active and shoot it */
signed char player_laser_shoot(invader_shootcmd_t shoot) {
  if (shoot == TRUE) {
    for (unsigned char i = 0; i < MAX_PLAYER_LASERS; i++) {
      if (player_lasers[i].active == FALSE) {
	player_lasers[i].active = TRUE;
	player_lasers[i].laser.x = player_ship.ship.x + player_ship.ship.images[player_ship.ship.state]->width;
	player_lasers[i].laser.y = player_ship.ship.y + player_ship.ship.images[player_ship.ship.state]->height / 2;
	break;
      }
    }
  }

  return 0;
}

signed char check_player_laser_collisions() {

  return 0;
}

signed char player_laser_tick() {
  for (unsigned char i = 0; i < MAX_PLAYER_LASERS; i++) {
      if (player_lasers[i].active == TRUE) {
	player_lasers[i].laser.x += PLAYER_LASER_VELOCITY;
	/* Adjust state so laser is animated */
	if (player_lasers[i].laser.state < NUM_PLAYER_LASER_FRAMES - 1) {
	  player_lasers[i].laser.state++;
	} else {
	  player_lasers[i].laser.state = 0;
	}
      }
      /* ISSUE: x is a signed character, max val of 127. Rolls over
	 into negative values (-128 specifically), then counts back
	 up. I didn't want to change x into an int (too much memory),
	 so instead I implemented a check to mark the laser as
	 inactive if x < 0 as well. Promoting it to int will hide the
	 warning, but not the actual problem + symptoms, so I'll leave
	 it. */
      /* Kinda odd, you'd think promoting one/both sides to int would
	 fix the problem but that's not what's happening. I'm pretty
	 sure int is signed with sdcc, but just in case I also tried
	 with (signed int), no effect. */
      if (player_lasers[i].laser.x < 0 || player_lasers[i].laser.x > game_width) {
	player_lasers[i].active = FALSE;
      }
      /* uart_printf("%d Active: %d\n\r", i, player_lasers[i].active); */
      /* uart_printf("%d x: %d\n\r", i, player_lasers[i].laser.x); */
      /* uart_printf("---\n\r"); */
    }

  check_player_laser_collisions();
  
  return 0;
}

/* SDCC 4.0.0 doesn't support passing structures directly, despite that
   being part of the C standard. Page 25 of sddcman.pdf. I cry every time. */
signed char invader_game_tick(struct InvaderCommands *commands) {
  ship_tick(commands->movement);
  player_laser_shoot(commands->shoot);
  player_laser_tick();
  
  return 0;
}

/* Initializes the structs */
signed char invader_game_init(unsigned char width, unsigned char height) {
  game_width = width;
  game_height = height;
  
  /* Initialize player ship */
  /* SDCC doesn't support compound literals so I need to create a
     temporary structure variable, then assign that. I am saddened. */
  struct DrawableImage spaceship_init = {.x = game_width / 16, .y = game_height / 2, .state = 0,
    .images = {&spaceship_image_0, &spaceship_image_1, &spaceship_image_2} };
  /* Another case where compound literals not being supported sucks. */
  player_ship.alive = TRUE;
  player_ship.ship = spaceship_init;
  
  /* Initialize player laser structs */
  for (unsigned char i = 0; i < MAX_PLAYER_LASERS; i++) {
    player_lasers[i].active = FALSE;
    struct DrawableImage player_laser_init = {.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0,
      .images = {&player_laser_image_0, &player_laser_image_1, &player_laser_image_2, &player_laser_image_3}};
    player_lasers[i].laser = player_laser_init;
  }

  
  return 0;
}

/* remove, debugging */
struct DrawableImage* debug_drawableimage_spaceship() {
  return &player_ship.ship;
}

/* remove, debugging */
struct DrawableImage* debug_drawableimage_playerlaser(unsigned char i) {
  if (player_lasers[i].active == TRUE) return &player_lasers[i].laser;
  return 0;
}
