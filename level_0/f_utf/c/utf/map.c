#include "../utf.h"
#include "../private-utf.h"
#include "private-string.h"
#include "private-map.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_utf_string_maps_adjust_
  f_status_t f_utf_string_maps_adjust(const f_array_length_t length, f_utf_string_maps_t * const maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_maps_adjust(length, maps);
  }
#endif // _di_f_utf_string_maps_adjust_

#ifndef _di_f_utf_string_maps_append_
  f_status_t f_utf_string_maps_append(const f_utf_string_map_t source, f_utf_string_maps_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_utf_string_maps_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].name.used = 0;
    destination->array[destination->used].value.used = 0;

    if (source.name.used) {
      status = private_f_utf_string_append(source.name.string, source.name.used, &destination->array[destination->used].name);
      if (F_status_is_error(status)) return status;
    }

    if (source.value.used) {
      status = private_f_utf_string_append(source.value.string, source.value.used, &destination->array[destination->used].value);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // _di_f_utf_string_maps_append_

#ifndef _di_f_utf_string_maps_append_all_
  f_status_t f_utf_string_maps_append_all(const f_utf_string_maps_t source, f_utf_string_maps_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_utf_string_maps_append_all(source, destination);
  }
#endif // _di_f_utf_string_maps_append_all_

#ifndef _di_f_utf_string_maps_decimate_by_
  f_status_t f_utf_string_maps_decimate_by(const f_array_length_t amount, f_utf_string_maps_t * const maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (maps->size > amount) {
      return private_f_utf_string_maps_adjust(maps->size - amount, maps);
    }

    return private_f_utf_string_maps_adjust(0, maps);
  }
#endif // _di_f_utf_string_maps_decimate_by_

#ifndef _di_f_utf_string_maps_decrease_by_
  f_status_t f_utf_string_maps_decrease_by(const f_array_length_t amount, f_utf_string_maps_t * const maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (maps->size > amount) {
      return private_f_utf_string_maps_resize(maps->size - amount, maps);
    }

    return private_f_utf_string_maps_resize(0, maps);
  }
#endif // _di_f_utf_string_maps_decrease_by_

#ifndef _di_f_utf_string_maps_increase_
  f_status_t f_utf_string_maps_increase(const f_array_length_t step, f_utf_string_maps_t * const maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && maps->used + 1 > maps->size) {
      f_array_length_t size = maps->used + step;

      if (size > F_array_length_t_size_d) {
        if (maps->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_utf_string_maps_resize(size, maps);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_maps_increase_

#ifndef _di_f_utf_string_maps_increase_by_
  f_status_t f_utf_string_maps_increase_by(const f_array_length_t amount, f_utf_string_maps_t * const maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (maps->used + amount > maps->size) {
      if (maps->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_utf_string_maps_resize(maps->used + amount, maps);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_maps_increase_by_

#ifndef _di_f_utf_string_maps_resize_
  f_status_t f_utf_string_maps_resize(const f_array_length_t length, f_utf_string_maps_t * const maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_maps_resize(length, maps);
  }
#endif // _di_f_utf_string_maps_resize_

#ifndef _di_f_utf_string_mapss_adjust_
  f_status_t f_utf_string_mapss_adjust(const f_array_length_t length, f_utf_string_mapss_t * const mapss) {
    #ifndef _di_level_0_parameter_checking_
      if (!mapss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_mapss_adjust(length, mapss);
  }
#endif // _di_f_utf_string_mapss_adjust_

#ifndef _di_f_utf_string_mapss_append_
  f_status_t f_utf_string_mapss_append(const f_utf_string_maps_t source, f_utf_string_mapss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_utf_string_mapss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used].used = 0;

    if (source.used) {
      status = private_f_utf_string_maps_append_all(source, &destination->array[destination->used]);
      if (F_status_is_error(status)) return status;
    }

    ++destination->used;

    return F_none;
  }
#endif // _di_f_utf_string_mapss_append_

#ifndef _di_f_utf_string_mapss_append_all_
  f_status_t f_utf_string_mapss_append_all(const f_utf_string_mapss_t source, f_utf_string_mapss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_utf_string_mapss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_utf_string_maps_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_utf_string_mapss_append_all_

#ifndef _di_f_utf_string_mapss_decimate_by_
  f_status_t f_utf_string_mapss_decimate_by(const f_array_length_t amount, f_utf_string_mapss_t * const mapss) {
    #ifndef _di_level_0_parameter_checking_
      if (!mapss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (mapss->size > amount) {
      return private_f_utf_string_mapss_adjust(mapss->size - amount, mapss);
    }

    return private_f_utf_string_mapss_adjust(0, mapss);
  }
#endif // _di_f_utf_string_mapss_decimate_by_

#ifndef _di_f_utf_string_mapss_decrease_by_
  f_status_t f_utf_string_mapss_decrease_by(const f_array_length_t amount, f_utf_string_mapss_t * const mapss) {
    #ifndef _di_level_0_parameter_checking_
      if (!mapss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (mapss->size > amount) {
      return private_f_utf_string_mapss_resize(mapss->size - amount, mapss);
    }

    return private_f_utf_string_mapss_resize(0, mapss);
  }
#endif // _di_f_utf_string_mapss_decrease_by_

#ifndef _di_f_utf_string_mapss_increase_
  f_status_t f_utf_string_mapss_increase(const f_array_length_t step, f_utf_string_mapss_t * const mapss) {
    #ifndef _di_level_0_parameter_checking_
      if (!mapss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && mapss->used + 1 > mapss->size) {
      f_array_length_t size = mapss->used + step;

      if (size > F_array_length_t_size_d) {
        if (mapss->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return private_f_utf_string_mapss_resize(size, mapss);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_mapss_increase_

#ifndef _di_f_utf_string_mapss_increase_by_
  f_status_t f_utf_string_mapss_increase_by(const f_array_length_t amount, f_utf_string_mapss_t * const mapss) {
    #ifndef _di_level_0_parameter_checking_
      if (!mapss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (mapss->used + amount > mapss->size) {
      if (mapss->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_utf_string_mapss_resize(mapss->used + amount, mapss);
    }

    return F_data_not;
  }
#endif // _di_f_utf_string_mapss_increase_by_

#ifndef _di_f_utf_string_mapss_resize_
  f_status_t f_utf_string_mapss_resize(const f_array_length_t length, f_utf_string_mapss_t * const mapss) {
    #ifndef _di_level_0_parameter_checking_
      if (!mapss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_utf_string_mapss_resize(length, mapss);
  }
#endif // _di_f_utf_string_mapss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
