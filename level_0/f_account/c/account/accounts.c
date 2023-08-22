#include "../account.h"
#include "accounts.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_account_delete_
  f_status_t f_account_delete(f_account_t * const account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &account->home.string, &account->home.used, &account->home.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &account->label.string, &account->label.used, &account->label.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &account->name.string, &account->name.used, &account->name.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &account->password.string, &account->password.used, &account->password.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &account->shell.string, &account->shell.used, &account->shell.size);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_account_delete_

#ifndef _di_f_account_destroy_
  f_status_t f_account_destroy(f_account_t * const account) {
    #ifndef _di_level_0_parameter_checking_
      if (!account) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &account->home.string, &account->home.used, &account->home.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &account->label.string, &account->label.used, &account->label.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &account->name.string, &account->name.used, &account->name.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &account->password.string, &account->password.used, &account->password.size);
      if (F_status_is_error(status)) return status;

      status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &account->shell.string, &account->shell.used, &account->shell.size);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_account_destroy_

#ifndef _di_f_accounts_delete_callback_
  f_status_t f_accounts_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_account_t * const array = (f_account_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].home.string, &array[i].home.used, &array[i].home.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].label.string, &array[i].label.used, &array[i].label.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].name.string, &array[i].name.used, &array[i].name.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].password.string, &array[i].password.used, &array[i].password.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].shell.string, &array[i].shell.used, &array[i].shell.size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accounts_delete_callback_

#ifndef _di_f_accounts_destroy_callback_
  f_status_t f_accounts_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_account_t * const array = (f_account_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].home.string, &array[i].home.used, &array[i].home.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].label.string, &array[i].label.used, &array[i].label.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].name.string, &array[i].name.used, &array[i].name.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].password.string, &array[i].password.used, &array[i].password.size);
        if (F_status_is_error(status)) return status;

        status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].shell.string, &array[i].shell.used, &array[i].shell.size);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accounts_destroy_callback_

#ifndef _di_f_accountss_delete_callback_
  f_status_t f_accountss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_accounts_t * const array = (f_accounts_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].home.string, &array[i].array[j].home.used, &array[i].array[j].home.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].label.string, &array[i].array[j].label.used, &array[i].array[j].label.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].name.string, &array[i].array[j].name.used, &array[i].array[j].name.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].password.string, &array[i].array[j].password.used, &array[i].array[j].password.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_resize(0, sizeof(f_char_t), (void **) &array[i].array[j].shell.string, &array[i].array[j].shell.used, &array[i].array[j].shell.size);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_account_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accountss_delete_callback_

#ifndef _di_f_accountss_destroy_callback_
  f_status_t f_accountss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_accounts_t * const array = (f_accounts_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].home.string, &array[i].array[j].home.used, &array[i].array[j].home.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].label.string, &array[i].array[j].label.used, &array[i].array[j].label.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].name.string, &array[i].array[j].name.used, &array[i].array[j].name.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].password.string, &array[i].array[j].password.used, &array[i].array[j].password.size);
          if (F_status_is_error(status)) return status;

          status = f_memory_array_adjust(0, sizeof(f_char_t), (void **) &array[i].array[j].shell.string, &array[i].array[j].shell.used, &array[i].array[j].shell.size);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_account_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_accountss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
