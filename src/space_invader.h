#ifndef SPACE_INVADER_H
#define SPACE_INVADER_H

#include "image.h"
#include "baseline.h"

typedef enum Movement {UP, DOWN, NOP} invader_movecmd_t;
typedef boolean_t invader_shootcmd_t;

/* Provide each gametick */
/* TODO typedef this */
struct InvaderCommands {
  invader_movecmd_t movement;
  invader_shootcmd_t shoot;
};

struct DrawableImage* get_spaceship_image();

signed char invader_game_init(unsigned char width, unsigned char height);

signed char invader_game_tick(struct InvaderCommands *commands);

struct DrawableImage * debug_drawableimage_spaceship();

struct DrawableImage * debug_drawableimage_playerlaser(unsigned char i);

struct DrawableImage * debug_drawableimage_invader(unsigned char i);

struct DrawableImage * debug_drawableimage_invaderlaser(unsigned char i);

#endif
