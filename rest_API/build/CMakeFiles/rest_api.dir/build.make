# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /app

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /app/build

# Include any dependencies generated for this target.
include CMakeFiles/rest_api.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rest_api.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rest_api.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rest_api.dir/flags.make

CMakeFiles/rest_api.dir/src/rest_api.cc.o: CMakeFiles/rest_api.dir/flags.make
CMakeFiles/rest_api.dir/src/rest_api.cc.o: /app/src/rest_api.cc
CMakeFiles/rest_api.dir/src/rest_api.cc.o: CMakeFiles/rest_api.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rest_api.dir/src/rest_api.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rest_api.dir/src/rest_api.cc.o -MF CMakeFiles/rest_api.dir/src/rest_api.cc.o.d -o CMakeFiles/rest_api.dir/src/rest_api.cc.o -c /app/src/rest_api.cc

CMakeFiles/rest_api.dir/src/rest_api.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rest_api.dir/src/rest_api.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/rest_api.cc > CMakeFiles/rest_api.dir/src/rest_api.cc.i

CMakeFiles/rest_api.dir/src/rest_api.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rest_api.dir/src/rest_api.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/rest_api.cc -o CMakeFiles/rest_api.dir/src/rest_api.cc.s

CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o: CMakeFiles/rest_api.dir/flags.make
CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o: /app/src/rest_impl/rest_impl.cc
CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o: CMakeFiles/rest_api.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o -MF CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o.d -o CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o -c /app/src/rest_impl/rest_impl.cc

CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/rest_impl/rest_impl.cc > CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.i

CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/rest_impl/rest_impl.cc -o CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.s

CMakeFiles/rest_api.dir/src/node/node_impl.cc.o: CMakeFiles/rest_api.dir/flags.make
CMakeFiles/rest_api.dir/src/node/node_impl.cc.o: /app/src/node/node_impl.cc
CMakeFiles/rest_api.dir/src/node/node_impl.cc.o: CMakeFiles/rest_api.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rest_api.dir/src/node/node_impl.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rest_api.dir/src/node/node_impl.cc.o -MF CMakeFiles/rest_api.dir/src/node/node_impl.cc.o.d -o CMakeFiles/rest_api.dir/src/node/node_impl.cc.o -c /app/src/node/node_impl.cc

CMakeFiles/rest_api.dir/src/node/node_impl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/rest_api.dir/src/node/node_impl.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/src/node/node_impl.cc > CMakeFiles/rest_api.dir/src/node/node_impl.cc.i

CMakeFiles/rest_api.dir/src/node/node_impl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/rest_api.dir/src/node/node_impl.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/src/node/node_impl.cc -o CMakeFiles/rest_api.dir/src/node/node_impl.cc.s

# Object files for target rest_api
rest_api_OBJECTS = \
"CMakeFiles/rest_api.dir/src/rest_api.cc.o" \
"CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o" \
"CMakeFiles/rest_api.dir/src/node/node_impl.cc.o"

# External object files for target rest_api
rest_api_EXTERNAL_OBJECTS =

