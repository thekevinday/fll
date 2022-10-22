#include "fake.h"
#include "private-common.h"
#include "private-clean.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_clean_operate_
  f_status_t fake_clean_operate(fake_data_t * const data) {

    if (data->main->output.verbosity != f_console_verbosity_quiet_e && data->main->output.verbosity != f_console_verbosity_error_e) {
      flockfile(data->main->output.to);

      fl_print_format("%r%[Deleting all files within build directory '%]", data->main->output.to, f_string_eol_s, data->main->context.set.important, data->main->context.set.important);
      fl_print_format("%[%Q%]", data->main->output.to, data->main->context.set.notable, data->path_build, data->main->context.set.notable);
      fl_print_format("%['.%]%r", data->main->output.to, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);

      funlockfile(data->main->output.to);
    }

    f_status_t status = F_none;

    if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
      status = f_directory_remove_custom(data->path_build, F_directory_descriptors_max_d, F_true, fake_clean_remove_recursively_verbosely);
    }
    else {
      status = f_directory_remove(data->path_build, F_directory_descriptors_max_d, F_true);
    }

    if (F_status_set_fine(status) == F_file_found_not || F_status_set_fine(status) == F_directory) {
      if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("The build directory '%[%Q%]' does not exist.%r", data->main->warning.to, data->main->context.set.notable, data->path_build, data->main->context.set.notable, f_string_eol_s);
      }

      status = F_none;
    }

    if (F_status_is_error(status)) {
      fll_error_file_print(data->main->error, F_status_set_fine(status), "f_directory_remove", F_true, data->path_build, f_file_operation_delete_s, fll_error_file_type_directory_e);

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

      // @todo in order to get this working, the recursive function that calls this needs to be rewritten with more flexibility or provide a higher-level equivalent function.
      fll_print_format("Removed '%S'.%r", F_type_input_d, path, f_string_eol_s);
    }

    return result;
  }
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif
