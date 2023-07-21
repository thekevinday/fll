#include "../socket.h"
#include "socket.h"
#include "private-socket.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_sockets_adjust_
  f_status_t f_sockets_adjust(const f_number_unsigned_t length, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_adjust(length, sizeof(f_socket_t), (void **) &sockets->array, &sockets->used, &sockets->size);
  }
#endif // _di_f_sockets_adjust_

#ifndef _di_f_sockets_append_
  f_status_t f_sockets_append(const f_socket_t source, f_sockets_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    const f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_socket_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // _di_f_sockets_append_

#ifndef _di_f_sockets_append_all_
  f_status_t f_sockets_append_all(const f_sockets_t source, f_sockets_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    return private_f_sockets_append_all(source, destination);
  }
#endif // _di_f_sockets_append_all_

#ifndef _di_f_sockets_decimate_by_
  f_status_t f_sockets_decimate_by(const f_number_unsigned_t amount, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decimate_by(amount, sizeof(f_socket_t), (void **) &sockets->array, &sockets->used, &sockets->size);
  }
#endif // _di_f_sockets_decimate_by_

#ifndef _di_f_sockets_decrease_by_
  f_status_t f_sockets_decrease_by(const f_number_unsigned_t amount, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_decrease_by(amount, sizeof(f_socket_t), (void **) &sockets->array, &sockets->used, &sockets->size);
  }
#endif // _di_f_sockets_decrease_by_

#ifndef _di_f_sockets_increase_
  f_status_t f_sockets_increase(const f_number_unsigned_t step, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_socket_t), (void **) &sockets->array, &sockets->used, &sockets->size);
  }
#endif // _di_f_sockets_increase_

#ifndef _di_f_sockets_increase_by_
  f_status_t f_sockets_increase_by(const f_number_unsigned_t amount, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_socket_t), (void **) &sockets->array, &sockets->used, &sockets->size);
  }
#endif // _di_f_sockets_increase_by_

#ifndef _di_f_sockets_resize_
  f_status_t f_sockets_resize(const f_number_unsigned_t length, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_resize(length, sizeof(f_socket_t), (void **) &sockets->array, &sockets->used, &sockets->size);
  }
#endif // _di_f_sockets_resize_

#ifndef _di_f_socketss_adjust_
  f_status_t f_socketss_adjust(const f_number_unsigned_t length, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_socketss_adjust(length, socketss);
  }
#endif // _di_f_socketss_adjust_

#ifndef _di_f_socketss_append_
  f_status_t f_socketss_append(const f_sockets_t source, f_socketss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase(F_memory_default_allocation_small_d, sizeof(f_sockets_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    status = private_f_sockets_append_all(source, &destination->array[destination->used]);
    if (F_status_is_error(status)) return status;

    ++destination->used;

    return F_none;
  }
#endif // _di_f_socketss_append_

#ifndef _di_f_socketss_append_all_
  f_status_t f_socketss_append_all(const f_socketss_t source, f_socketss_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!source.used) return F_data_not;

    f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_sockets_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i, ++destination->used) {

      destination->array[destination->used].used = 0;

      if (source.array[i].used) {
        status = private_f_sockets_append_all(source.array[i], &destination->array[destination->used]);
        if (F_status_is_error(status)) return status;
      }
    } // for

    return F_none;
  }
#endif // _di_f_socketss_append_all_

#ifndef _di_f_socketss_decimate_by_
  f_status_t f_socketss_decimate_by(const f_number_unsigned_t amount, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_socketss_adjust((socketss->size - amount > 0) ? socketss->size - amount : 0, socketss);
  }
#endif // _di_f_socketss_decimate_by_

#ifndef _di_f_socketss_decrease_by_
  f_status_t f_socketss_decrease_by(const f_number_unsigned_t amount, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_socketss_resize((socketss->size - amount > 0) ? socketss->size - amount : 0, socketss);
  }
#endif // _di_f_socketss_decrease_by_

#ifndef _di_f_socketss_increase_
  f_status_t f_socketss_increase(const f_number_unsigned_t step, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_sockets_t), (void **) &socketss->array, &socketss->used, &socketss->size);
  }
#endif // _di_f_socketss_increase_

#ifndef _di_f_socketss_increase_by_
  f_status_t f_socketss_increase_by(const f_number_unsigned_t amount, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_sockets_t), (void **) &socketss->array, &socketss->used, &socketss->size);
  }
#endif // _di_f_socketss_increase_by_

#ifndef _di_f_socketss_resize_
  f_status_t f_socketss_resize(const f_number_unsigned_t length, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_socketss_resize(length, socketss);
  }
#endif // _di_f_socketss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
