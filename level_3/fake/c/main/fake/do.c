#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_do_copy_action_
  void fake_do_copy_action(void * const void_recurse, const f_string_static_t name, const uint16_t flag) {

    if (!void_recurse) return;

    f_directory_recurse_do_t * const recurse = (f_directory_recurse_do_t *) void_recurse;

    if (!recurse->state.custom) return;

    fake_local_t * const local = (fake_local_t *) recurse->state.custom;

    if (!local->custom_1) {
      recurse->state.status = F_status_set_error(F_parameter);

      return;
    }

    f_string_map_t * const map = (f_string_map_t *) local->custom_1;

    if (flag & f_directory_recurse_do_flag_before_e) {
      if (flag & f_directory_recurse_do_flag_top_e) {
        if (recurse->state.code & fake_state_code_clone_e) {
          fake_print_verbose_cloning(&local->main->program.message, *recurse->path_top, map->name);

          recurse->state.status = f_file_clone(*recurse->path_top, map->name, F_file_default_write_size_d, f_file_stat_flag_group_e | f_file_stat_flag_owner_e | (f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e));
        }
        else {
          fake_print_verbose_copying(&local->main->program.message, *recurse->path_top, map->name);

          recurse->state.status = f_file_copy(*recurse->path_top, map->name, recurse->mode, F_file_default_write_size_d, f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e);
        }

        if (F_status_is_error(recurse->state.status)) {
          local->main->setting.state.status = recurse->state.status;

          fake_print_error_file(&local->main->program.error, (recurse->state.code & fake_state_code_clone_e) ? macro_fake_f(f_file_clone) : macro_fake_f(f_file_copy), *recurse->path_top, (recurse->state.code & fake_state_code_clone_e) ? f_file_operation_clone_s : f_file_operation_copy_s, fll_error_file_type_directory_e);

          // Save the error status for when the error message is printed.
          *((f_status_t *) local->custom_2) = recurse->state.status;
        }
        else {
          fake_string_dynamic_reset(&recurse->path_cache);

          // Pre-populate the destination into the path cache.
          recurse->state.status = f_string_dynamic_append_nulless(map->name, &recurse->path_cache);

          if (F_status_is_error_not(recurse->state.status)) {
            recurse->state.status = F_none;

            // Do not allow trailing path separators in the string's length calculation, except root directory '/'.
            for (; recurse->path_cache.used; --recurse->path_cache.used) {
              if (recurse->path_cache.string[recurse->path_cache.used - 1] != f_path_separator_s.string[0]) break;
            } // for

            recurse->path_cache.string[recurse->path_cache.used] = 0;
          }
        }

        return;
      }

      if (flag & f_directory_recurse_do_flag_directory_e) {

        // Push the directory name on the path stack (the destination path is expected to be pre-populated).
        recurse->state.status = f_string_dynamic_increase_by(f_path_separator_s.used + name.used + 1, &recurse->path_cache);

        if (F_status_is_error_not(recurse->state.status)) {
          recurse->state.status = f_string_dynamic_append_assure(f_path_separator_s, &recurse->path_cache);
        }

        if (F_status_is_error_not(recurse->state.status)) {
          recurse->state.status = f_string_dynamic_append_nulless(name, &recurse->path_cache);
        }

        // Guaranetee NULL terminated string.
        recurse->path_cache.string[recurse->path_cache.used] = 0;

        if (F_status_is_error(recurse->state.status)) return;

        if (recurse->state.code & fake_state_code_clone_e) {
          fake_print_verbose_cloning(&local->main->program.message, recurse->path, recurse->path_cache);

          recurse->state.status = f_file_clone(recurse->path, recurse->path_cache, F_file_default_write_size_d, f_file_stat_flag_group_e | f_file_stat_flag_owner_e | (f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e));
        }
        else {
          fake_print_verbose_copying(&local->main->program.message, recurse->path, recurse->path_cache);

          recurse->state.status = f_file_copy(recurse->path, recurse->path_cache, recurse->mode, F_file_default_write_size_d, f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e);
        }

        if (F_status_is_error(recurse->state.status)) {
          local->main->setting.state.status = recurse->state.status;

          fake_print_error_file(&local->main->program.error, (recurse->state.code & fake_state_code_clone_e) ? macro_fake_f(f_file_clone) : macro_fake_f(f_file_copy), recurse->path, (recurse->state.code & fake_state_code_clone_e) ? f_file_operation_clone_s : f_file_operation_copy_s, fll_error_file_type_directory_e);

          // Save the error status for when the error message is printed.
          *((f_status_t *) local->custom_2) = recurse->state.status;
        }
      }

      return;
    }

    if (flag & f_directory_recurse_do_flag_after_e) {
      if (flag & f_directory_recurse_do_flag_directory_e) {

        // Pop the current path off of the path stack.
        if (F_status_is_error_not(recurse->state.status)) {
          recurse->path_cache.used -= f_path_separator_s.used + name.used;
        }

        // Guaranetee NULL terminated string.
        recurse->path_cache.string[recurse->path_cache.used] = 0;
      }

      return;
    }

    fake_string_dynamic_reset(&map->value);

    recurse->state.status = f_string_dynamic_increase_by(recurse->path_cache.used + f_path_separator_s.used + name.used + 1, &map->value);

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_nulless(recurse->path_cache, &map->value);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_assure(f_path_separator_s, &map->value);
    }

    if (F_status_is_error_not(recurse->state.status)) {
      recurse->state.status = f_string_dynamic_append_nulless(name, &map->value);
    }

    // Guaranetee NULL terminated string.
    map->value.string[map->value.used] = 0;

    if (F_status_is_error(recurse->state.status)) return;

    if (recurse->state.code & fake_state_code_clone_e) {
      fake_print_verbose_cloning(&local->main->program.message, recurse->path, map->value);

      recurse->state.status = f_file_clone(recurse->path, map->value, F_file_default_write_size_d, f_file_stat_flag_group_e | f_file_stat_flag_owner_e | (f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e));
    }
    else {
      fake_print_verbose_copying(&local->main->program.message, recurse->path, map->value);

      recurse->state.status = f_file_copy(recurse->path, map->value, recurse->mode, F_file_default_write_size_d, f_directory_recurse_do_flag_dereference_e ? 0 : f_file_stat_flag_reference_e);
    }

    if (F_status_is_error(recurse->state.status)) {
      local->main->setting.state.status = recurse->state.status;

      fake_print_error_file(&local->main->program.error, (recurse->state.code & fake_state_code_clone_e) ? macro_fake_f(f_file_clone) : macro_fake_f(f_file_copy), map->value, f_file_operation_create_s, (flag & f_directory_recurse_do_flag_directory_e) ? fll_error_file_type_directory_e : fll_error_file_type_file_e);

      // Save the error status for when the error message is printed.
      *((f_status_t *) local->custom_2) = recurse->state.status;
    }
  }
#endif // _di_fake_do_copy_action_

#ifndef _di_fake_do_copy_handle_
  void fake_do_copy_handle(void * const void_recurse, const f_string_static_t name, const uint16_t flag) {

    if (!void_recurse) return;

    f_directory_recurse_do_t * const recurse = (f_directory_recurse_do_t *) void_recurse;

    // Do not print any errors on interrupts.
    if (F_status_set_fine(recurse->state.status) == F_interrupt) return;

    if (!recurse->state.custom) return;

    fake_local_t * const local = (fake_local_t *) recurse->state.custom;

    if (!local->main || !local->custom_1 || !local->custom_2) return;

    if (F_status_is_error_not(*((f_status_t *) local->custom_2))) {
      local->main->setting.state.status = recurse->state.status;

      fake_print_error_build_operation_file(&local->main->program.error, macro_fake_f(fl_directory_do), (recurse->state.code & fake_state_code_clone_e) ? f_file_operation_clone_s : f_file_operation_copy_s, *recurse->path_top, recurse->path_cache, f_file_operation_to_s, F_true);

      *((f_status_t *) local->custom_2) = recurse->state.status;
    }
  }
#endif // _di_fake_do_copy_handle_

#ifdef __cplusplus
} // extern "C"
#endif
