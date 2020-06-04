#include <level_3/fake.h>
#include "private-fake.h"
#include "private-clean.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_clean_operate_
  f_return_status fake_clean_operate(const fake_data data) {
    f_status status = F_none;

    if (data.verbosity != fake_verbosity_quiet) {
      printf("%c", f_string_eol[0]);
      fl_color_print(f_type_output, data.context.important, data.context.reset, "Deleting all files within build directory '");
      fl_color_print(f_type_output, data.context.notable, data.context.reset, "%s", data.path_build.string);
      fl_color_print_line(f_type_output, data.context.important, data.context.reset, "'.");
    }

    if (data.verbosity == fake_verbosity_verbose) {
      status = f_directory_remove_custom(data.path_build.string, f_directory_descriptors_max, F_true, fake_clean_remove_recursively_verbosely);
    }
    else {
      status = f_directory_remove(data.path_build.string, f_directory_descriptors_max, F_true);
    }

    if (F_status_is_error(status)) {
      fake_print_error(data.context, data.verbosity, F_status_set_fine(status), "f_directory_remove", F_true);
      return status;
    }

    return F_none;
  }
#endif // _di_fake_clean_operate_

#if !defined(_di_fake_clean_operate_)
  int fake_clean_remove_recursively_verbosely(const char *path, const struct stat *file_stat, int type, struct FTW *entity) {
    if (entity->level == 0) return 0;

    int result = remove(path);

    if (result == 0) {
      printf("Removed '%s'.%c", path, f_string_eol[0]);

      // @fixme this really should be the line below, but nftw()'s design does not allow for this. Get rid of nftw() and manually traverse directory.
      //fl_color_print_line(f_type_output, data.context.standout, data.context.reset, "Removed '%s'.", path);
    }

    return result;
  }
#endif // !defined(_di_fake_clean_operate_)

#ifdef __cplusplus
} // extern "C"
#endif
