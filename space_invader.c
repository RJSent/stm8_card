#include <stdint.h>

#include "space_invader.h"
#include "baseline.h"
/* #include "uart.h" */

/* TODO: Refactor code so that .state is a part of the PlayerLaser and PlayerShip structs */

/* TODO: Find safe way to calculate this */
#define NUM_SHIP_FRAMES              (3)
#define NUM_PLAYER_LASER_FRAMES      (4)
#define NUM_INVADER_FRAMES           (2)
#define NUM_INVADER_LASER_FRAMES     (2)
#define NUM_INVADER_EXPLOSION_FRAMES (4)

#define PLAYER_SHIP_TICKS_PER_FRAME   (2)
#define INVADER_TICKS_PER_FRAME       (26)
#define INVADER_LASER_TICKS_PER_FRAME (6)
#define INVADER_TICKS_BETWEEN_SPAWN   (32)

#define MAX_INVADERS        (3)
#define MAX_PLAYER_LASERS   (3)
#define MAX_INVADER_LASERS  (3)

#define PLAYER_LASER_VELOCITY   (game_width / 32)
#define INVADER_LASER_VELOCITY  (game_width / 32)

#define PLAYER_MAX_VELOCITY            (game_height / 8)
#define PLAYER_VELOCITY_TICKS_PER_GAIN (2) /* TODO: adjust in terms of game_height */
#define PLAYER_VELOCITY_GAIN_PER_TICK  (1)
#define PLAYER_VELOCITY_LOSS_PER_TICK  (3)
#define INVADER_Y_SPEED                (game_height / 16)
#define INVADER_X_SPEED                (game_width / 32)

#define INVADER_SPAWN_CHANCE (8) /* percentage out of 100 per tick */
#define INVADER_SHOOT_CHANCE (3)

typedef enum {STATUS_ALIVE, STATUS_EXPLODING, STATUS_DEAD} ship_status_t;

struct PlayerLaser {
  boolean_t active;
  struct DrawableImage laser;
};

struct PlayerShip {
  ship_status_t status;
  signed char velocity;
  struct DrawableImage ship;
  struct DrawableImage explosion;
};

/* TODO: Support different types of invaders. Maybe by different DrawableImage structs + a invader_num variable? Memory intensive... */
struct InvaderMob {
  ship_status_t status;
  enum InvaderDirection {INVADERDIRECTION_UP, INVADERDIRECTION_DOWN} direction;
  struct DrawableImage invader;
  struct DrawableImage explosion;
};

struct InvaderLaser {
  boolean_t active;
  struct DrawableImage laser;
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

const uint8_t invader_1_frame_0[11] = {
  0x60, 0x18, 0x7C, 0xB6,       /* top half */
  0xAC, 0x2C, 0xAC,             /* middle part */
  0xB6, 0x7C, 0x18, 0x60        /* bottom part */
};
const uint8_t invader_1_frame_1[11] = {
  0x20, 0x19, 0x7C, 0xB6,       /* top half */
  0x2C, 0x2C, 0x2C,             /* middle part */
  0xB6, 0x7C, 0x19, 0x20        /* bottom part */
};

const uint8_t invader_explosion_frame_0[11] = {
  0x00, 0x00, 0x00, 0x18,
  0x24, 0x24, 0x24,
  0x18, 0x00, 0x00, 0x00
};
const uint8_t invader_explosion_frame_1[11] = {
  0x00, 0x00, 0x18,
  0x24, 0x42, 0x42, 0x42, 0x24,
  0x18, 0x00, 0x00
};
const uint8_t invader_explosion_frame_2[11] = {
  0x10, 0x24, 0x42,
  0x81, 0x01, 0x81, 0x80, 0x81,
  0x02, 0x24, 0x08
};
const uint8_t invader_explosion_frame_3[11] = {
  0x08, 0x24, 0x00,
  0x01, 0x80, 0x81, 0x01, 0x80,
  0x02, 0x00, 0x08
};


const uint8_t invader_laser_frame_0[3] = { 0x2A, 0xFF, 0x2A};
const uint8_t invader_laser_frame_1[3] = { 0x66, 0xFF, 0x66};


const struct Image spaceship_image_0 = {.width = 24, .height = 8, .pixels = spaceship_frame_0};
const struct Image spaceship_image_1 = {.width = 24, .height = 8, .pixels = spaceship_frame_1};
const struct Image spaceship_image_2 = {.width = 24, .height = 8, .pixels = spaceship_frame_2};

const struct Image player_laser_image_0 = {.width = 8, .height = 2, .pixels = player_laser_frame_0};
const struct Image player_laser_image_1 = {.width = 8, .height = 2, .pixels = player_laser_frame_1};
const struct Image player_laser_image_2 = {.width = 8, .height = 2, .pixels = player_laser_frame_2};
const struct Image player_laser_image_3 = {.width = 8, .height = 2, .pixels = player_laser_frame_3};

const struct Image invader_1_image_0 = {.width = 8, .height = 11, .pixels = invader_1_frame_0};
const struct Image invader_1_image_1 = {.width = 8, .height = 11, .pixels = invader_1_frame_1};

const struct Image invader_explosion_image_0 = {.width = 8, .height = 11, .pixels = invader_explosion_frame_0};
const struct Image invader_explosion_image_1 = {.width = 8, .height = 11, .pixels = invader_explosion_frame_1};
const struct Image invader_explosion_image_2 = {.width = 8, .height = 11, .pixels = invader_explosion_frame_2};
const struct Image invader_explosion_image_3 = {.width = 8, .height = 11, .pixels = invader_explosion_frame_3};

const struct Image invader_laser_image_0 = {.width = 8, .height = 3, .pixels = invader_laser_frame_0};
const struct Image invader_laser_image_1 = {.width = 8, .height = 3, .pixels = invader_laser_frame_1};


static struct PlayerShip  player_ship;
static struct PlayerLaser player_lasers[MAX_PLAYER_LASERS];
static struct InvaderMob  invader_mobs[MAX_INVADERS];
static struct InvaderLaser invader_lasers[MAX_INVADER_LASERS];

static unsigned char game_width, game_height;

#ifdef UART_H
void _debug_ship_tick(invader_movecmd_t movement, char ticks_until_gain) {
  static char tick_num = 0;
  uart_printf("---\n\r");
  uart_printf("tick: %d\n\r", tick_num++);
  if (movement == UP) {
    uart_printf("UP\n\r");
  } else if (movement == DOWN) {
    uart_printf("DOWN\n\r");
  } else if (movement == NOP) {
    uart_printf("NOP\n\r");
  } else {
    uart_printf("Invalid movement cmd\n\r");
  }
  uart_printf("vel: %d\n\r", player_ship.velocity);
  uart_printf("tug: %d\n\r", ticks_until_gain);
  uart_printf("pos: %d\n\r", player_ship.ship.y);
}

void _debug_invader_tick() {
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (invader_mobs[i].status == STATUS_ALIVE) {
      uart_printf("---\n\r");
      uart_printf("invader: %d\n\r", i);
      uart_printf("ypos: %d\t", invader_mobs[i].invader.y);
      uart_printf("xpos: %d\n\r", invader_mobs[i].invader.x);
    }
  }
  uart_printf("-----END TICK-----\n\r");
}
#endif

/* FIXME: Visually it seems like it's faster for the ship to move down
   than up. Test with print statements if that's accurate, and if so,
   fix it. */
