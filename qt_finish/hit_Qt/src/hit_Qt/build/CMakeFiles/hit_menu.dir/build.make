# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_SOURCE_DIR = /home/sd-robot/hql_test/hit_Qt/src/hit_Qt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build

# Include any dependencies generated for this target.
include CMakeFiles/hit_menu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hit_menu.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hit_menu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hit_menu.dir/flags.make

hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp: ../resources.qrc
hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp: CMakeFiles/hit_menu_autogen.dir/AutoRcc_resources_EWIEGA46WW_Info.json
hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp: ../images/3.jpg
hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp: /usr/lib/qt5/bin/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for resources.qrc"
	/usr/bin/cmake -E cmake_autorcc /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles/hit_menu_autogen.dir/AutoRcc_resources_EWIEGA46WW_Info.json Release

CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o: hit_menu_autogen/mocs_compilation.cpp
CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o -MF CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/hit_menu_autogen/mocs_compilation.cpp

CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/hit_menu_autogen/mocs_compilation.cpp > CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.i

CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/hit_menu_autogen/mocs_compilation.cpp -o CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.s

CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o: ../src/cameraWidget.cpp
CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o -MF CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o.d -o CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/cameraWidget.cpp

CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/cameraWidget.cpp > CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.i

CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/cameraWidget.cpp -o CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.s

CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o: ../src/lidarWidget.cpp
CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o -MF CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o.d -o CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/lidarWidget.cpp

CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/lidarWidget.cpp > CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.i

CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/lidarWidget.cpp -o CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.s

CMakeFiles/hit_menu.dir/src/main.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/hit_menu.dir/src/main.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/hit_menu.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/main.cpp.o -MF CMakeFiles/hit_menu.dir/src/main.cpp.o.d -o CMakeFiles/hit_menu.dir/src/main.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/main.cpp

CMakeFiles/hit_menu.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/main.cpp > CMakeFiles/hit_menu.dir/src/main.cpp.i

CMakeFiles/hit_menu.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/main.cpp -o CMakeFiles/hit_menu.dir/src/main.cpp.s

CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o: ../src/mainWidget.cpp
CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o -MF CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o.d -o CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/mainWidget.cpp

CMakeFiles/hit_menu.dir/src/mainWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/mainWidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/mainWidget.cpp > CMakeFiles/hit_menu.dir/src/mainWidget.cpp.i

CMakeFiles/hit_menu.dir/src/mainWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/mainWidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/mainWidget.cpp -o CMakeFiles/hit_menu.dir/src/mainWidget.cpp.s

CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o: ../src/resizableitem.cpp
CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o -MF CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o.d -o CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/resizableitem.cpp

CMakeFiles/hit_menu.dir/src/resizableitem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/resizableitem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/resizableitem.cpp > CMakeFiles/hit_menu.dir/src/resizableitem.cpp.i

CMakeFiles/hit_menu.dir/src/resizableitem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/resizableitem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/resizableitem.cpp -o CMakeFiles/hit_menu.dir/src/resizableitem.cpp.s

CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o: ../src/sysLogWidegt.cpp
CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o -MF CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o.d -o CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/sysLogWidegt.cpp

CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/sysLogWidegt.cpp > CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.i

CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/sysLogWidegt.cpp -o CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.s

CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o: ../src/sysSettingWidget.cpp
CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o -MF CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o.d -o CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/sysSettingWidget.cpp

CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/sysSettingWidget.cpp > CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.i

CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/src/sysSettingWidget.cpp -o CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.s

CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o: CMakeFiles/hit_menu.dir/flags.make
CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o: hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp
CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o: CMakeFiles/hit_menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o -MF CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o.d -o CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o -c /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp

CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp > CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.i

CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp -o CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.s

# Object files for target hit_menu
hit_menu_OBJECTS = \
"CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o" \
"CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o" \
"CMakeFiles/hit_menu.dir/src/main.cpp.o" \
"CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o" \
"CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o" \
"CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o" \
"CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o" \
"CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o"

# External object files for target hit_menu
hit_menu_EXTERNAL_OBJECTS =

