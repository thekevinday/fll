/**
 * FLL - Level 3
 *
 * Project: Init
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the FLL Init program.
 */
#include "init.h"
#include "private-init.h"

#ifdef __cplusplus
extern "C" {
#endif

// version printed may be used by scripts, so this will only print the version number and a newline, no extra information or colors
#ifndef _di_init_print_version_
  f_return_status init_print_version(const init_data_t data) {
    printf("%s\n", init_version);

    return F_none;
  }
#endif // _di_init_print_version_

#ifndef _di_init_print_help_
  f_return_status init_print_help(const fl_color_context_t context) {
    fll_program_print_help_header(context, init_name_long, init_version);

    fll_program_print_help_option(context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");
    fll_program_print_help_option(context, f_console_standard_short_debug, f_console_standard_long_debug, f_console_symbol_short_disable, f_console_symbol_long_disable, " Enable debugging.");

    printf("%c", f_string_eol[0]);

    fll_program_print_help_option(context, init_parameter_no_prepare_short_name, init_parameter_no_prepare_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, " Do not attempt to process kernel command line or perform any boot-time specific preparations.");
    fll_program_print_help_option(context, init_parameter_runlevel_short_name, init_parameter_runlevel_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, " Specify a custom run level, ignoring the kernel command line runlevel argument.");

    fll_program_print_help_usage(context, init_name, "");

    return F_none;
  }
#endif // _di_init_print_help_

#ifndef _di_init_main_
  f_return_status init_main(const f_console_arguments_t arguments, init_data_t *data) {
    f_status_t status  = F_none;
    int8_t run_level[init_kernel_runlevel_buffer];

    memset(run_level, 0, init_kernel_runlevel_buffer);

    unsigned short do_socket_file = F_true;
    unsigned short do_socket_port = F_false;

    {
      f_console_parameters_t parameters = { data->parameters, init_total_parameters };
      f_console_parameter_id_t ids[3] = { init_parameter_no_color, init_parameter_light, init_parameter_dark };
      f_console_parameter_ids_t choices = { ids, 3 };

      status = fll_program_parameter_process(arguments, parameters, choices, F_true, &data->remaining, &data->context);

      if (F_status_is_error(status)) {
        // @todo: init_delete_data(data);
        return F_status_set_error(status);
      }

      status = F_none;
    }

    if (data->parameters[init_parameter_runlevel].result == f_console_result_found) {
      const unsigned int parameter_length = strlen(arguments.argv[data->parameters[init_parameter_runlevel].additional.array[0]]);

      // if the run_level value is greater than the static buffer size, ignore the entire string rather than process a cut off value.
      if (parameter_length > 0 && parameter_length < init_kernel_runlevel_buffer) {
        strncpy((char *) &run_level, arguments.argv[data->parameters[init_parameter_runlevel].additional.array[0]], parameter_length);
      }
    }


    // before doing anything make sure that the rootfs has been properly setup.
    if (data->parameters[init_parameter_no_prepare].result == f_console_result_none) {
      //init_prepare_system(&run_level);
    }

    // make sure appropriate required directories exist.
    //init_prepare_init();


    // attempt to load the main rule before forking and starting child processes.
    {
      // @todo: should this pre-scan the main rule file to see if there is a custom chroot command, if so, change behavior to process rules and then chroot into a new system (cleaning up resources as much as possible before doing chroot) (don't fork child processes?)?
      // 1) check the last object for a chroot command in reverse order.
      //   - if the chroot fails then additional rules may apply. the chroot command does not have to be the last command.
      // 2) if chroot is not specified, then continue onto code below.
      // 3) if chroot is specified, then execute rules directly and exit this process on success (via chroot command).
      // 4) if chroot is specified, but chroot fails, then continue processing rules and then exit this process (dropping to bash shell).
      // effectively use my initrd_init and pre_init code here.

      // @todo: init_process_main_rule();
    }


    // commented out code is an alternative method to avoid using malloc for stacks passed to clone.
    //f_char stack_services[init_stack_size_small_services];
    //f_char stack_control_file[init_stack_size_small_control_file];
    init_stack_memory stack_memory = init_stack_memory_initialize;

    //status = init_initialize_stack_memory(&stack_memory);
    if (F_status_is_error(status)) {
      // @todo: init_delete_data((*data));
      // @todo: init_delete_stack_memory(&stack_memory);
      return status;
    }

    {
      /*
      pid_t pid_services = clone(init_handler_child_services, stack_memory.services + init_stack_size_small_services, init_flags_clone, stack_memory.services);

      if (pid_services < 0) {
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Failed to clone services process (errno = %i).", errno);
      }

      pid_t pid_control_file = clone(init_handler_child_control_file, stack_memory.control_file + init_stack_size_control_file, init_flags_clone, stack_memory.control_file);

      if (pid_control_file < 0) {
        fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Failed to clone control via file process (errno = %i).", errno);
      }
    */

      // block signals
      sigset_t  signal_mask;
      siginfo_t signal_information;

      memset(&signal_mask, 0, sizeof(sigset_t));
      memset(&signal_information, 0, sizeof(siginfo_t));

      // block all signals.
      sigfillset(&signal_mask);
      sigprocmask(SIG_BLOCK, &signal_mask, 0);

      int signal_problem_count = 0;
      const int problem_count_max_signal_size = 10;

      // sit and wait for signals.
      for (;;) {
        int signal_result = sigwaitinfo(&signal_mask, &signal_information);

        if (signal_result < 0) {
          if (errno == EAGAIN) {
            // do nothing.
            continue;
          }
          else if (errno != EINTR) {
            fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: sigwaitinfo() failed (errno = %i).", errno);

            signal_problem_count++;
            if (signal_problem_count > problem_count_max_signal_size) {
              fl_color_print_line(f_type_error, data->context.error, data->context.reset, "ERROR: Max signal problem count has been reached, sleeping for a period of time.", errno);
              sleep(init_panic_signal_sleep_seconds);
              signal_problem_count = 0;
            }

            continue;
          }
        }

        signal_problem_count = 0;

        if (signal_information.si_signo == SIGHUP) {
          // @todo: close all child process connections? try using small initial memory instead?
        }
        else if (signal_information.si_signo == SIGINT) {
          // check the status of processes to see if they are still running, if not, then restart them.
        }
        else if (signal_information.si_signo == SIGQUIT || signal_information.si_signo == SIGTERM) {
          // @todo: block these or attempt to respawn init process? try using small initial memory instead?
          break;
        }
        else if (signal_information.si_signo == SIGSEGV || signal_information.si_signo == SIGBUS || signal_information.si_signo == SIGILL || signal_information.si_signo == SIGFPE) {
          // @todo: block these or attempt to respawn init process?
        }
        else if (signal_information.si_signo == SIGPWR) {
          // @todo: shutdown process?
        }
        else if (signal_information.si_signo == SIGABRT || signal_information.si_signo == SIGIOT || signal_information.si_signo == SIGXCPU) {
          // do nothing.
        }
        else if (signal_information.si_signo == SIGCHLD) {
          // @todo: restart child processes? try using large initial memory instead?
        }

        memset(&signal_information, 0, sizeof(siginfo_t));
        continue;
      } // for
    }

    // @todo: init_delete_data((*data));
    // @todo: init_delete_stack_memory(&stack_memory);
    return status;
  }
#endif // _di_init_main_

#ifdef __cplusplus
} // extern "C"
#endif
