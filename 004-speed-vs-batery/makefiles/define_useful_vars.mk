# Define some usefull variables
CC := gcc
SRC_D := src/
BLD_D := bin/
OBJ_D := obj/
ASST_D := assets/
LIBS_D := libs/
INCLUDE_D := -I$(LIBS_D)include/
STATIC_LIBS_D := -L$(LIBS_D)static/
CFLAGS := -g -Wall -std=c99
