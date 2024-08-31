# -*- MakeFile -*-


# Directories
TOOLS_DIR = ${TOOLS_PATH}
MSPGCC_ROOT_DIR =$(TOOLS_DIR)/msp430-gcc
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUD_DIRS =$(MSPGCC_INCLUDE_DIR)
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)
# C:\ti\ccs1280\ccs\ccs_base\DebugServer\bin
TI_CCS_DIR = $(TOOLS_DIR)/ccs1280/ccs
DEBUG_BIN_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/drivers
ADDR2LINE = $(MSPGCC_BIN_DIR)/msp430-elf-addr2line

#for memory management debugging
SIZE = $(MSPGCC_BIN_DIR)/msp430-elf-size
READELF = $(MSPGCC_BIN_DIR)/msp430-elf-readelf

BUILD_DIR = build
OBJ_DIR =$(BUILD_DIR)/$(TARGET_NAME)
SRC_DIR = $(BUILD_DIR)/build

ifneq ($(TEST),) # TEST argument
ifeq ($(findstring test_,$(TEST)),)
$(error "TEST=$(TEST) is invalid (test function must start with test_)")
else
TARGET_NAME=$(TEST)
endif
endif

# Target
TARGET_HW=sumo
TARGET_NAME=$(TARGET_HW)
TARGET = $(SRC_DIR)/$(TARGET_NAME)


# Toolchain
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc

SOURCES_WITH_HEADERS = src/drivers/io.c \
					src/drivers/led.c \
					src/drivers/mcu_init.c \
					src/common/assert_handler.c \
					src/common/ring_buffer.c \
					src/drivers/uart.c \
					external/printf.c \
					src/common/trace.c \
					src/drivers/ir_remote.c \
					src/common/enum_to_string.c \
					src/drivers/pwm.c \
					src/drivers/tb6612fng.c \


SOURCES = $(MAIN_FILE) \
		$(SOURCES_WITH_HEADERS)


OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

# Defines
TEST_DEFINE = $(addprefix -DTEST=,$(TEST))
DEFINES = \
	$(TEST_DEFINE) \
	-DPRINTF_INCLUDE_CONFIG_H \

#choice on which environment we are running compling for.
ifndef TEST
MAIN_FILE = src/main.c
else
MAIN_FILE = src/test/test.c
# Touch test.c to force rebuild every time in case TEST define changed
$(shell touch src/test/test.c)
endif

# cppcheck flags
IGNORE_FILES_FORMAT_CPPCHECK = \
	external/printf/printf.c
SOURCES_FORMAT_CPPCHECK = $(filter-out $(IGNORE_FILES_FORMAT_CPPCHECK),$(SOURCES))
CPPCHECK_FLAGS = \
	--quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unmatchedSuppression \
	--suppress=unusedFunction \
	--force $(addprefix -I,"$(INCLUD_DIRS)") \
	# --force -I"$(INCLUD_DIRS)" 

#Flags
MCU =msp430g2553
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mmcu=$(MCU) $(WFLAGS) -fshort-enums $(addprefix -I,"$(INCLUD_DIRS)") $(DEFINES) -Og -g
LFLAGS = -mmcu=$(MCU) $(addprefix -L,"$(LIB_DIRS)")


# cppcheck
CPPCHECK = cppcheck

#Build
#Linking
# $(TARGET): main.o led.o
# 	$(CC) $(LFLAGS) led.o  main.o -o $(TARGET)

# #Compiling 
# led.o: led.c led.h
# 	$(CC) $(CFLAGS) -c led.c -o led.o

#Build
#Linking
$(TARGET): $(OBJECTS) 
	@mkdir -p $(dir $@)
	$(CC) $(LFLAGS) $^ -o $@

#Compiling 
$(OBJ_DIR)/%.o: %.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

# # Compiling
# main.o: main.c led.h
# 	$(CC) $(CFLAGS) -c main.c -o main.o

# Phonies
.PHONY: all clean cppcheck tests size symbols 
all: $(TARGET)

clean:
	rm -r build

cppcheck:
	@$(CPPCHECK) $(CPPCHECK_FLAGS) $(SOURCES_FORMAT_CPPCHECK)

tests:
	@# Build all tests
	@chmod +x tools/build_tests.sh
	@tools/build_tests.sh

size: $(TARGET)
	@$(SIZE) $(TARGET)

symbols: $(TARGET)
	# List symbols table sorted by size
	@$(READELF) -s $(TARGET) | sort -n -k3

addr2line: $(TARGET)
	@$(ADDR2LINE) -e $(TARGET) $(ADDR)