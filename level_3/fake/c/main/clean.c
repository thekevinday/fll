#include "fake.h"
#include "clean.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_clean_operate_
  f_status_t fake_clean_operate(fake_data_t * const data) {

    if (data->main->message.verbosity != f_console_verbosity_quiet_e && data->main->message.verbosity != f_console_verbosity_error_e) {
      f_file_stream_lock(data->main->message.to);

      fl_print_format("%r%[Deleting all files within build directory '%]", data->main->message.to, f_string_eol_s, data->main->context.set.important, data->main->context.set.important);
      fl_print_format("%[%Q%]", data->main->message.to, data->main->context.set.notable, data->setting->build, data->main->context.set.notable);
      fl_print_format("%['.%]%r", data->main->message.to, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);

      f_file_stream_unlock(data->main->message.to);
    }

    f_status_t status = F_none;

    if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
      status = f_directory_remove_custom(data->setting->build, F_directory_descriptors_max_d, F_true, fake_clean_remove_recursively_verbosely);
    }
    else {
      status = f_directory_remove(data->setting->build, F_directory_descriptors_max_d, F_true);
    }

    if (F_status_set_fine(status) == F_file_found_not || F_status_set_fine(status) == F_directory) {
      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("The build directory '%[%Q%]' does not exist.%r", data->main->warning.to, data->main->context.set.notable, data->setting->build, data->main->context.set.notable, f_string_eol_s);
      }

      status = F_none;
    }

    if (F_status_is_error(status)) {
      fake_print_error_file(data->setting, data->main->error, status, macro_fake_f(f_directory_remove), data->setting->build, f_file_operation_delete_s, fll_error_file_type_directory_e);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_clean_operate_

#if !defined(_di_fake_clean_operate_)
  int fake_clean_remove_recursively_verbosely(const char * const path, const struct stat *file_stat, int type, struct FTW *entity) {

    if (!entity->level || !path) return 0;

    const int result = remove(path);

    if (!result) {

      const f_file_t output = macro_f_file_t_initialize_stream(F_type_output_d);

      // @todo in order to get this working, the recursive function that calls this needs to be rewritten with more flexibility or provide a higher-level equivalent function.
      fll_print_format("Removed '%S'.%r", output, path, f_string_eol_s);
    }

    return result;
  }
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif
