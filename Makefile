family = stm8
part = stm8s103?3
programmer = stlinkv2
output = --out-fmt-ihx

all: main.rel baseline.rel blink_code.rel gpio.rel 
	sdcc -m$(family) --out-fmt-ihx -o main.ihx main.rel baseline.rel blink_code.rel gpio.rel

main.rel: main.c # Careful to include -m$(family) in both compiling and linking stage
	sdcc -m$(family) -c main.c

baseline.rel: baseline.c
	sdcc -m$(family) -c baseline.c

blink_code.rel: blink_code.c
	sdcc -m$(family) -c blink_code.c

gpio.rel: gpio.c
	sdcc -m$(family) -c gpio.c

flash: all
	stm8flash -c $(programmer) -p $(part) -w main.ihx

clean:
	rm -f *.asm *.cdb *.lk *.lst *.map *.rel *.rst *.sym *.mem *.ihx
