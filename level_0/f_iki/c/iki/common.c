#include "../iki.h"
#include "../private-iki.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_iki_syntax_
  const f_string_static_t f_iki_syntax_separator_s = macro_f_string_static_t_initialize(F_iki_syntax_separator_s, 0, F_iki_syntax_separator_s_length);
  const f_string_static_t f_iki_syntax_placeholder_s = macro_f_string_static_t_initialize(F_iki_syntax_placeholder_s, 0, F_iki_syntax_placeholder_s_length);
  const f_string_static_t f_iki_syntax_quote_double_s = macro_f_string_static_t_initialize(F_iki_syntax_quote_double_s, 0, F_iki_syntax_quote_double_s_length);
  const f_string_static_t f_iki_syntax_quote_single_s = macro_f_string_static_t_initialize(F_iki_syntax_quote_single_s, 0, F_iki_syntax_quote_single_s_length);
  const f_string_static_t f_iki_syntax_slash_s = macro_f_string_static_t_initialize(F_iki_syntax_slash_s, 0, F_iki_syntax_slash_s_length);
#endif //_di_f_iki_syntax_

#ifndef _di_f_iki_vocabulary_0001_s_
  const f_string_static_t f_iki_vocabulary_0001_address_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_address_s, 0, F_iki_vocabulary_0001_address_s_length);
  const f_string_static_t f_iki_vocabulary_0001_code_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_code_s, 0, F_iki_vocabulary_0001_code_s_length);
  const f_string_static_t f_iki_vocabulary_0001_email_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_email_s, 0, F_iki_vocabulary_0001_email_s_length);
  const f_string_static_t f_iki_vocabulary_0001_name_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_name_s, 0, F_iki_vocabulary_0001_name_s_length);
  const f_string_static_t f_iki_vocabulary_0001_phone_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_phone_s, 0, F_iki_vocabulary_0001_phone_s_length);
  const f_string_static_t f_iki_vocabulary_0001_quote_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_quote_s, 0, F_iki_vocabulary_0001_quote_s_length);
  const f_string_static_t f_iki_vocabulary_0001_uri_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_uri_s, 0, F_iki_vocabulary_0001_uri_s_length);
  const f_string_static_t f_iki_vocabulary_0001_url_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_url_s, 0, F_iki_vocabulary_0001_url_s_length);
  const f_string_static_t f_iki_vocabulary_0001_urn_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_urn_s, 0, F_iki_vocabulary_0001_urn_s_length);
  const f_string_static_t f_iki_vocabulary_0001_variable_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0001_variable_s, 0, F_iki_vocabulary_0001_variable_s_length);
#endif // _di_f_iki_vocabulary_0001_s_

#ifndef _di_f_iki_vocabulary_0002_s_
  const f_string_static_t f_iki_vocabulary_0002_context_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_context_s, 0, F_iki_vocabulary_0002_context_s_length);
  const f_string_static_t f_iki_vocabulary_0002_define_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_define_s, 0, F_iki_vocabulary_0002_define_s_length);
  const f_string_static_t f_iki_vocabulary_0002_parameter_s = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_parameter_s, 0, F_iki_vocabulary_0002_parameter_s_length);
#endif // _di_f_iki_vocabulary_0002_s_

#ifndef _di_f_iki_data_delete_
  f_status_t f_iki_data_delete(f_iki_data_t *data) {
    #ifndef _di_level_0_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = f_string_ranges_resize(0, &data->content);
    if (F_status_is_error(status)) return status;

    status = f_array_lengths_resize(0, &data->delimits);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_resize(0, &data->variable);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_resize(0, &data->vocabulary);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_iki_data_delete_

#ifndef _di_f_iki_data_destroy_
  f_status_t f_iki_data_destroy(f_iki_data_t *data) {
    #ifndef _di_level_0_parameter_checking_
      if (!data) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = f_string_ranges_adjust(0, &data->content);
    if (F_status_is_error(status)) return status;

    status = f_array_lengths_adjust(0, &data->delimits);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_adjust(0, &data->variable);
    if (F_status_is_error(status)) return status;

    status = f_string_ranges_adjust(0, &data->vocabulary);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_f_iki_data_destroy_

#ifndef _di_f_iki_datas_adjust_
  f_status_t f_iki_datas_adjust(const f_array_length_t length, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datas_adjust(length, datas);
  }
#endif // _di_f_iki_datas_adjust_

#ifndef _di_f_iki_datas_append_
  f_status_t f_iki_datas_append(const f_iki_datas_t source, f_iki_datas_t *destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_iki_datas_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      status = f_string_ranges_append(source.array[i].content, &destination->array[destination->used].content);
      if (F_status_is_error(status)) return status;

      status = f_array_lengths_append(source.array[i].delimits, &destination->array[destination->used].delimits);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_append(source.array[i].variable, &destination->array[destination->used].variable);
      if (F_status_is_error(status)) return status;

      status = f_string_ranges_append(source.array[i].vocabulary, &destination->array[destination->used].vocabulary);
      if (F_status_is_error(status)) return status;
    } // for

    return F_none;
  }
#endif // _di_f_iki_datas_append_

#ifndef _di_f_iki_datas_decimate_by_
  f_status_t f_iki_datas_decimate_by(const f_array_length_t amount, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (datas->size - amount > 0) {
      return private_f_iki_datas_adjust(datas->size - amount, datas);
    }

    return private_f_iki_datas_adjust(0, datas);
  }
#endif // _di_f_iki_datas_decimate_by_

#ifndef _di_f_iki_datas_decrease_by_
  f_status_t f_iki_datas_decrease_by(const f_array_length_t amount, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (datas->size - amount > 0) {
      return private_f_iki_datas_resize(datas->size - amount, datas);
    }

    return private_f_iki_datas_resize(0, datas);
  }
#endif // _di_f_iki_datas_decrease_by_

#ifndef _di_f_iki_datas_increase_
  f_status_t f_iki_datas_increase(const f_array_length_t step, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!step) return F_status_set_error(F_parameter);
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (datas->used + 1 > datas->size) {
      f_array_length_t size = datas->used + step;

      if (size > F_array_length_t_size_d) {
        if (datas->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_iki_datas_resize(size, datas);
    }

    return F_data_not;
  }
#endif // _di_f_iki_datas_increase_

#ifndef _di_f_iki_datas_increase_by_
  f_status_t f_iki_datas_increase_by(const f_array_length_t amount, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (datas->used + amount > datas->size) {
      if (datas->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_iki_datas_resize(datas->used + amount, datas);
    }

    return F_data_not;
  }
#endif // _di_f_iki_datas_increase_by_

#ifndef _di_f_iki_datas_resize_
  f_status_t f_iki_datas_resize(const f_array_length_t length, f_iki_datas_t *datas) {
    #ifndef _di_level_0_parameter_checking_
      if (!datas) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_iki_datas_resize(length, datas);
  }
#endif // _di_f_iki_datas_resize_

#ifdef __cplusplus
} // extern "C"
#endif