signed char ship_tick(invader_movecmd_t movement) {
  static char ticks_until_gain = PLAYER_VELOCITY_TICKS_PER_GAIN;
  /* Change velocity based on direction cmd, also decrease mag if NOP so it stops naturally */
  if (movement == UP && ticks_until_gain <= 1) {
    player_ship.velocity -= PLAYER_VELOCITY_GAIN_PER_TICK;
    ticks_until_gain = PLAYER_VELOCITY_TICKS_PER_GAIN;
  }
  else if (movement == DOWN && ticks_until_gain <= 1) {
    player_ship.velocity += PLAYER_VELOCITY_GAIN_PER_TICK;
    ticks_until_gain = PLAYER_VELOCITY_TICKS_PER_GAIN;
  } else if (movement == NOP) {
    player_ship.velocity = math_mag_decrease(player_ship.velocity, PLAYER_VELOCITY_LOSS_PER_TICK);
    ticks_until_gain = PLAYER_VELOCITY_TICKS_PER_GAIN;
  } else {
    ticks_until_gain--;
  }
  /* Ensure |velocity| <= MAX_VELOCITY */
  if (math_absolute(player_ship.velocity) > PLAYER_MAX_VELOCITY) player_ship.velocity = math_mag_set(player_ship.velocity, PLAYER_MAX_VELOCITY);

  /* Change y position based on velocity */
  player_ship.ship.y += player_ship.velocity;
  /* Ensure the ship stays on screen */
  char ship_height = player_ship.ship.images[player_ship.ship.state]->height;
  if (player_ship.ship.y < 0) player_ship.ship.y = 0;
  if (player_ship.ship.y + ship_height > game_height) player_ship.ship.y = game_height - ship_height;

  /* Adjust state so ship is animated */
  static char ticks_until_state_change = PLAYER_SHIP_TICKS_PER_FRAME;
  if (ticks_until_state_change <= 1) {
    if (player_ship.ship.state < NUM_SHIP_FRAMES - 1) {
      player_ship.ship.state++;
    } else {
      player_ship.ship.state = 0;
    }
    ticks_until_state_change = PLAYER_SHIP_TICKS_PER_FRAME;
  } else {
    ticks_until_state_change--;
  }

  /* Debugging ship movement. */
#ifdef UART_H
  /* _debug_ship_tick(movement, ticks_until_gain); */
#endif

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

signed char player_laser_tick() {
  for (unsigned char i = 0; i < MAX_PLAYER_LASERS; i++) {
    if (player_lasers[i].active == TRUE) {
      /* adjust position based on velocity */
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
    /* Actually that makes sense since the overflow occurs before the
       casting. I can always move this above the +=
       PLAYER_LASER_VELOCITY and cast before overflow occurs. Might be
       worth considering. */
    if (player_lasers[i].laser.x < 0 || player_lasers[i].laser.x > game_width) {
      player_lasers[i].active = FALSE;
    }
  }

  return 0;
}

signed char invader_spawn() {
  /* determine if we would overlap with another invader if we spawn*/
  /* if (invader_spawn_collision_check()) { */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (invader_mobs[i].status == STATUS_DEAD) {
      invader_mobs[i].status = STATUS_ALIVE;
      /* spawn on right side (high x) fully on screen at top */
      invader_mobs[i].invader.x = game_width - invader_mobs[i].invader.images[invader_mobs[i].invader.state]->width;
      invader_mobs[i].invader.y = 0;
      invader_mobs[i].direction = INVADERDIRECTION_DOWN;
      break;                  /* only spawn 1 */
    }
  }
  /* } */

  return 0;
}

signed char invader_laser_shoot(unsigned char invader_num) {
  /* Mark first empty laser as active and shoot it */
  for (unsigned char i = 0; i < MAX_INVADER_LASERS; i++) {
    if (invader_lasers[i].active == FALSE) {
      invader_lasers[i].active = TRUE;
      invader_lasers[i].laser.x = invader_mobs[invader_num].invader.x - 1;
      signed char invader_height = invader_mobs[invader_num].invader.images[invader_mobs[invader_num].invader.state]->height;
      invader_lasers[i].laser.y = invader_mobs[invader_num].invader.y + invader_height / 2;
      break;
    }
  }
  
  return 0;
}

/* decides if we should spawn invader + initializes position */
signed char invader_tick() {
  /* randomly spawn invaders */
  /* TODO: Change to < INVADER_SPAWN_CHANCE??? Same with invader_shoot? */
  static unsigned char ticks_since_spawn = 0;
  if (ticks_since_spawn++ >= INVADER_TICKS_BETWEEN_SPAWN) {
    if (random_upto(100) > 100 - INVADER_SPAWN_CHANCE) {
      invader_spawn();
      ticks_since_spawn = 0;
    }
  }
  
  /* determine if spawned invaders should shoot */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (random_upto(100) > 100 - INVADER_SHOOT_CHANCE && invader_mobs[i].status == STATUS_ALIVE) {
      invader_laser_shoot(i);
    }
  }

  /* update invader y positions (vertical) */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (invader_mobs[i].status == STATUS_ALIVE) {
      if (invader_mobs[i].direction == INVADERDIRECTION_DOWN) {
	invader_mobs[i].invader.y += INVADER_Y_SPEED;
      } else if (invader_mobs[i].direction == INVADERDIRECTION_UP) {
	invader_mobs[i].invader.y -= INVADER_Y_SPEED;
      }
    }
  }

  /* verify positions are within valid bounds. If not, we should update x and direction */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (invader_mobs[i].status == STATUS_ALIVE) {
      if (invader_mobs[i].invader.y + invader_mobs[i].invader.images[invader_mobs[i].invader.state]->height > game_height) {
	/* too far down */
	invader_mobs[i].invader.y = game_height - invader_mobs[i].invader.images[invader_mobs[i].invader.state]->height;
	invader_mobs[i].direction = INVADERDIRECTION_UP;
	invader_mobs[i].invader.x -= INVADER_X_SPEED;
      } else if (invader_mobs[i].invader.y < 0) {
	/* too far up */
	invader_mobs[i].invader.y = 0;
	invader_mobs[i].direction = INVADERDIRECTION_DOWN;
	invader_mobs[i].invader.x -= INVADER_X_SPEED;
      } 
    }
  }

  /* adjust state so invader is animated */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (invader_mobs[i].status == STATUS_ALIVE) {
      if (invader_mobs[i].invader.state < NUM_INVADER_FRAMES - 1) {
	invader_mobs[i].invader.state++;
      } else {
	invader_mobs[i].invader.state = 0;
      }
    } else if (invader_mobs[i].status == STATUS_EXPLODING) {
      if (invader_mobs[i].explosion.state < NUM_INVADER_EXPLOSION_FRAMES -1) {
	invader_mobs[i].explosion.state++;
      } else {
	invader_mobs[i].explosion.state = 0;
	invader_mobs[i].status = STATUS_DEAD;
      }
    }
  }

  /* kill invader if it goes off the left side of screen (x = 0). Shouldn't happen in practice */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    if (invader_mobs[i].status == STATUS_ALIVE) {
      /* if fully off-screen */
      if (invader_mobs[i].invader.x + invader_mobs[i].invader.images[invader_mobs[i].invader.state]->width < 0) {
	invader_mobs[i].status = STATUS_DEAD;
      }
    }
  }

