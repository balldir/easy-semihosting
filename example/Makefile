# Project name
NAME := qemu-test

# Echo
NOECHO ?= @

# Base pas
SOURCE := .
BUILD := build

# Files
objs := main.o ../src/esem.o

IPATH += -I../src/include

# Toolchain config
TOOLCHAIN_PREFIX := arm-none-eabi-
CC := $(TOOLCHAIN_PREFIX)gcc
LD := $(TOOLCHAIN_PREFIX)ld
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy

# Core config 
ARCH := ARMv7E
CORTEX_M := 3
CORE := CM$(CORTEX_M)
CPU  := CORTEX_M$(CORTEX_M)
SOC  := STM32L1XX_XL

# Start up files
STARTUP := startup/startup_ARM$(CORE).o 
objs += $(STARTUP)

# Linker script
LD_SCRIPT := ${SOURCE}/ldscripts/gcc.ld

# Options
CONFIG_DEFINES = -D__thumb__ -D${ARCH} -D${CORE} -D${CPU} -D${SOC} \
                 -D__ARCH__=${ARCH} -D__CORE__=${CORE} -D__CPU__=${CPU} \
                 -D__SOC__=${SOC}

WARN_FLAGS = -Wall -Wextra -Wno-unused-function \
             -Wno-multichar -Wextra -Wno-comment\
             -Wlogical-op -Werror=logical-op -Wno-main \
             -Wno-implicit-function-declaration # it's better to remove it later
              
CFLAGS := -Os -mthumb -nostdlib\
          -mcpu=cortex-m$(CORTEX_M) \
          -D__STARTUP_CLEAR_BSS -D__START=main \
          -ffunction-sections -fdata-sections \
          -std=gnu11 $(WARN_FLAGS) $(CONFIG_DEFINES) $(IPATH) -g

ASFLAGS := $(CFLAGS)

LDFLAGS := --gc-sections,-T,$(LD_SCRIPT)

##########################################################################
OBJS := $(addprefix $(BUILD)/, $(objs))
DIR_LIST := $(dir $(OBJS))

#Rules
.PHONY : qemu-test
qemu-test : all
	qemu-system-arm -machine lm3s6965evb -semihosting -monitor null -serial null -kernel $(BUILD)/$(NAME).elf

all :dir $(BUILD)/$(NAME).bin Makefile 
.PHONY : all

.PHONY : dir
dir:
	$(NOECHO) echo "Creating dir tree $< ..."
	$(NOECHO) mkdir -p $(DIR_LIST)

$(BUILD)/%.o: %.c
	$(NOECHO) echo "Compile $< ..."
	$(NOECHO) $(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S
	$(NOECHO) echo "Compile $< ..."
	$(NOECHO) $(CC) $(ASFLAGS) -c $< -o $@

$(BUILD)/$(NAME).elf: $(OBJS)
	$(NOECHO) echo "Link $@ ..."
	$(NOECHO) $(CC) $(CFLAGS) -Wl,$(LDFLAGS) -o $@ $^ 

$(BUILD)/$(NAME).bin: $(BUILD)/$(NAME).elf
	$(NOECHO) echo "Striping $< ..."
	$(NOECHO) $(OBJCOPY) -O binary $< $@

clean:
	$(NOECHO) echo "Clean up ..."
	$(NOECHO) rm -rf $(DIR_LIST)