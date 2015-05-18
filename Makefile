###
# This makefile is prepared to compile
# OpenGL/SDL programs on Mac OS (Yosemite)
###

### FRIENDLY REMINDERS :
# 	(Use homebrew to install libs : http://brew.sh)
#	(before including OpenGL check #ifdef __APPLE__ !)
## #

APP_BIN = thomas_Was_Alone
LIBS = -lm -L/usr/X11R6/lib -lSDL -lSDLmain -lSDL_image
CC = gcc
CFLAGS = -Wall
INCLUDES = -I/usr/X11R6/include -framework Cocoa -framework OpenGL
 
SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = 

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	#@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH) $(APP_BIN) $(OBJ_FILES) $(LIBS) $(INCLUDES) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)$(APP_BIN)
	@echo cleaned .o files and executable !
