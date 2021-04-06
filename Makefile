# http://web.mit.edu/gnu/doc/html/make_4.html
# Use -m$(family) in both compiling and linking stage
# FIXME: It seems like files aren't always recompiled when they should be. Maybe only when I change the header? Not sure.
# Adapted from https://stackoverflow.com/questions/231229
CC         :=  sdcc
LD         :=  sdcc
CFLAGS     =  -m$(family)
LDFLAGS    =  -m$(family) --out-fmt-$(bin_fmt)

# change when splitting into separate libraries
SRC_DIR    := src
BUILD_DIR  := build

SRC        := $(wildcard $(SRC_DIR)/*.c)
OBJ        := $(patsubst $(SRC_DIR)/%.c,build/%.rel,$(SRC))
INCLUDES   := $(addprefix -I,$(SRC_DIR))

family     :=  stm8
part       :=  stm8s103?3
programmer :=  stlinkv2
bin_fmt    := ihx
final_exe  := $(BUILD_DIR)/main.$(bin_fmt)

vpath %.c $(SRC_DIR)

define make-goal
$1/%.rel: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
endef

.PHONY: all clean dump flash graph_deps

# Order matters here. Can we stop that?
all: checkdirs $(final_exe)

$(final_exe): $(OBJ)
	$(LD) $(LDFLAGS) -o $(final_exe) $(OBJ)

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

# looped in case multiple build dirs becomes a thing
$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

clean:
	@rm -rf $(BUILD_DIR)

# Valid options for dump are flash, eeprom, ram, opt, or an explicit address
dump:
	stm8flash -s $(dump) -c $(programmer) -p $(part) -r $(dump).dump

flash: all
	stm8flash -c $(programmer) -p $(part) -w $(final_exe)

graph_deps:
	codeviz -r



