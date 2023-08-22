#include "../directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_recurse_do_delete_
  f_status_t f_directory_recurse_do_delete(f_directory_recurse_do_t * const recurse) {
    #ifndef _di_level_0_parameter_checking_
      if (!recurse) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &recurse->path.string, &recurse->path.used, &recurse->path.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &recurse->path_cache.string, &recurse->path_cache.used, &recurse->path_cache.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.block.array, &recurse->listing.block.used, &recurse->listing.block.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.character.array, &recurse->listing.character.used, &recurse->listing.character.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.directory.array, &recurse->listing.directory.used, &recurse->listing.directory.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.regular.array, &recurse->listing.regular.used, &recurse->listing.regular.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.link.array, &recurse->listing.link.used, &recurse->listing.link.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.fifo.array, &recurse->listing.fifo.used, &recurse->listing.fifo.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.socket.array, &recurse->listing.socket.used, &recurse->listing.socket.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.unknown.array, &recurse->listing.unknown.used, &recurse->listing.unknown.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_directory_recurse_do_delete_

#ifndef _di_f_directory_recurse_do_destroy_
  f_status_t f_directory_recurse_do_destroy(f_directory_recurse_do_t * const recurse) {
    #ifndef _di_level_0_parameter_checking_
      if (!recurse) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &recurse->path.string, &recurse->path.used, &recurse->path.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &recurse->path_cache.string, &recurse->path_cache.used, &recurse->path_cache.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.block.array, &recurse->listing.block.used, &recurse->listing.block.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.character.array, &recurse->listing.character.used, &recurse->listing.character.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.directory.array, &recurse->listing.directory.used, &recurse->listing.directory.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.regular.array, &recurse->listing.regular.used, &recurse->listing.regular.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.link.array, &recurse->listing.link.used, &recurse->listing.link.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.fifo.array, &recurse->listing.fifo.used, &recurse->listing.fifo.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.socket.array, &recurse->listing.socket.used, &recurse->listing.socket.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &recurse->listing.unknown.array, &recurse->listing.unknown.used, &recurse->listing.unknown.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_directory_recurse_do_destroy_

#ifndef _di_f_directory_recurse_dos_delete_callback_
  f_status_t f_directory_recurse_dos_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_recurse_do_t * const array = (f_directory_recurse_do_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].path.string, &array[i].path.used, &array[i].path.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].path_cache.string, &array[i].path_cache.used, &array[i].path_cache.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.block.array, &array[i].listing.block.used, &array[i].listing.block.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.character.array, &array[i].listing.character.used, &array[i].listing.character.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.directory.array, &array[i].listing.directory.used, &array[i].listing.directory.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.regular.array, &array[i].listing.regular.used, &array[i].listing.regular.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.link.array, &array[i].listing.link.used, &array[i].listing.link.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.fifo.array, &array[i].listing.fifo.used, &array[i].listing.fifo.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.socket.array, &array[i].listing.socket.used, &array[i].listing.socket.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.unknown.array, &array[i].listing.unknown.used, &array[i].listing.unknown.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_recurse_dos_delete_callback_

#ifndef _di_f_directory_recurse_dos_destroy_callback_
  f_status_t f_directory_recurse_dos_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_recurse_do_t * const array = (f_directory_recurse_do_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].path.string, &array[i].path.used, &array[i].path.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].path_cache.string, &array[i].path_cache.used, &array[i].path_cache.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.block.array, &array[i].listing.block.used, &array[i].listing.block.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.character.array, &array[i].listing.character.used, &array[i].listing.character.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.directory.array, &array[i].listing.directory.used, &array[i].listing.directory.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.regular.array, &array[i].listing.regular.used, &array[i].listing.regular.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.link.array, &array[i].listing.link.used, &array[i].listing.link.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.fifo.array, &array[i].listing.fifo.used, &array[i].listing.fifo.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.socket.array, &array[i].listing.socket.used, &array[i].listing.socket.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].listing.unknown.array, &array[i].listing.unknown.used, &array[i].listing.unknown.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_recurse_dos_destroy_callback_

#ifndef _di_f_directory_recurse_doss_delete_callback_
  f_status_t f_directory_recurse_doss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_recurse_dos_t * const array = (f_directory_recurse_dos_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].path.string, &array[i].array[j].path.used, &array[i].array[j].path.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].path_cache.string, &array[i].array[j].path_cache.used, &array[i].array[j].path_cache.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.block.array, &array[i].array[j].listing.block.used, &array[i].array[j].listing.block.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.character.array, &array[i].array[j].listing.character.used, &array[i].array[j].listing.character.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.directory.array, &array[i].array[j].listing.directory.used, &array[i].array[j].listing.directory.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.regular.array, &array[i].array[j].listing.regular.used, &array[i].array[j].listing.regular.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.link.array, &array[i].array[j].listing.link.used, &array[i].array[j].listing.link.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.fifo.array, &array[i].array[j].listing.fifo.used, &array[i].array[j].listing.fifo.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.socket.array, &array[i].array[j].listing.socket.used, &array[i].array[j].listing.socket.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.unknown.array, &array[i].array[j].listing.unknown.used, &array[i].array[j].listing.unknown.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_directory_recurse_do_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_recurse_doss_delete_callback_

#ifndef _di_f_directory_recurse_doss_destroy_callback_
  f_status_t f_directory_recurse_doss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_recurse_dos_t * const array = (f_directory_recurse_dos_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].path.string, &array[i].array[j].path.used, &array[i].array[j].path.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].path_cache.string, &array[i].array[j].path_cache.used, &array[i].array[j].path_cache.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.block.array, &array[i].array[j].listing.block.used, &array[i].array[j].listing.block.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.character.array, &array[i].array[j].listing.character.used, &array[i].array[j].listing.character.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.directory.array, &array[i].array[j].listing.directory.used, &array[i].array[j].listing.directory.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.regular.array, &array[i].array[j].listing.regular.used, &array[i].array[j].listing.regular.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.link.array, &array[i].array[j].listing.link.used, &array[i].array[j].listing.link.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.fifo.array, &array[i].array[j].listing.fifo.used, &array[i].array[j].listing.fifo.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.socket.array, &array[i].array[j].listing.socket.used, &array[i].array[j].listing.socket.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].listing.unknown.array, &array[i].array[j].listing.unknown.used, &array[i].array[j].listing.unknown.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_directory_recurse_do_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_recurse_doss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