rest_api: CMakeFiles/rest_api.dir/src/rest_api.cc.o
rest_api: CMakeFiles/rest_api.dir/src/rest_impl/rest_impl.cc.o
rest_api: CMakeFiles/rest_api.dir/src/node/node_impl.cc.o
rest_api: CMakeFiles/rest_api.dir/build.make
rest_api: libprotolib.a
rest_api: /usr/local/lib/libprotobuf.a
rest_api: /usr/local/lib/libgrpc++.a
rest_api: /usr/local/lib/libgrpc.a
rest_api: /usr/local/lib/libabsl_strings.a
rest_api: /usr/local/lib/libabsl_synchronization.a
rest_api: /usr/local/lib/libupb_json_lib.a
rest_api: /usr/local/lib/libupb_textformat_lib.a
rest_api: /usr/local/lib/libupb_mini_descriptor_lib.a
rest_api: /usr/local/lib/libupb_wire_lib.a
rest_api: /usr/local/lib/libutf8_range_lib.a
rest_api: /usr/local/lib/libupb_message_lib.a
rest_api: /usr/local/lib/libupb_base_lib.a
rest_api: /usr/local/lib/libupb_mem_lib.a
rest_api: /usr/local/lib/libre2.a
rest_api: /usr/local/lib/libz.a
rest_api: /usr/local/lib/libabsl_statusor.a
rest_api: /usr/local/lib/libcares.a
rest_api: /usr/local/lib/libgpr.a
rest_api: /usr/local/lib/libabsl_status.a
rest_api: /usr/local/lib/libabsl_flags_internal.a
rest_api: /usr/local/lib/libabsl_flags_reflection.a
rest_api: /usr/local/lib/libabsl_raw_hash_set.a
rest_api: /usr/local/lib/libabsl_hashtablez_sampler.a
rest_api: /usr/local/lib/libabsl_flags_config.a
rest_api: /usr/local/lib/libabsl_flags_program_name.a
rest_api: /usr/local/lib/libabsl_flags_private_handle_accessor.a
rest_api: /usr/local/lib/libabsl_flags_commandlineflag.a
rest_api: /usr/local/lib/libabsl_flags_commandlineflag_internal.a
rest_api: /usr/local/lib/libabsl_flags_marshalling.a
rest_api: /usr/local/lib/libabsl_random_distributions.a
rest_api: /usr/local/lib/libabsl_random_seed_sequences.a
rest_api: /usr/local/lib/libabsl_random_internal_pool_urbg.a
rest_api: /usr/local/lib/libabsl_random_internal_randen.a
rest_api: /usr/local/lib/libabsl_random_internal_randen_hwaes.a
rest_api: /usr/local/lib/libabsl_random_internal_randen_hwaes_impl.a
rest_api: /usr/local/lib/libabsl_random_internal_randen_slow.a
rest_api: /usr/local/lib/libabsl_random_internal_platform.a
rest_api: /usr/local/lib/libabsl_random_internal_seed_material.a
rest_api: /usr/local/lib/libabsl_random_seed_gen_exception.a
rest_api: /usr/local/lib/libabsl_cord.a
rest_api: /usr/local/lib/libabsl_cordz_info.a
rest_api: /usr/local/lib/libabsl_cord_internal.a
rest_api: /usr/local/lib/libabsl_cordz_functions.a
rest_api: /usr/local/lib/libabsl_exponential_biased.a
rest_api: /usr/local/lib/libabsl_cordz_handle.a
rest_api: /usr/local/lib/libabsl_crc_cord_state.a
rest_api: /usr/local/lib/libabsl_crc32c.a
rest_api: /usr/local/lib/libabsl_crc_internal.a
rest_api: /usr/local/lib/libabsl_crc_cpu_detect.a
rest_api: /usr/local/lib/libssl.a
rest_api: /usr/local/lib/libcrypto.a
rest_api: /usr/local/lib/libaddress_sorting.a
rest_api: /usr/local/lib/libabsl_log_internal_check_op.a
rest_api: /usr/local/lib/libabsl_log_internal_conditions.a
rest_api: /usr/local/lib/libabsl_log_internal_message.a
rest_api: /usr/local/lib/libabsl_strerror.a
rest_api: /usr/local/lib/libabsl_log_internal_nullguard.a
rest_api: /usr/local/lib/libabsl_examine_stack.a
rest_api: /usr/local/lib/libabsl_log_internal_format.a
rest_api: /usr/local/lib/libabsl_str_format_internal.a
rest_api: /usr/local/lib/libabsl_log_internal_proto.a
rest_api: /usr/local/lib/libabsl_log_internal_log_sink_set.a
rest_api: /usr/local/lib/libabsl_log_globals.a
rest_api: /usr/local/lib/libabsl_hash.a
rest_api: /usr/local/lib/libabsl_city.a
rest_api: /usr/local/lib/libabsl_bad_variant_access.a
rest_api: /usr/local/lib/libabsl_low_level_hash.a
rest_api: /usr/local/lib/libabsl_log_internal_globals.a
rest_api: /usr/local/lib/libabsl_log_sink.a
rest_api: /usr/local/lib/libabsl_log_entry.a
rest_api: /usr/local/lib/libabsl_vlog_config_internal.a
rest_api: /usr/local/lib/libabsl_synchronization.a
rest_api: /usr/local/lib/libabsl_graphcycles_internal.a
rest_api: /usr/local/lib/libabsl_kernel_timeout_internal.a
rest_api: /usr/local/lib/libabsl_stacktrace.a
rest_api: /usr/local/lib/libabsl_symbolize.a
rest_api: /usr/local/lib/libabsl_malloc_internal.a
rest_api: /usr/local/lib/libabsl_debugging_internal.a
rest_api: /usr/local/lib/libabsl_demangle_internal.a
rest_api: /usr/local/lib/libabsl_demangle_rust.a
rest_api: /usr/local/lib/libabsl_decode_rust_punycode.a
rest_api: /usr/local/lib/libabsl_utf8_for_code_point.a
rest_api: /usr/local/lib/libabsl_time.a
rest_api: /usr/local/lib/libabsl_civil_time.a
rest_api: /usr/local/lib/libabsl_time_zone.a
rest_api: /usr/local/lib/libabsl_bad_optional_access.a
rest_api: /usr/local/lib/libabsl_log_internal_fnmatch.a
rest_api: /usr/local/lib/libabsl_strings.a
rest_api: /usr/local/lib/libabsl_strings_internal.a
rest_api: /usr/local/lib/libabsl_string_view.a
rest_api: /usr/local/lib/libabsl_base.a
rest_api: /usr/local/lib/libabsl_spinlock_wait.a
rest_api: /usr/local/lib/libabsl_int128.a
rest_api: /usr/local/lib/libabsl_throw_delegate.a
rest_api: /usr/local/lib/libabsl_raw_logging_internal.a
rest_api: /usr/local/lib/libabsl_log_severity.a
rest_api: /usr/local/lib/libprotobuf.a
rest_api: CMakeFiles/rest_api.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable rest_api"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rest_api.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rest_api.dir/build: rest_api
.PHONY : CMakeFiles/rest_api.dir/build

CMakeFiles/rest_api.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rest_api.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rest_api.dir/clean

CMakeFiles/rest_api.dir/depend:
	cd /app/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /app /app /app/build /app/build /app/build/CMakeFiles/rest_api.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/rest_api.dir/depend