#ifdef UART_H
  _debug_invader_tick();
#endif
  
  return 0;
}

signed char invader_laser_tick() {
  for (unsigned char i = 0; i < MAX_INVADER_LASERS; i++) {
    if (invader_lasers[i].active == TRUE) {
      /* adjust position based on velocity */
      invader_lasers[i].laser.x -= INVADER_LASER_VELOCITY;

      /* Adjust state so laser is animated */
      if (invader_lasers[i].laser.state < NUM_INVADER_LASER_FRAMES - 1) {
	invader_lasers[i].laser.state++;
      } else {
	invader_lasers[i].laser.state = 0;
      }
    }

    /* remove lasers that go offscreen */
    if (invader_lasers[i].laser.x < 0) {
      invader_lasers[i].active = FALSE;
    }
  }
  
  return 0;
}

/* code to explode the invader located at num */
signed char invader_explode(unsigned char num) {
  if (num >= MAX_INVADERS) return 1;
  invader_mobs[num].status = STATUS_EXPLODING;
  invader_mobs[num].explosion.x = invader_mobs[num].invader.x;
  invader_mobs[num].explosion.y = invader_mobs[num].invader.y;
  return 0;
}

/* iterate through player_lasers and invader_mobs, setting invader_mobs as dead. Return # of collisions  */
signed char check_player_laser_collisions() {
  char hits = 0;
  for (unsigned char i = 0; i < MAX_PLAYER_LASERS; i++) {
    for (unsigned char j = 0; j < MAX_INVADERS; j++) {
      if (drawable_overlap(&player_lasers[i].laser, &invader_mobs[j].invader) == TRUE
	  && invader_mobs[j].status == STATUS_ALIVE
	  && player_lasers[i].active == TRUE) {
	invader_explode(j);
	player_lasers[i].active = FALSE;
	hits++;
      }
    }
  }

  return hits;
}

