#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_fss_identify_) || !defined(_di_fll_fss_identify_file_)
  f_status_t private_fll_fss_identify(const f_string_static_t buffer, f_fss_header_t *header) {
    register f_array_length_t i = 0;

    if (buffer.used < 10) {
      // "# fss-0000" is always at least 10 characters.
      return FL_fss_header_not;
    }

    // If this correctly follows the FSS specification, then this should be all that needs to be done (as well as atoh for ascii to hex).
    // All characters used in the identifier are only in the ascii equivalents of the characters, any similarly looking character or number representing in UTF-8 is considered invalid.
    if (buffer.string[i] == f_fss_type_header_open) {
      i++;

      if (buffer.string[i] == f_fss_type_header_part1) {
        i++;

        if (buffer.string[i] == f_fss_type_header_part2) {
          i++;

          if (buffer.string[i] == f_fss_type_header_part3) {
            i++;

            if (buffer.string[i] == f_fss_type_header_part4) {
              i++;

              if (buffer.string[i] == f_fss_type_header_part5) {
                i++;

                if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                  i++;

                  if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                    i++;

                    if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                      i++;

                      if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                        i++;

                        f_string_range_t range = f_string_range_t_initialize;

                        range.start = i - 4;
                        range.stop = i;

                        // 1: A possibly valid header type was found, now convert it into its proper format and save the header type.
                        const f_status_t status = fl_conversion_string_to_hexidecimal_unsigned(buffer.string, range, &header->type);
                        if (F_status_is_error(status)) return status;

                        if (status == F_none) {
                          // 2: At this point, we can still know the proper format for the file and still have a invalid header, handle accordingly.
                          if (buffer.string[i] == f_fss_type_header_close) {
                            header->length = i + 1;

                            return F_none;
                          }
                          else {
                            // @todo this needs to be changed to support sub-headers (maybe something like FL_fss_accepted_additional).
                            // if "# fss-0000" is there, regardless of whats next, we can guess this to be of fss-0000, even if its fss-00001 (this is a guess afterall).
                            header->length = i + 1;

                            return F_status_set_warning(FL_fss_accepted_invalid);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      // people can miss spaces, so lets accept in an attempt to interpret the file anyway, but return values at this point are to be flagged as invalid.
      else if (buffer.string[i] == f_fss_type_header_part2) {
        i++;

        if (buffer.string[i] == f_fss_type_header_part3) {
          i++;

          if (buffer.string[i] == f_fss_type_header_part4) {
            i++;

            if (buffer.string[i] == f_fss_type_header_part5) {
              i++;

              if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                i++;

                if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                  i++;

                  if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                    i++;

                    if (f_conversion_character_is_hexidecimal(buffer.string[i]) == F_true) {
                      // @todo this needs to be changed to support sub-headers (maybe something like FL_fss_accepted_additional).
                      i++;

                      f_string_range_t range = f_string_range_t_initialize;

                      range.start = i - 4;
                      range.stop = i;

                      const f_status_t status = fl_conversion_string_to_hexidecimal_unsigned(buffer.string, range, &header->type);
                      if (F_status_is_error(status)) return status;

                      header->length = i + 1;

                      return F_status_set_warning(FL_fss_accepted_invalid);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    // @todo At some point add checksum and compressions checks here, but the above statements will have to be adjusted accordingly.
    // 3: eventually this will be processing the checksum and 4: will be processing the compression.

    return FL_fss_header_not;
  }
#endif // !defined(_di_fll_fss_identify_) || !defined(_di_fll_fss_identify_file_)

#ifdef __cplusplus
} // extern "C"
#endif
