#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_assure_inside_project_
  void fake_make_assure_inside_project(fake_make_data_t * const data_make, const f_string_static_t path) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_string_dynamic_reset(&main->cache_argument);

    main->setting.state.status = fl_path_canonical(path, &main->cache_argument);
    if (F_status_is_error(main->setting.state.status)) return;

    if (main->cache_argument.used < data_make->path.stack.array[0].used) {
      main->setting.state.status = F_status_set_error(F_false);

      return;
    }

    const f_string_range_t range = macro_f_string_range_t_initialize_2(data_make->path.stack.array[0].used);

    if (range.start <= range.stop) {
      main->setting.state.status = f_compare_dynamic_partial(data_make->path.stack.array[0], main->cache_argument, range, range);
      if (F_status_is_error(main->setting.state.status)) return;

      if (main->setting.state.status) {
        if (main->cache_argument.used == data_make->path.stack.array[0].used || main->cache_argument.string[data_make->path.stack.array[0].used] == f_path_separator_s.string[0]) {
          main->setting.state.status = F_true;

          return;
        }
      }
    }

    main->setting.state.status = F_status_set_error(F_false);
  }
#endif // _di_fake_make_assure_inside_project_

#ifndef _di_fake_make_get_id_
  f_number_unsigned_t fake_make_get_id(fake_make_data_t * const data_make, const bool is_owner, const f_string_static_t buffer) {

    if (!data_make || !data_make->main) return 0;

    fake_main_t * const main = data_make->main;

    if (!buffer.used) {
      fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id));

      main->setting.state.status = F_status_set_error(F_parameter);

      return 0;
    }

    f_number_unsigned_t number = 0;

    main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, &number);

    // Negative numbers are not supported.
    if (main->setting.state.status == F_number_negative) {
      main->setting.state.status = F_status_set_error(F_number_negative);
    }

    if (F_status_is_error(main->setting.state.status)) {

      // When the buffer is not a number, then check to see if this is a group or owner name.
      if (F_status_set_fine(main->setting.state.status) == F_number) {
        if (is_owner) {
          uid_t uid = 0;

          main->setting.state.status = f_account_id_by_name(buffer, &uid);
        }
        else {
          gid_t gid = 0;

          main->setting.state.status = f_account_group_id_by_name(buffer, &gid);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, is_owner ? macro_fake_f(f_account_id_by_name) : macro_fake_f(f_account_group_id_by_name));
        }
        else {
          if (main->setting.state.status == F_exist_not) {
            fake_print_error_group_not_found(&main->program.error, buffer);

            main->setting.state.status = F_status_set_error(F_exist_not);
          }
          else {
            main->setting.state.status = F_none;
          }
        }
      }
      else {
        fake_print_error(&main->program.error, macro_fake_f(fl_conversion_dynamic_to_unsigned_detect));
      }

      return 0;
    }

    if (number > F_type_size_32_unsigned_d) {
      fake_print_error_number_too_large(&main->program.error, buffer);

      main->setting.state.status = F_status_set_error(F_failure);

      return 0;
    }

    return number;
  }
#endif // _di_fake_make_get_id_

#ifndef _di_fake_make_get_id_mode_
  void fake_make_get_id_mode(fake_make_data_t * const data_make, const f_string_static_t buffer, f_file_mode_t *mode, uint8_t *replace) {

    if (!data_make || !data_make->main || !mode || !replace) return;

    fake_main_t * const main = data_make->main;

    if (!buffer.used) {
      fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id_mode));

      main->setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    main->setting.state.status = f_file_mode_from_string(buffer, main->program.umask, mode, replace);

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_syntax) {
        fake_print_error_mode_invalid(&main->program.error, buffer);
      }
      else {
        fake_print_error(&main->program.error, macro_fake_f(fake_make_get_id_mode));
      }
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_get_id_mode_

#ifndef _di_fake_make_path_relative_
  void fake_make_path_relative(fake_make_data_t * const data_make, const f_string_static_t path) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    fake_string_dynamic_reset(&main->cache_argument);

    if (!path.used || path.used == data_make->path.stack.array[0].used) {
      main->setting.state.status = F_none;

      return;
    }

    if (path.used < data_make->path.stack.array[0].used) {
      main->setting.state.status = F_status_set_error(F_failure);

      return;
    }

    f_string_range_t range = f_string_range_t_initialize;

    range.start = data_make->path.stack.array[0].used + 1;
    range.stop = range.start + (path.used - range.start) - 1;

    main->setting.state.status = f_string_dynamic_partial_append(path, range, &main->cache_argument);
    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = f_string_dynamic_terminate(&main->cache_argument);
    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif
