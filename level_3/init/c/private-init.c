/**
 * Private source file for firewall.c.
 */
#include "init.h"
#include "private-init.h"
/*
#ifndef _di_init_rule_buffer_
  f_return_status init_rule_buffer(const init_data_t data, const f_string_t filename, f_string_dynamic_t *buffer, f_fss_objects_t *objects, f_fss_contents_t *contents) {
    f_file_t file = f_file_t_initialize;
    f_status_t status = F_none;
    f_string_quantity_t quantity = f_string_quantity_t_initialize;

    status = f_file_open(filename, 0, 0, &file);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (optional) {
        if (status == F_parameter) {
          fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: Invalid parameter when calling f_file_open().");
        } else if (status != F_file_found_not && status != F_file_open && status != F_file_descriptor) {
          fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open().", status);
        }
      } else {
        if (status == F_parameter) {
          fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: Invalid parameter when calling f_file_open().");
        } else if (status == F_file_found_not) {
          fl_color_print_line(f_type_error, data.context.set.error, "ERROR: Unable to find the file '%s'.", filename);
        } else if (status == F_file_open) {
          fl_color_print_line(f_type_error, data.context.set.error, "ERROR: Unable to open the file '%s'.", filename);
        } else if (status == F_file_descriptor) {
          fl_color_print_line(f_type_error, data.context.set.error, "ERROR: File descriptor error while trying to open the file '%s'.", filename);
        } else {
          fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_open().", status);
        }
      }

      return F_status_set_error(status);
    }

    f_macro_file_t_reset_position(quantity, file)

    fflush(stdout);
    status = f_file_read_until(file, quantity, buffer);

    f_file_close(&file.id);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_parameter) {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: Invalid parameter when calling f_file_read_until().");
      } else if (status == F_number_overflow) {
        fl_color_print_line(f_type_error, data.context.set.error, "ERROR: Integer overflow while trying to buffer the file '%s'.", filename);
      } else if (status == F_file_closed) {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: The file '%s' is no longer open.", filename);
      } else if (status == F_file_seek) {
        fl_color_print_line(f_type_error, data.context.set.error, "ERROR: A seek error occurred while accessing the file '%s'.", filename);
      } else if (status == F_file_read) {
        fl_color_print_line(f_type_error, data.context.set.error, "ERROR: A read error occurred while accessing the file '%s'.", filename);
      } else if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
      } else {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling f_file_read_until().", status);
      }

      return F_status_set_error(status);
    } else {
      f_string_range_t input = f_string_range_t_initialize;

      input.stop = buffer->used - 1;

      status = fll_fss_basic_list_read(buffer, &input, objects, contents);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_parameter) {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_list_read() for the file '%s'.", filename);
      } else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
        fl_color_print_line(f_type_error, data.context.set.error, "ERROR: No relevant data was found within the file '%s'.", filename);
      } else if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
      } else {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling fll_fss_basic_list_read() for the file '%s'.", status, filename);
      }

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_init_rule_buffer_

#ifndef _di_init_rules_process_main_
  f_return_status init_rules_process_main(const init_data_t data, const f_string_t filename, f_string_dynamic_t *buffer, f_fss_objects_t *objects, f_fss_contents_t *contents) {
    f_status_t status  = F_none;

    // @todo: resume replacing code below.
    status = fll_fss_extended_read(&buffer, input, &local->rule_objects, &local->rule_contents, 0, 0);

    if (F_status_is_error_not(status)) {
      //status = init_perform_commands(*local, *data); // @fixme

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_memory_allocation || status == F_memory_reallocation) {
          fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
        } else if (status == F_failure) {
          // the error message has already been displayed.
        } else {
          fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling firewall_perform_commands().", status);
        }

        f_macro_fss_objects_t_delete_simple(local->rule_objects);
        f_macro_fss_contents_t_delete_simple(local->rule_contents);
        return F_status_set_error(status);
      }
    }

    f_macro_fss_objects_t_delete_simple(local->rule_objects);
    f_macro_fss_contents_t_delete_simple(local->rule_contents);
    return status;
  }
#endif // _init_rules_process_main_

#ifndef _di_init_handler_child_services_
  f_return_status init_handler_child_services(void *data) {
    init_local_data *local_data = (init_local_data *) data;

    // load and process rules.

    return F_none;
  }
#endif // _di_init_handler_child_services_

#ifndef _di_init_handler_child_control_file_
  f_return_status init_handler_child_control_file(void *data) {
    init_local_data *local_data = (init_local_data *) data;

    return F_none;
  }
#endif // _di_init_handler_child_control_file_

#ifndef _di_init_initialize_stack_memory_
  f_return_status init_initialize_stack_memory(init_stack_memory *stack_memory) {
    stack_memory->services = mmap(0, init_stack_size_small_services, init_stack_protections, init_stack_flags, -1, 0);
    stack_memory->control_file = mmap(0, init_stack_size_small_control_file, init_stack_protections, init_stack_flags, -1, 0);

    if (stack_memory->services == (void *) -1) {
      return F_failure;
    }

    if (stack_memory->control_file == (void *) -1) {
      return F_failure;
    }

    return F_none;
  }
#endif // _di_init_initialize_stack_memory_

#ifndef _di_init_delete_stack_memory_
  f_return_status init_delete_stack_memory(init_stack_memory *stack_memory) {
    f_status_t status = F_none;

    if (stack_memory->services > 0) {
      if (munmap(stack_memory->services, 0) >= 0) {
        stack_memory->services = 0;
      }
      else {
        status = F_failure;
      }
    }

    if (stack_memory->control_file > 0) {
      if (munmap(stack_memory->control_file, 0) >= 0) {
        stack_memory->control_file = 0;
      }
      else {
        status = F_failure;
      }
    }

    return status;
  }
#endif // _di_init_delete_stack_memory_

#ifndef _di_init_prepare_system_
  f_return_status init_prepare_system(int8_t *run_level) {
    f_status_t status = F_none;
    f_stat stat;

    memset(&stat, 0, sizeof(f_stat));


    // create the required directories if they do not already exist and then perform appropriate mount.
    status = f_file_stat(init_paths_devices, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_devices);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " init_paths_devices);

    status = f_file_stat(init_paths_system, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_system);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " -p " init_paths_system);

    status = f_file_stat(init_paths_devices_pts, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_devices_pts);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " -t " init_paths_devices_pts);

    status = f_file_stat(init_paths_log, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_log);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " init_paths_log);

    status = f_file_stat(var_run_path, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " var_run_path);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " var_run_path);

    status = f_file_stat(mnt_path, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " mnt_path);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " mnt_path);

    status = f_file_stat(tmp_path, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " tmp_path);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " tmp_path);

    status = f_file_stat(init_paths_processes, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_processes);
      memset(&stat, 0, sizeof(f_stat));
    }

    // Look for the kernel command line to determine whether or not the proc is mounted.
    // doing this also allows for unusual circumstances where the kernel command line is not mounted but a custom kernel command line is statically provided.
    status = f_file_stat(init_kernel_command_line, &stat);

    if (status == F_file_found_not) {
      system(init_program_mount " " init_paths_processes);
    }


    // create the required devices
    system(init_program_mknod " -m 0660 " init_path_device_null " c 1 3");
    system(init_program_mknod " -m 0660 " init_path_device_zero " c 1 5");
    system(init_program_mknod " -m 0660 " init_path_device_console " c 5 1");
    system(init_program_mknod " -m 0440 " init_path_device_random " c 1 8");
    system(init_program_mknod " -m 0440 " init_path_device_urandom " c 1 9");
    system(init_program_chgrp " " init_group_process_null " " init_path_device_null);
    system(init_program_chgrp " " init_group_process_zero " " init_path_device_zero);
    system(init_program_chgrp " " init_group_process_console " " init_path_device_console);
    system(init_program_chgrp " " init_group_process_random " " init_path_device_random);
    system(init_program_chgrp " " init_group_process_urandom " " init_path_device_urandom);

    // attempt to load kernel command line, but do not stop on failure.
    if (run_level > 0 && run_level[0] != 0) {
      f_file_p kernel_command_line_file = 0;
      f_string_t kernel_command_line_string = f_string_t_initialize;
      size_t   kernel_command_line_length = 0;

      kernel_command_line_file = fopen(init_kernel_command_line, "ro");

      if (kernel_command_line_file > 0) {
        getline(&kernel_command_line_string, &kernel_command_line_length, kernel_command_line_file);

        if (kernel_command_line_file) {
          fclose(kernel_command_line_file);
        }
      }

      if (kernel_command_line_length > 0) {
        regex_t    expression;
        regmatch_t match;
        unsigned int    reg_result = 0;
        unsigned int    string_length = 0;

        reg_result = do_regex_match(&expression, &match, kernel_command_line_string, init_kernel_runlevel);

        if (reg_result == REG_OK) {
          string_length = match.rm_eo - match.rm_so - init_kernel_runlevel_ignore;

          // if the run_level value is greater than the static buffer size, ignore the entire string rather than process a cut off value.
          if (string_length > 0 && string_length < init_kernel_runlevel_buffer) {
            strncpy(run_level, kernel_command_line_string + match.rm_so + init_kernel_runlevel_ignore, string_length);
          }
        }
      }

      if (kernel_command_line_string) {
        f_status_t status_free = F_none;
        f_macro_string_t_delete(status_free, kernel_command_line_string, string_length);
      }
    }

    return F_none;
  }
#endif // _di_init_prepare_system_

#ifndef _di_init_prepare_system_
  f_return_status init_prepare_system() {
    f_status_t status = F_none;
    f_stat stat;

    memset(&stat, 0, sizeof(f_stat));

    // @fixme: this is implemented using user space tools.
    //         such a design allows for quick implementation but I consider this bad practice.
    //         work towards replacing this with custom functions.

    // create the required directories if they do not already exist and then perform appropriate mount.
    status = f_file_stat(init_paths_devices, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_devices);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " init_paths_devices);

    status = f_file_stat(init_paths_system, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_system);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " -p " init_paths_system);

    status = f_file_stat(init_paths_devices_pts, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_devices_pts);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " -t " init_paths_devices_pts);

    status = f_file_stat(init_paths_log, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_log);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " init_paths_log);

    status = f_file_stat(var_run_path, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " var_run_path);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " var_run_path);

    status = f_file_stat(mnt_path, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " mnt_path);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " mnt_path);

    status = f_file_stat(tmp_path, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " tmp_path);
      memset(&stat, 0, sizeof(f_stat));
    }

    system(init_program_mount " " tmp_path);

    // create the required devices
    system(init_program_mknod " -m 0660 " init_path_device_null " c 1 3");
    system(init_program_mknod " -m 0660 " init_path_device_zero " c 1 5");
    system(init_program_mknod " -m 0660 " init_path_device_console " c 5 1");
    system(init_program_mknod " -m 0440 " init_path_device_random " c 1 8");
    system(init_program_mknod " -m 0440 " init_path_device_urandom " c 1 9");
    system(init_program_chgrp " " init_group_process_null " " init_path_device_null);
    system(init_program_chgrp " " init_group_process_zero " " init_path_device_zero);
    system(init_program_chgrp " " init_group_process_console " " init_path_device_console);
    system(init_program_chgrp " " init_group_process_random " " init_path_device_random);
    system(init_program_chgrp " " init_group_process_urandom " " init_path_device_urandom);

    return F_none;
  }
#endif // _di_init_prepare_system_

#ifndef _di_init_prepare_init_
  f_return_status init_prepare_init() {
    f_stat stat;

    memset(&stat, 0, sizeof(f_stat));

    // @fixme: this is implemented using user space tools.
    //         such a design allows for quick implementation but I consider this bad practice.
    //         work towards replacing this with custom functions.

    status = f_file_stat(init_paths_init_run, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_init_run);
      system(init_program_chgrp " " init_group_init_run " " init_paths_init_run);
      memset(&stat, 0, sizeof(f_stat));
    }

    status = f_file_stat(init_paths_init_settings, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_init_settings);
      system(init_program_chgrp " " init_group_init_settings " " init_paths_init_settings);
      memset(&stat, 0, sizeof(f_stat));
    }

    status = f_file_stat(init_paths_init_socket, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_init_socket);
      system(init_program_chgrp " " init_group_init_socket " " init_paths_init_socket);
      memset(&stat, 0, sizeof(f_stat));
    }

    status = f_file_stat(init_paths_init_process, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_init_process);
      system(init_program_chgrp " " init_group_init_process " " init_paths_init_process);
      memset(&stat, 0, sizeof(f_stat));
    }

    status = f_file_stat(init_paths_init_log, &stat);

    if (status == F_file_found_not || status == F_status_set_error(F_directory)) {
      system(init_program_mkdir " -p " init_paths_init_log);
      system(init_program_chgrp " " init_group_init_log " " init_paths_init_log);
      memset(&stat, 0, sizeof(f_stat));
    }

    memset(&stat, 0, sizeof(f_stat));

    return F_none;
  }
#endif // _di_init_prepare_init_

#ifndef _di_init_process_main_rule_
  f_return_status init_process_main_rule(const init_data_t data, f_string_dynamic_t *buffer, init_data_t *settings) {
    f_status_t status = F_none;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
    f_string_range_t range = f_string_range_t_initialize;
    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;
    f_string_length_t position = 0;

    // load the main file into memory.
    status = init_rule_buffer(&data, init_rule_core_file, &buffer, &objects, &contents);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_parameter) {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_list_read() for the file '%s'.", init_rule_core_file);
      } else if (status == F_data_not_eos || status == F_data_not || status == F_data_not_stop) {
        fl_color_print_line(f_type_error, data.context.set.error, "ERROR: No relevant data was found within the file '%s'.", init_rule_core_file);
      } else if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
      } else {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling fll_fss_basic_list_read() for the file '%s'.", status, init_rule_core_file);
      }

      f_macro_string_dynamic_t_delete(buffer);
      f_macro_fss_objects_t_delete(objects);
      f_macro_fss_contents_t_delete(contents);
      return status;
    }

    while (position < objects.used) {
      location.start = objects.array[position].start;
      location.stop = objects.array[position].stop;

      status = fll_fss_extended_read(&buffer, &location, &objects, &contents, 0, 0);

      position++;
    } // while

    // @fixme: resume here, below is just notes and copy&pasted code as examples/reminders.

    /*
    status = fll_fss_extended_read(&buffer, &location, &objects, &contents, 0, 0);

    if (F_status_is_error(status_process)) {
      if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
      }
      else {
        fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling init_load_main_rule().", status);
      }

      // @todo: init_delete_data((*data));
      // @todo: init_delete_stack_memory(&stack_memory);
      return status_process;
    }
    */


    /*
    f_status_t status  = F_none;

    status = fll_fss_extended_read(buffer, location, objects, contents, 0, 0);

    if (F_status_is_error_not(status)) {
      // @todo: process objects and contents.
      // execute individual processes.

      if (F_status_is_error(status)) {
        status = F_status_set_fine(status);

        if (status == F_memory_allocation || status == F_memory_reallocation) {
          fl_color_print_line(f_type_error, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
        } else if (status == F_failure) {
          // the error message has already been displayed.
        } else {
          fl_color_print_line(f_type_error, data.context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling firewall_perform_commands().", status);
        }

        f_macro_fss_objects_t_delete_simple((*rule_objects));
        f_macro_fss_contents_t_delete_simple((*rule_contents));
        return F_status_set_error(status);
      }
    }
    else {
      if (status == F_memory_allocation || status == F_memory_reallocation) {
        fl_color_print_line(f_type_error, context.set.error, "CRITICAL ERROR: Unable to allocate memory.");
      }
      else {
        fl_color_print_line(f_type_error, context.set.error, "INTERNAL ERROR: An unhandled error (%u) has occurred while calling init_load_main_rule().", status);
      }
    }

    f_macro_fss_objects_t_delete_simple((*rule_objects));
    f_macro_fss_contents_t_delete_simple((*rule_contents));
    */
/*
    f_macro_string_dynamic_t_delete(buffer);
    f_macro_fss_objects_t_delete(objects);
    f_macro_fss_contents_t_delete(contents);
    return status;
  }
#endif // _di_init_process_main_rule_
  */
