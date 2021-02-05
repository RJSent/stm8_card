
#ifndef SSD1306_H
#define SSD1306_H

#define SSD1306_I2C_ADDRESS 0x3C	/* 0x3C xor 0x3D for SSD1306 and SSD1306B. Determined by D/C# pin */

/* Control byte format: CO_DC_000000 */
/* CO = continuation bit */
/* DC = Data/command selection bit */
#define CO_DATA		0	/* 0 means rest of the transmission is data only. Continuation bit. */
#define DC_COMMAND	0
#define DC_DATA		1
#endif
