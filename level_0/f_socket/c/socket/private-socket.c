#include "../socket.h"
#include "private-socket.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_sockets_adjust_) || !defined(_di_f_sockets_decimate_by_)
  f_status_t private_f_sockets_adjust(const f_number_unsigned_t length, f_sockets_t * const sockets) {

    const f_status_t status = f_memory_adjust(sockets->size, length, sizeof(f_socket_t), (void **) & sockets->array);
    if (F_status_is_error(status)) return status;

    sockets->size = length;

    if (sockets->used > sockets->size) {
      sockets->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_sockets_adjust_) || !defined(_di_f_sockets_decimate_by_)

#if !defined(_di_f_sockets_append_) || !defined(_di_f_socketss_append_)
  extern f_status_t private_f_sockets_append(const f_socket_t source, f_sockets_t * const destination) {

    if (destination->used + 1 > destination->size) {
      const f_status_t status = private_f_sockets_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

    destination->array[destination->used++] = source;

    return F_none;
  }
#endif // !defined(_di_f_sockets_append_) || !defined(_di_f_socketss_append_)

#if !defined(_di_f_sockets_append_) || !defined(_di_f_sockets_append_all_) || !defined(_di_f_socketss_append_all_)
  extern f_status_t private_f_sockets_append_all(const f_sockets_t source, f_sockets_t * const destination) {



    if (destination->used + source.used > destination->size) {
      const f_status_t status = private_f_sockets_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {
      destination->array[destination->used++] = source.array[i];
    } // for

    return F_none;
  }
#endif // !defined(_di_f_sockets_append_) || !defined(_di_f_sockets_append_all_) || !defined(_di_f_socketss_append_all_)

#if !defined(_di_f_sockets_resize_) || !defined(_di_f_sockets_append_) || !defined(_di_f_sockets_decrease_by_) || !defined(_di_f_socketss_append_)
  f_status_t private_f_sockets_resize(const f_number_unsigned_t length, f_sockets_t * const sockets) {

    const f_status_t status = f_memory_resize(sockets->size, length, sizeof(f_socket_t), (void **) & sockets->array);
    if (F_status_is_error(status)) return status;

    sockets->size = length;

    if (sockets->used > sockets->size) {
      sockets->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_sockets_resize_) || !defined(_di_f_sockets_append_) || !defined(_di_f_sockets_decrease_by_) || !defined(_di_f_socketss_append_)

#if !defined(_di_f_socketss_adjust_) || !defined(_di_f_socketss_decimate_by_)
  f_status_t private_f_socketss_adjust(const f_number_unsigned_t length, f_socketss_t * const socketss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < socketss->size; ++i) {

      status = f_memory_destroy(socketss->array[i].size, sizeof(f_socket_t), (void **) & socketss->array[i].array);
      if (F_status_is_error(status)) return status;

      socketss->array[i].size = 0;
      socketss->array[i].used = 0;
    } // for

    status = f_memory_adjust(socketss->size, length, sizeof(f_sockets_t), (void **) & socketss->array);
    if (F_status_is_error(status)) return status;

    socketss->size = length;

    if (socketss->used > socketss->size) {
      socketss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_socketss_adjust_) || !defined(_di_f_socketss_decimate_by_)

#if !defined(_di_f_socketss_decrease_by_) || !defined(_di_f_socketss_increase_) || !defined(_di_f_socketss_increase_by_) || !defined(_di_f_socketss_resize_)
  f_status_t private_f_socketss_resize(const f_number_unsigned_t length, f_socketss_t * const socketss) {

    f_status_t status = F_none;

    for (f_number_unsigned_t i = length; i < socketss->size; ++i) {

      status = f_memory_delete(socketss->array[i].size, sizeof(f_socket_t), (void **) & socketss->array[i].array);
      if (F_status_is_error(status)) return status;

      socketss->array[i].size = 0;
      socketss->array[i].used = 0;
    } // for

    status = f_memory_resize(socketss->size, length, sizeof(f_sockets_t), (void **) & socketss->array);
    if (F_status_is_error(status)) return status;

    socketss->size = length;

    if (socketss->used > socketss->size) {
      socketss->used = length;
    }

    return F_none;
  }
#endif // !defined(_di_f_socketss_decrease_by_) || !defined(_di_f_socketss_increase_) || !defined(_di_f_socketss_increase_by_) || !defined(_di_f_socketss_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
