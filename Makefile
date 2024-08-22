# -*- MakeFile -*-


# Directories
TOOLS_DIR = ${TOOLS_PATH}
MSPGCC_ROOT_DIR =$(TOOLS_DIR)/msp430-gcc
MSPGCC_BIN_DIR = $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include
INCLUD_DIRS =$(MSPGCC_INCLUDE_DIR)
LIB_DIRS = $(MSPGCC_INCLUDE_DIR)

BUILD_DIR = build
OBJ_DIR =$(BUILD_DIR)/obj
SRC_DIR = $(BUILD_DIR)/build


# Toolchain
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc

SOURCES = src/main.c src/app/led.c 

OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

#Flags
MCU =msp430g2553
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mmcu=$(MCU) $(WFLAGS) $(addprefix -I,"$(INCLUD_DIRS)") -Og -g
LFLAGS = -mmcu=$(MCU) $(addprefix -L,"$(LIB_DIRS)")

# Target
TARGET = $(SRC_DIR)/blinky

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
.PHONY: all clean cppcheck
all: $(TARGET)

clean:
	rm -r build

cppcheck:
	@$(CPPCHECK) --quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--force -I"$(INCLUD_DIRS)" \
	$(SOURCES)
