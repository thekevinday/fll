#include "fss_extended_read.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_read_data_delete_simple_
  void fss_extended_read_data_delete_simple(fss_extended_read_data_t *data) {

    if (!data) return;

    // data->files is expected to be statically loaded and cannot be deallocated.

    fss_extended_read_depths_resize(0, &data->depths);

    macro_f_string_dynamic_t_delete_simple(data->buffer);
    macro_f_fss_contents_t_delete_simple(data->contents);
    macro_f_fss_objects_t_delete_simple(data->objects);
    macro_f_fss_delimits_t_delete_simple(data->delimits_object);
    macro_f_fss_delimits_t_delete_simple(data->delimits_content);
    macro_f_fss_quotes_t_delete_simple(data->quotes_object);
    macro_f_fss_quotess_t_delete_simple(data->quotes_content);
  }
#endif // _di_fss_extended_read_data_delete_simple_

#ifndef _di_fss_extended_read_depth_delete_simple_
  void fss_extended_read_depth_delete_simple(fss_extended_read_depth_t *depth) {

    if (!depth) return;

    f_string_dynamic_resize(0, &depth->value_name);
  }
#endif // _di_fss_extended_read_depth_delete_simple_

#ifndef _di_fss_extended_read_depths_resize_
  f_status_t fss_extended_read_depths_resize(const f_array_length_t length, fss_extended_read_depths_t *depths) {

    if (!depths) {
      return F_status_set_error(F_parameter);
    }

    for (f_array_length_t i = length; i < depths->size; ++i) {
      fss_extended_read_depth_delete_simple(&depths->array[i]);
    } // for

    const f_status_t status = f_memory_resize(depths->size, length, sizeof(fss_extended_read_depth_t), (void **) & depths->array);
    if (F_status_is_error(status)) return status;

    depths->size = length;

    if (depths->used > depths->size) {
      depths->used = length;
    }

    return F_none;
  }
#endif // _di_fss_extended_read_depths_resize_

#ifndef _di_fss_extended_read_print_signal_received_
  void fss_extended_read_print_signal_received(fll_program_data_t * const main) {

    if (main->warning.verbosity != f_console_verbosity_verbose_e && main->warning.verbosity != f_console_verbosity_debug_e) return;

    // Must flush and reset color because the interrupt may have interrupted the middle of a print function.
    fflush(main->warning.to.stream);

    flockfile(main->warning.to.stream);

    fl_print_format("%]%r%r%[Received signal code %]", main->warning.to.stream, main->context.set.reset, f_string_eol_s, f_string_eol_s, main->context.set.warning, main->context.set.warning);
    fl_print_format("%[%i%]", main->warning.to.stream, main->context.set.notable, main->signal_received, main->context.set.notable);
    fl_print_format("%[.%]%r", main->warning.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s);

    funlockfile(main->warning.to.stream);
  }
#endif // _di_fss_extended_read_print_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif
