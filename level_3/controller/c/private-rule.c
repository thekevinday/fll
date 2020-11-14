#include "controller.h"
#include "private-rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_items_increase_by_
  f_return_status controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) {
    f_status_t status = F_none;
    f_string_length_t size = items->size + amount;

    if (size > f_array_length_t_size) {
      if (items->size == f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      size = items->size;
      status = F_array_too_large;
    }

    const f_status_t status_resize = f_memory_resize((void **) & items.array, sizeof(controller_rule_items_t), items.size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    items.size = size;
    return status;
  }
#endif // _di_controller_rule_items_increase_by_

#ifndef _di_controller_rule_read_
  f_return_status controller_rule_read(const controller_data_t data, const f_string_static_t file_name, controller_rule_items_t *items) {
    f_status_t status = F_none;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    items->used = 0;

    {
      f_file_t file = f_file_t_initialize;

      status = f_file_stream_open(arguments.argv[data->remaining.array[i]], 0, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_open", F_true, file_name.string, "open", fll_error_file_type_file);
      }
      else {
        status = f_file_stream_read(file, 1, &buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_read", F_true, file_name.string, "read", fll_error_file_type_file);
        }
      }

      f_file_stream_close(F_true, &file);

      if (F_status_is_error(status)) {
        f_macro_string_dynamic_t_delete_simple(buffer);
        return F_false;
      }
    }

    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;

    if (buffer.used) {
      f_string_range_t range = f_macro_string_range_t_initialize(buffer.used);
      f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
      f_fss_comments_t comments = f_fss_comments_t_initialize;

      status = fll_fss_basic_list_read(&data_make->buffer, &range, &objects, &contents, &delimits, 0, &comments);

      if (F_status_is_error(status)) {
        fake_print_error_fss(data, status, "fll_fss_basic_list_read", data.file_data_build_fakefile.string, range, F_true);
      }
      else {
        status = fl_fss_apply_delimit(delimits, &data_make->buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
      }

      f_macro_fss_delimits_t_delete_simple(delimits);
      f_macro_fss_comments_t_delete_simple(comments);
    }

    if (F_status_is_error_not(status) && objects.used) {
      status = controller_rule_items_increase_by(objects.used, items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        for (f_array_length_t i = 0; i < objects.used; ++i) {

          status = f_fss_count_lines(buffer, objects.array[i], &items->array[items->used].line);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            break;
          }

          status = fl_string_dynamic_partial_append_nulless(buffer, objects.array[i], items->array[items->used].name);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
            break;
          }

          status = fl_string_dynamic_terminate_after(items->array[items->used].name);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }

          content.used = 0;
          status = fl_string_dynamic_partial_append(buffer, contents.array[i].array[0], &content);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append", F_true);
            break;
          }

          status = controller_rule_read_content(data, file_name, items->array[items->used].line, &content, items);
          if (F_status_is_error(status)) break;

          items->used++;
        } // for

        f_macro_fss_content_t_delete_simple(content);
      }
    }

    f_macro_fss_objects_t_delete_simple(objects);
    f_macro_fss_contents_t_delete_simple(contents);
    f_macro_string_dynamic_t_delete_simple(buffer);

    return status;
  }
#endif // _di_controller_rule_read_

#ifndef _di_controller_rule_read_content_
  f_return_status controller_rule_read_content(const controller_data_t data, const f_string_static_t file_name, const f_string_length_t line, f_string_static_t *content, controller_rule_items_t *items) {
    f_status_t status = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(content->used);
    f_string_length_t last = 0;

    f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
    f_fss_comments_t comments = f_fss_comments_t_initialize;
    f_fss_object_t child_object = f_fss_object_t_initialize;
    f_fss_content_t child_content = f_fss_content_t_initialize;
    f_fss_quote_t quote = f_fss_quote_t_initialize;

    uint8_t type = 0;

    for (range.start = 0; range.start < content->used; last = range.start, type = 0) {

      delimits.used = 0;
      status = fl_fss_extended_list_object_read(content, &range, &child_object, &delimits);

      if (F_status_is_error(status)) {
        fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true, file_name.string, "read", fll_error_file_type_file);
        break;
      }

      if (range.start >= range.stop || range.start >= content->used) {
        if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
          if (error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fprintf(data.error.to.stream, "%s%sUnterminated FSS Extended List at end of file '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
            fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, file_name.string, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
          }

          status = F_status_set_error(FL_fss_found_object_content_not);
        }

        break;
      }

      if (status == FL_fss_found_object) {
        // @fixme I just noticed that Extended List wasn't intended to be recursive, this will be updated.
        comments.used = 0;
        status = fl_fss_extended_list_content_read(content, &range, &child_content, &delimits, &comments);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true, file_name.string, "read", fll_error_file_type_file);
          break;
        }

        if (status == FL_fss_found_content) {
          type = controller_rule_item_type_multiple;
        }
      }
      else {
        status = fl_fss_basic_object_read(content, &range, &child_object, &quote, &delimits);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_basic_object_read", F_true, file_name.string, "read", fll_error_file_type_file);
          break;
        }

        if (range.start >= range.stop || range.start >= content->used) {
          // in this case, if status is FL_fss_found_object or FL_fss_found_object_content_not, there is no content so do not save this item.
          break;
        }

        if (status == FL_fss_found_object) {
          status = fl_fss_basic_content_read(content, &range, &child_content, &delimits);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_basic_content_read", F_true, file_name.string, "read", fll_error_file_type_file);
            break;
          }

          if (status == FL_fss_found_content) {
            type = controller_rule_item_type_single;
          }
        }
      }

      if (type) {
        status = fl_fss_apply_delimit(delimits, &data_make->buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, file_name.string, "read", fll_error_file_type_file);
          break;
        }

        status = f_fss_count_lines(buffer, contents.array[i], &items->array[items->used].line);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
          break;
        }

        // @todo
        //if (fl_string_dynamic_compare_string(x, items->array[i].name) == f_equal_to) {
          //items->array[i].name
          // @todo
        //}
      }
    } // for

    f_macro_fss_delimits_t_delete_simple(delimits);
    f_macro_fss_comments_t_delete_simple(comments);
    f_macro_fss_content_t_delete_simple(child_content);

    if (F_status_is_error(status)) return status;

    /*
    uint8_t type;
    uint8_t intent;

    f_string_length_t line;

    f_string_dynamic_t name;
    f_string_dynamic_t content;
    */
    /*
    status = fl_string_dynamic_partial_append_nulless(buffer, objects.array[i], items->array[i].name);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
      break;
    }

    status = fl_string_dynamic_terminate_after(items->array[i].name);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      break;
    }


    */
  }
#endif // _di_controller_rule_read_content_

#ifdef __cplusplus
} // extern "C"
#endif