hit_menu: CMakeFiles/hit_menu.dir/hit_menu_autogen/mocs_compilation.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/cameraWidget.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/lidarWidget.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/main.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/mainWidget.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/resizableitem.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/sysLogWidegt.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/src/sysSettingWidget.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp.o
hit_menu: CMakeFiles/hit_menu.dir/build.make
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5Sql.so.5.15.3
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5MultimediaWidgets.so.5.15.3
hit_menu: /usr/local/lib/libpcl_apps.so
hit_menu: /usr/local/lib/libpcl_outofcore.so
hit_menu: /usr/local/lib/libpcl_people.so
hit_menu: /usr/lib/libOpenNI.so
hit_menu: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
hit_menu: /usr/lib/x86_64-linux-gnu/libOpenNI2.so
hit_menu: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
hit_menu: /usr/lib/x86_64-linux-gnu/libflann_cpp.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkWrappingTools-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkViewsQt-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkViewsInfovis-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkJava-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkTestingRendering-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingTk-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingQt-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkPythonContext2D-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingVolumeOpenGL2-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkPythonInterpreter-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingLabel-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingImage-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkParallelMPI4Py-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOVeraOut-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOTecplotTable-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOSegY-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOParallelXML-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOParallelNetCDF-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOOggTheora-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIONetCDF-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOMotionFX-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOMPIParallel-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOParallel-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOMPIImage-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOMINC-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOLSDyna-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOInfovis-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOImport-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOIOSS-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkioss-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOHDF-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOVideo-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOMovie-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOExportPDF-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOExportGL2PS-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingGL2PSOpenGL2-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOExport-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingVtkJS-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingSceneGraph-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOExodus-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOEnSight-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOCityGML-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOChemistry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOCONVERGECFD-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOCGNSReader-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOAsynchronous-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOAMR-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingStencil-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingStatistics-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingMorphological-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingMath-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingFourier-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOSQL-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkGeovisCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkInfovisLayout-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersTopology-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersSelection-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersSMP-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersPython-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersProgrammable-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersPoints-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersParallelVerdict-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersVerdict-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkverdict-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersParallelImaging-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersParallelGeometry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersImaging-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersHyperTree-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersGeneric-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersFlowPaths-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersAMR-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkDomainsParallelChemistry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersParallelMPI-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersParallel-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkDomainsChemistryOpenGL2-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkDomainsChemistry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonPython-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkWrappingPythonCore3.10-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5Multimedia.so.5.15.3
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.15.3
hit_menu: /usr/local/lib/libpcl_surface.so
hit_menu: /usr/local/lib/libpcl_keypoints.so
hit_menu: /usr/local/lib/libpcl_tracking.so
hit_menu: /usr/local/lib/libpcl_recognition.so
hit_menu: /usr/local/lib/libpcl_registration.so
hit_menu: /usr/local/lib/libpcl_stereo.so
hit_menu: /usr/local/lib/libpcl_segmentation.so
hit_menu: /usr/local/lib/libpcl_features.so
hit_menu: /usr/local/lib/libpcl_filters.so
hit_menu: /usr/local/lib/libpcl_sample_consensus.so
hit_menu: /usr/local/lib/libpcl_ml.so
hit_menu: /usr/local/lib/libpcl_visualization.so
hit_menu: /usr/local/lib/libpcl_search.so
hit_menu: /usr/local/lib/libpcl_kdtree.so
hit_menu: /usr/local/lib/libpcl_io.so
hit_menu: /usr/local/lib/libpcl_octree.so
hit_menu: /usr/lib/x86_64-linux-gnu/libpng.so
hit_menu: /usr/lib/x86_64-linux-gnu/libz.so
hit_menu: /usr/lib/libOpenNI.so
hit_menu: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
hit_menu: /usr/lib/x86_64-linux-gnu/libOpenNI2.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOPLY-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingLOD-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkViewsContext2D-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingContextOpenGL2-9.1.so.9.1.0
hit_menu: /usr/local/lib/libpcl_common.so
hit_menu: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
hit_menu: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
hit_menu: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.74.0
hit_menu: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so.1.74.0
hit_menu: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.74.0
hit_menu: /usr/lib/x86_64-linux-gnu/libqhull_r.so.8.0.2
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkChartsCore-9.1.so.9.1.0
hit_menu: /usr/lib/jvm/default-java/lib/libjawt.so
hit_menu: /usr/lib/jvm/default-java/lib/server/libjvm.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkInteractionImage-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkGUISupportQt-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.15.3
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
hit_menu: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
hit_menu: /usr/lib/x86_64-linux-gnu/libGLX.so
hit_menu: /usr/lib/x86_64-linux-gnu/libOpenGL.so
hit_menu: /usr/lib/x86_64-linux-gnu/libtheora.so
hit_menu: /usr/lib/x86_64-linux-gnu/libtheoradec.so
hit_menu: /usr/lib/x86_64-linux-gnu/libtheoraenc.so
hit_menu: /usr/lib/x86_64-linux-gnu/libogg.so
hit_menu: /usr/lib/x86_64-linux-gnu/libxml2.so
hit_menu: /usr/lib/x86_64-linux-gnu/libicuuc.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOGeometry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtklibharu-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libjsoncpp.so
hit_menu: /usr/lib/x86_64-linux-gnu/libgl2ps.so
hit_menu: /usr/lib/x86_64-linux-gnu/libpng.so
hit_menu: /usr/lib/x86_64-linux-gnu/libz.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkexodusII-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libnetcdf.so.19
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkcgns-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5.so
hit_menu: /usr/lib/x86_64-linux-gnu/hdf5/serial/libhdf5_hl.so
hit_menu: /usr/lib/x86_64-linux-gnu/libsqlite3.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkViewsCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkInteractionWidgets-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkInteractionStyle-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingAnnotation-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingContext2D-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingVolume-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingColor-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libproj.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingHybrid-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkInfovisCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOImage-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkDICOMParser-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkmetaio-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingFreeType-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libfreetype.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingGeneral-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersExtraction-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkParallelDIY-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOXML-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersStatistics-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersModeling-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersTexture-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersHybrid-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingSources-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkImagingCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkParallelMPI-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libmpi.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkParallelCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingOpenGL2-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libGLEW.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingUI-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libX11.so
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOLegacy-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkRenderingCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonColor-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersGeometry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersSources-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersGeneral-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonComputationalGeometry-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkFiltersCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkfmt-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOXMLParser-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkIOCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonExecutionModel-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonDataModel-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonTransforms-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkpugixml-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonSystem-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonMisc-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonMath-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkkissfft-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkCommonCore-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtkloguru-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libvtksys-9.1.so.9.1.0
hit_menu: /usr/lib/x86_64-linux-gnu/libtbb.so.12.5
hit_menu: /usr/lib/x86_64-linux-gnu/libpython3.10.so
hit_menu: /usr/lib/x86_64-linux-gnu/libexpat.so
hit_menu: /usr/lib/x86_64-linux-gnu/libdouble-conversion.so
hit_menu: /usr/lib/x86_64-linux-gnu/liblz4.so
hit_menu: /usr/lib/x86_64-linux-gnu/liblzma.so
hit_menu: /usr/lib/x86_64-linux-gnu/libjpeg.so
hit_menu: /usr/lib/x86_64-linux-gnu/libtiff.so
hit_menu: CMakeFiles/hit_menu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable hit_menu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hit_menu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hit_menu.dir/build: hit_menu
.PHONY : CMakeFiles/hit_menu.dir/build

CMakeFiles/hit_menu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hit_menu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hit_menu.dir/clean

CMakeFiles/hit_menu.dir/depend: hit_menu_autogen/EWIEGA46WW/qrc_resources.cpp
	cd /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sd-robot/hql_test/hit_Qt/src/hit_Qt /home/sd-robot/hql_test/hit_Qt/src/hit_Qt /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build /home/sd-robot/hql_test/hit_Qt/src/hit_Qt/build/CMakeFiles/hit_menu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hit_menu.dir/depend

