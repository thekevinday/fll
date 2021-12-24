#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_clean_operate_
  f_status_t fake_clean_operate(fake_main_t * const main) {

    f_status_t status = F_none;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      flockfile(main->output.to.stream);

      fl_print_format("%c%[Deleting all files within build directory '%]", main->output.to.stream, f_string_eol_s[0], main->context.set.important, main->context.set.important);
      fl_print_format("%[%Q%]", main->output.to.stream, main->context.set.notable, main->path_build, main->context.set.notable);
      fl_print_format("%[.%]%c", main->output.to.stream, main->context.set.important, main->context.set.important, f_string_eol_s[0]);

      funlockfile(main->output.to.stream);
    }

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    if (main->error.verbosity == f_console_verbosity_verbose_e) {
      status = f_directory_remove_custom(main->path_build.string, F_directory_descriptors_max_d, F_true, fake_clean_remove_recursively_verbosely);
    }
    else {
      status = f_directory_remove(main->path_build.string, F_directory_descriptors_max_d, F_true);
    }

    if (F_status_set_fine(status) == F_file_found_not) {
      if (main->error.verbosity == f_console_verbosity_verbose_e) {
        flockfile(main->output.to.stream);

        f_print_terminated("The build directory '", main->output.to.stream);
        fl_print_format("%[%Q%]", main->output.to.stream, main->context.set.notable, main->path_build, main->context.set.notable);
        fl_print_format("' does not exist.%c", main->output.to.stream, f_string_eol_s[0]);

        funlockfile(main->output.to.stream);
      }

      status = F_none;
    }

    if (F_status_is_error(status)) {
      fll_error_file_print(main->error, F_status_set_fine(status), "f_directory_remove", F_true, main->path_build.string, "remove", fll_error_file_type_directory_e);

      return status;
    }

    return F_none;
  }
#endif // _di_fake_clean_operate_

#if !defined(_di_fake_clean_operate_)
  int fake_clean_remove_recursively_verbosely(const char *path, const struct stat *file_stat, int type, struct FTW *entity) {

    if (!entity->level) return 0;

    const int result = remove(path);

    if (!result) {

      // @todo in order to get this working, the recursive function that calls this needs to be rewritten with more flexibility or provide a higher-level equivalent function.
      fll_print_format("Removed '%S'.%c", stdout, path, f_string_eol_s[0]);
    }

    return result;
  }
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif
