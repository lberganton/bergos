# Directories
SRC_DIR := src

# Output
OUTPUT_SIZE := 64k

# Assembler
AS := nasm
AS_FLAGS := -felf32

# C Compiler
CC := gcc
CC_FLAGS := -std=gnu99 -m32 -Wall -Wextra -nostdlib -ffreestanding -fno-pic -fno-pie -fno-stack-protector -mno-sse -mno-sse2 -mno-mmx
CC_INCLUDES := $(addprefix -I,$(dir $(shell find $(SRC_DIR) $(KERNEL_DIR) -type f -name '*.h')))

# Linker
LINKER_SCRIPT := linker.ld
LINKER_FLAGS := -T $(LINKER_SCRIPT)

# QEMU
QEMU := qemu-system-i386
QEMU_FLAGS := -enable-kvm -no-reboot -monitor stdio

# Sources
CC_SRCS := $(shell find $(SRC_DIR) $(KERNEL_DIR) -type f -name '*.c')
AS_SRCS := $(shell find $(SRC_DIR) -type f -name '*.asm')

CC_OBJS := $(patsubst %.c,%.o,$(addprefix $(BUILD_DIR)/,$(CC_SRCS)))
AS_OBJS := $(patsubst %.asm,%.o,$(addprefix $(BUILD_DIR)/,$(AS_SRCS)))

# Targets
all: $(OUTPUT)

$(OUTPUT): $(AS_OBJS) $(CC_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(LINKER_FLAGS) -o $@ $^
	@truncate --size=$(OUTPUT_SIZE) $@

$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $(CC_INCLUDES) -c -o $@ $<

run: $(OUTPUT)
	$(QEMU) $(QEMU_FLAGS) -drive format=raw,file=$<
