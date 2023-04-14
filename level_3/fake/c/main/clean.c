#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_clean_operate_
  void fake_clean_operate(fake_data_t * const data) {

    if (!data || !data->main) return;
    if (F_status_is_error(data->main->setting.state.status)) return;

    fake_main_t * const main = data->main;

    fake_print_message_delete_all_files(&main->program.message);

    main->setting.state.status = F_none;

    if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
      main->setting.state.status = f_directory_remove_custom(main->setting.build, F_directory_max_descriptors_d, F_true, fake_clean_remove_recursively_verbosely);
    }
    else {
      main->setting.state.status = f_directory_remove(main->setting.build, F_directory_max_descriptors_d, F_true);
    }

    if (F_status_set_fine(main->setting.state.status) == F_file_found_not || F_status_set_fine(main->setting.state.status) == F_directory) {
      fake_print_warning_build_directory_not_directory(&main->program.warning, main->setting.build);

      main->setting.state.status = F_none;
    }

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error_file(&main->program.error, macro_fake_f(f_directory_remove), main->setting.build, f_file_operation_delete_s, fll_error_file_type_directory_e);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_clean_operate_

#if !defined(_di_fake_clean_operate_)
  int fake_clean_remove_recursively_verbosely(const char * const path, const struct stat *file_stat, int type, struct FTW *entity) {

    if (!path || !entity || !entity->level) return 0;

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
