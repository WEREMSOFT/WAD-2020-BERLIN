# Define some usefull variables
CC := gcc
SRC_D := src/
BLD_D := bin/
OBJ_D := obj/
ASST_D := assets/
LIBS_D := libs/
HTML_D := html/
INCLUDE_D := -I$(LIBS_D)include/
STATIC_LIBS_D := -L$(LIBS_D)static/
CFLAGS := -g -Wall -std=c99

RAYLIB_PATH := /Users/pabloweremczuk/Documents/Proyectos/c/raylib
EMSC_CFLAGS := -O2 -s -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 -g4 -s USE_GLFW=3 -s TOTAL_MEMORY=67108864 -v -D PLATFORM_WEB
EMSC_CC := emcc
EMSC_STATIC_LIBS_D := $(LIBS_D)static/libraylib.bc
