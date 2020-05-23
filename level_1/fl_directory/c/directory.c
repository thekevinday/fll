#include <level_1/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_copy_
  f_return_status f_directory_copy(const f_string source, const f_string destination, const mode_t mode, const f_number_unsigned size_block, const bool exclusive) {
    f_status status = F_none;
    /*
@todo
    status = f_directory_exists(source);
    if (F_status_is_error(status)) return status;
    if (status == F_false) return F_status_set_error(F_directory);

    status = f_directory_exists(destination);
    if (F_status_is_error(status)) return status;

    if (exclusive) {
    }
    else {
    }

    status = private_fl_directory_list(source, 0, 0, listing);*/

    return F_none;
  }
#endif // _di_f_directory_copy_

#ifndef _di_fl_directory_list_
  f_return_status fl_directory_list(const f_string path, int (*filter)(const struct dirent *), int (*sort)(const struct dirent **, const struct dirent **), f_directory_listing *listing) {
    #ifndef _di_level_2_parameter_checking_
      if (listing == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fl_directory_list(path, filter, sort, listing);
  }
#endif // _di_fl_directory_list_

#ifdef __cplusplus
} // extern "C"
#endif
