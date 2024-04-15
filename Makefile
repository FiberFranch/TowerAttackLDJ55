# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fornf/jams/TowerAttackLDJ55

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fornf/jams/TowerAttackLDJ55

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target package
package: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Run CPack packaging tool..."
	/usr/bin/cpack --config ./CPackConfig.cmake
.PHONY : package

# Special rule for the target package
package/fast: package
.PHONY : package/fast

# Special rule for the target package_source
package_source:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Run CPack packaging tool for source..."
	/usr/bin/cpack --config ./CPackSourceConfig.cmake /home/fornf/jams/TowerAttackLDJ55/CPackSourceConfig.cmake
.PHONY : package_source

# Special rule for the target package_source
package_source/fast: package_source
.PHONY : package_source/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fornf/jams/TowerAttackLDJ55/CMakeFiles /home/fornf/jams/TowerAttackLDJ55//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fornf/jams/TowerAttackLDJ55/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named TowerAttack

# Build rule for target.
TowerAttack: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 TowerAttack
.PHONY : TowerAttack

# fast build rule for target.
TowerAttack/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/build
.PHONY : TowerAttack/fast

#=============================================================================
# Target rules for targets named uninstall

# Build rule for target.
uninstall: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 uninstall
.PHONY : uninstall

# fast build rule for target.
uninstall/fast:
	$(MAKE) $(MAKESILENT) -f external/raylib/CMakeFiles/uninstall.dir/build.make external/raylib/CMakeFiles/uninstall.dir/build
.PHONY : uninstall/fast

#=============================================================================
# Target rules for targets named raylib

# Build rule for target.
raylib: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 raylib
.PHONY : raylib

# fast build rule for target.
raylib/fast:
	$(MAKE) $(MAKESILENT) -f external/raylib/raylib/CMakeFiles/raylib.dir/build.make external/raylib/raylib/CMakeFiles/raylib.dir/build
.PHONY : raylib/fast

#=============================================================================
# Target rules for targets named glfw

# Build rule for target.
glfw: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 glfw
.PHONY : glfw

# fast build rule for target.
glfw/fast:
	$(MAKE) $(MAKESILENT) -f external/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/build.make external/raylib/raylib/external/glfw/src/CMakeFiles/glfw.dir/build
.PHONY : glfw/fast

#=============================================================================
# Target rules for targets named update_mappings

# Build rule for target.
update_mappings: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 update_mappings
.PHONY : update_mappings

# fast build rule for target.
update_mappings/fast:
	$(MAKE) $(MAKESILENT) -f external/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build.make external/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build
.PHONY : update_mappings/fast

src/asset_loader.o: src/asset_loader.c.o
.PHONY : src/asset_loader.o

# target to build an object file
src/asset_loader.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/asset_loader.c.o
.PHONY : src/asset_loader.c.o

src/asset_loader.i: src/asset_loader.c.i
.PHONY : src/asset_loader.i

# target to preprocess a source file
src/asset_loader.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/asset_loader.c.i
.PHONY : src/asset_loader.c.i

src/asset_loader.s: src/asset_loader.c.s
.PHONY : src/asset_loader.s

# target to generate assembly for a file
src/asset_loader.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/asset_loader.c.s
.PHONY : src/asset_loader.c.s

src/grid.o: src/grid.c.o
.PHONY : src/grid.o

# target to build an object file
src/grid.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/grid.c.o
.PHONY : src/grid.c.o

src/grid.i: src/grid.c.i
.PHONY : src/grid.i

# target to preprocess a source file
src/grid.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/grid.c.i
.PHONY : src/grid.c.i

src/grid.s: src/grid.c.s
.PHONY : src/grid.s

# target to generate assembly for a file
src/grid.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/grid.c.s
.PHONY : src/grid.c.s

src/level.o: src/level.c.o
.PHONY : src/level.o

# target to build an object file
src/level.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/level.c.o
.PHONY : src/level.c.o

src/level.i: src/level.c.i
.PHONY : src/level.i

# target to preprocess a source file
src/level.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/level.c.i
.PHONY : src/level.c.i

src/level.s: src/level.c.s
.PHONY : src/level.s

# target to generate assembly for a file
src/level.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/level.c.s
.PHONY : src/level.c.s

src/main.o: src/main.c.o
.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/main.c.s
.PHONY : src/main.c.s

src/render.o: src/render.c.o
.PHONY : src/render.o

# target to build an object file
src/render.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/render.c.o
.PHONY : src/render.c.o

src/render.i: src/render.c.i
.PHONY : src/render.i

# target to preprocess a source file
src/render.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/render.c.i
.PHONY : src/render.c.i

src/render.s: src/render.c.s
.PHONY : src/render.s

# target to generate assembly for a file
src/render.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/render.c.s
.PHONY : src/render.c.s

src/unit.o: src/unit.c.o
.PHONY : src/unit.o

# target to build an object file
src/unit.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/unit.c.o
.PHONY : src/unit.c.o

src/unit.i: src/unit.c.i
.PHONY : src/unit.i

# target to preprocess a source file
src/unit.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/unit.c.i
.PHONY : src/unit.c.i

src/unit.s: src/unit.c.s
.PHONY : src/unit.s

# target to generate assembly for a file
src/unit.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/TowerAttack.dir/build.make CMakeFiles/TowerAttack.dir/src/unit.c.s
.PHONY : src/unit.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... package"
	@echo "... package_source"
	@echo "... rebuild_cache"
	@echo "... uninstall"
	@echo "... update_mappings"
	@echo "... TowerAttack"
	@echo "... glfw"
	@echo "... raylib"
	@echo "... src/asset_loader.o"
	@echo "... src/asset_loader.i"
	@echo "... src/asset_loader.s"
	@echo "... src/grid.o"
	@echo "... src/grid.i"
	@echo "... src/grid.s"
	@echo "... src/level.o"
	@echo "... src/level.i"
	@echo "... src/level.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/render.o"
	@echo "... src/render.i"
	@echo "... src/render.s"
	@echo "... src/unit.o"
	@echo "... src/unit.i"
	@echo "... src/unit.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

