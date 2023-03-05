/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * The Feautureless Make System (aka fake) used as a package build tool.
 *
 * This program is intented only to build source code into binaries.
 * It specifically does not install, test, or package some project.
 * It does provide the built binaries and scripts in a consistent range for other programs to operate on.
 *
 * This currently only supports a few select languages.
 * Additional languages can be provided via explicit operations.
 *
 * The built sources are placed in the build directory with the following structure:
 *   - build/
 *     ├── data
 *     ├── documentation
 *     ├── documents
 *     ├── includes
 *     ├── libraries
 *     │   ├── script
 *     │   ├── shared
 *     │   └── static
 *     ├── objects
 *     │   ├── script
 *     │   ├── shared
 *     │   └── static
 *     ├── programs
 *     │   ├── script
 *     │   ├── shared
 *     │   └── static
 *     ├── settings
 *     └── stage
 *
 * The "data/" directory contains all file data, such as firmware or files commonly found under /usr/share in a standard GNU Linux system.
 * The "documentation/" directory contains special documentation files such as man pages.
 * The "documents/" directory contains all other documents, data, and documentation.
 * The "includes/" directory contains all include files (such as C header files).
 * The "libraries/", "objects/", and "programs/" directories contains the sub-directories "script/", "shared/", and "static/".
 * The "libraries/" directory will contain compiled libraries or library-like scripts in their respective sub-directories.
 * The "objects/" directory will contain any compile object files.
 * The "programs/" directory will contain compiled programs or program-like scripts in their respective sub-directories.
 * The "settings/" directory contains all configuration data, such as files commonly found under /etc in a standard GNU Linux system.
 * The "stage/" directory will contain build-time data.
 */
#ifndef _fake_h
#define _fake_h

// Libc includes.
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/account.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/environment.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/file.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/directory.h>
#include <fll/level_1/environment.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/file.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/fss/basic_list.h>
#include <fll/level_2/fss/extended.h>
#include <fll/level_2/path.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Featureless Make includes.
#include <program/fake/main/common/define.h>
#include <program/fake/main/common/enumeration.h>
#include <program/fake/main/common/print.h>
#include <program/fake/main/common/string.h>
#include <program/fake/main/common/type.h>
#include <program/fake/main/common.h>
#include <program/fake/main/build.h>
#include <program/fake/main/build/enumeration.h>
#include <program/fake/main/build/library.h>
#include <program/fake/main/build/load.h>
#include <program/fake/main/build/object.h>
#include <program/fake/main/build/objects.h>
#include <program/fake/main/build/print.h>
#include <program/fake/main/build/print/compile.h>
#include <program/fake/main/build/print/error.h>
#include <program/fake/main/build/print/verbose.h>
#include <program/fake/main/build/print/warning.h>
#include <program/fake/main/build/program.h>
#include <program/fake/main/build/skeleton.h>
#include <program/fake/main/build/string.h>
#include <program/fake/main/clean.h>
#include <program/fake/main/fake/path_generate.h>
#include <program/fake/main/make.h>
#include <program/fake/main/make/load_fakefile.h>
#include <program/fake/main/make/operate.h>
#include <program/fake/main/make/operate_block.h>
#include <program/fake/main/make/operate_process.h>
#include <program/fake/main/make/operate_process_type.h>
#include <program/fake/main/make/operate_validate.h>
#include <program/fake/main/make/operate_validate_type.h>
#include <program/fake/main/make/print.h>
#include <program/fake/main/make/print/error.h>
#include <program/fake/main/make/print/verbose.h>
#include <program/fake/main/make/print/warning.h>
#include <program/fake/main/print.h>
#include <program/fake/main/print/context.h>
#include <program/fake/main/print/error.h>
#include <program/fake/main/print/operation.h>
#include <program/fake/main/print/verbose.h>
#include <program/fake/main/print/warning.h>
#include <program/fake/main/skeleton.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute main program.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param setting
 *   The main program settings.
 *   Must be of type (fake_setting_t *).
 *
 *   This is used by the main thread and should not be modified within individual threads.
 *
 *   This alters setting.state.status:
 *     F_none on success.
 *     F_child if this is a child process returning.
 *
 *     F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *     F_parameter (with error bit) if main is NULL or setting is NULL.
 *
 * @param arguments
 *   The parameters passed to the process.
 */
#ifndef _di_fake_main_
  extern void fake_main(fll_program_data_t * const main, fake_setting_t * const setting);
#endif // _di_fake_main_

/**
 * Execute the given command and arguments.
 *
 * Will print the command if in verbose mode.
 *
 * @param data
 *   The program data.
 * @param environment
 *   The environment variable data.
 * @param program
 *   The program to be executed.
 * @param arguments
 *   The arguments to be passed to the program.
 * @param status
 *   The return status.
 *
 * @return
 *   The return code result from execution.
 *   A value of 1 is returned if status has the error bit set.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 */
#ifndef _di_fake_execute_
  extern int fake_execute(fake_data_t * const data, const f_string_maps_t environment, const f_string_static_t program, const f_string_statics_t arguments, f_status_t * const status);
#endif // _di_fake_execute_

/**
 * Load the contents of a file into the given buffer, handling all potential errors.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *     F_false on file not found and file is not required.
 *
 *     F_file_found_not (with error bit) if file is not found and file is required.
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_file_exists()
 *     Errors (with error bit) from: f_file_size()
 *     Errors (with error bit) from: f_file_stream_open()
 *     Errors (with error bit) from: f_file_stream_read()
 *     Errors (with error bit) from: f_string_dynamic_increase_by()
 * @param path_file
 *   The path to the file to load.
 * @param required
 *   If TRUE, then return error when file is not found.
 *   If FALSE, then return F_false when file is not found.
 * @param buffer
 *   A buffer containing the contents of the file.
 *
 * @see f_file_exists()
 * @see f_file_size()
 * @see f_file_stream_open()
 * @see f_file_stream_read()
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_fake_file_buffer_
  extern void fake_file_buffer(fake_data_t * const data, const f_string_static_t path_file, const bool required, f_string_dynamic_t * const buffer);
#endif // _di_fake_file_buffer_

/**
 * Load the contents of the standard input pipe into the given buffer, handling all potential errors.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.setting.state.status:
 *     F_none on success.
 *
 *     F_interrupt (with error bit) on interrupt signal received.
 *
 *     Errors (with error bit) from: f_file_stream_read_block()
 *     Errors (with error bit) from: f_string_dynamic_increase_by()
 * @param buffer
 *   A buffer containing the contents of the file.
 *
 * @see f_file_stream_read_block()
 * @see f_string_dynamic_increase_by()
 */
#ifndef _di_fake_pipe_buffer_
  extern void fake_pipe_buffer(fake_data_t * const data, f_string_dynamic_t * const buffer);
#endif // _di_fake_pipe_buffer_

/**
 * Validate directories and print any relating error messages.
 *
 * This should not be called for skeleton as in that case the directories probably do not exist.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_validate_parameter_paths_
  extern f_status_t fake_validate_parameter_paths(fake_data_t * const data);
#endif // _di_fake_validate_parameter_paths_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_h
