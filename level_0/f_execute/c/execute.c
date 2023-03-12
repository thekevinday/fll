#include "execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_execute_status_from_status_
  uint8_t f_execute_status_from_status(f_status_t status) {

    if (F_status_set_fine(status) == F_none)                        return F_execute_none;
    if (F_status_set_fine(status) == F_access)                      return F_execute_access;
    if (F_status_set_fine(status) == F_buffer)                      return F_execute_buffer;
    if (F_status_set_fine(status) == F_busy)                        return F_execute_busy;
    if (F_status_set_fine(status) == F_capability)                  return F_execute_capability;
    if (F_status_set_fine(status) == F_control_group)               return F_execute_control_group;
    if (F_status_set_fine(status) == F_child)                       return F_execute_child;
    if (F_status_set_fine(status) == F_directory_not)               return F_execute_directory_not;
    if (F_status_set_fine(status) == F_execute_not)                 return F_execute_bad;
    if (F_status_set_fine(status) == F_failure)                     return F_execute_failure;
    if (F_status_set_fine(status) == F_file_found_not)              return F_execute_file_found_not;
    if (F_status_set_fine(status) == F_file_type_directory)         return F_execute_file_type_directory;
    if (F_status_set_fine(status) == F_fork_not)                    return F_execute_fork_not;
    if (F_status_set_fine(status) == F_format_not)                  return F_execute_format_not;
    if (F_status_set_fine(status) == F_group)                       return F_execute_group;
    if (F_status_set_fine(status) == F_input_output)                return F_execute_input_output;
    if (F_status_set_fine(status) == F_limit)                       return F_execute_limit;
    if (F_status_set_fine(status) == F_loop)                        return F_execute_loop;
    if (F_status_set_fine(status) == F_memory_not)                  return F_execute_memory_not;
    if (F_status_set_fine(status) == F_name_not)                    return F_execute_name_not;
    if (F_status_set_fine(status) == F_nice)                        return F_execute_nice;
    if (F_status_set_fine(status) == F_parameter)                   return F_execute_parameter;
    if (F_status_set_fine(status) == F_pipe)                        return F_execute_pipe;
    if (F_status_set_fine(status) == F_processor)                   return F_execute_processor;
    if (F_status_set_fine(status) == F_prohibited)                  return F_execute_prohibited;
    if (F_status_set_fine(status) == F_resource_not)                return F_execute_resource_not;
    if (F_status_set_fine(status) == F_schedule)                    return F_execute_schedule;
    if (F_status_set_fine(status) == F_terminal)                    return F_execute_terminal;
    if (F_status_set_fine(status) == F_terminal_known_not)          return F_execute_terminal_known_not;
    if (F_status_set_fine(status) == F_terminal_not)                return F_execute_terminal_not;
    if (F_status_set_fine(status) == F_terminal_prohibited)         return F_execute_terminal_prohibited;
    if (F_status_set_fine(status) == F_terminal_valid_not)          return F_execute_terminal_valid_not;
    if (F_status_set_fine(status) == F_too_large)                   return F_execute_too_large;
    if (F_status_set_fine(status) == F_user)                        return F_execute_user;
    if (F_status_set_fine(status) == F_valid_not)                   return F_execute_valid_not;
    if (F_status_set_fine(status) == F_call_not)                    return F_execute_invoke_not;
    if (F_status_set_fine(status) == F_found_not)                   return F_execute_found_not;
    if (F_status_set_fine(status) == F_exit)                        return F_execute_exit_parameter;
    if (F_status_set_fine(status) == F_signal_hangup)               return F_execute_signal_hangup;
    if (F_status_set_fine(status) == F_signal_interrupt)            return F_execute_signal_interrupt;
    if (F_status_set_fine(status) == F_signal_quit)                 return F_execute_signal_quit;
    if (F_status_set_fine(status) == F_signal_illegal)              return F_execute_signal_illegal;
    if (F_status_set_fine(status) == F_signal_trap)                 return F_execute_signal_trap;
    if (F_status_set_fine(status) == F_signal_abort)                return F_execute_signal_abort;
    if (F_status_set_fine(status) == F_signal_bus_error)            return F_execute_signal_bus_error;
    if (F_status_set_fine(status) == F_signal_floating_point_error) return F_execute_signal_floating_point_error;
    if (F_status_set_fine(status) == F_signal_kill)                 return F_execute_signal_kill;
    if (F_status_set_fine(status) == F_signal_user_1)               return F_execute_signal_user_1;
    if (F_status_set_fine(status) == F_signal_segmentation_fault)   return F_execute_signal_segmentation_fault;
    if (F_status_set_fine(status) == F_signal_user_2)               return F_execute_signal_user_2;
    if (F_status_set_fine(status) == F_signal_broken_pipe)          return F_execute_signal_broken_pipe;
    if (F_status_set_fine(status) == F_signal_alarm_clock)          return F_execute_signal_alarm_clock;
    if (F_status_set_fine(status) == F_signal_termination)          return F_execute_signal_termination;
    if (F_status_set_fine(status) == F_signal_stack_fault)          return F_execute_signal_stack_fault;
    if (F_status_set_fine(status) == F_signal_child)                return F_execute_signal_child;
    if (F_status_set_fine(status) == F_signal_continue)             return F_execute_signal_continue;
    if (F_status_set_fine(status) == F_signal_stop)                 return F_execute_signal_stop;
    if (F_status_set_fine(status) == F_signal_keyboard_stop)        return F_execute_signal_keyboard_stop;
    if (F_status_set_fine(status) == F_signal_tty_in)               return F_execute_signal_tty_in;
    if (F_status_set_fine(status) == F_signal_tty_out)              return F_execute_signal_tty_out;
    if (F_status_set_fine(status) == F_signal_urgent)               return F_execute_signal_urgent;
    if (F_status_set_fine(status) == F_signal_cpu_limit)            return F_execute_signal_cpu_limit;
    if (F_status_set_fine(status) == F_signal_file_size_limit)      return F_execute_signal_file_size_limit;
    if (F_status_set_fine(status) == F_signal_virtual_alarm_clock)  return F_execute_signal_virtual_alarm_clock;
    if (F_status_set_fine(status) == F_signal_profile_alarm_clock)  return F_execute_signal_profile_alarm_clock;
    if (F_status_set_fine(status) == F_signal_window_size_change)   return F_execute_signal_window_size_change;
    if (F_status_set_fine(status) == F_signal_pollable_event)       return F_execute_signal_pollable_event;
    if (F_status_set_fine(status) == F_signal_power_failure)        return F_execute_signal_power_failure;
    if (F_status_set_fine(status) == F_signal_bad_system_call)      return F_execute_signal_bad_system_call;
    if (F_status_set_fine(status) == F_signal_reserved_32)          return F_execute_signal_reserved_32;
    if (F_status_set_fine(status) == F_signal_reserved_33)          return F_execute_signal_reserved_33;
    if (F_status_set_fine(status) == F_signal_reserved_34)          return F_execute_signal_reserved_34;
    if (F_status_set_fine(status) == F_signal_reserved_35)          return F_execute_signal_reserved_35;
    if (F_status_set_fine(status) == F_signal_reserved_36)          return F_execute_signal_reserved_36;
    if (F_status_set_fine(status) == F_signal_reserved_37)          return F_execute_signal_reserved_37;
    if (F_status_set_fine(status) == F_signal_reserved_38)          return F_execute_signal_reserved_38;
    if (F_status_set_fine(status) == F_signal_reserved_39)          return F_execute_signal_reserved_39;
    if (F_status_set_fine(status) == F_signal_reserved_40)          return F_execute_signal_reserved_40;
    if (F_status_set_fine(status) == F_signal_reserved_41)          return F_execute_signal_reserved_41;
    if (F_status_set_fine(status) == F_signal_reserved_42)          return F_execute_signal_reserved_42;
    if (F_status_set_fine(status) == F_signal_reserved_43)          return F_execute_signal_reserved_43;
    if (F_status_set_fine(status) == F_signal_reserved_44)          return F_execute_signal_reserved_44;
    if (F_status_set_fine(status) == F_signal_reserved_45)          return F_execute_signal_reserved_45;
    if (F_status_set_fine(status) == F_signal_reserved_46)          return F_execute_signal_reserved_46;
    if (F_status_set_fine(status) == F_signal_reserved_47)          return F_execute_signal_reserved_47;
    if (F_status_set_fine(status) == F_signal_reserved_48)          return F_execute_signal_reserved_48;
    if (F_status_set_fine(status) == F_signal_reserved_49)          return F_execute_signal_reserved_49;
    if (F_status_set_fine(status) == F_signal_reserved_50)          return F_execute_signal_reserved_50;
    if (F_status_set_fine(status) == F_signal_reserved_51)          return F_execute_signal_reserved_51;
    if (F_status_set_fine(status) == F_signal_reserved_52)          return F_execute_signal_reserved_52;
    if (F_status_set_fine(status) == F_signal_reserved_53)          return F_execute_signal_reserved_53;
    if (F_status_set_fine(status) == F_signal_reserved_54)          return F_execute_signal_reserved_54;
    if (F_status_set_fine(status) == F_signal_reserved_55)          return F_execute_signal_reserved_55;
    if (F_status_set_fine(status) == F_signal_reserved_56)          return F_execute_signal_reserved_56;
    if (F_status_set_fine(status) == F_signal_reserved_57)          return F_execute_signal_reserved_57;
    if (F_status_set_fine(status) == F_signal_reserved_58)          return F_execute_signal_reserved_58;
    if (F_status_set_fine(status) == F_signal_reserved_59)          return F_execute_signal_reserved_59;
    if (F_status_set_fine(status) == F_signal_reserved_60)          return F_execute_signal_reserved_60;
    if (F_status_set_fine(status) == F_signal_reserved_61)          return F_execute_signal_reserved_61;
    if (F_status_set_fine(status) == F_signal_reserved_62)          return F_execute_signal_reserved_62;
    if (F_status_set_fine(status) == F_signal_reserved_63)          return F_execute_signal_reserved_63;
    if (F_status_set_fine(status) == F_signal_reserved_64)          return F_execute_signal_reserved_64;

    return F_execute_code_last;
  }
#endif // _di_f_execute_status_from_status_

#ifndef _di_f_execute_status_to_status_
  f_status_t f_execute_status_to_status(uint8_t status) {

    if (status == F_execute_none)                        return F_none;
    if (status == F_execute_access)                      return F_access;
    if (status == F_execute_bad)                         return F_execute_not;
    if (status == F_execute_buffer)                      return F_buffer;
    if (status == F_execute_busy)                        return F_busy;
    if (status == F_execute_capability)                  return F_capability;
    if (status == F_execute_control_group)               return F_control_group;
    if (status == F_execute_child)                       return F_child;
    if (status == F_execute_directory_not)               return F_directory_not;
    if (status == F_execute_failure)                     return F_failure;
    if (status == F_execute_file_found_not)              return F_file_found_not;
    if (status == F_execute_file_type_directory)         return F_file_type_directory;
    if (status == F_execute_fork_not)                    return F_fork_not;
    if (status == F_execute_format_not)                  return F_format_not;
    if (status == F_execute_group)                       return F_group;
    if (status == F_execute_input_output)                return F_input_output;
    if (status == F_execute_limit)                       return F_limit;
    if (status == F_execute_loop)                        return F_loop;
    if (status == F_execute_memory_not)                  return F_memory_not;
    if (status == F_execute_name_not)                    return F_name_not;
    if (status == F_execute_nice)                        return F_nice;
    if (status == F_execute_parameter)                   return F_parameter;
    if (status == F_execute_pipe)                        return F_pipe;
    if (status == F_execute_processor)                   return F_processor;
    if (status == F_execute_prohibited)                  return F_prohibited;
    if (status == F_execute_resource_not)                return F_resource_not;
    if (status == F_execute_schedule)                    return F_schedule;
    if (status == F_execute_terminal)                    return F_terminal;
    if (status == F_execute_terminal_known_not)          return F_terminal_known_not;
    if (status == F_execute_terminal_not)                return F_terminal_not;
    if (status == F_execute_terminal_prohibited)         return F_terminal_prohibited;
    if (status == F_execute_terminal_valid_not)          return F_terminal_valid_not;
    if (status == F_execute_too_large)                   return F_too_large;
    if (status == F_execute_user)                        return F_user;
    if (status == F_execute_valid_not)                   return F_valid_not;
    if (status == F_execute_invoke_not)                  return F_call_not;
    if (status == F_execute_found_not)                   return F_found_not;
    if (status == F_execute_exit_parameter)              return F_exit;
    if (status == F_execute_signal_hangup)               return F_signal_hangup;
    if (status == F_execute_signal_interrupt)            return F_signal_interrupt;
    if (status == F_execute_signal_quit)                 return F_signal_quit;
    if (status == F_execute_signal_illegal)              return F_signal_illegal;
    if (status == F_execute_signal_trap)                 return F_signal_trap;
    if (status == F_execute_signal_abort)                return F_signal_abort;
    if (status == F_execute_signal_bus_error)            return F_signal_bus_error;
    if (status == F_execute_signal_floating_point_error) return F_signal_floating_point_error;
    if (status == F_execute_signal_kill)                 return F_signal_kill;
    if (status == F_execute_signal_user_1)               return F_signal_user_1;
    if (status == F_execute_signal_segmentation_fault)   return F_signal_segmentation_fault;
    if (status == F_execute_signal_user_2)               return F_signal_user_2;
    if (status == F_execute_signal_broken_pipe)          return F_signal_broken_pipe;
    if (status == F_execute_signal_alarm_clock)          return F_signal_alarm_clock;
    if (status == F_execute_signal_termination)          return F_signal_termination;
    if (status == F_execute_signal_stack_fault)          return F_signal_stack_fault;
    if (status == F_execute_signal_child)                return F_signal_child;
    if (status == F_execute_signal_continue)             return F_signal_continue;
    if (status == F_execute_signal_stop)                 return F_signal_stop;
    if (status == F_execute_signal_keyboard_stop)        return F_signal_keyboard_stop;
    if (status == F_execute_signal_tty_in)               return F_signal_tty_in;
    if (status == F_execute_signal_tty_out)              return F_signal_tty_out;
    if (status == F_execute_signal_urgent)               return F_signal_urgent;
    if (status == F_execute_signal_cpu_limit)            return F_signal_cpu_limit;
    if (status == F_execute_signal_file_size_limit)      return F_signal_file_size_limit;
    if (status == F_execute_signal_virtual_alarm_clock)  return F_signal_virtual_alarm_clock;
    if (status == F_execute_signal_profile_alarm_clock)  return F_signal_profile_alarm_clock;
    if (status == F_execute_signal_window_size_change)   return F_signal_window_size_change;
    if (status == F_execute_signal_pollable_event)       return F_signal_pollable_event;
    if (status == F_execute_signal_power_failure)        return F_signal_power_failure;
    if (status == F_execute_signal_bad_system_call)      return F_signal_bad_system_call;
    if (status == F_execute_signal_reserved_32)          return F_signal_reserved_32;
    if (status == F_execute_signal_reserved_33)          return F_signal_reserved_33;
    if (status == F_execute_signal_reserved_34)          return F_signal_reserved_34;
    if (status == F_execute_signal_reserved_35)          return F_signal_reserved_35;
    if (status == F_execute_signal_reserved_36)          return F_signal_reserved_36;
    if (status == F_execute_signal_reserved_37)          return F_signal_reserved_37;
    if (status == F_execute_signal_reserved_38)          return F_signal_reserved_38;
    if (status == F_execute_signal_reserved_39)          return F_signal_reserved_39;
    if (status == F_execute_signal_reserved_40)          return F_signal_reserved_40;
    if (status == F_execute_signal_reserved_41)          return F_signal_reserved_41;
    if (status == F_execute_signal_reserved_42)          return F_signal_reserved_42;
    if (status == F_execute_signal_reserved_43)          return F_signal_reserved_43;
    if (status == F_execute_signal_reserved_44)          return F_signal_reserved_44;
    if (status == F_execute_signal_reserved_45)          return F_signal_reserved_45;
    if (status == F_execute_signal_reserved_46)          return F_signal_reserved_46;
    if (status == F_execute_signal_reserved_47)          return F_signal_reserved_47;
    if (status == F_execute_signal_reserved_48)          return F_signal_reserved_48;
    if (status == F_execute_signal_reserved_49)          return F_signal_reserved_49;
    if (status == F_execute_signal_reserved_50)          return F_signal_reserved_50;
    if (status == F_execute_signal_reserved_51)          return F_signal_reserved_51;
    if (status == F_execute_signal_reserved_52)          return F_signal_reserved_52;
    if (status == F_execute_signal_reserved_53)          return F_signal_reserved_53;
    if (status == F_execute_signal_reserved_54)          return F_signal_reserved_54;
    if (status == F_execute_signal_reserved_55)          return F_signal_reserved_55;
    if (status == F_execute_signal_reserved_56)          return F_signal_reserved_56;
    if (status == F_execute_signal_reserved_57)          return F_signal_reserved_57;
    if (status == F_execute_signal_reserved_58)          return F_signal_reserved_58;
    if (status == F_execute_signal_reserved_59)          return F_signal_reserved_59;
    if (status == F_execute_signal_reserved_60)          return F_signal_reserved_60;
    if (status == F_execute_signal_reserved_61)          return F_signal_reserved_61;
    if (status == F_execute_signal_reserved_62)          return F_signal_reserved_62;
    if (status == F_execute_signal_reserved_63)          return F_signal_reserved_63;
    if (status == F_execute_signal_reserved_64)          return F_signal_reserved_64;

    return F_status_set_error(F_known_not);
  }
#endif // _di_f_execute_status_to_status_

#ifdef __cplusplus
} // extern "C"
#endif
