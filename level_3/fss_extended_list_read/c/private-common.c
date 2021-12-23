#include "fss_extended_list_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_read_data_delete_simple_
  void fss_extended_list_read_data_delete_simple(fss_extended_list_read_data_t *data) {

    if (!data) return;

    // data->files is expected to be statically loaded and cannot be deallocated.

    fss_extended_list_read_depths_resize(0, &data->depths);

    macro_f_string_dynamic_t_delete_simple(data->buffer);
    macro_f_fss_contents_t_delete_simple(data->contents);
    macro_f_fss_objects_t_delete_simple(data->objects);
    macro_f_fss_delimits_t_delete_simple(data->delimits_object);
    macro_f_fss_delimits_t_delete_simple(data->delimits_content);
    macro_f_fss_comments_t_delete_simple(data->comments);
  }
#endif // _di_fss_extended_list_read_data_delete_simple_

#ifndef _di_fss_extended_list_read_depth_delete_simple_
  void fss_extended_list_read_depth_delete_simple(fss_extended_list_read_depth_t *depth) {

    if (!depth) return;

    f_string_dynamic_resize(0, &depth->value_name);
  }
#endif // _di_fss_extended_list_read_depth_delete_simple_

#ifndef _di_fss_extended_list_read_depths_resize_
  f_status_t fss_extended_list_read_depths_resize(const f_array_length_t length, fss_extended_list_read_depths_t *depths) {

    if (!depths) {
      return F_status_set_error(F_parameter);
    }

    for (f_array_length_t i = length; i < depths->size; ++i) {
      fss_extended_list_read_depth_delete_simple(&depths->array[i]);
    } // for

    const f_status_t status = f_memory_resize(depths->size, length, sizeof(fss_extended_list_read_depth_t), (void **) & depths->array);

    if (F_status_is_error_not(status)) {
      depths->size = length;

      if (depths->used > depths->size) {
        depths->used = length;
      }
    }

    return status;
  }
#endif // _di_fss_extended_list_read_depths_resize_

#ifndef _di_fss_extended_list_read_print_signal_received_
  void fss_extended_list_read_print_signal_received(fss_extended_list_read_main_t * const main, const f_status_t signal) {

    if (main->warning.verbosity != f_console_verbosity_verbose) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%c%c%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s[0], f_string_eol_s[0], main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, signal, main->context.set.notable);
    fl_print_format("%[.%]%c", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s[0]);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fss_extended_list_read_print_signal_received_

#ifndef _di_fss_extended_list_read_signal_received_
  f_status_t fss_extended_list_read_signal_received(fss_extended_list_read_main_t * const main) {

    if (main->signal.id == -1) {
      return F_false;
    }

    struct signalfd_siginfo information;

    memset(&information, 0, sizeof(struct signalfd_siginfo));

    if (f_signal_read(main->signal, 0, &information) == F_signal) {
      switch (information.ssi_signo) {
        case F_signal_abort:
        case F_signal_broken_pipe:
        case F_signal_hangup:
        case F_signal_interrupt:
        case F_signal_quit:
        case F_signal_termination:
          fss_extended_list_read_print_signal_received(main, information.ssi_signo);

          return information.ssi_signo;
      }
    }

    return F_false;
  }
#endif // _di_fss_extended_list_read_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
