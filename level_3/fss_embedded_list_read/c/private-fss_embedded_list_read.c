#include "fss_embedded_list_read.h"
#include "private-common.h"
#include "private-fss_embedded_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_read_main_preprocess_depth_
  f_status_t fss_embedded_list_read_main_preprocess_depth(const f_console_arguments_t arguments, const fss_embedded_list_read_main_t main, fss_embedded_list_read_depths_t *depths) {
    f_status_t status = F_none;

    const f_array_length_t values_total = main.parameters[fss_embedded_list_read_parameter_depth].values.used + main.parameters[fss_embedded_list_read_parameter_at].values.used + main.parameters[fss_embedded_list_read_parameter_name].values.used;

    f_array_length_t values_order[values_total];
    f_array_length_t values_type[values_total];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    // determine the linear order in which all of the three parameter values are to be applied.
    if (values_total) {
      memset(values_order, 0, values_total);

      f_array_length_t k = 0;
      f_array_length_t l = 0;

      for (; j < main.parameters[fss_embedded_list_read_parameter_depth].values.used; ++j) {

        values_order[i] = main.parameters[fss_embedded_list_read_parameter_depth].values.array[j];
        values_type[i++] = fss_embedded_list_read_parameter_depth;
      } // for

      if (i) {
        for (j = 0; j < main.parameters[fss_embedded_list_read_parameter_at].values.used; ++j) {

          for (k = 0; k < i; ++k) {

            if (values_order[k] > main.parameters[fss_embedded_list_read_parameter_at].values.array[j]) {
              for (l = i; l > k; --l) {
                values_order[l] = values_order[l - 1];
                values_type[l] = values_type[l - 1];
              } // for

              values_order[k] = main.parameters[fss_embedded_list_read_parameter_at].values.array[j];
              values_type[k] = fss_embedded_list_read_parameter_at;
              i++;
              break;
            }
          } // for

          if (k == i) {
            values_order[i] = main.parameters[fss_embedded_list_read_parameter_at].values.array[j];
            values_type[i++] = fss_embedded_list_read_parameter_at;
          }
        } // for
      }
      else {
        for (; j < main.parameters[fss_embedded_list_read_parameter_at].values.used; ++j) {

          values_order[i] = main.parameters[fss_embedded_list_read_parameter_at].values.array[j];
          values_type[i++] = fss_embedded_list_read_parameter_at;
        } // for
      }

      if (i) {
        for (j = 0; j < main.parameters[fss_embedded_list_read_parameter_name].values.used; ++j) {

          for (k = 0; k < i; ++k) {

            if (values_order[k] > main.parameters[fss_embedded_list_read_parameter_name].values.array[j]) {
              for (l = i; l > k; --l) {
                values_order[l] = values_order[l - 1];
                values_type[l] = values_type[l - 1];
              } // for

              values_order[k] = main.parameters[fss_embedded_list_read_parameter_name].values.array[j];
              values_type[k] = fss_embedded_list_read_parameter_name;
              i++;
              break;
            }
          } // for

          if (k == i) {
            values_order[i] = main.parameters[fss_embedded_list_read_parameter_name].values.array[j];
            values_type[i++] = fss_embedded_list_read_parameter_name;
          }
        } // for
      }
      else {
        for (; j < main.parameters[fss_embedded_list_read_parameter_name].values.used; ++j) {

          values_order[i] = main.parameters[fss_embedded_list_read_parameter_name].values.array[j];
          values_type[i++] = fss_embedded_list_read_parameter_name;
        } // for
      }
    }

    {
      i = 1;

      if (main.parameters[fss_embedded_list_read_parameter_depth].result == f_console_result_additional) {
        i = main.parameters[fss_embedded_list_read_parameter_depth].values.used + 1;
      }

      macro_fss_embedded_list_read_depths_t_resize(status, (*depths), i);

      if (F_status_is_error(status)) {
        fll_error_print(main.error, F_status_set_fine(status), "fss_embedded_list_read_main_preprocess_depth", F_true);

        return status;
      }
    }

    // provide default level-0 depth values.
    depths->array[0].depth = 0;
    depths->array[0].index_at = 0;
    depths->array[0].index_name = 0;
    depths->array[0].value_at = 0;

    {
      f_number_unsigned_t number = 0;
      bool first_depth = F_true;

      for (i = 0; i < values_total; ++i) {

        if (values_type[i] == fss_embedded_list_read_parameter_depth || values_type[i] == fss_embedded_list_read_parameter_at) {
          const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[values_order[i]]));

          status = fl_conversion_string_to_number_unsigned(arguments.argv[values_order[i]], range, &number);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(main.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_embedded_list_read_long_depth, arguments.argv[values_order[i]]);

            return status;
          }
        }

        if (values_type[i] == fss_embedded_list_read_parameter_depth) {

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
        else if (values_type[i] == fss_embedded_list_read_parameter_at) {
          depths->array[depths->used].index_at = values_order[i];
          depths->array[depths->used].value_at = number;
        }
        else if (values_type[i] == fss_embedded_list_read_parameter_name) {
          depths->array[depths->used].index_name = values_order[i];
          depths->array[depths->used].value_name.used = 0;

          if (main.parameters[fss_embedded_list_read_parameter_trim].result == f_console_result_found) {
            status = fl_string_rip(arguments.argv[values_order[i]], strnlen(arguments.argv[values_order[i]], f_console_parameter_size), &depths->array[depths->used].value_name);

            if (F_status_is_error(status)) {
              fll_error_print(main.error, F_status_set_fine(status), "fl_string_rip", F_true);

              return status;
            }
          }
          else {
            status = f_string_append(arguments.argv[values_order[i]], strnlen(arguments.argv[values_order[i]], f_console_parameter_size), &depths->array[depths->used].value_name);

            if (F_status_is_error(status)) {
              fll_error_print(main.error, F_status_set_fine(status), "f_string_append", F_true);

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
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%sThe value '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%ul%]", main.error.to.stream, main.error.notable, depths->array[i].depth, main.error.notable);
          fl_print_format("%[' may only be specified once for the parameter '%]", main.error.to.stream, main.error.notable, main.error.notable);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth, main.error.notable);
          fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);

          return F_status_set_error(F_parameter);
        }
        else if (depths->array[i].depth > depths->array[j].depth) {
          flockfile(main.error.to.stream);

          fl_print_format("%c%[%sThe parameter '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
          fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fss_embedded_list_read_long_depth, main.error.notable);
          fl_print_format("%[' may not have the value '%]", main.error.to.stream, main.error.notable, main.error.notable);
          fl_print_format("%[%ul%]", main.error.to.stream, main.error.notable, depths->array[i].depth, main.error.notable);
          fl_print_format("%[' before the value '%]", main.error.to.stream, main.error.notable, main.error.notable);
          fl_print_format("%[%ul%]", main.error.to.stream, main.error.notable, depths->array[j].depth, main.error.notable);
          fl_print_format("%['.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

          funlockfile(main.error.to.stream);

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_embedded_list_read_main_preprocess_depth_

#ifndef _di_fss_embedded_list_read_main_process_file_
  f_status_t fss_embedded_list_read_main_process_file(const f_console_arguments_t arguments, fss_embedded_list_read_main_t *main, const f_string_t filename, const fss_embedded_list_read_depths_t depths, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits, f_fss_comments_t *comments) {

    f_status_t status = F_none;

    {
      f_state_t state = macro_f_state_t_initialize(fss_embedded_list_read_common_allocation_large, fss_embedded_list_read_common_allocation_small, 0, 0, 0, 0, 0);
      f_string_range_t input = macro_f_string_range_t_initialize(main->buffer.used);

      objects_delimits->used = 0;
      contents_delimits->used = 0;
      comments->used = 0;

      status = fll_fss_embedded_list_read(main->buffer, state, &input, &main->nest, objects_delimits, contents_delimits, comments);

      if (F_status_is_error(status)) {
        // @todo detect and replace fll_error_file_type_file with fll_error_file_type_pipe as appropriate.
        fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_embedded_list_read", F_true, filename, "process", fll_error_file_type_file);
      }
      else if (status == F_data_not_stop || status == F_data_not_eos) {
        macro_f_fss_nest_t_delete_simple(main->nest);
        macro_f_string_dynamic_t_delete_simple(main->buffer);

        if (main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
          fll_print_format("0%c", main->output.to.stream, f_string_eol_s[0]);

          return F_none;
        }

        return F_status_set_warning(status);
      }

      if (F_status_is_error(status)) {
        macro_f_fss_nest_t_delete_simple(main->nest);
        macro_f_string_dynamic_t_delete_simple(main->buffer);

        return status;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      // comments are not to be part of the file, so remove them.
      for (; i < comments->used; ++i) {
        for (j = comments->array[i].start; j <= comments->array[i].stop; ++j) {
          main->buffer.string[j] = f_fss_delimit_placeholder;
        } // for
      } // for
    }

    // Requested depths cannot be greater than contents depth.
    if (depths.used > main->nest.used) {
      if (main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
        fll_print_format("0%c", main->output.to.stream, f_string_eol_s[0]);

        return F_none;
      }

      return F_none;
    }

    {
      f_number_unsigned_t select = 0;

      if (main->parameters[fss_embedded_list_read_parameter_select].result == f_console_result_additional) {
        const f_array_length_t index = main->parameters[fss_embedded_list_read_parameter_select].values.array[main->parameters[fss_embedded_list_read_parameter_select].values.used - 1];
        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

        status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &select);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_embedded_list_read_long_select, arguments.argv[index]);

          return status;
        }

        // This standard does not support multiple content groups.
        if (select > 0) {
          return F_none;
        }
      }
    }

    f_array_length_t line = 0;

    if (main->parameters[fss_embedded_list_read_parameter_line].result == f_console_result_additional) {
      const f_array_length_t index = main->parameters[fss_embedded_list_read_parameter_line].values.array[main->parameters[fss_embedded_list_read_parameter_line].values.used - 1];
      const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments.argv[index]));

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], range, &line);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_embedded_list_read_long_line, arguments.argv[index]);

        return status;
      }
    }

    fss_embedded_list_read_process_delimits(*main, objects_delimits, contents_delimits);

    const fss_embedded_list_read_skip_t parents = fss_embedded_list_read_skip_t_initialize;


    if (main->parameters[fss_embedded_list_read_parameter_raw].result == f_console_result_found) {
      f_fss_delimits_t except_none = f_fss_delimits_t_initialize;

      return fss_embedded_list_read_main_process_for_depth(arguments, filename, depths, 0, line, parents, main, &except_none, &except_none);
    }

    return fss_embedded_list_read_main_process_for_depth(arguments, filename, depths, 0, line, parents, main, objects_delimits, contents_delimits);
  }
