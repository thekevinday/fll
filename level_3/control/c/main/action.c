#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_action_type_identify_
  const uint8_t control_action_type_identify(const f_string_static_t action) {

    if (f_compare_dynamic(action, control_freeze_s) == F_equal_to) return control_action_type_freeze_e;
    if (f_compare_dynamic(action, control_kexec_s) == F_equal_to) return control_action_type_kexec_e;
    if (f_compare_dynamic(action, control_kill_s) == F_equal_to) return control_action_type_kill_e;
    if (f_compare_dynamic(action, control_pause_s) == F_equal_to) return control_action_type_pause_e;
    if (f_compare_dynamic(action, control_reboot_s) == F_equal_to) return control_action_type_reboot_e;
    if (f_compare_dynamic(action, control_reload_s) == F_equal_to) return control_action_type_reload_e;
    if (f_compare_dynamic(action, control_rerun_s) == F_equal_to) return control_action_type_rerun_e;
    if (f_compare_dynamic(action, control_restart_s) == F_equal_to) return control_action_type_restart_e;
    if (f_compare_dynamic(action, control_resume_s) == F_equal_to) return control_action_type_resume_e;
    if (f_compare_dynamic(action, control_shutdown_s) == F_equal_to) return control_action_type_shutdown_e;
    if (f_compare_dynamic(action, control_start_s) == F_equal_to) return control_action_type_start_e;
    if (f_compare_dynamic(action, control_stop_s) == F_equal_to) return control_action_type_stop_e;
    if (f_compare_dynamic(action, control_thaw_s) == F_equal_to) return control_action_type_thaw_e;

    return 0;
  }
#endif // _di_control_action_type_identify_

#ifndef _di_control_action_type_name_
  const f_string_static_t control_action_type_name(const uint8_t type) {

    switch (type) {
      case control_action_type_freeze_e:
        return control_freeze_s;

      case control_action_type_kexec_e:
        return control_kexec_s;

      case control_action_type_kill_e:
        return control_kill_s;

      case control_action_type_pause_e:
        return control_pause_s;

      case control_action_type_reboot_e:
        return control_reboot_s;

      case control_action_type_reload_e:
        return control_reload_s;

      case control_action_type_rerun_e:
        return control_rerun_s;

      case control_action_type_restart_e:
        return control_restart_s;

      case control_action_type_resume_e:
        return control_resume_s;

      case control_action_type_shutdown_e:
        return control_shutdown_s;

      case control_action_type_start_e:
        return control_start_s;

      case control_action_type_stop_e:
        return control_stop_s;

      case control_action_type_thaw_e:
        return control_thaw_s;
    }

    return f_string_empty_s;
  }
#endif // _di_control_action_type_name_

#ifndef _di_control_action_verify_
  void control_action_verify(control_main_t * const main) {

    if (!main) return;

    switch (main->setting.action) {
      case control_action_type_freeze_e:
      case control_action_type_kill_e:
      case control_action_type_pause_e:
      case control_action_type_reload_e:
      case control_action_type_rerun_e:
      case control_action_type_restart_e:
      case control_action_type_resume_e:
      case control_action_type_start_e:
      case control_action_type_stop_e:
      case control_action_type_thaw_e:
        if (main->setting.actions.used < 3) {
          control_print_error_parameter_action_rule_not(&main->program.error, main->setting.actions.array[0]);

          main->setting.state.status = F_status_set_error(F_parameter);

          return;
        }

        if (main->setting.actions.used > 3) {
          if (f_compare_dynamic(control_at_s, main->setting.actions.array[3]) == F_equal_to) {
            if (main->setting.actions.used < 5) {
              control_print_error_parameter_action_rule_too_few_with(&main->program.error, main->setting.actions.array[0], control_at_s);

              main->setting.state.status = F_status_set_error(F_parameter);

              return;
            }

            if (main->setting.actions.used > 5) {
              control_print_error_parameter_action_rule_too_many_with(&main->program.error, main->setting.actions.array[0], control_at_s);

              main->setting.state.status = F_status_set_error(F_parameter);

              return;
            }
          }
          else if (f_compare_dynamic(control_in_s, main->setting.actions.array[3]) == F_equal_to) {
            if (main->setting.actions.used < 6) {
              control_print_error_parameter_action_rule_too_few_with(&main->program.error, main->setting.actions.array[0], control_in_s);

              main->setting.state.status = F_status_set_error(F_parameter);

              return;
            }
          }
          else if (f_compare_dynamic(control_now_s, main->setting.actions.array[3]) == F_equal_to) {
            if (main->setting.actions.used > 4) {
              control_print_error_parameter_action_rule_too_many_with(&main->program.error, main->setting.actions.array[0], control_now_s);

              main->setting.state.status = F_status_set_error(F_parameter);

              return;
            }
          }
          else {
            control_print_error_parameter_action_rule_with_unknown(&main->program.error, main->setting.actions.array[0], main->setting.actions.array[2]);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
          }
        }

        if (!main->setting.actions.array[1].used) {
          if (main->setting.actions.used == 3) {
            control_print_error_parameter_action_rule_empty(&main->program.error, main->setting.actions.array[0]);
          }
          else {
            control_print_error_parameter_action_rule_directory_empty(&main->program.error, main->setting.actions.array[0]);
          }

          main->setting.state.status = F_status_set_error(F_parameter);

          return;
        }

        if (main->setting.actions.used == 3) {
          if (!main->setting.actions.array[2].used) {
            control_print_error_parameter_action_rule_basename_empty(&main->program.error, main->setting.actions.array[0]);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
          }
        }

        main->setting.state.status = F_none;

        return;

      case control_action_type_kexec_e:
      case control_action_type_reboot_e:
      case control_action_type_shutdown_e:
        if (main->setting.actions.used < 2) {
          control_print_error_parameter_action_rule_too_few(&main->program.error, main->setting.actions.array[0]);

          main->setting.state.status = F_status_set_error(F_parameter);

          return;
        }

        if (f_compare_dynamic(control_at_s, main->setting.actions.array[1]) == F_equal_to) {
          if (main->setting.actions.used < 3) {
            control_print_error_parameter_action_rule_too_few_with(&main->program.error, main->setting.actions.array[0], control_at_s);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
          }

          if (main->setting.actions.used > 3) {
            control_print_error_parameter_action_rule_too_many_with(&main->program.error, main->setting.actions.array[0], control_at_s);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
          }
        }
        else if (f_compare_dynamic(control_in_s, main->setting.actions.array[1]) == F_equal_to) {
          if (main->setting.actions.used < 4) {
            control_print_error_parameter_action_rule_too_few_with(&main->program.error, main->setting.actions.array[0], control_in_s);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
          }
        }
        else if (f_compare_dynamic(control_now_s, main->setting.actions.array[1]) == F_equal_to) {
          if (main->setting.actions.used > 2) {
            control_print_error_parameter_action_rule_too_many_with(&main->program.error, main->setting.actions.array[0], control_now_s);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
          }
        }
        else {
          control_print_error_parameter_action_rule_with_unknown(&main->program.error, main->setting.actions.array[0], main->setting.actions.array[1]);

            main->setting.state.status = F_status_set_error(F_parameter);

            return;
        }
    }

    main->setting.state.status = F_none;
  }
#endif // _di_control_action_verify_

#ifdef __cplusplus
} // extern "C"
#endif
