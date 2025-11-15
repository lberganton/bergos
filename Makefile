# Architecture
ARCH ?= i386

# Directories
ARCH_DIR := arch/$(ARCH)
KERNEL_DIR := kernel
BUILD_DIR := build/$(ARCH)

# Output
OUTPUT := $(BUILD_DIR)/os.img

# Assembler
AS := nasm
AS_FLAGS := -felf32

# C Compiler
CC := gcc
CC_FLAGS := -std=gnu99 -m16 -Wall -Wextra -nostdlib -ffreestanding -fno-pic -fno-pie -fno-stack-protector -mno-sse -mno-sse2 -mno-mmx
CC_INCLUDES := $(addprefix -I,$(shell find  $(ARCH_DIR) $(KERNEL_DIR) -type d -name '*include'))

# Linker
LINKER_SCRIPT := $(ARCH_DIR)/linker.ld
LINKER_FLAGS := -T $(LINKER_SCRIPT)

# QEMU
QEMU := qemu-system-i386
QEMU_FLAGS := -enable-kvm -no-reboot -monitor stdio

# Sources
CC_SRCS := $(shell find $(ARCH_DIR) $(KERNEL_DIR) -type f -name '*.c')
AS_SRCS := $(shell find $(ARCH_DIR) $(KERNEL_DIR) -type f -name '*.asm')

CC_OBJS := $(patsubst %.c,%.o,$(addprefix $(BUILD_DIR)/,$(CC_SRCS)))
AS_OBJS := $(patsubst %.asm,%.o,$(addprefix $(BUILD_DIR)/,$(AS_SRCS)))

# Targets
all: $(OUTPUT)

$(OUTPUT): $(AS_OBJS) $(CC_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(LINKER_FLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(CC_INCLUDES) -c -o $@ $<

run: $(OUTPUT)
	$(QEMU) $(QEMU_FLAGS) -drive format=raw,file=$<

.PHONY: clean

clean:
	@rm -rf $(BUILD_DIR)
