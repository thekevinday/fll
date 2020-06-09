#include <level_1/fss.h>
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_identify_
  f_return_status fl_fss_identify(const f_string_static buffer, f_fss_header *header) {
    #ifndef _di_level_1_parameter_checking_
      if (header == 0) return F_status_set_error(F_parameter);
      if (buffer.used <= 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_fss_identify(buffer, header);
  }
#endif // _di_fl_fss_identify_

#ifndef _di_fl_fss_identify_file_
  f_return_status fl_fss_identify_file(f_file *file, f_fss_header *header) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return F_status_set_error(F_parameter);
      if (header == 0) return F_status_set_error(F_parameter);
      if (file->id == 0) return F_status_set_error(F_file_closed);
      if (file->id < 0) return F_status_set_error(F_file);
    #endif // _di_level_1_parameter_checking_

    {
      f_string_length seeked = 0;
      if (F_status_is_error(f_file_seek(file->id, SEEK_SET, 0, &seeked))) {
        return F_status_set_error(F_file_seek);
      }
    }

    f_status status = F_none;
    f_string_dynamic buffer = f_string_dynamic_initialize;

    f_macro_string_dynamic_resize(status, buffer, f_fss_max_header_length + 1);
    if (F_status_is_error(status)) return status;

    status = f_file_read_until(*file, &buffer, f_fss_max_header_length + 1);
    if (F_status_is_error(status)) return status;

    return private_fl_fss_identify(buffer, header);
  }
#endif // _di_fl_fss_identify_file_

#ifdef __cplusplus
} // extern "C"
#endif
