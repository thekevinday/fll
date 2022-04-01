#include "fss_embedded_list_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_main_preprocess_depth_
  f_status_t fss_embedded_list_read_main_preprocess_depth(fss_embedded_list_read_data_t * const data, fss_embedded_list_read_depths_t *depths) {

    f_status_t status = F_none;

    const f_array_length_t values_total = data->main->parameters.array[fss_embedded_list_read_parameter_depth_e].values.used + data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.used + data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.used;

    f_array_length_t values_order[values_total];
    f_array_length_t values_type[values_total];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    // Determine the linear order in which all of the three parameter values are to be applied.
    if (values_total) {
      memset(values_order, 0, sizeof(f_char_t) * values_total);

      f_array_length_t k = 0;
      f_array_length_t l = 0;

      for (; j < data->main->parameters.array[fss_embedded_list_read_parameter_depth_e].values.used; ++j) {

        values_order[i] = data->main->parameters.array[fss_embedded_list_read_parameter_depth_e].values.array[j];
        values_type[i++] = fss_embedded_list_read_parameter_depth_e;
      } // for

      if (i) {
        for (j = 0; j < data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.used; ++j) {

          for (k = 0; k < i; ++k) {

            if (values_order[k] > data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.array[j]) {
              for (l = i; l > k; --l) {
                values_order[l] = values_order[l - 1];
                values_type[l] = values_type[l - 1];
              } // for

              values_order[k] = data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.array[j];
              values_type[k] = fss_embedded_list_read_parameter_at_e;
              i++;

              break;
            }
          } // for

          if (k == i) {
            values_order[i] = data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.array[j];
            values_type[i++] = fss_embedded_list_read_parameter_at_e;
          }
        } // for
      }
      else {
        for (; j < data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.used; ++j) {

          values_order[i] = data->main->parameters.array[fss_embedded_list_read_parameter_at_e].values.array[j];
          values_type[i++] = fss_embedded_list_read_parameter_at_e;
        } // for
      }

      if (i) {
        for (j = 0; j < data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.used; ++j) {

          for (k = 0; k < i; ++k) {

            if (values_order[k] > data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.array[j]) {
              for (l = i; l > k; --l) {
                values_order[l] = values_order[l - 1];
                values_type[l] = values_type[l - 1];
              } // for

              values_order[k] = data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.array[j];
              values_type[k] = fss_embedded_list_read_parameter_name_e;
              i++;

              break;
            }
          } // for

          if (k == i) {
            values_order[i] = data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.array[j];
            values_type[i++] = fss_embedded_list_read_parameter_name_e;
          }
        } // for
      }
      else {
        for (; j < data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.used; ++j) {

          values_order[i] = data->main->parameters.array[fss_embedded_list_read_parameter_name_e].values.array[j];
          values_type[i++] = fss_embedded_list_read_parameter_name_e;
        } // for
      }
    }

    {
      i = 1;

      if (data->main->parameters.array[fss_embedded_list_read_parameter_depth_e].result == f_console_result_additional_e) {
        i = data->main->parameters.array[fss_embedded_list_read_parameter_depth_e].values.used + 1;
      }

      macro_fss_embedded_list_read_depths_t_resize(status, (*depths), i);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "fss_embedded_list_read_main_preprocess_depth", F_true);

        return status;
      }
    }

    // Provide default level-0 depth values.
    depths->array[0].depth = 0;
    depths->array[0].index_at = 0;
    depths->array[0].index_name = 0;
    depths->array[0].value_at = 0;

    {
      f_string_static_t * const argv = data->main->parameters.arguments.array;
      f_number_unsigned_t number = 0;
      bool first_depth = F_true;

      for (i = 0; i < values_total; ++i) {

        if (!((++data->main->signal_check) % fss_embedded_list_read_signal_check_d)) {
          if (fll_program_standard_signal_received(data->main)) {
            fss_embedded_list_read_print_signal_received(data);

            return F_status_set_error(F_interrupt);
          }

          data->main->signal_check = 0;
        }

        if (values_type[i] == fss_embedded_list_read_parameter_depth_e || values_type[i] == fss_embedded_list_read_parameter_at_e) {
          status = fl_conversion_dynamic_to_number_unsigned(argv[values_order[i]], &number);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(data->main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_number_unsigned", F_true, fss_embedded_list_read_long_depth_s, argv[values_order[i]]);

            return status;
          }
        }

        if (values_type[i] == fss_embedded_list_read_parameter_depth_e) {

          if (first_depth) {
            if (i && number) {
              depths->array[++depths->used].index_at = 0;
              depths->array[depths->used].index_name = 0;
              depths->array[depths->used].value_at = 0;
            }

            first_depth = F_false;
            depths->array[depths->used].depth = number;
          }
          else {
            depths->array[++depths->used].depth = number;
            depths->array[depths->used].index_at = 0;
            depths->array[depths->used].index_name = 0;
            depths->array[depths->used].value_at = 0;
          }
        }
        else if (values_type[i] == fss_embedded_list_read_parameter_at_e) {
          depths->array[depths->used].index_at = values_order[i];
          depths->array[depths->used].value_at = number;
        }
        else if (values_type[i] == fss_embedded_list_read_parameter_name_e) {
          depths->array[depths->used].index_name = values_order[i];
          depths->array[depths->used].value_name.used = 0;

          if (data->main->parameters.array[fss_embedded_list_read_parameter_trim_e].result == f_console_result_found_e) {
            status = fl_string_dynamic_rip(argv[values_order[i]], &depths->array[depths->used].value_name);

            if (F_status_is_error(status)) {
              fll_error_print(data->main->error, F_status_set_fine(status), "fl_string_dynamic_rip", F_true);

              return status;
            }
          }
          else {
            status = f_string_dynamic_append(argv[values_order[i]], &depths->array[depths->used].value_name);

            if (F_status_is_error(status)) {
              fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

              return status;
            }
          }
        }
      } // for

      depths->used++;
    }

    for (i = 0; i < depths->used; ++i) {

      for (j = i + 1; j < depths->used; ++j) {

        if (depths->array[i].depth == depths->array[j].depth) {
          flockfile(data->main->error.to.stream);

          fl_print_format("%r%[%QThe value '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->error.notable, depths->array[i].depth, data->main->error.notable);
          fl_print_format("%[' may only be specified once for the parameter '%]", data->main->error.to.stream, data->main->error.notable, data->main->error.notable);
          fl_print_format("%[%r%r%]", data->main->error.to.stream, data->main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, data->main->error.notable);
          fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

          funlockfile(data->main->error.to.stream);

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          flockfile(data->main->error.to.stream);

          fl_print_format("%r%[%QThe parameter '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
          fl_print_format("%[%r%r%]", data->main->error.to.stream, data->main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth_s, data->main->error.notable);
          fl_print_format("%[' may not have the value '%]", data->main->error.to.stream, data->main->error.notable, data->main->error.notable);
          fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->error.notable, depths->array[i].depth, data->main->error.notable);
          fl_print_format("%[' before the value '%]", data->main->error.to.stream, data->main->error.notable, data->main->error.notable);
          fl_print_format("%[%ul%]", data->main->error.to.stream, data->main->error.notable, depths->array[j].depth, data->main->error.notable);
          fl_print_format("%['.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

          funlockfile(data->main->error.to.stream);

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_embedded_list_read_main_preprocess_depth_

#ifndef _di_fss_embedded_list_read_main_process_file_
  f_status_t fss_embedded_list_read_main_process_file(fss_embedded_list_read_data_t * const data, const f_string_static_t filename, const fss_embedded_list_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits, f_fss_comments_t *comments) {

    f_status_t status = F_none;

    {
      f_state_t state = macro_f_state_t_initialize(fss_embedded_list_read_common_allocation_large_d, fss_embedded_list_read_common_allocation_small_d, 0, &fll_program_standard_signal_state, 0, (void *) data->main, 0);
      f_string_range_t input = macro_f_string_range_t_initialize2(data->buffer.used);

      objects_delimits->used = 0;
      contents_delimits->used = 0;
      comments->used = 0;

      status = fll_fss_embedded_list_read(data->buffer, state, &input, &data->nest, objects_delimits, contents_delimits, comments);

      if (F_status_is_error(status)) {
        // @todo detect and replace fll_error_file_type_file_e with fll_error_file_type_pipe_e as appropriate.
        fll_error_file_print(data->main->error, F_status_set_fine(status), "fll_fss_embedded_list_read", F_true, filename, f_file_operation_process_s, fll_error_file_type_file_e);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        macro_f_fss_nest_t_delete_simple(data->nest);
        f_string_dynamic_resize(0, &data->buffer);

        if (data->main->parameters.array[fss_embedded_list_read_parameter_total_e].result == f_console_result_found_e) {
          fll_print_format("%r%r", data->main->output.to.stream, f_string_ascii_0_s, f_string_eol_s);

          return F_none;
        }

        return F_status_set_warning(status);
      }

      if (F_status_is_error(status)) {
        macro_f_fss_nest_t_delete_simple(data->nest);
        f_string_dynamic_resize(0, &data->buffer);

        return status;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      // Comments are not to be part of the file, so remove them.
      for (; i < comments->used; ++i) {

        for (j = comments->array[i].start; j <= comments->array[i].stop; ++j) {
          data->buffer.string[j] = f_fss_delimit_placeholder_s.string[0];
        } // for
      } // for
    }

    // Requested depths cannot be greater than contents depth.
    if (depths.used > data->nest.used) {
      if (data->main->parameters.array[fss_embedded_list_read_parameter_total_e].result == f_console_result_found_e) {
        fll_print_format("%r%r", data->main->output.to.stream, f_string_ascii_0_s, f_string_eol_s);

        return F_none;
      }

      return F_none;
    }

    {
      f_number_unsigned_t select = 0;

      if (data->main->parameters.array[fss_embedded_list_read_parameter_select_e].result == f_console_result_additional_e) {
        const f_array_length_t index = data->main->parameters.array[fss_embedded_list_read_parameter_select_e].values.array[data->main->parameters.array[fss_embedded_list_read_parameter_select_e].values.used - 1];

        status = fl_conversion_dynamic_to_number_unsigned(data->main->parameters.arguments.array[index], &select);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(data->main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_number_unsigned", F_true, fss_embedded_list_read_long_select_s, data->main->parameters.arguments.array[index]);

          return status;
        }

        // This standard does not support multiple content groups.
        if (select) {
          return F_none;
        }
      }
    }

    f_array_length_t line = 0;

    if (data->main->parameters.array[fss_embedded_list_read_parameter_line_e].result == f_console_result_additional_e) {
      const f_array_length_t index = data->main->parameters.array[fss_embedded_list_read_parameter_line_e].values.array[data->main->parameters.array[fss_embedded_list_read_parameter_line_e].values.used - 1];

      status = fl_conversion_dynamic_to_number_unsigned(data->main->parameters.arguments.array[index], &line);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data->main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_number_unsigned", F_true, fss_embedded_list_read_long_line_s, data->main->parameters.arguments.array[index]);

        return status;
      }
    }

    fss_embedded_list_read_process_delimits(data, objects_delimits, contents_delimits);

    const fss_embedded_list_read_skip_t parents = fss_embedded_list_read_skip_t_initialize;


    if (data->main->parameters.array[fss_embedded_list_read_parameter_raw_e].result == f_console_result_found_e) {
      f_fss_delimits_t except_none = f_fss_delimits_t_initialize;

      return fss_embedded_list_read_main_process_for_depth(data, filename, depths, 0, line, parents, &except_none, &except_none);
    }

    return fss_embedded_list_read_main_process_for_depth(data, filename, depths, 0, line, parents, objects_delimits, contents_delimits);
  }
#endif // _di_fss_embedded_list_read_main_process_file_

#ifndef _di_fss_embedded_list_read_main_process_for_depth_
  f_status_t fss_embedded_list_read_main_process_for_depth(fss_embedded_list_read_data_t * const data, const f_string_static_t filename, const fss_embedded_list_read_depths_t depths, const f_array_length_t depths_index, const f_array_length_t line, const fss_embedded_list_read_skip_t parents, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {

    f_fss_items_t *items = &data->nest.depth[depths.array[depths_index].depth];

    bool skip[items->used];

    // Setup defaults to be not skipped unless any given parent is skipped.
    memset(skip, F_false, sizeof(skip) * items->used);

    if (parents.used) {
      for (f_array_length_t i = 0; i < items->used; ++i) {

        if (items->array[i].parent >= parents.used || parents.skip[items->array[i].parent]) {
          skip[i] = F_true;
        }
      } // for
    }

    if (depths.array[depths_index].index_name || depths.array[depths_index].index_at) {
      const f_array_lengths_t except_none = f_array_lengths_t_initialize;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      if (!depths.array[depths_index].index_name || (depths.array[depths_index].index_at && depths.array[depths_index].index_at < depths.array[depths_index].index_name)) {

        // All other non-"at" parameters must be FALSE.
        for (; i < items->used; ++i) {

          if (skip[i]) continue;

          if (j != depths.array[depths_index].value_at) {
            skip[i] = F_true;
          }

          ++j;
        } // for

        if (depths.array[depths_index].value_at < items->used && !skip[depths.array[depths_index].value_at]) {
          if (depths.array[depths_index].index_name) {

            if (data->main->parameters.array[fss_embedded_list_read_parameter_trim_e].result == f_console_result_found_e) {

              if (fl_string_dynamic_partial_compare_except_trim_dynamic(depths.array[depths_index].value_name, data->buffer, items->array[depths.array[depths_index].value_at].object, except_none, *objects_delimits) != F_equal_to) {
                skip[depths.array[depths_index].value_at] = F_true;
              }
            }
            else {
              if (fl_string_dynamic_partial_compare_except_dynamic(depths.array[depths_index].value_name, data->buffer, items->array[depths.array[depths_index].value_at].object, except_none, *objects_delimits) != F_equal_to) {
                skip[depths.array[depths_index].value_at] = F_true;
              }
            }
          }
        }
      }
      else {
        if (data->main->parameters.array[fss_embedded_list_read_parameter_trim_e].result == f_console_result_found_e) {
          for (i = 0; i < items->used; ++i) {

            if (skip[i]) continue;

            if (fl_string_dynamic_partial_compare_except_trim_dynamic(depths.array[depths_index].value_name, data->buffer, items->array[i].object, except_none, *objects_delimits) != F_equal_to) {
              skip[i] = F_true;
            }
          } // for
        }
        else {
          for (i = 0; i < items->used; ++i) {

            if (skip[i]) continue;

            if (fl_string_dynamic_partial_compare_except_dynamic(depths.array[depths_index].value_name, data->buffer, items->array[i].object, except_none, *objects_delimits) != F_equal_to) {
              skip[i] = F_true;
            }
          } // for
        }

        if (depths.array[depths_index].index_at) {

          // all other non-"at" parameters must be FALSE.
          for (i = 0, j = 0; i < items->used; ++i) {

            if (skip[i]) continue;

            if (j != depths.array[depths_index].value_at) {
              skip[i] = F_true;
            }

            ++j;
          } // for
        }
      }
    }

    // If the current depth is not the final depth, then recurse into the next depth.
    if (depths_index + 1 < depths.used) {
      bool skip_next[data->nest.depth[depths.array[depths_index + 1].depth - 1].used];

      fss_embedded_list_read_skip_t parents_next = fss_embedded_list_read_skip_t_initialize;

      if (depths.array[depths_index].depth + 1 == depths.array[depths_index + 1].depth) {
        parents_next.skip = skip;
        parents_next.used = items->used;
      }
      else {
        const f_array_length_t parents_depth = depths.array[depths_index + 1].depth - 1;
        const f_array_length_t depth_next = depths.array[depths_index + 1].depth;

        parents_next.skip = skip_next;
        parents_next.used = data->nest.depth[parents_depth].used;

        memset(skip_next, F_true, sizeof(skip_next) * parents_next.used);

        f_fss_items_t *items_next = &data->nest.depth[depth_next];
        f_fss_items_t *items_previous = 0;
        f_fss_item_t *item_previous = 0;

        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < items_next->used; ++i) {

          j = depth_next;

          item_previous = &items_next->array[i];
          items_previous = &data->nest.depth[--j];

          while (j > depths.array[depths_index].depth) {

            item_previous = &items_previous->array[item_previous->parent];
            items_previous = &data->nest.depth[--j];
          } // while

          if (skip[item_previous->parent]) {
            skip_next[items_next->array[i].parent] = F_true;
          }
          else {
            skip_next[items_next->array[i].parent] = F_false;
          }
        } // for
      }

      return fss_embedded_list_read_main_process_for_depth(data, filename, depths, depths_index + 1, line, parents_next, objects_delimits, contents_delimits);
    }

    // Process objects.
    f_array_length_t i = 0;
    f_array_length_t j = 0;

    if (data->main->parameters.array[fss_embedded_list_read_parameter_object_e].result == f_console_result_found_e) {
      if (data->main->parameters.array[fss_embedded_list_read_parameter_total_e].result == f_console_result_found_e) {
        f_array_length_t total = 0;

        for (i = 0; i < items->used; ++i) {
          if (skip[i]) continue;

          ++total;
        } // for

        fll_print_format("%ul%r", data->main->output.to.stream, total, f_string_eol_s);

        return F_none;
      }

      f_status_t (*print_object)(const f_string_static_t, const f_string_range_t, const f_array_lengths_t, FILE *) = &f_print_except_dynamic_partial;

      if (data->main->parameters.array[fss_embedded_list_read_parameter_trim_e].result == f_console_result_found_e) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      flockfile(data->main->output.to.stream);

      for (i = 0; i < items->used; ++i) {

        if (skip[i]) continue;

        print_object(data->buffer, items->array[i].object, *objects_delimits, data->main->output.to.stream);

        if (data->main->parameters.array[fss_embedded_list_read_parameter_content_e].result == f_console_result_found_e) {
          fss_embedded_list_read_print_object_end(data);

          if (items->array[i].content.used) {
            f_print_except_dynamic_partial(data->buffer, items->array[i].content.array[0], *contents_delimits, data->main->output.to.stream);
          }
        }

        fss_embedded_list_read_print_set_end(data);
      } // for

      funlockfile(data->main->output.to.stream);

      return F_none;
    }

    // Process contents.
    bool include_empty = 0;

    if (data->main->parameters.array[fss_embedded_list_read_parameter_empty_e].result == f_console_result_found_e) {
      include_empty = 1;
    }

    if (data->main->parameters.array[fss_embedded_list_read_parameter_total_e].result == f_console_result_found_e) {
      f_array_length_t total = 0;

      for (i = 0; i < items->used; ++i) {

        if (skip[i]) continue;

        if (!((++data->main->signal_check) % fss_embedded_list_read_signal_check_d)) {
          if (fll_program_standard_signal_received(data->main)) {
            fss_embedded_list_read_print_signal_received(data);

            return F_status_set_error(F_interrupt);
          }

          data->main->signal_check = 0;
        }

        if (!items->array[i].content.used) {
          if (include_empty) {
            ++total;
          }

          continue;
        }

        for (j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; ++j) {

          if (!data->buffer.string[j]) continue;

          if (data->buffer.string[j] == f_string_eol_s.string[0]) {
            ++total;
          }
        } // for
      } // for

      fll_print_format("%ul%r", data->main->output.to.stream, total, f_string_eol_s);

      return F_none;
    }

    if (data->main->parameters.array[fss_embedded_list_read_parameter_line_e].result == f_console_result_additional_e) {
      f_array_length_t line_current = 0;

      flockfile(data->main->output.to.stream);

      for (; i < items->used; ++i) {

        if (skip[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            if (line_current == line) {
              fss_embedded_list_read_print_set_end(data);

              break;
            }

            ++line_current;
          }

          continue;
        }

        j = items->array[i].content.array[0].start;

        if (line_current != line) {
          for (; j <= items->array[i].content.array[0].stop; ++j) {

            if (data->buffer.string[j] == f_string_eol_s.string[0]) {
              ++line_current;

              if (line_current == line) {
                ++j;

                break;
              }
            }
          } // for
        }

        if (line_current == line) {
          if (j > items->array[i].content.array[0].stop) continue;

          for (; j <= items->array[i].content.array[0].stop; ++j) {

            if (!data->buffer.string[j]) continue;

            if (data->buffer.string[j] == f_string_eol_s.string[0]) {
              f_print_dynamic_raw(f_string_eol_s, data->main->output.to.stream);

              break;
            }

            f_print_character(data->buffer.string[j], data->main->output.to.stream);
          } // for

          break;
        }
      } // for

      funlockfile(data->main->output.to.stream);

      return F_none;
    }

    flockfile(data->main->output.to.stream);

    for (i = 0; i < items->used; ++i) {

      if (skip[i]) continue;

      if (!items->array[i].content.used) {
        if (include_empty) {
          fss_embedded_list_read_print_set_end(data);
        }

        continue;
      }

      f_print_except_dynamic_partial(data->buffer, items->array[i].content.array[0], *contents_delimits, data->main->output.to.stream);

      if (data->main->parameters.array[fss_embedded_list_read_parameter_pipe_e].result == f_console_result_found_e) {
        f_print_dynamic_raw(fss_embedded_list_read_pipe_content_end_s, data->main->output.to.stream);
      }
    } // for

    funlockfile(data->main->output.to.stream);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_main_process_for_depth_

#ifndef _di_fss_embedded_list_read_process_delimits_
  void fss_embedded_list_read_process_delimits(fss_embedded_list_read_data_t * const data, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {

    if (!data->nest.used) return;

    if ((!objects_delimits->used && !contents_delimits->used) || data->delimit_mode == fss_embedded_list_read_delimit_mode_all_e) return;

    if (data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_lesser_e && data->nest.used < data->delimit_depth) return;
    if (data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_greater_e && data->delimit_depth == 0) return;

    if (data->delimit_mode == fss_embedded_list_read_delimit_mode_none_e) {
      objects_delimits->used = 0;
      contents_delimits->used = 0;

      return;
    }

    if (data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_e || data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_greater_e) {
      if (data->delimit_depth >= data->nest.used) {
        objects_delimits->used = 0;
        contents_delimits->used = 0;

        return;
      }
    }

    const f_array_length_t original_objects_used = objects_delimits->used;
    const f_array_length_t original_contents_used = contents_delimits->used;

    f_array_length_t original_objects_delimits[original_objects_used];
    f_array_length_t original_contents_delimits[original_contents_used];

    memcpy(&original_objects_delimits, objects_delimits->array, original_objects_used * sizeof(f_array_length_t));
    memcpy(&original_contents_delimits, contents_delimits->array, original_contents_used * sizeof(f_array_length_t));

    objects_delimits->used = 0;
    contents_delimits->used = 0;

    if (data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_e) {

      // Only depth 0 objects are stored in objects_delimits.
      if (data->delimit_depth) {
        fss_embedded_list_read_process_delimits_objects(data, data->delimit_depth, original_contents_delimits, original_contents_used, contents_delimits);
      }
      else {
        fss_embedded_list_read_process_delimits_objects(data, data->delimit_depth, original_objects_delimits, original_objects_used, objects_delimits);
      }

      fss_embedded_list_read_process_delimits_contents(data, data->delimit_depth, original_contents_delimits, original_contents_used, contents_delimits);
    }
    else {
      if (data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_lesser_e) {

        // Only depth 0 objects are stored in objects_delimits.
        fss_embedded_list_read_process_delimits_objects(data, 0, original_objects_delimits, original_objects_used, objects_delimits);
        fss_embedded_list_read_process_delimits_contents(data, 0, original_contents_delimits, original_contents_used, contents_delimits);

        for (f_array_length_t i = 1; i <= data->delimit_depth && i < data->nest.used; ++i) {

          fss_embedded_list_read_process_delimits_objects(data, i, original_contents_delimits, original_contents_used, contents_delimits);
          fss_embedded_list_read_process_delimits_contents(data, i, original_contents_delimits, original_contents_used, contents_delimits);
        } // for
      }
      else if (data->delimit_mode == fss_embedded_list_read_delimit_mode_depth_greater_e) {
        for (f_array_length_t i = data->delimit_depth; i < data->nest.used; ++i) {

          fss_embedded_list_read_process_delimits_objects(data, i, original_contents_delimits, original_contents_used, contents_delimits);
          fss_embedded_list_read_process_delimits_contents(data, i, original_contents_delimits, original_contents_used, contents_delimits);
        } // for
      }
    }
  }
#endif // _di_fss_embedded_list_read_process_delimits_

#ifndef _di_fss_embedded_list_read_process_delimits_contents_
  void fss_embedded_list_read_process_delimits_contents(fss_embedded_list_read_data_t * const data, const f_array_length_t depth, const f_array_length_t original_delimits[], const f_array_length_t original_used, f_fss_delimits_t *delimits) {

    if (!original_used) return;

    f_fss_items_t *items = &data->nest.depth[depth];

    if (!items->used) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;
    f_array_length_t m = 0;

    for (i = 0; i < items->used; ++i) {

      for (j = 0; j < original_used; ++j) {

        for (k = 0; k < items->array[i].content.used; ++k) {

          if (original_delimits[j] >= items->array[i].content.array[k].start && original_delimits[j] <= items->array[i].content.array[k].stop) {

            // Preserve linear order when adding back delimits.
            if (delimits->used) {
              for (l = 0; l < delimits->used; ++l) {

                if (original_delimits[j] > delimits->array[l]) continue;
                if (original_delimits[j] == delimits->array[l]) break;

                for (m = delimits->used; m > l; --m) {
                  delimits->array[m] = delimits->array[m - 1];
                } // for

                if (fss_embedded_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
                  delimits->array[l] = original_delimits[j];
                  ++delimits->used;
                }

                break;
              } // for
            }
            else if (fss_embedded_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
              delimits->array[0] = original_delimits[j];
              delimits->used = 1;
            }
          }
        }
      } // for
    } // for
  }
#endif // _di_fss_embedded_list_read_process_delimits_contents_

#ifndef _di_fss_embedded_list_read_process_delimits_objects_
  void fss_embedded_list_read_process_delimits_objects(fss_embedded_list_read_data_t * const data, const f_array_length_t depth, const f_array_length_t original_delimits[], const f_array_length_t original_used, f_fss_delimits_t *delimits) {

    if (!original_used) return;

    f_fss_items_t *items = &data->nest.depth[depth];

    if (!items->used) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;

    for (i = 0; i < items->used; ++i) {

      for (j = 0; j < original_used; ++j) {

        if (original_delimits[j] >= items->array[i].object.start && original_delimits[j] <= items->array[i].object.stop) {

          // Preserve linear order when adding back delimits.
          if (delimits->used) {
            for (k = 0; k < delimits->used; ++k) {

              if (original_delimits[j] > delimits->array[k]) continue;
              if (original_delimits[j] == delimits->array[k]) break;

              for (l = delimits->used; l > k; --l) {
                delimits->array[l] = delimits->array[l - 1];
              } // for

              if (fss_embedded_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
                delimits->array[k] = original_delimits[j];
                ++delimits->used;
              }

              break;
            } // for
          }
          else if (fss_embedded_list_read_process_delimits_within_greater(data, depth, original_delimits[j]) == F_false) {
            delimits->array[0] = original_delimits[j];
            delimits->used = 1;
          }
        }
      } // for
    } // for
  }
#endif // _di_fss_embedded_list_read_process_delimits_objects_

#ifndef _di_fss_embedded_list_read_process_delimits_within_greater_
  f_status_t fss_embedded_list_read_process_delimits_within_greater(fss_embedded_list_read_data_t * const data, const f_array_length_t depth, const f_array_length_t location) {

    if (depth + 1 >= data->nest.used) return F_false;

    f_fss_items_t *items = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (f_array_length_t d = depth + 1; d < data->nest.used; ++d) {
      items = &data->nest.depth[d];

      for (i = 0; i < items->used; ++i) {

        for (j = 0; j < items->array[i].content.used; ++j) {

          if (location >= items->array[i].content.array[j].start && location <= items->array[i].content.array[j].stop) {
            return F_true;
          }
        } // for
      } // for
    } // for

    return F_false;
  }
#endif // _di_fss_embedded_list_read_process_delimits_within_greater_

#ifdef __cplusplus
} // extern "C"
#endif
