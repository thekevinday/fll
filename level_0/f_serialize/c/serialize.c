#include "serialize.h"
#include "private-serialize.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_serialize_from_simple_
  f_status_t f_serialize_from_simple(const f_string_static_t source, f_string_dynamics_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_okay;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t start = 0;
    f_number_unsigned_t total = 0;
    uint8_t width = 0;

    do {
      width = macro_f_utf_byte_width(source.string[i]);

      if (i + width > source.used) {
        total = i - start;

        status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &destination->array, &destination->used, &destination->size);
        if (F_status_is_error(status)) return status;

        destination->array[destination->used].used = 0;

        status = f_string_append(source.string + start, total, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;

        ++destination->used;

        return F_complete_not_utf_eos;
      }

      if (source.string[i] == f_serialize_to_simple_splitter_s.string[0]) {
        total = i - start;

        status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &destination->array, &destination->used, &destination->size);
        if (F_status_is_error(status)) return status;

        destination->array[destination->used].used = 0;

        status = f_string_append(source.string + start, total, &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;

        ++destination->used;
        start = i + width;

        // Handle case when splitter as at the end of the string, creating a new empty string.
        if (start == source.used) {
          status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &destination->array, &destination->used, &destination->size);
          if (F_status_is_error(status)) return status;

          destination->array[++destination->used].used = 0;
        }
      }

      i += width;

    } while (i < source.used);

    if (start < source.used) {
      total = source.used - start;

      status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &destination->array, &destination->used, &destination->size);
      if (F_status_is_error(status)) return status;

      destination->array[destination->used].used = 0;

      status = f_string_append(source.string + start, total, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;

      ++destination->used;
    }

    return F_okay;
  }
#endif // _di_f_serialize_from_simple_

#ifndef _di_f_serialize_from_simple_get_
  f_status_t f_serialize_from_simple_get(const f_string_static_t source, const f_number_unsigned_t index, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_range_t range = f_range_t_initialize;

    f_status_t status = private_f_serialize_from_simple_select(source, index, &range);
    if (F_status_is_error(status)) return status;

    if (status == F_data_not_eos) {
      return status;
    }

    const f_number_unsigned_t total = (range.stop - range.start) + 1;

    if (range.start <= range.stop) {
      const f_status_t status_allocation = f_string_append(source.string + range.start, total, destination);
      if (F_status_is_error(status_allocation)) return status_allocation;
    }

    return status;
  }
#endif // _di_f_serialize_from_simple_get_

#ifndef _di_f_serialize_from_simple_range_
  f_status_t f_serialize_from_simple_range(const f_string_static_t source, f_ranges_t * const ranges) {
    #ifndef _di_level_0_parameter_checking_
      if (!ranges) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_okay;
    f_number_unsigned_t i = 0;
    f_number_unsigned_t start = 0;
    f_number_unsigned_t total = 0;
    uint8_t width = 0;

    do {
      width = macro_f_utf_byte_width(source.string[i]);

      if (i + width > source.used) {
        total = i - start;

        status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
        if (F_status_is_error(status)) return status;

        if (total) {
          ranges->array[ranges->used].start = start;
          ranges->array[ranges->used++].stop = start + (total - 1);
        }
        else {
          ranges->array[ranges->used].start = 1;
          ranges->array[ranges->used++].stop = 0;
        }

        return F_complete_not_utf_eos;
      }

      if (source.string[i] == f_serialize_to_simple_splitter_s.string[0]) {
        total = i - start;

        status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
        if (F_status_is_error(status)) return status;

        if (total) {
          ranges->array[ranges->used].start = start;
          ranges->array[ranges->used++].stop = start + (total - 1);
        }
        else {
          ranges->array[ranges->used].start = 1;
          ranges->array[ranges->used++].stop = 0;
        }

        start = i + width;

        // Handle case when splitter as at the end of the string, creating a new empty string.
        if (start == source.used) {
          status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
          if (F_status_is_error(status)) return status;

          ranges->array[ranges->used].start = 1;
          ranges->array[ranges->used++].stop = 0;
        }
      }

      i += width;

    } while (i < source.used);

    if (start < source.used) {
      total = source.used - start;

      status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_range_t), (void **) &ranges->array, &ranges->used, &ranges->size);
      if (F_status_is_error(status)) return status;

      if (total) {
        ranges->array[ranges->used].start = start;
        ranges->array[ranges->used++].stop = start + (total - 1);
      }
      else {
        ranges->array[ranges->used].start = 1;
        ranges->array[ranges->used++].stop = 0;
      }
    }

    return F_okay;
  }
#endif // _di_f_serialize_from_simple_range_

#ifndef _di_f_serialize_from_simple_select_
  f_status_t f_serialize_from_simple_select(const f_string_static_t source, const f_number_unsigned_t index, f_range_t * const range) {
    #ifndef _di_level_0_parameter_checking_
      if (!range) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_serialize_from_simple_select(source, index, range);
  }
#endif // _di_f_serialize_from_simple_select_

#ifndef _di_f_serialize_to_simple_
  f_status_t f_serialize_to_simple(const f_string_static_t source, f_string_dynamic_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_okay;

    if (destination->used) {
      status = f_string_dynamic_append_assure(f_serialize_to_simple_splitter_s, destination);
      if (F_status_is_error(status)) return status;
    }

    status = f_string_dynamic_append(source, destination);
    if (F_status_is_error(status)) return status;

    return F_okay;
  }
#endif // _di_f_serialize_to_simple_

#ifdef __cplusplus
} // extern "C"
#endif
