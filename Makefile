family = stm8
part = stm8s103?3
programmer = stlinkv2
output = --out-fmt-ihx

all: main.rel
	sdcc -m$(family) --out-fmt-ihx -o main.ihx main.rel

main.rel: main.c # Careful to include -m$(family) in both compiling and linking stage
	sdcc -m$(family) -c main.c

flash: all
	stm8flash -c $(programmer) -p $(part) -w main.ihx

clean:
	rm -f *.asm *.cdb *.lk *.lst *.map *.rel *.rst *.sym *.mem *.ihx
