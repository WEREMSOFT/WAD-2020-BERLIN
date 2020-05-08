include ./makefiles/define_useful_vars.mk
include ./makefiles/dettect_os.mk
include ./makefiles/configure_static_libraries_by_os.mk

.PHONY: print_information create_folder_structure run_html_u run_html_o run_performance_test

all: print_information $(BLD_D)main_optimized.bin $(BLD_D)main_unoptimized.bin $(HTML_D)main_optimized.html $(HTML_D)main_unoptimized.html

%.o: $(SRC_D)%.c
	$(CC_COMMAND) -o $(OBJ_D)$@ $^ $(LINK_LIBS)

$(BLD_D)main_unoptimized.bin: $(SRC_D)main_unoptimized.c
	@echo "### Building $(@) START ###"
	$(CC_COMMAND) -o $@ $^ $(LINK_LIBS)
	@echo "### End ###"
	@echo ""

$(BLD_D)main_optimized.bin: $(SRC_D)main_optimized.c
	@echo "### Building $(@) START ###"
	$(CC_COMMAND) -o $@ $^ $(LINK_LIBS)
	@echo "### End ###"
	@echo ""

$(HTML_D)main_optimized.html: $(SRC_D)main_optimized.c
	$(EMSC_CC_COMMAND) -o $@ $^ $(EMSC_STATIC_LIBS_D)

$(HTML_D)main_unoptimized.html: $(SRC_D)main_unoptimized.c
	$(EMSC_CC_COMMAND) -o $@ $^ $(EMSC_STATIC_LIBS_D)

print_information:
	@echo "Dettected OS: $(DETTECTED_OS)"

create_folders:
	$(shell mkdir bin)	
	$(shell mkdir src)
	$(shell mkdir libs/include)
	$(shell mkdir libs/static)
	$(shell mkdir html)
	
clean:
	$(shell rm -r bin/*)
	$(shell rm -r html/*)

run_html_o: main_optimized.html
	$(shell emrun $(HTML_D)main_optimized.html)

run_html_u: main_unoptimized.html
	$(shell emrun $(HTML_D)main_unoptimized.html)

run_performance_test: main_unoptimized.bin main_optimized.bin
	$(shell perf stat -e task-clock,cycles,instructions,cache-references,cache-misses $(BLD_D)main_optimized.bin)
	$(shell perf stat -e task-clock,cycles,instructions,cache-references,cache-misses $(BLD_D)main_unoptimized.bin)

run_perf_log: main_unoptimized.bin main_optimized.bin
	$(shell perf record -e L1-dcache-load-misses -c 10000 -ag -- sleep 5)
	
run_both_versions: $(BLD_D)main_unoptimized.bin $(BLD_D)main_optimized.bin
	$(BLD_D)main_optimized.bin &
	$(BLD_D)main_unoptimized.bin &
	
run_unoptimized: $(BLD_D)main_unoptimized.bin
	$(shell $(BLD_D)main_unoptimized.bin)

run_optimized: $(BLD_D)main_optimized.bin
	$(shell $(BLD_D)main_optimized.bin)