#endif // _di_fss_embedded_list_read_main_process_file_

#ifndef _di_fss_embedded_list_read_main_process_for_depth_
  f_status_t fss_embedded_list_read_main_process_for_depth(const f_console_arguments_t arguments, const f_string_t filename, const fss_embedded_list_read_depths_t depths, const f_array_length_t depths_index, const f_array_length_t line, const fss_embedded_list_read_skip_t parents, fss_embedded_list_read_main_t *main, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {

    f_fss_items_t *items = &main->nest.depth[depths.array[depths_index].depth];

    bool skip[items->used];

    // setup defaults to be not skipped unless any given parent is skipped.
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

        // all other non-"at" parameters must be FALSE.
        for (; i < items->used; ++i) {

          if (skip[i]) continue;

          if (j != depths.array[depths_index].value_at) {
            skip[i] = F_true;
          }

          ++j;
        } // for

        if (depths.array[depths_index].value_at < items->used && !skip[depths.array[depths_index].value_at]) {
          if (depths.array[depths_index].index_name) {

            if (main->parameters[fss_embedded_list_read_parameter_trim].result == f_console_result_found) {

              if (fl_string_dynamic_partial_compare_except_trim_dynamic(depths.array[depths_index].value_name, main->buffer, items->array[depths.array[depths_index].value_at].object, except_none, *objects_delimits) != F_equal_to) {
                skip[depths.array[depths_index].value_at] = F_true;
              }
            }
            else {
              if (fl_string_dynamic_partial_compare_except_dynamic(depths.array[depths_index].value_name, main->buffer, items->array[depths.array[depths_index].value_at].object, except_none, *objects_delimits) != F_equal_to) {
                skip[depths.array[depths_index].value_at] = F_true;
              }
            }
          }
        }
      }
      else {
        if (main->parameters[fss_embedded_list_read_parameter_trim].result == f_console_result_found) {
          for (i = 0; i < items->used; ++i) {

            if (skip[i]) continue;

            if (fl_string_dynamic_partial_compare_except_trim_dynamic(depths.array[depths_index].value_name, main->buffer, items->array[i].object, except_none, *objects_delimits) != F_equal_to) {
              skip[i] = F_true;
            }
          } // for
        }
        else {
          for (i = 0; i < items->used; ++i) {

            if (skip[i]) continue;

            if (fl_string_dynamic_partial_compare_except_dynamic(depths.array[depths_index].value_name, main->buffer, items->array[i].object, except_none, *objects_delimits) != F_equal_to) {
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

    // if the current depth is not the final depth, then recurse into the next depth.
    if (depths_index + 1 < depths.used) {
      bool skip_next[main->nest.depth[depths.array[depths_index + 1].depth - 1].used];

      fss_embedded_list_read_skip_t parents_next = fss_embedded_list_read_skip_t_initialize;

      if (depths.array[depths_index].depth + 1 == depths.array[depths_index + 1].depth) {
        parents_next.skip = skip;
        parents_next.used = items->used;
      }
      else {
        const f_array_length_t parents_depth = depths.array[depths_index + 1].depth - 1;
        const f_array_length_t depth_next = depths.array[depths_index + 1].depth;

        parents_next.skip = skip_next;
        parents_next.used = main->nest.depth[parents_depth].used;

        memset(skip_next, F_true, sizeof(skip_next) * parents_next.used);

        f_fss_items_t *items_next = &main->nest.depth[depth_next];
        f_fss_items_t *items_previous = 0;
        f_fss_item_t *item_previous = 0;

        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < items_next->used; ++i) {

          j = depth_next;

          item_previous = &items_next->array[i];
          items_previous = &main->nest.depth[--j];

          while (j > depths.array[depths_index].depth) {

            item_previous = &items_previous->array[item_previous->parent];
            items_previous = &main->nest.depth[--j];
          } // while

          if (skip[item_previous->parent]) {
            skip_next[items_next->array[i].parent] = F_true;
          }
          else {
            skip_next[items_next->array[i].parent] = F_false;
          }
        } // for
      }

      return fss_embedded_list_read_main_process_for_depth(arguments, filename, depths, depths_index + 1, line, parents_next, main, objects_delimits, contents_delimits);
    }

    // process objects.
    f_array_length_t i = 0;
    f_array_length_t j = 0;

    if (main->parameters[fss_embedded_list_read_parameter_object].result == f_console_result_found) {
      if (main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
        f_array_length_t total = 0;

        for (i = 0; i < items->used; ++i) {
          if (skip[i]) continue;

          ++total;
        } // for

        fll_print_format("%lu%c", main->output.to.stream, total, f_string_eol_s[0]);

        return F_none;
      }

      f_status_t (*print_object)(const f_string_static_t, const f_string_range_t, const f_array_lengths_t, FILE *) = &f_print_except_dynamic_partial;

      if (main->parameters[fss_embedded_list_read_parameter_trim].result == f_console_result_found) {
        print_object = &fl_print_trim_except_dynamic_partial;
      }

      flockfile(main->output.to.stream);

      for (i = 0; i < items->used; ++i) {

        if (skip[i]) continue;

        print_object(main->buffer, items->array[i].object, *objects_delimits, main->output.to.stream);

        if (main->parameters[fss_embedded_list_read_parameter_content].result == f_console_result_found) {
          fss_embedded_list_read_print_object_end(*main);

          if (items->array[i].content.used) {
            f_print_except_dynamic_partial(main->buffer, items->array[i].content.array[0], *contents_delimits, main->output.to.stream);
          }
        }

        fss_embedded_list_read_print_set_end(*main);
      } // for

      funlockfile(main->output.to.stream);

      return F_none;
    }

    // process contents.
    bool include_empty = 0;

    if (main->parameters[fss_embedded_list_read_parameter_empty].result == f_console_result_found) {
      include_empty = 1;
    }

    if (main->parameters[fss_embedded_list_read_parameter_total].result == f_console_result_found) {
      f_array_length_t total = 0;

      for (i = 0; i < items->used; ++i) {

        if (skip[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            ++total;
          }

          continue;
        }

        for (j = items->array[i].content.array[0].start; j <= items->array[i].content.array[0].stop; ++j) {

          if (!main->buffer.string[j]) continue;

          if (main->buffer.string[j] == f_string_eol_s[0]) {
            ++total;
          }
        } // for
      } // for

      fll_print_format("%lu%c", main->output.to.stream, total, f_string_eol_s[0]);

      return F_none;
    }

    if (main->parameters[fss_embedded_list_read_parameter_line].result == f_console_result_additional) {
      f_array_length_t line_current = 0;

      flockfile(main->output.to.stream);

      for (; i < items->used; ++i) {

        if (skip[i]) continue;

        if (!items->array[i].content.used) {
          if (include_empty) {
            if (line_current == line) {
              fss_embedded_list_read_print_set_end(*main);
              break;
            }

            ++line_current;
          }

          continue;
        }

        j = items->array[i].content.array[0].start;

        if (line_current != line) {
          for (; j <= items->array[i].content.array[0].stop; ++j) {

            if (main->buffer.string[j] == f_string_eol_s[0]) {
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

            if (!main->buffer.string[j]) continue;

            if (main->buffer.string[j] == f_string_eol_s[0]) {
              f_print_character(f_string_eol_s[0], main->output.to.stream);
              break;
            }

            f_print_character(main->buffer.string[j], main->output.to.stream);
          } // for

          break;
        }
      } // for

      funlockfile(main->output.to.stream);

      return F_none;
    }

    flockfile(main->output.to.stream);

    for (i = 0; i < items->used; ++i) {

      if (skip[i]) continue;

      if (!items->array[i].content.used) {
        if (include_empty) {
          fss_embedded_list_read_print_set_end(*main);
        }

        continue;
      }

      f_print_except_dynamic_partial(main->buffer, items->array[i].content.array[0], *contents_delimits, main->output.to.stream);

      if (main->parameters[fss_embedded_list_read_parameter_pipe].result == f_console_result_found) {
        f_print_character(fss_embedded_list_read_pipe_content_end, main->output.to.stream);
      }
    } // for

    funlockfile(main->output.to.stream);

    return F_none;
  }
#endif // _di_fss_embedded_list_read_main_process_for_depth_

#ifndef _di_fss_embedded_list_read_print_object_end_
  void fss_embedded_list_read_print_object_end(const fss_embedded_list_read_main_t main) {

    if (main.parameters[fss_embedded_list_read_parameter_pipe].result == f_console_result_found) {
      f_print_character(fss_embedded_list_read_pipe_content_start, main.output.to.stream);
    }
    else {
      if (main.parameters[fss_embedded_list_read_parameter_object].result == f_console_result_found && main.parameters[fss_embedded_list_read_parameter_content].result == f_console_result_found) {
        f_print_character(f_fss_embedded_list_open, main.output.to.stream);
        f_print_character(f_fss_embedded_list_open_end, main.output.to.stream);
      }
      else {
        f_print_character(f_fss_eol, main.output.to.stream);
      }
    }
  }
#endif // _di_fss_embedded_list_read_print_object_end_

#ifndef _di_fss_embedded_list_read_print_content_ignore_
  void fss_embedded_list_read_print_content_ignore(const fss_embedded_list_read_main_t main) {

    if (main.parameters[fss_embedded_list_read_parameter_pipe].result == f_console_result_found) {
      f_print_character(fss_embedded_list_read_pipe_content_ignore, main.output.to.stream);
    }
  }
#endif // _di_fss_embedded_list_read_print_content_ignore_

#ifndef _di_fss_embedded_list_read_print_set_end_
  void fss_embedded_list_read_print_set_end(const fss_embedded_list_read_main_t main) {

    if (main.parameters[fss_embedded_list_read_parameter_pipe].result == f_console_result_found) {
      f_print_character(fss_embedded_list_read_pipe_content_end, main.output.to.stream);
    }
    else {
      if (main.parameters[fss_embedded_list_read_parameter_object].result == f_console_result_found && main.parameters[fss_embedded_list_read_parameter_content].result == f_console_result_found) {
        f_print_character(f_fss_embedded_list_close, main.output.to.stream);
        f_print_character(f_fss_embedded_list_close_end, main.output.to.stream);
      }
      else {
        f_print_character(f_fss_eol, main.output.to.stream);
      }
    }
  }
#endif // _di_fss_embedded_list_read_print_set_end_

#ifndef _di_fss_embedded_list_read_process_delimits_
  void fss_embedded_list_read_process_delimits(const fss_embedded_list_read_main_t main, f_fss_delimits_t *objects_delimits, f_fss_delimits_t *contents_delimits) {

    if (!main.nest.used) return;

    if ((!objects_delimits->used && !contents_delimits->used) || main.delimit_mode == fss_embedded_list_read_delimit_mode_all) return;

    if (main.delimit_mode == fss_embedded_list_read_delimit_mode_depth_lesser && main.nest.used < main.delimit_depth) return;
    if (main.delimit_mode == fss_embedded_list_read_delimit_mode_depth_greater && main.delimit_depth == 0) return;

    if (main.delimit_mode == fss_embedded_list_read_delimit_mode_none) {
      objects_delimits->used = 0;
      contents_delimits->used = 0;
      return;
    }

    if (main.delimit_mode == fss_embedded_list_read_delimit_mode_depth || main.delimit_mode == fss_embedded_list_read_delimit_mode_depth_greater) {
      if (main.delimit_depth >= main.nest.used) {
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

    if (main.delimit_mode == fss_embedded_list_read_delimit_mode_depth) {

      // only depth 0 objects are stored in objects_delimits.
      if (main.delimit_depth) {
        fss_embedded_list_read_process_delimits_objects(main, main.delimit_depth, original_contents_delimits, original_contents_used, contents_delimits);
      }
      else {
        fss_embedded_list_read_process_delimits_objects(main, main.delimit_depth, original_objects_delimits, original_objects_used, objects_delimits);
      }

      fss_embedded_list_read_process_delimits_contents(main, main.delimit_depth, original_contents_delimits, original_contents_used, contents_delimits);
    }
    else {

      if (main.delimit_mode == fss_embedded_list_read_delimit_mode_depth_lesser) {

        // only depth 0 objects are stored in objects_delimits.
        fss_embedded_list_read_process_delimits_objects(main, 0, original_objects_delimits, original_objects_used, objects_delimits);
        fss_embedded_list_read_process_delimits_contents(main, 0, original_contents_delimits, original_contents_used, contents_delimits);

        for (f_array_length_t i = 1; i <= main.delimit_depth && i < main.nest.used; ++i) {

          fss_embedded_list_read_process_delimits_objects(main, i, original_contents_delimits, original_contents_used, contents_delimits);
          fss_embedded_list_read_process_delimits_contents(main, i, original_contents_delimits, original_contents_used, contents_delimits);
        } // for
      }
      else if (main.delimit_mode == fss_embedded_list_read_delimit_mode_depth_greater) {
        for (f_array_length_t i = main.delimit_depth; i < main.nest.used; ++i) {

          fss_embedded_list_read_process_delimits_objects(main, i, original_contents_delimits, original_contents_used, contents_delimits);
          fss_embedded_list_read_process_delimits_contents(main, i, original_contents_delimits, original_contents_used, contents_delimits);
        } // for
      }
    }
  }
#endif // _di_fss_embedded_list_read_process_delimits_

#ifndef _di_fss_embedded_list_read_process_delimits_contents_
  void fss_embedded_list_read_process_delimits_contents(const fss_embedded_list_read_main_t main, const f_array_length_t depth, const f_array_length_t original_delimits[], const f_array_length_t original_used, f_fss_delimits_t *delimits) {

    if (!original_used) return;

    f_fss_items_t *items = &main.nest.depth[depth];

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

            // preserve linear order when adding back delimits.
            if (delimits->used) {
              for (l = 0; l < delimits->used; ++l) {

                if (original_delimits[j] > delimits->array[l]) continue;
                if (original_delimits[j] == delimits->array[l]) break;

                for (m = delimits->used; m > l; --m) {
                  delimits->array[m] = delimits->array[m - 1];
                } // for

                if (fss_embedded_list_read_process_delimits_within_greater(main, depth, original_delimits[j]) == F_false) {
                  delimits->array[l] = original_delimits[j];
                  ++delimits->used;
                }

                break;
              } // for
            }
            else if (fss_embedded_list_read_process_delimits_within_greater(main, depth, original_delimits[j]) == F_false) {
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
  void fss_embedded_list_read_process_delimits_objects(const fss_embedded_list_read_main_t main, const f_array_length_t depth, const f_array_length_t original_delimits[], const f_array_length_t original_used, f_fss_delimits_t *delimits) {

    if (!original_used) return;

    f_fss_items_t *items = &main.nest.depth[depth];

    if (!items->used) return;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;

    for (i = 0; i < items->used; ++i) {

      for (j = 0; j < original_used; ++j) {

        if (original_delimits[j] >= items->array[i].object.start && original_delimits[j] <= items->array[i].object.stop) {

          // preserve linear order when adding back delimits.
          if (delimits->used) {
            for (k = 0; k < delimits->used; ++k) {

              if (original_delimits[j] > delimits->array[k]) continue;
              if (original_delimits[j] == delimits->array[k]) break;

              for (l = delimits->used; l > k; --l) {
                delimits->array[l] = delimits->array[l - 1];
              } // for

              if (fss_embedded_list_read_process_delimits_within_greater(main, depth, original_delimits[j]) == F_false) {
                delimits->array[k] = original_delimits[j];
                ++delimits->used;
              }

              break;
            } // for
          }
          else if (fss_embedded_list_read_process_delimits_within_greater(main, depth, original_delimits[j]) == F_false) {
            delimits->array[0] = original_delimits[j];
            delimits->used = 1;
          }
        }
      } // for
    } // for
  }
#endif // _di_fss_embedded_list_read_process_delimits_objects_

#ifndef _di_fss_embedded_list_read_process_delimits_within_greater_
  f_status_t fss_embedded_list_read_process_delimits_within_greater(const fss_embedded_list_read_main_t main, const f_array_length_t depth, const f_array_length_t location) {

    if (depth + 1 >= main.nest.used) return F_false;

    f_fss_items_t *items = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (f_array_length_t d = depth + 1; d < main.nest.used; ++d) {
      items = &main.nest.depth[d];

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
