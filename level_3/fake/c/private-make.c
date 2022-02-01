#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-load_fakefile.h"
#include "private-make-load_parameters.h"
#include "private-make-operate.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_assure_inside_project_
  f_status_t fake_make_assure_inside_project(fake_make_data_t * const data_make, const f_string_static_t path) {

    data_make->path_cache.used = 0;

    f_status_t status = fll_path_canonical(path.string, &data_make->path_cache);
    if (F_status_is_error(status)) return status;

    if (data_make->path_cache.used < data_make->path.stack.array[0].used) {
      return F_status_set_error(F_false);
    }

    const f_string_range_t range = macro_f_string_range_t_initialize(data_make->path.stack.array[0].used);

    if (range.start <= range.stop) {
      status = fl_string_dynamic_partial_compare(data_make->path.stack.array[0], data_make->path_cache, range, range);
      if (F_status_is_error(status)) return status;

      if (status) {
        if (data_make->path_cache.used == data_make->path.stack.array[0].used) {
          return F_true;
        }

        if (data_make->path_cache.string[data_make->path.stack.array[0].used] == f_path_separator_s.string[0]) {
          return F_true;
        }
      }
    }

    return F_status_set_error(F_false);
  }
#endif // _di_fake_make_assure_inside_project_

#ifndef _di_fake_make_get_id_group_
  f_status_t fake_make_get_id_group(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, gid_t *id) {

    const f_string_range_t range = macro_f_string_range_t_initialize(buffer.used);

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, range, &number);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_number) {
        status = f_account_group_id_by_name(buffer.string, id);

        if (F_status_is_error(status)) {
          fll_error_print(print, F_status_set_fine(status), "f_account_group_id_by_name", F_true);

          return F_status_set_error(status);
        }
        else if (status == F_exist_not) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe group name '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, buffer, main->error.notable);
            fl_print_format("%[' was not found.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }

        return F_none;
      }

      fll_error_print(print, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true);
      return F_status_set_error(status);
    }
    else if (number > F_type_size_32_unsigned_d) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe number '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, number, main->error.notable);
        fl_print_format("%[' is too large.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }
    }

    *id = (gid_t) number;
    return status;
  }
#endif // _di_fake_make_get_id_group_

#ifndef _di_fake_make_get_id_mode_
  f_status_t fake_make_get_id_mode(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, f_file_mode_t *mode, uint8_t *replace) {

    if (!buffer.used) {
      fll_error_print(print, F_parameter, "fake_make_get_id_mode", F_true);

      return F_status_set_error(F_parameter);
    }

    const f_status_t status = f_file_mode_from_string(buffer.string, main->umask, mode, replace);

    if (F_status_is_error(status)) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        if (F_status_set_fine(status) == F_syntax) {
          flockfile(main->error.to.stream);

          fl_print_format("%r%[%QThe mode '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
          fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, buffer, main->error.notable);
          fl_print_format("%[' is invalid.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

          funlockfile(main->error.to.stream);
        }
        else {
          fll_error_print(print, status, "f_file_mode_from_string", F_true);
        }
      }

      return status;
    }

    return F_none;
  }
#endif // _di_fake_make_get_id_mode_

#ifndef _di_fake_make_get_id_owner_
  f_status_t fake_make_get_id_owner(fake_main_t * const main, const fl_print_t print, const f_string_static_t buffer, uid_t *id) {

    const f_string_range_t range = macro_f_string_range_t_initialize(buffer.used);

    f_number_unsigned_t number = 0;

    f_status_t status = fl_conversion_string_to_number_unsigned(buffer.string, range, &number);

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_number) {
        status = f_account_id_by_name(buffer.string, id);

        if (F_status_is_error(status)) {
          fll_error_print(print, status, "f_account_id_by_name", F_true);

          return F_status_set_error(status);
        }
        else if (status == F_exist_not) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe user '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, buffer, main->error.notable);
            fl_print_format("%[' was not found.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(F_failure);
        }

        return F_none;
      }

      fll_error_print(print, status, "fl_conversion_string_to_number_unsigned", F_true);
      return F_status_set_error(status);
    }
    else if (number > F_type_size_32_unsigned_d) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        flockfile(main->error.to.stream);

        fl_print_format("%r%[%QThe number '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
        fl_print_format("%[%un%]", main->error.to.stream, main->error.notable, number, main->error.notable);
        fl_print_format("%[' is too large.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

        funlockfile(main->error.to.stream);
      }
    }

    *id = (uid_t) number;
    return status;
  }
#endif // _di_fake_make_get_id_owner_

#ifndef _di_fake_make_path_relative_
  f_status_t fake_make_path_relative(fake_make_data_t * const data_make, const f_string_static_t path) {

    data_make->path_cache.used = 0;

    if (!path.used || path.used == data_make->path.stack.array[0].used) {
      return F_none;
    }

    if (path.used < data_make->path.stack.array[0].used) {
      return F_status_set_error(F_failure);
    }

    f_string_range_t range = f_string_range_t_initialize;

    range.start = data_make->path.stack.array[0].used + 1;
    range.stop = range.start + (path.used - range.start) - 1;

    f_status_t status = f_string_dynamic_partial_append(path, range, &data_make->path_cache);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_terminate(&data_make->path_cache);
    if (F_status_is_error(status)) return status;

    return status;
  }
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif
