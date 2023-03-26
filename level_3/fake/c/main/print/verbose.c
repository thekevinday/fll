#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_verbose_create_directory_
  void fake_print_verbose_create_directory(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return;
    if (print->verbosity < f_console_verbosity_verbose_e) return;

    fake_print_common_simple_variable(print, "Created directory ", path);
  }
#endif // _di_fake_print_verbose_create_directory_

#ifndef _di_fake_print_verbose_create_file_
  f_status_t fake_print_verbose_create_file(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_simple_variable(print, "Created file ", path);

    return F_none;
  }
#endif // _di_fake_print_verbose_create_file_

#ifndef _di_fake_print_verbose_directory_exists_
  f_status_t fake_print_verbose_directory_exists(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "Directory ", path, " already exists");

    return F_none;
  }
#endif // _di_fake_print_verbose_directory_exists_

#ifndef _di_fake_print_verbose_file_exists_
  f_status_t fake_print_verbose_file_exists(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "File ", path, " already exists");
  }
#endif // _di_fake_print_verbose_file_exists_

#ifndef _di_fake_print_verbose_file_exists_as_link_
  f_status_t fake_print_verbose_file_exists_as_link(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "File ", path, " already exists (as a symbolic link)");
  }
#endif // _di_fake_print_verbose_file_exists_as_link_

#ifndef _di_fake_print_verbose_file_exists_not_regular_or_link_
  f_status_t fake_print_verbose_file_exists_not_regular_or_link(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_wrapped_variable(print, "File ", path, " already exists but is not a regular file (or a symbolic link)");
  }
#endif // _di_fake_print_verbose_file_exists_not_regular_or_link_

#ifndef _di_fake_print_verbose_file_pre_populated_
  f_status_t fake_print_verbose_file_pre_populated(fl_print_t * const print, const f_string_static_t path) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    fake_print_common_simple_variable(print, "Pre-populated file ", path);
  }
#endif // _di_fake_print_verbose_file_pre_populated_

#ifndef _di_fake_print_verbose_recursive_clone_
  void fake_print_verbose_recursive_clone(const f_string_static_t source, const f_string_static_t destination, void * const void_recurse) {

    if (!void_recurse) return;

    f_directory_recurse_copy_t * const recurse = (f_directory_recurse_copy_t * const) void_recurse;

    if (!recurse->state.custom) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_main_t * const main = (fake_main_t *) recurse->state.custom;

    if (main->program.message.verbosity < f_console_verbosity_verbose_e) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_print_common_wrapped_variables(&main->program.message, "Cloned ", source, " to ", destination, 0);
  }
#endif // _di_fake_print_verbose_recursive_clone_

#ifndef _di_fake_print_verbose_recursive_copy_
  void fake_print_verbose_recursive_copy(const f_string_static_t source, const f_string_static_t destination, void * const void_recurse) {

    if (!void_recurse) return;

    f_directory_recurse_copy_t * const recurse = (f_directory_recurse_copy_t * const) void_recurse;

    if (!recurse->state.custom) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_main_t * const main = (fake_main_t *) recurse->state.custom;

    if (main->program.message.verbosity < f_console_verbosity_verbose_e) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_print_common_wrapped_variables(&main->program.message, "Copied ", source, " to ", destination, 0);
  }
#endif // _di_fake_print_verbose_recursive_copy_

#ifndef _di_fake_print_verbose_recursive_move_
  void fake_print_verbose_recursive_move(const f_string_static_t source, const f_string_static_t destination, void * const void_recurse) {

    if (!void_recurse) return;

    f_directory_recurse_copy_t * const recurse = (f_directory_recurse_copy_t * const) void_recurse;

    if (!recurse->state.custom) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_main_t * const main = (fake_main_t *) recurse->state.custom;

    if (main->program.message.verbosity < f_console_verbosity_verbose_e) {
      recurse->state.status = F_output_not;

      return;
    }

    fake_print_common_wrapped_variables(&main->program.message, "Moved ", source, " to ", destination, 0);
  }
#endif // _di_fake_print_verbose_recursive_move_

#ifdef __cplusplus
} // extern "C"
#endif
