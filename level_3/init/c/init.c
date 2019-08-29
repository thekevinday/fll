/* FLL - Level 3
 * Project:       Firewall
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_3/init.h>
#include "private-init.h"

#ifdef __cplusplus
extern "C" {
#endif

// version printed may be used by scripts, so this will only print the version number and a newline, no extra information or colors
#ifndef _di_init_print_version_
  f_return_status init_print_version(const init_argument argument) {
    printf("%s\n", init_version);

    return f_none;
  }
#endif // _di_init_print_version_

#ifndef _di_init_print_help_
  f_return_status init_print_help(const init_argument argument) {
    printf("\n");
    fl_print_color(f_standard_output, argument.context.title, argument.context.reset, " %s", init_name_long);

    printf("\n");
    fl_print_color(f_standard_output, argument.context.notable, argument.context.reset, "  Version %s", init_version);

    printf("\n\n");
    fl_print_color(f_standard_output, argument.context.important, argument.context.reset, " Available Options: ");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_help);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_help);
    printf("      Print this help message");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_light);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_light);
    printf("     Output using colors that show up better on light backgrounds");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_no_color);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_no_color);
    printf("  Do not output in color");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_version);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_version);
    printf("   Print only the version number");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_debug);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_debug);
    printf("   Enable debugging");

    printf("\n  %s", init_parameter_no_prepare_short_name);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_debug);

    printf(", %s", init_parameter_no_prepare_long_name);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_debug);
    printf("   Do not attempt to process kernel command line or perform any boot-time specific preparations.");

    printf("\n  %s", init_parameter_runlevel_short_name);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_short_debug);

    printf(", %s", init_parameter_runlevel_long_name);
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, f_console_standard_long_debug);
    printf("   Specify a custom run level, ignoring the kernel command line runlevel argument.");

    printf("\n\n");
    fl_print_color(f_standard_output, argument.context.important, argument.context.reset, " Usage: ");

    printf("\n  ");
    fl_print_color(f_standard_output, argument.context.standout, argument.context.reset, init_name);

    printf("  ");
    fl_print_color(f_standard_output, argument.context.notable, argument.context.reset, "[");

    printf(" options ");
    fl_print_color(f_standard_output, argument.context.notable, argument.context.reset, "]");

    printf("\n\n");

    return f_none;
  }
#endif // _di_init_print_help_

#ifndef _di_init_main_
  f_return_status init_main(const f_s_int argc, const f_string argv[], init_argument *argument) {
    f_status status  = f_none;
    f_status status2 = f_none;
    f_autochar run_level[init_kernel_runlevel_buffer];

    memset(run_level, 0, sizeof(f_autochar) * init_kernel_runlevel_buffer);

    f_u_short do_socket_file = f_true;
    f_u_short do_socket_port = f_false;

    status = fl_process_parameters(argc, argv, argument->parameters, init_total_parameters, &argument->remaining);

    // load colors when not told to show no colors
    if (argument->parameters[init_parameter_no_color].result == f_console_result_none) {
      fl_new_color_context(status2, argument->context);

      if (status2 == f_none) {
        fll_colors_load_context(&argument->context, argument->parameters[init_parameter_light].result == f_console_result_found);
      } else {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        init_delete_argument((*argument));
        return status2;
      }
    }

    if (f_error_is_error(status)) {
      status = f_error_set_fine(status);

      if (status == f_no_data) {
        fl_print_color_line(f_standard_error, argument->context.error, argument->context.reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      } else if (status == f_allocation_error || status == f_reallocation_error) {
        fl_print_color_line(f_standard_error, argument->context.error, argument->context.reset, "CRITICAL ERROR: unable to allocate memory");
      } else if (f_error_set_fine(status) == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, argument->context.error, argument->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_process_parameters()");
      } else {
        fl_print_color_line(f_standard_error, argument->context.error, argument->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_process_parameters()", f_error_set_error(status));
      }

      init_delete_argument((*argument));
      return f_error_set_error(status);
    }


    if (argument->parameters[init_parameter_runlevel].result == f_console_result_found) {
      const f_u_int parameter_length = strlen(argv[argument->parameters[init_parameter_runlevel].additional.array[0]]);

      // if the run_level value is greater than the static buffer size, ignore the entire string rather than process a cut off value.
      if (parameter_length > 0 && parameter_length < init_kernel_runlevel_buffer) {
        strncpy(&run_level, argv[argument->parameters[init_parameter_runlevel].additional.array[0]], parameter_length);
      }
    }


    // before doing anything make sure that the rootfs has been properly setup.
    if (argument->parameters[init_parameter_no_prepare].result == f_console_result_none) {
      init_prepare_system(&run_level);
    }

    // make sure appropriate required directories exist.
    init_prepare_init();


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

    status = init_initialize_stack_memory(&stack_memory);
    if (f_error_is_error(status)) {
      init_delete_argument((*argument));
      init_delete_stack_memory(&stack_memory);
      return status;
    }

    {
      f_pid_t pid_services = clone(init_handler_child_services, stack_memory.services + init_stack_size_services, init_flags_clone, stack_memory.services);

      if (pid_services < 0) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to clone services process (errno = %i).", errno);
      }

      f_pid_t pid_control_file = clone(init_handler_child_control_file, stack_memory.control_file + init_stack_size_control_file, init_flags_clone, stack_memory.control_file);

      if (pid_control_file < 0) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to clone control via file process (errno = %i).", errno);
      }


      // block signals
      f_sigset_t  signal_mask;
      f_siginfo_t signal_information;

      memset(&signal_mask, 0, sizeof(f_sigset_t));
      memset(&signal_information_parent, 0, sizeof(f_siginfo_t));

      // block all signals.
      sigfillset(&signal_mask);
      sigprocmask(SIG_BLOCK, &signal_mask, 0);


      // sit and wait for signals.
      for (;;) {
        signal_result = sigwaitinfo(&signal_mask, &signal_information);

        if (signal_result < 0) {
          if (errno == EAGAIN) {
            // do nothing.
            continue;
          }
          else if (errno != EINTR) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: sigwaitinfo() failed (errno = %i).", errno);

            signal_problem_count++;
            if (signal_problem_count > PROBLEM_COUNT_MAX_SIGNAL_SIZE) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: max signal problem count has been reached, sleeping for a period of time.", errno);
              sleep(init_panic_signal_sleep_seconds);
              signal_problem_count = 0;
            }

            continue;
          }
        }

        signal_problem_count = 0;

        if (signal_information_parent.si_signo == SIGHUP) {
          // @todo: close all child process connections? try using small initial memory instead?
        }
        else if (signal_information_parent.si_signo == SIGINT {
          // check the status of processes to see if they are still running, if not, then restart them.
        }
        else if (signal_information_parent.si_signo == SIGQUIT || signal_information_parent.si_signo == SIGTERM) {
          // @todo: block these or attempt to respawn init process? try using small initial memory instead?
          break;
        }
        else if (signal_information_parent.si_signo == SIGSEGV || signal_information_parent.si_signo == SIGBUS || signal_information_parent.si_signo == SIGILL || signal_information_parent.si_signo == SIGFPE) {
          // @todo: block these or attempt to respawn init process?
        }
        else if (signal_information_parent.si_signo == SIGPWR) {
          // @todo: shutdown process?
        }
        else if (signal_information_parent.si_signo == SIGABRT || signal_information_parent.si_signo == SIGIOT || signal_information_parent.si_signo == SIGXCPU) {
          // do nothing.
        }
        else if (signal_information_parent.si_signo == SIGCHLD) {
          // @todo: restart child processes? try using large initial memory instead?
        }

        memset(&signal_information, 0, sizeof(siginfo_t));
        continue;
      } // for
    }

    init_delete_argument((*argument));
    init_delete_stack_memory(&stack_memory);
    return status;
  }
#endif // _di_init_main_

#ifdef __cplusplus
} // extern "C"
#endif
