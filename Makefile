# http://web.mit.edu/gnu/doc/html/make_4.html
# Use -m$(family) in both compiling and linking stage
# FIXME: It seems like files aren't always recompiled when they should be. Maybe only when I change the header? Not sure.
CC = sdcc
CFLAGS = -m$(family)
LDFLAGS = -m$(family) --out-fmt-$(bin_fmt)
objects := $(patsubst %.c,%.rel,$(wildcard *.c))

family = stm8
part = stm8s103?3
programmer = stlinkv2
bin_fmt = ihx
final_exe = main.$(bin_fmt)

all: $(final_exe)

$(final_exe): $(objects)
	$(CC) $(LDFLAGS) -o $(final_exe) $(objects)

%.rel : %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@

main.rel: main.c
	$(CC) -c $(CFLAGS) $< -o $@

flash: $(final_exe)
	stm8flash -c $(programmer) -p $(part) -w $(final_exe)

# Valid options for dump are flash, eeprom, ram, opt, or an explicit address
dump:
	stm8flash -s $(dump) -c $(programmer) -p $(part) -r $(dump).dump

graph_deps:
	codeviz -r

clean:
	rm -f *.asm *.cdb *.lk *.lst *.map *.rel *.rst *.sym *.mem *.ihx *.elf *.s19 *.dump codeviz.*
