#include "init.h"
#include "private-init.h"

/*
Use the initrd_init source to base this project off, but be a little more generic than Kevux specific.
1: mount temporary proc
2: read kernel command line, look for (use IKI syntax?):
 - setting:""
 - failsafe:"" (such as failsafe:"/bin/bash")
 - root:"" (such as root:"" (for floating root), root:"/dev/abc", root:"UUID:0000")
 - subroot:""
 - mode:"" (such as mode:"squash", mode:"squish", mode:"maintenance", mode:"classic", mode:"install")
 - run:"" (was "finalinit", such as run:"/sbin/init" or run:"/bin/bash")
 - setting_name="" (such as a name fo the settings file).
3: act based on those options.
4: create and mount floating root.
5: unmount temporary proc and anything else that is temporary.
6: perform pivot root.
7: perform chroot.
8: perform any setup tasks.
9: execute program from run:"".
10: at any point on error, print error the execute failsafe:"".

Settings should utilize/process:
- blkid, find devices (is there a blkid library?).
- mdadm, for mounting any raid devices.
- cryptsetup, for decrypting a device.
- squashfs, unsquashfs

Support ".lock" files to lock out adding custom command line parameters (such as home.lock to prevent home_device:"" from being used).
Support "settings/" or ".settings/".
Support ".sfs" loopback mounting.

process /proc/partitions, and support things like: LABEL=.
consider matching partition types as well.
Consider the "*.device" files such that they are also use IKI.
*/

#ifndef _di_init_load_failsafe_
  f_return_status init_load_failsafe(const init_data_t data) {

    return F_none;
  }
#endif // _di_init_load_failsafe_

#ifndef _di_init_load_kernel_setting_
  f_return_status init_load_kernel_setting(const init_data_t data, init_setting_kernel_t *setting_kernel) {
    f_status_t status = F_none;

    status = f_directory_exists(init_path_proc_cmdline);

    if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_directory_exists", F_true, init_path_proc_cmdline, "exists", fll_error_file_type_directory);
      return status;
    }

    if (status == F_false) {
      status = f_directory_create(init_path_proc_cmdline, f_file_mode_user_directory);

      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "f_directory_create", F_true, init_path_proc_cmdline, "create", fll_error_file_type_directory);
        return status;
      }
    }

    f_file_t command_line = f_file_t_initialize;

    // Note: this will specifically not be unmounted on error.
    mount("proc", init_path_proc_cmdline, "proc", 0, "");

    status = f_file_stream_open(init_path_proc_cmdline, 0, &command_line);

    if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_open", F_true, init_path_proc_cmdline, "open", fll_error_file_type_file);
      return status;
    }

    if (init_signal_received(data)) {
      f_file_stream_close(F_true, &command_line);
      return F_signal;
    }

    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    status = f_file_stream_read(command_line, 1, &buffer);

    if (F_status_is_error(status)) {
      fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_read", F_true, init_path_proc_cmdline, "read", fll_error_file_type_file);
    }

    if (F_status_is_error_not(status)) {
      f_string_dynamic_t cache = f_string_dynamic_t_initialize;

      // set used to 1 with size of 0 to represent that the parameter was not specified via the kernel command line.
      setting_kernel->root.used = 1;
      setting_kernel->root_group.used = 1;
      setting_kernel->root_sub.used = 1;
      setting_kernel->run.used = 1;
      setting_kernel->settings.used = 1;
      setting_kernel->settings_name.used = 1;

      const f_string_t parameter_name[] = {
        init_string_color,
        init_string_failsafe,
        init_string_mode,
        init_string_root,
        init_string_root_group,
        init_string_root_mode,
        init_string_root_size,
        init_string_root_sub,
        init_string_run,
        init_string_settings,
        init_string_settings_name,
        init_string_verbosity,
      };

      const f_string_length_t parameter_length[] = {
        init_string_color_length,
        init_string_failsafe_length,
        init_string_mode_length,
        init_string_root_length,
        init_string_root_group_length,
        init_string_root_mode_length,
        init_string_root_size_length,
        init_string_root_sub_length,
        init_string_run_length,
        init_string_settings_length,
        init_string_settings_name_length,
        init_string_verbosity_length,
      };

      f_string_dynamic_t * const parameter_value[] = {
        &cache,
        &cache,
        &cache,
        &setting_kernel->root,
        &setting_kernel->root_group,
        &cache,
        &cache,
        &setting_kernel->root_sub,
        &setting_kernel->run,
        &setting_kernel->settings,
        &setting_kernel->settings_name,
        &cache,
      };

      bool * const parameter_value_bool[] = {
        0,
        &setting_kernel->failsafe,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
      };

      uint8_t * const parameter_value_uint8[] = {
        &setting_kernel->color,
        0,
        &setting_kernel->mode,
        0,
        0,
        &setting_kernel->root_mode,
        0,
        0,
        0,
        0,
        0,
        &setting_kernel->verbosity,
      };

      // @todo: create f_metric_t, such that it is an f_number_unsigned_t with an exponent type, such as: Y (yotta), Z (zetta), E (exa), P (peta), T (Tera), G (giga), M (mega), k (kilo), h (hecto), da (deca), (none), d (deci), c (centi), m (milli), μ (micro), n (nano), p (pico), f (femto), a (atto), z (zepto), and y (yocto).
      f_number_unsigned_t * const parameter_value_number_unsigned[] = {
        0,
        0,
        0,
        0,
        0,
        0,
        &setting_kernel->root_size,
        0,
        0,
        0,
        0,
        0,
      };

      // 0 = string, 1 = yes/no, 2 = file mode, 3 = quiet, normal, verbose, or debug, 4 = light, dark, or no, 5 = init mode, 6 = size.
      const uint8_t parameter_type[] = {
        4,
        1,
        5,
        0,
        0,
        2,
        6,
        0,
        0,
        0,
        0,
        3,
      };

      f_iki_variable_t variable = f_iki_variable_t_initialize;
      f_iki_vocabulary_t vocabulary = f_iki_vocabulary_t_initialize;
      f_iki_content_t content = f_iki_content_t_initialize;

      {
        f_string_range_t range = f_macro_string_range_t_initialize(buffer.used);

        status = fl_iki_read(&buffer, &range, &variable, &vocabulary, &content);
      }

      {
        f_string_length_t i = 0;
        f_string_length_t j = 0;

        for (; i < variable.used; ++i) {

          for (j = 0; j < 12; ++j) {

            if (fl_string_dynamic_partial_compare_string(parameter_name[i], buffer, parameter_length[i], vocabulary.array[j]) == F_equal_to) {
              parameter_value[j]->used = 0;

              if (content.array[j].start <= content.array[j].stop) {
                status = fl_string_dynamic_partial_append(buffer, content.array[j], parameter_value[j]);

                if (F_status_is_error(status)) {
                  fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append", F_true);

                  i = variable.used;
                  break;
                }
              }

              if (parameter_type[i] == 0) {
                // nothing to do.
              }
              else if (parameter_type[i] == 1) {

                if (fl_string_dynamic_compare_string(init_string_yes, *parameter_value[j], init_string_yes_length) == F_equal_to) {
                  *parameter_value_bool[i] = F_true;
                }
                else if (fl_string_dynamic_compare_string(init_string_yes, *parameter_value[j], init_string_no_length) == F_equal_to) {
                  *parameter_value_bool[i] = F_false;
                }
                else {
                  // @todo: warning about invalid value (save to an array and then print after settings are processed?)
                }
              }
              else if (parameter_type[i] == 2) {
                // @todo: use same kind of logic as used in fake.
              }
              else if (parameter_type[i] == 3) {
                if (fl_string_dynamic_compare_string(init_string_quiet, *parameter_value[j], init_string_quiet_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_console_verbosity_quiet;
                }
                else if (fl_string_dynamic_compare_string(init_string_normal, *parameter_value[j], init_string_normal_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_console_verbosity_normal;
                }
                else if (fl_string_dynamic_compare_string(init_string_verbose, *parameter_value[j], init_string_verbose_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_console_verbosity_verbose;
                }
                else if (fl_string_dynamic_compare_string(init_string_debug, *parameter_value[j], init_string_debug_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_console_verbosity_debug;
                }
                else {
                  // @todo: warning about invalid value (save to an array and then print after settings are processed?)
                }
              }
              else if (parameter_type[i] == 4) {
                if (fl_string_dynamic_compare_string(init_string_dark, *parameter_value[j], init_string_dark_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_color_mode_dark;
                }
                else if (fl_string_dynamic_compare_string(init_string_light, *parameter_value[j], init_string_light_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_color_mode_light;
                }
                else if (fl_string_dynamic_compare_string(init_string_no, *parameter_value[j], init_string_no_length) == F_equal_to) {
                  *parameter_value_uint8[i] = f_color_mode_no_color;
                }
                else {
                  // @todo: warning about invalid value (save to an array and then print after settings are processed?)
                }
              }
              else if (parameter_type[i] == 5) {
                if (fl_string_dynamic_compare_string(init_string_classic, *parameter_value[j], init_string_classic_length) == F_equal_to) {
                  *parameter_value_uint8[i] = init_mode_classic;
                }
                else if (fl_string_dynamic_compare_string(init_string_custom, *parameter_value[j], init_string_custom_length) == F_equal_to) {
                  *parameter_value_uint8[i] = init_mode_custom;
                }
                else if (fl_string_dynamic_compare_string(init_string_maintenance, *parameter_value[j], init_string_maintenance_length) == F_equal_to) {
                  *parameter_value_uint8[i] = init_mode_maintenance;
                }
                else if (fl_string_dynamic_compare_string(init_string_normal, *parameter_value[j], init_string_normal_length) == F_equal_to) {
                  *parameter_value_uint8[i] = init_mode_normal;
                }
                else if (fl_string_dynamic_compare_string(init_string_squash, *parameter_value[j], init_string_squash_length) == F_equal_to) {
                  *parameter_value_uint8[i] = init_mode_squash;
                }
                else if (fl_string_dynamic_compare_string(init_string_squish, *parameter_value[j], init_string_squish_length) == F_equal_to) {
                  *parameter_value_uint8[i] = init_mode_squish;
                }
                else {
                  // @todo: warning about invalid value (save to an array and then print after settings are processed?)
                }
              }
              else if (parameter_type[i] == 6) {
                // @todo
                // fl_conversion_string_to_number_unsigned
              }
              else {
                // @todo: warning about unknown IKI in verbose mode (save to an array and then print after settings are processed?)
              }
            }
          } // for
        } // for
      }

      f_macro_iki_variable_t_delete_simple(variable);
      f_macro_iki_vocabulary_t_delete_simple(vocabulary);
      f_macro_iki_content_t_delete_simple(content);
      f_macro_string_dynamic_t_delete_simple(cache);
    }

    f_file_stream_close(F_true, &command_line);

    f_macro_string_dynamic_t_delete_simple(buffer);

    return status;
  }
#endif // _di_init_load_kernel_setting_

#ifndef _di_init_signal_read_
  f_return_status init_signal_received(const init_data_t data) {

    if (!data.signal.id) {
      return F_false;
    }

    f_status_t status = F_none;

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    status = f_signal_read(data.signal, &information);

    if (status == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fl_color_print(data.error.to.stream, data.context.set.error, "ALERT: An appropriate exit signal has been received, now aborting.");
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          }

          return F_true;
      }
    }

    return F_false;
  }
#endif // _di_init_signal_read_
