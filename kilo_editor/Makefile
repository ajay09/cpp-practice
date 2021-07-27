BUILD_DIR := build
SRC_DIR := .
CC := gcc
CFLAGS := -g -Wall -Wextra -pedantic -O0 -std=c99

# .DEFAULT_GOAL := kilo
# By default, it begins by processing the first target that does not begin with a .


build_run: kilo
# if a target is specified without an action, it simply adds a dependency to the target

.PHONY: build_run




$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)




# to create kilo it needs kilo.c
$(BUILD_DIR)/kilo: $(SRC_DIR)/kilo.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@
kilo: $(BUILD_DIR)/kilo
	$<
# build_run target is the first target and its prerequisite is kilo which is also a target.
# kilo's prerequisite is $(BUILD_DIR)/kilo target
# $(BUILD_DIR)/kilo depends on $(SRC_DIR)/kilo.c and $(BUILD_DIR)
# if kilo.c is updated then the action under  $(BUILD_DIR)/kilo  is performed
# at last the action under kilo is performed.

.PHONY: kilo




clean: clean_dir
	rm -f kilo *.o
# @ before a command => the command won't be printed on the terminal when executed.

clean_dir:
	rm -rf build


.PHONY: clean clean_dir

# target-name : dependencies
# 	action
# each target has an associated command which is run in the shell to build the target.




#
# $@ => filename representing the target
# $^ => list of dependencies
# $< => the first entry in the list of dependencies




# # Phony targets
# The clean target doesn't actually create a file named clean and thus doesn't fit
#  the pattern of targets. Clean is just a shortcut for running a command which clears
#  the project's build files.
# 
# We flag targets like this by listing them as dependencies of .PHONY which is a pseudo-target
#  that we'll never actually build.
# 
# When Make encounters a phony target it will run the associated command automatically
#  without performing any dependency checks.


#  cs 107 stanford make tutorial