/* iterate through invader_mobs and see if any hit the player ship. Return 1 if collided, else 0 */
signed char check_invader_body_collisions() {

  return 0;
}

/* iterate through invader_lasers and see if any hit player ship. Return 1 if collided, else 0 */
signed char check_invader_laser_collisions() {

  return 0;
}

/* SDCC 4.0.0 doesn't support passing structures directly, despite that
   being part of the C standard. Page 25 of sddcman.pdf. I cry every time. */
/* A "recent" (2020) revision in changelog said they removed some
   barriers regarding this. */
signed char invader_game_tick(struct InvaderCommands *commands) {
  static int score = 0;
  ship_tick(commands->movement); /* should this be combined with player_laser_shoot and player_laser_tick? */
  player_laser_shoot(commands->shoot);
  player_laser_tick();

  /* _debug_invader_tick(); */
  invader_tick();               /* combine??? */
  invader_laser_tick();

  score += check_player_laser_collisions();
  check_invader_laser_collisions();
  
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
  player_ship.status = STATUS_ALIVE;
  player_ship.ship = spaceship_init;
  
  /* Initialize player laser structs */
  for (unsigned char i = 0; i < MAX_PLAYER_LASERS; i++) {
    player_lasers[i].active = FALSE;
    struct DrawableImage player_laser_init = {.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0,
      .images = {&player_laser_image_0, &player_laser_image_1, &player_laser_image_2, &player_laser_image_3}};
    player_lasers[i].laser = player_laser_init;
  }

  /* initialize invader structs */
  for (unsigned char i = 0; i < MAX_INVADERS; i++) {
    invader_mobs[i].status = STATUS_DEAD;
    /* TODO: Support different invader "skins" by initializing to different .images, or with another trick */
    struct DrawableImage invader_init = {.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0,
      .images = {&invader_1_image_0, &invader_1_image_1}};
    struct DrawableImage invader_explosion_init = {.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0,
      .images = {&invader_explosion_image_0, &invader_explosion_image_1, &invader_explosion_image_2, &invader_explosion_image_3}};
    invader_mobs[i].invader = invader_init;
    invader_mobs[i].explosion = invader_explosion_init;
  }

  /* initialize invader laser structs */
  for (unsigned char i = 0; i < MAX_INVADER_LASERS; i++) {
    invader_lasers[i].active = FALSE;
    struct DrawableImage invader_laser_init = {.x = UNINITIALIZED, .y = UNINITIALIZED, .state = 0,
      .images = {&invader_laser_image_0, &invader_laser_image_1}};
    invader_lasers[i].laser = invader_laser_init;
  }
  
  return 0;
}

/* remove, debugging */
struct DrawableImage* debug_drawableimage_spaceship() {
  return &player_ship.ship;
}

/* remove, debugging */
struct DrawableImage* debug_drawableimage_playerlaser(unsigned char i) {
  if (i >= MAX_PLAYER_LASERS) return 0;
  if (player_lasers[i].active == TRUE) return &player_lasers[i].laser;
  return 0;
}

/* remove, debugging */
struct DrawableImage* debug_drawableimage_invader(unsigned char i) {
  if (i >= MAX_INVADERS) return 0;
  if (invader_mobs[i].status == STATUS_ALIVE) return &invader_mobs[i].invader;
  if (invader_mobs[i].status == STATUS_EXPLODING) return &invader_mobs[i].explosion;
  return 0;
}

/* remove, debugging */
struct DrawableImage* debug_drawableimage_invaderlaser(unsigned char i) {
  if (i >= MAX_INVADER_LASERS) return 0;
  if (invader_lasers[i].active == TRUE) return &invader_lasers[i].laser;
  return 0;
}

