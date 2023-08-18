#include "../socket.h"
#include "private-socket.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_sockets_append_all_) || !defined(_di_f_socketss_append_) || !defined(_di_f_socketss_append_all_)
  extern f_status_t private_f_sockets_append_all(const f_sockets_t source, f_sockets_t * const destination) {

    const f_status_t status = f_memory_array_increase_by(source.used, sizeof(f_socket_t), (void **) &destination->array, &destination->used, &destination->size);
    if (F_status_is_error(status)) return status;

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_okay;
  }
#endif // !defined(_di_f_sockets_append_all_) || !defined(_di_f_socketss_append_) || !defined(_di_f_socketss_append_all_)

#if !defined(_di_f_socketss_adjust_) || !defined(_di_f_socketss_decimate_by_)
  f_status_t private_f_socketss_adjust(const f_number_unsigned_t length, f_socketss_t * const socketss) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < socketss->size; ++i) {

      status = f_memory_array_adjust(0, sizeof(f_socket_t), (void **) &socketss->array[i].array, &socketss->array[i].used, &socketss->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_adjust(length, sizeof(f_sockets_t), (void **) &socketss->array, &socketss->used, &socketss->size);
  }
#endif // !defined(_di_f_socketss_adjust_) || !defined(_di_f_socketss_decimate_by_)

#if !defined(_di_f_socketss_decrease_by_) || !defined(_di_f_socketss_increase_) || !defined(_di_f_socketss_increase_by_) || !defined(_di_f_socketss_resize_)
  f_status_t private_f_socketss_resize(const f_number_unsigned_t length, f_socketss_t * const socketss) {

    f_status_t status = F_okay;

    for (f_number_unsigned_t i = length; i < socketss->size; ++i) {

      status = f_memory_array_resize(0, sizeof(f_socket_t), (void **) &socketss->array[i].array, &socketss->array[i].used, &socketss->array[i].size);
      if (F_status_is_error(status)) return status;
    } // for

    return f_memory_array_resize(length, sizeof(f_sockets_t), (void **) &socketss->array, &socketss->used, &socketss->size);
  }
#endif // !defined(_di_f_socketss_decrease_by_) || !defined(_di_f_socketss_increase_) || !defined(_di_f_socketss_increase_by_) || !defined(_di_f_socketss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
