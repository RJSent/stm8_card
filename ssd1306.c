
#include "ssd1306.h"

/* Control byte format: CO_DC_000000 */
/* CO = continuation bit */
/* DC = Data/command selection bit */
#define CO_BOTH		1
#define CO_DATA		0	/* 0 means rest of the transmission is data only. Continuation bit. */
#define DC_COMMAND	0       /* Next byte transmitted is command */
#define DC_DATA		1       /* Next byte transmitted is data */
