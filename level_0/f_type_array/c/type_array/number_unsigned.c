#include "../type_array.h"
#include "number_unsigned.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_number_unsigneds_append_
  f_status_t f_number_unsigneds_append(const f_number_unsigned_t source, f_number_unsigneds_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_append((const void *) &source, sizeof(f_number_unsigned_t), (void **) &destination->array, &destination->used, &destination->size);
  }
#endif // _di_f_number_unsigneds_append_

#ifndef _di_f_number_unsigneds_append_all_
  f_status_t f_number_unsigneds_append_all(const f_number_unsigneds_t source, f_number_unsigneds_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return f_memory_array_append_all((const void *) &source.array, source.used, sizeof(f_number_unsigned_t), (void **) &destination->array, &destination->used, &destination->size);
  }
#endif // _di_f_number_unsigneds_append_all_

#ifndef _di_f_number_unsigneds_decimate_by_
  f_status_t f_number_unsigneds_decimate_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_number_unsigned_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsigneds_decimate_by_

#ifndef _di_f_number_unsigneds_decrease_by_
  f_status_t f_number_unsigneds_decrease_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_number_unsigned_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsigneds_decrease_by_

#ifndef _di_f_number_unsigneds_increase_
  f_status_t f_number_unsigneds_increase(const f_number_unsigned_t step, f_number_unsigneds_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_number_unsigned_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsigneds_increase_

#ifndef _di_f_number_unsigneds_increase_by_
  f_status_t f_number_unsigneds_increase_by(const f_number_unsigned_t amount, f_number_unsigneds_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_number_unsigned_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsigneds_increase_by_

#ifndef _di_f_number_unsignedss_adjust_
  f_status_t f_number_unsignedss_adjust(const f_number_unsigned_t length, f_number_unsignedss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < structure->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_number_unsigneds_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsignedss_adjust_

#ifndef _di_f_number_unsignedss_append_
  f_status_t f_number_unsignedss_append(const f_number_unsigneds_t source, f_number_unsignedss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_number_unsigneds_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = f_memory_array_append_all((const void *) &source.array, source.used, sizeof(f_number_unsigned_t), (void **) &destination->array[destination->used].array, &destination->array[destination->used].used, &destination->array[destination->used].size);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_number_unsignedss_append_

#ifndef _di_f_number_unsignedss_append_all_
  f_status_t f_number_unsignedss_append_all(const f_number_unsignedss_t source, f_number_unsignedss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_number_unsigneds_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = f_memory_array_append_all((const void *) &source.array[i].array, source.array[i].used, sizeof(f_number_unsigned_t), (void **) &destination->array[destination->used].array, &destination->array[destination->used].used, &destination->array[destination->used].size);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_number_unsignedss_append_all_

#ifndef _di_f_number_unsignedss_decimate_by_
  f_status_t f_number_unsignedss_decimate_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    const f_number_unsigned_t length = (structure->size - amount > 0) ? structure->size - amount : 0;

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_adjust(length, sizeof(f_number_unsigneds_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsignedss_decimate_by_

#ifndef _di_f_number_unsignedss_decrease_by_
  f_status_t f_number_unsignedss_decrease_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    const f_number_unsigned_t length = (structure->size - amount > 0) ? structure->size - amount : 0;

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_number_unsigneds_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsignedss_decrease_by_

#ifndef _di_f_number_unsignedss_increase_
  f_status_t f_number_unsignedss_increase(const f_number_unsigned_t step, f_number_unsignedss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && structure->used + 1 > structure->size) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      f_number_unsigned_t length = structure->used + step;

      if (length > F_number_t_size_unsigned_d) {
        if (structure->used + 1 > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        length = F_number_t_size_unsigned_d;
      }

      {
        f_status_t status = F_none;

        for (f_number_unsigned_t i = length; i < structure->size; ++i) {

          status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
          if (F_status_is_error(status)) return status;
        } // for
      }

      return f_memory_array_resize(length, sizeof(f_number_unsigneds_t), (void **) &structure->array, &structure->used, &structure->size);
    }

    return F_data_not;
  }
#endif // _di_f_number_unsignedss_increase_

#ifndef _di_f_number_unsignedss_increase_by_
  f_status_t f_number_unsignedss_increase_by(const f_number_unsigned_t amount, f_number_unsignedss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (amount) {
      if (structure->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = structure->used + amount;

      if (length > structure->size) {
        if (length > F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

        {
          f_status_t status = F_none;

          for (f_number_unsigned_t i = length; i < structure->size; ++i) {

            status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
            if (F_status_is_error(status)) return status;
          } // for
        }

        return f_memory_array_resize(length, sizeof(f_number_unsigneds_t), (void **) &structure->array, &structure->used, &structure->size);
      }
    }

    return F_data_not;
  }
#endif // _di_f_number_unsignedss_increase_by_

#ifndef _di_f_number_unsignedss_resize_
  f_status_t f_number_unsignedss_resize(const f_number_unsigned_t length, f_number_unsignedss_t * const structure) {
    #ifndef _di_level_0_parameter_checking_
      if (!structure) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = F_none;

      for (f_number_unsigned_t i = length; i < structure->size; ++i) {

        status = f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &structure->array[i].array, &structure->array[i].used, &structure->array[i].size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return f_memory_array_resize(length, sizeof(f_number_unsigneds_t), (void **) &structure->array, &structure->used, &structure->size);
  }
#endif // _di_f_number_unsignedss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
