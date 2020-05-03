include ./makefiles/define_useful_vars.mk
include ./makefiles/dettect_os.mk
include ./makefiles/configure_static_libraries_by_os.mk

.PHONY: print_information create_folder_structure run_html_u run_html_o run_performance_test

all: print_information main_optimized.bin main_unoptimized.bin main_optimized.html main_unoptimized.html

%.o: $(SRC_D)%.c
	$(CC_COMMAND) -o $(OBJ_D)$@ $^ $(LINK_LIBS)

%.bin: $(SRC_D)%.c
	@echo "### Building $(@) START ###"
	$(CC_COMMAND) -o $(BLD_D)$@ $^ $(LINK_LIBS)
	@echo "### End ###"
	@echo ""

%.html: $(SRC_D)%.c 
	$(EMSC_CC_COMMAND) -o $(HTML_D)$@ $^ $(EMSC_STATIC_LIBS_D)

main_optimized: main_optimized.o
	 $(CC_COMMAND) -o $(BLD_D)$@ $(OBJ_D)$^ $(LINK_LIBS) -v

$(BLD_D)main_unoptimized: $(SRC_D)main_unoptimized.c
	 $(CC_COMMAND) -o $@ $^ $(LINK_LIBS)

print_information:
	@echo "Dettected OS: $(DETTECTED_OS)"

create_folders:
	$(shell mkdir bin)	
	$(shell mkdir obj)
	$(shell mkdir src)
	$(shell mkdir libs/include)
	$(shell mkdir libs/static)
	$(shell mkdir html)
	
clean:
	$(shell rm -r bin/*)
	$(shell rm -r obj/*)
	$(shell rm -r html/*)

run_html_o: main_optimized.html
	$(shell emrun $(HTML_D)main_optimized.html)

run_html_u: main_unoptimized.html
	$(shell emrun $(HTML_D)main_unoptimized.html)

dummy: #main_unoptimized.html main_optimized.html
	# $(shell emrun $(HTML_D)main_optimized.html)

run_performance_test: main_unoptimized.bin main_optimized.bin
	$(shell perf stat -e task-clock,cycles,instructions,cache-references,cache-misses $(BLD_D)main_optimized.bin)
	$(shell perf stat -e task-clock,cycles,instructions,cache-references,cache-misses $(BLD_D)main_unoptimized.bin)
	
run_both_versions: main_unoptimized.bin main_optimized.bin
	$(shell $(BLD_D)main_optimized.bin & $(BLD_D)main_unoptimized.bin &)
	
