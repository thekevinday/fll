#include <level_2/fss.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_fss_snatch_
  f_return_status fll_fss_snatch(const f_string_dynamic buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], f_string_dynamic *values[], const f_string_length size) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return f_no_data;
    if (objects.used == 0) return f_no_data;
    if (contents.used == 0) return f_no_data;

    f_status status = f_none;
    f_string_length length_object = 0;

    f_array_length i = 0;
    f_array_length j = 0;
    f_array_length k = 0;

    for (; i < objects.used; i++) {
      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        if (fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]) == f_equal_to) {
          if (values[j]->used == 0) {
            for (k = 0; k < contents.array[i].used; k++) {
              status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[k], values[j]);

              if (f_status_is_error(status)) break;
            } // for

            if (f_status_is_error(status)) break;
          }
        }
      } // for

      if (f_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_fll_fss_snatch_

#ifndef _di_fll_fss_snatch_together_
  f_return_status fll_fss_snatch_together(const f_string_dynamic buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], f_string_dynamic *values[], const f_string_length size) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return f_no_data;
    if (objects.used == 0) return f_no_data;
    if (contents.used == 0) return f_no_data;

    f_status status = f_none;
    f_string_length length_object = 0;

    f_array_length i = 0;
    f_array_length j = 0;
    f_array_length k = 0;

    for (; i < objects.used; i++) {
      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        if (fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]) == f_equal_to) {
          for (k = 0; k < contents.array[i].used; k++) {
            status = fl_string_dynamic_partial_append_nulless(buffer, contents.array[i].array[k], values[j]);

            if (f_status_is_error(status)) break;
          } // for

          if (f_status_is_error(status)) break;
        }
      } // for

      if (f_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_fll_fss_snatch_together_

#ifndef _di_fll_fss_snatch_mash_
  f_return_status fll_fss_snatch_mash(const f_string_dynamic buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], f_string_dynamic *values[], const f_string_length size, const f_string glue, const f_string_length glue_length) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return f_no_data;
    if (objects.used == 0) return f_no_data;
    if (contents.used == 0) return f_no_data;

    f_status status = f_none;
    f_string_length length_object = 0;

    f_array_length i = 0;
    f_array_length j = 0;
    f_array_length k = 0;

    for (; i < objects.used; i++) {
      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        if (fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]) == f_equal_to) {
          if (values[j]->used == 0) {
            for (k = 0; k < contents.array[i].used; k++) {
              status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], values[j]);

              if (f_status_is_error(status)) break;
            } // for

            if (f_status_is_error(status)) break;
          }
        }
      } // for

      if (f_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_fll_fss_snatch_mash_

#ifndef _di_fll_fss_snatch_mash_together_
  f_return_status fll_fss_snatch_mash_together(const f_string_dynamic buffer, const f_fss_objects objects, const f_fss_contents contents, const f_string names[], const f_string_length lengths[], f_string_dynamic *values[], const f_string_length size, const f_string glue, const f_string_length glue_length) {
    #ifndef _di_level_2_parameter_checking_
      if (size == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    if (buffer.used == 0) return f_no_data;
    if (objects.used == 0) return f_no_data;
    if (contents.used == 0) return f_no_data;

    f_status status = f_none;
    f_string_length length_object = 0;

    f_array_length i = 0;
    f_array_length j = 0;
    f_array_length k = 0;

    for (; i < objects.used; i++) {
      length_object = (objects.array[i].stop - objects.array[i].start) + 1;

      for (j = 0; j < size; j++) {
        if (fl_string_compare_trim(buffer.string + objects.array[i].start, names[j], length_object, lengths[j]) == f_equal_to) {
          for (k = 0; k < contents.array[i].used; k++) {
            status = fl_string_dynamic_partial_mash_nulless(glue, glue_length, buffer, contents.array[i].array[k], values[j]);

            if (f_status_is_error(status)) break;
          } // for

          if (f_status_is_error(status)) break;
        }
      } // for

      if (f_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_fll_fss_snatch_mash_together_

#ifdef __cplusplus
} // extern "C"
#endif
