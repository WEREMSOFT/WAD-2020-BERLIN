include ./makefiles/define_useful_vars.mk
include ./makefiles/dettect_os.mk
include ./makefiles/configure_static_libraries_by_os.mk

CC_COMMAND := $(CC) $(CFLAGS) $(INCLUDE_D) $(STATIC_LIBS_D)

.PHONY: print_information create_folder_structure

all: print_information $(BLD_D)main_optimized
	@echo "Finished"

%.o: $(SRC_D)%.c
	$(CC_COMMAND) -o $(OBJ_D)$@ $^ $(LINK_LIBS)

%.bin: $(SRC_D)%.c
	$(CC_COMMAND) -o $(BLD_D)$@ $^ $(LINK_LIBS)


main_optimized: main_optimized.o
	 $(CC_COMMAND) -o $(BLD_D)$@ $(OBJ_D)$^ $(LINK_LIBS) -v

$(BLD_D)main_unoptimized: $(SRC_D)main_unoptimized.c
	 $(CC_COMMAND) -o $@ $^ $(LINK_LIBS)

print_information:
	@echo "Dettected OS: $(DETTECTED_OS)"

create_folder_structure:
	$(shell mkdir bin)	
	$(shell mkdir obj)
	$(shell mkdir src)
	$(shell mkdir libs/include)
	$(shell mkdir libs/static)
	
clean:
	$(shell rm -r bin/*)
	$(shell rm -r obj/*)
