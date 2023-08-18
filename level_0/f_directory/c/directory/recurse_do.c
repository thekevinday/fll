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
      f_status_t status = f_string_dynamic_resize(0, &recurse->path);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_resize(0, &recurse->path_cache);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.block);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.character);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.directory);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.regular);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.link);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.fifo);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.socket);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &recurse->listing.unknown);
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

    recurse->depth = 0;
    recurse->depth_max = 0;
    recurse->flag = 0;
    recurse->path_top = 0;

    macro_f_state_t_clear(recurse->state);
    memset((void *) &recurse->mode, 0, sizeof(f_mode_t));

    {
      f_status_t status = f_string_dynamic_adjust(0, &recurse->path);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamic_adjust(0, &recurse->path_cache);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.block);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.character);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.directory);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.regular);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.link);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.fifo);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.socket);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &recurse->listing.unknown);
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

        status = f_string_dynamic_resize(0, &array[i].path);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_resize(0, &array[i].path_cache);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.block);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.character);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.directory);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.regular);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.link);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.fifo);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.socket);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].listing.unknown);
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

        array[i].depth = 0;
        array[i].depth_max = 0;
        array[i].flag = 0;
        array[i].path_top = 0;

        macro_f_state_t_clear(array[i].state);

        memset((void *) &array[i].mode, 0, sizeof(f_mode_t));

        status = f_string_dynamic_adjust(0, &array[i].path);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_adjust(0, &array[i].path_cache);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.block);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.character);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.directory);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.regular);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.link);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.fifo);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.socket);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].listing.unknown);
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

          status = f_string_dynamic_resize(0, &array[i].array[j].path);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_resize(0, &array[i].array[j].path_cache);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.block);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.character);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.directory);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.regular);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.link);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.fifo);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.socket);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].listing.unknown);
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

          array[i].array[j].depth = 0;
          array[i].array[j].depth_max = 0;
          array[i].array[j].flag = 0;
          array[i].array[j].path_top = 0;

          macro_f_state_t_clear(array[i].array[j].state);

          memset((void *) &array[i].array[j].mode, 0, sizeof(f_mode_t));

          status = f_string_dynamic_adjust(0, &array[i].array[j].path);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamic_adjust(0, &array[i].array[j].path_cache);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.block);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.character);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.directory);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.regular);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.link);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.fifo);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.socket);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].listing.unknown);
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
