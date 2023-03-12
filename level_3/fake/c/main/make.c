#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_assure_inside_project_
  void fake_make_assure_inside_project(fake_make_data_t * const data_make, const f_string_static_t path) {

    if (!data_make) return;

    data_make->cache_path.used = 0;

    data.setting.state.status = fll_path_canonical(path, &data_make->cache_path);
    if (F_status_is_error(data.setting.state.status)) return;

    if (data_make->cache_path.used < data_make->path.stack.array[0].used) {
      data.setting.state.status = F_status_set_error(F_false);

      return;
    }

    const f_string_range_t range = macro_f_string_range_t_initialize2(data_make->path.stack.array[0].used);

    if (range.start <= range.stop) {
      data.setting.state.status = fl_string_dynamic_partial_compare(data_make->path.stack.array[0], data_make->cache_path, range, range);
      if (F_status_is_error(data.setting.state.status)) return;

      if (data.setting.state.status) {
        if (data_make->cache_path.used == data_make->path.stack.array[0].used || data_make->cache_path.string[data_make->path.stack.array[0].used] == f_path_separator_s.string[0]) {
          data.setting.state.status = F_true;

          return;
        }
      }
    }

    data.setting.state.status = F_status_set_error(F_false);
  }
#endif // _di_fake_make_assure_inside_project_

#ifndef _di_fake_make_get_id_
  void fake_make_get_id(fake_make_data_t * const data_make, const bool is_owner, const f_string_static_t buffer, void *id) {

    if (!data || !id) return;

    if (!buffer.used) {
      fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(fake_make_get_id));

      data_make->setting->state.status = F_status_set_error(F_parameter);

      return;
    }

    f_number_unsigned_t number = 0;

    data_make->setting->state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, buffer, &number);

    if (F_status_is_error(data_make->setting->state.status)) {
      if (F_status_set_fine(data_make->setting->state.status) == F_number) {

        data_make->setting->state.status = is_owner
          ? f_account_id_by_name(buffer, (uid_t *) id)
          : f_account_group_id_by_name(buffer, (gid_t *) id);

        if (F_status_is_error(data_make->setting->state.status)) {
          fake_print_error(
            data_make->setting,
            data_make->main->error,
            macro_fake_f(is_owner
              ? f_account_id_by_name
              : f_account_group_id_by_name
            )
          );
        }
        else {
          if (data_make->setting->state.status == F_exist_not) {
            fake_print_error_group_not_found(data_make->setting, data_make->main->error, buffer);

            data_make->setting->state.status = F_status_set_error(F_exist_not);
          }
          else {
            data_make->setting->state.status = F_none;
          }
        }
      }
      else {
        fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(fl_conversion_dynamic_to_unsigned_detect));
      }

      return;
    }

    if (number > F_type_size_32_unsigned_d) {
      fake_print_error_number_too_large(data_make->setting, data_make->main->error, buffer);

      data.setting.state.status = F_status_set_error(F_failure);

      return;
    }

    *id = is_owner ? (uid_t) number : (gid_t) number;
  }
#endif // _di_fake_make_get_id_

#ifndef _di_fake_make_get_id_mode_
  void fake_make_get_id_mode(fake_make_data_t * const data_make, const f_string_static_t buffer, f_file_mode_t *mode, uint8_t *replace) {

    if (!data_make || !mode || !replace) return;

    if (!buffer.used) {
      fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(fake_make_get_id_mode));

      data.setting.state.status = F_status_set_error(F_parameter);

      return;
    }

    data_make->setting->state.status = f_file_mode_from_string(buffer, data->main->umask, mode, replace);

    if (F_status_is_error(data_make->setting->state.status)) {
      if (F_status_set_fine(data_make->setting->state.status) == F_syntax) {
        fake_print_error_mode_invalid(data_make->setting, data_make->main->error, buffer);
      }
      else {
        fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(fake_make_get_id_mode));
      }
    }
    else {
      data.setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_get_id_mode_

#ifndef _di_fake_make_path_relative_
  void fake_make_path_relative(fake_make_data_t * const data_make, const f_string_static_t path) {

    if (!data_make) return;

    data_make->cache_path.used = 0;

    if (!path.used || path.used == data_make->path.stack.array[0].used) {
      data.setting.state.status = F_none;

      return;
    }

    if (path.used < data_make->path.stack.array[0].used) {
      data.setting.state.status = F_status_set_error(F_failure);

      return;
    }

    f_string_range_t range = f_string_range_t_initialize;

    range.start = data_make->path.stack.array[0].used + 1;
    range.stop = range.start + (path.used - range.start) - 1;

    data.setting.state.status = f_string_dynamic_partial_append(path, range, &data_make->cache_path);
    if (F_status_is_error(data.setting.state.status)) return;

    data.setting.state.status = f_string_dynamic_terminate(&data_make->cache_path);
    if (F_status_is_error(data.setting.state.status)) return;

    data.setting.state.status = F_none;
  }
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif
