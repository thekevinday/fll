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

    return private_f_sockets_adjust(length, sockets);
  }
#endif // _di_f_sockets_adjust_

#ifndef _di_f_sockets_append_
  f_status_t f_sockets_append(const f_socket_t source, f_sockets_t * const destination) {
    #ifndef _di_level_0_parameter_checking_
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_sockets_append(source, destination);
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

    if (!amount) return F_data_not;

    if (sockets->size - amount > 0) {
      return private_f_sockets_adjust(sockets->size - amount, sockets);
    }

    return private_f_sockets_adjust(0, sockets);
  }
#endif // _di_f_sockets_decimate_by_

#ifndef _di_f_sockets_decrease_by_
  f_status_t f_sockets_decrease_by(const f_number_unsigned_t amount, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sockets->size - amount > 0) {
      return private_f_sockets_resize(sockets->size - amount, sockets);
    }

    return private_f_sockets_resize(0, sockets);
  }
#endif // _di_f_sockets_decrease_by_

#ifndef _di_f_sockets_increase_
  f_status_t f_sockets_increase(const f_number_unsigned_t step, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && sockets->used + 1 > sockets->size) {
      f_number_unsigned_t size = sockets->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (sockets->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_sockets_resize(size, sockets);
    }

    return F_data_not;
  }
#endif // _di_f_sockets_increase_

#ifndef _di_f_sockets_increase_by_
  f_status_t f_sockets_increase_by(const f_number_unsigned_t amount, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (sockets->used + amount > sockets->size) {
      if (sockets->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_sockets_resize(sockets->used + amount, sockets);
    }

    return F_data_not;
  }
#endif // _di_f_sockets_increase_by_

#ifndef _di_f_sockets_resize_
  f_status_t f_sockets_resize(const f_number_unsigned_t length, f_sockets_t * const sockets) {
    #ifndef _di_level_0_parameter_checking_
      if (!sockets) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_sockets_resize(length, sockets);
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

    f_status_t status = F_none;

    if (destination->used + 1 > destination->size) {
      status = private_f_socketss_resize(destination->used + F_memory_default_allocation_small_d, destination);
      if (F_status_is_error(status)) return status;
    }

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

    f_status_t status = F_none;

    if (destination->used + source.used > destination->size) {
      status = private_f_socketss_resize(destination->used + source.used, destination);
      if (F_status_is_error(status)) return status;
    }

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

    if (socketss->size - amount > 0) {
      return private_f_socketss_adjust(socketss->size - amount, socketss);
    }

    return private_f_socketss_adjust(0, socketss);
  }
#endif // _di_f_socketss_decimate_by_

#ifndef _di_f_socketss_decrease_by_
  f_status_t f_socketss_decrease_by(const f_number_unsigned_t amount, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (socketss->size - amount > 0) {
      return private_f_socketss_resize(socketss->size - amount, socketss);
    }

    return private_f_socketss_resize(0, socketss);
  }
#endif // _di_f_socketss_decrease_by_

#ifndef _di_f_socketss_increase_
  f_status_t f_socketss_increase(const f_number_unsigned_t step, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (step && socketss->used + 1 > socketss->size) {
      f_number_unsigned_t size = socketss->used + step;

      if (size > F_number_t_size_unsigned_d) {
        if (socketss->used + 1 > F_number_t_size_unsigned_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_number_t_size_unsigned_d;
      }

      return private_f_socketss_resize(size, socketss);
    }

    return F_data_not;
  }
#endif // _di_f_socketss_increase_

#ifndef _di_f_socketss_increase_by_
  f_status_t f_socketss_increase_by(const f_number_unsigned_t amount, f_socketss_t * const socketss) {
    #ifndef _di_level_0_parameter_checking_
      if (!socketss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    if (socketss->used + amount > socketss->size) {
      if (socketss->used + amount > F_number_t_size_unsigned_d) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_socketss_resize(socketss->used + amount, socketss);
    }

    return F_data_not;
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
