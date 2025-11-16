# Architecture
ARCH ?= i386

# Directories
export PROJECT_ROOT_DIR := $(abspath .)
export KERNEL_DIR := $(PROJECT_ROOT_DIR)/kernel
export BUILD_DIR := $(PROJECT_ROOT_DIR)/build/$(ARCH)

ARCH_DIR := arch/$(ARCH)

# Output
export OUTPUT := $(BUILD_DIR)/bergos.img

# Targets
all: $(OUTPUT)

$(OUTPUT): $(ARCH_DIR)
	$(MAKE) -C $(ARCH_DIR)

run: $(OUTPUT)
	$(MAKE) -C $(ARCH_DIR) run

.PHONY: clean

clean:
	@rm -rf $(BUILD_DIR)
