#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_load_fakefile_
  void fake_make_load_fakefile(fake_make_data_t * const data_make, const bool process_pipe) {

    if (!data_make || !data_make->data || !data_make->main) return;
    if (F_status_is_error(data_make->main->setting.state.status)) return;
    if (fake_signal_check(data_make->main)) return;

    data_make->fakefile.used = 0;

    if (process_pipe) {
      fake_pipe_buffer(data_make->data, &data_make->main->buffer);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        fake_string_dynamic_reset(&data_make->main->buffer);
      }
      else {
        data_make->main->setting.state.status = f_string_dynamic_append_assure(f_string_eol_s, &data_make->main->buffer);
      }
    }

    if (F_status_is_error_not(data_make->main->setting.state.status)) {
      fake_file_buffer(data_make->data, data_make->data->file_data_build_fakefile, process_pipe ? F_false : F_true, &data_make->main->buffer);
    }

    if (F_status_is_error(data_make->main->setting.state.status)) return;

    if (!data_make->main->buffer.used) {
      fake_make_print_warning_fakefile_empty(&data_make->main->program.warning, data_make->data->file_data_build_fakefile);

      return;
    }

    f_string_ranges_t list_objects = f_string_ranges_t_initialize;
    f_string_rangess_t list_contents = f_string_rangess_t_initialize;
    f_number_unsigneds_t delimits = f_number_unsigneds_t_initialize;

    {
      f_string_range_t range = macro_f_string_range_t_initialize_2(data_make->main->buffer.used);
      f_string_ranges_t comments = f_string_ranges_t_initialize;

      fll_fss_basic_list_read(data_make->main->buffer, &range, &list_objects, &list_contents, &delimits, 0, &comments, &data_make->main->setting.state);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        fake_print_error_fss(&data_make->main->program.error, macro_fake_f(fll_fss_basic_list_read), data_make->data->file_data_build_fakefile, range, F_true);
      }
      else {
        f_fss_apply_delimit(delimits, &data_make->main->buffer, &data_make->main->setting.state);

        if (F_status_is_error(data_make->main->setting.state.status)) {
          fake_print_error(&data_make->main->program.error, macro_fake_f(f_fss_apply_delimit));
        }

        delimits.used = 0;
      }

      f_string_ranges_resize(0, &comments);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        f_string_ranges_resize(0, &list_objects);
        f_string_rangess_resize(0, &list_contents);
        f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);

        return;
      }
    }

    {
      bool missing_main = F_true;
      bool missing_settings = F_true;

      f_fss_set_t settings = f_fss_set_t_initialize;

      data_make->fakefile.used = 0;

      data_make->main->setting.state.status = f_memory_array_increase_by(list_objects.used, sizeof(f_fss_named_t), (void **) &data_make->fakefile.array, &data_make->fakefile.used, &data_make->fakefile.size);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        fake_print_error(&data_make->main->program.error, macro_fake_f(f_memory_array_resize));

        f_fss_set_delete(&settings);
        f_string_ranges_resize(0, &list_objects);
        f_string_rangess_resize(0, &list_contents);
        f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);

        return;
      }

      {
        f_string_range_t content_range = f_string_range_t_initialize;

        for (f_number_unsigned_t i = 0; i < list_objects.used; ++i) {

          if (fake_signal_check(data_make->main)) break;

          if (f_compare_dynamic_partial_string(fake_make_item_settings_s.string, data_make->main->buffer, fake_make_item_settings_s.used, list_objects.array[i]) == F_equal_to) {
            if (!missing_settings) {
              fake_make_print_warning_setting_object_multiple(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, fake_make_item_settings_s);

              continue;
            }

            delimits.used = 0;
            content_range = list_contents.array[i].array[0];

            fll_fss_extended_read(data_make->main->buffer, &content_range, &settings.objects, &settings.contents, 0, 0, &delimits, 0, &data_make->main->setting.state);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error_fss(&data_make->main->program.error, macro_fake_f(fll_fss_extended_read), data_make->data->file_data_build_fakefile, content_range, F_true);

              break;
            }

            f_fss_apply_delimit(delimits, &data_make->main->buffer, &data_make->main->setting.state);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error(&data_make->main->program.error, macro_fake_f(f_fss_apply_delimit));

              break;
            }

            missing_settings = F_false;

            continue;
          }

          if (f_compare_dynamic_partial_string(fake_make_item_main_s.string, data_make->main->buffer, fake_make_item_main_s.used, list_objects.array[i]) == F_equal_to) {
            if (!missing_main) {
              fake_make_print_warning_setting_object_multiple(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, fake_make_item_main_s);

              continue;
            }

            missing_main = F_false;
            data_make->id_main = data_make->fakefile.used;
          }

          delimits.used = 0;
          data_make->fakefile.array[data_make->fakefile.used].name = list_objects.array[i];
          data_make->fakefile.array[data_make->fakefile.used].objects.used = 0;
          data_make->fakefile.array[data_make->fakefile.used].contents.used = 0;
          data_make->fakefile.array[data_make->fakefile.used].quotess.used = 0;

          if (list_contents.array[i].used) {
            content_range = list_contents.array[i].array[0];

            fll_fss_extended_read(data_make->main->buffer, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, &data_make->fakefile.array[data_make->fakefile.used].quotess, &delimits, 0, &data_make->main->setting.state);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error_fss(&data_make->main->program.error, macro_fake_f(fll_fss_extended_read), data_make->data->file_data_build_fakefile, content_range, F_true);

              break;
            }

            f_fss_apply_delimit(delimits, &data_make->main->buffer, &data_make->main->setting.state);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error(&data_make->main->program.error, macro_fake_f(f_fss_apply_delimit));

              break;
            }
          }

          ++data_make->fakefile.used;
        } // for
      }

      f_string_ranges_resize(0, &list_objects);
      f_string_rangess_resize(0, &list_contents);
      f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &delimits.array, &delimits.used, &delimits.size);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        f_fss_set_delete(&settings);

        return;
      }

      // Set the id out of range to designate that it is missing.
      if (missing_main) {
        data_make->id_main = data_make->fakefile.used;
      }

      // Always have the parameter variable "return" map at index 0 and be pre-initialized.
      {
        f_string_t function_name = macro_fake_f(macro_f_string_map_multis_t_resize);

        data_make->main->setting.state.status = f_string_map_multis_resize(data_make->main->setting.state.step_small, &data_make->setting_make.parameter);

        if (F_status_is_error_not(data_make->main->setting.state.status)) {
          data_make->setting_make.parameter.used = 1;

          function_name = macro_fake_f(f_string_dynamic_append);
          data_make->main->setting.state.status = f_string_dynamic_append(fake_make_setting_return_s, &data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_error_not(data_make->main->setting.state.status)) {
          function_name = macro_fake_f(f_memory_arrays_resize);

          data_make->main->setting.state.status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &data_make->setting_make.parameter.array[0].value.array, &data_make->setting_make.parameter.array[0].value.used, &data_make->setting_make.parameter.array[0].value.size, &f_string_dynamics_delete_callback);
        }

        if (F_status_is_error(data_make->main->setting.state.status)) {
          fake_print_error(&data_make->main->program.error, function_name);

          f_fss_set_delete(&settings);

          return;
        }
      }

      f_string_range_t *range_compiler = 0;
      f_string_range_t *range_indexer = 0;

      data_make->setting_make.parameter.array[0].value.used = 1;
      data_make->setting_make.load_build = F_false;
      data_make->setting_make.fail = fake_make_operation_fail_exit_e;

      if (settings.objects.used) {
        for (f_number_unsigned_t i = 0; i < settings.objects.used; ++i) {

          if (f_compare_dynamic_partial_string(fake_make_setting_load_build_s.string, data_make->main->buffer, fake_make_setting_load_build_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_build(data_make, &settings.objects.array[i], &settings.contents.array[i]);
          }
          else if (f_compare_dynamic_partial_string(fake_make_setting_compiler_s.string, data_make->main->buffer, fake_make_setting_compiler_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_compiler(data_make, &settings.objects.array[i], &settings.contents.array[i], &range_compiler);
          }
          else if (f_compare_dynamic_partial_string(fake_make_setting_environment_s.string, data_make->main->buffer, fake_make_setting_environment_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_environment(data_make, &settings.contents.array[i]);
            if (F_status_is_error(data_make->main->setting.state.status)) break;
          }
          else if (f_compare_dynamic_partial_string(fake_make_setting_fail_s.string, data_make->main->buffer, fake_make_setting_fail_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_fail(data_make, &settings.objects.array[i], &settings.contents.array[i]);
          }
          else if (f_compare_dynamic_partial_string(fake_make_setting_indexer_s.string, data_make->main->buffer, fake_make_setting_indexer_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_indexer(data_make, &settings.objects.array[i], &settings.contents.array[i], &range_indexer);
          }
          else if (f_compare_dynamic_partial_string(fake_make_setting_parameter_s.string, data_make->main->buffer, fake_make_setting_parameter_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_parameter(data_make, &settings.objects.array[i], &settings.contents.array[i]);
            if (F_status_is_error(data_make->main->setting.state.status)) break;
          }
        } // for

        if (F_status_is_error(data_make->main->setting.state.status)) {
          f_fss_set_delete(&settings);

          return;
        }
      }

      if (F_status_is_error_not(data_make->main->setting.state.status) && data_make->setting_make.load_build) {
        fake_build_load_setting(data_make->data, 0, F_false, &data_make->setting_build);

        if (F_status_is_error(data_make->main->setting.state.status) && data_make->main->setting.state.status != F_status_set_error(F_interrupt)) {
          fake_print_error(&data_make->main->program.error, macro_fake_f(fake_build_load_setting));
        }
      }

      if (F_status_is_error(data_make->main->setting.state.status)) {
        f_fss_set_delete(&settings);

        return;
      }

      // If either compiler or indexer is specified, each will replace any existing build_compiler or build_indexer, respectively.
      if (range_compiler) {
        data_make->setting_build.build_compiler.used = 0;

        data_make->main->setting.state.status = f_string_dynamic_partial_append(data_make->main->buffer, *range_compiler, &data_make->setting_build.build_compiler);
      }

      if (F_status_is_error_not(data_make->main->setting.state.status) && range_indexer) {
        data_make->setting_build.build_indexer.used = 0;

        data_make->main->setting.state.status = f_string_dynamic_partial_append(data_make->main->buffer, *range_indexer, &data_make->setting_build.build_indexer);
      }

      if (F_status_is_error(data_make->main->setting.state.status)) {
        if (F_status_set_fine(data_make->main->setting.state.status) != F_interrupt) {
          fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_partial_append));
        }

        f_fss_set_delete(&settings);

        return;
      }

      fake_make_load_fakefile_setting_define_and_parameter(data_make, &settings);

      f_fss_set_delete(&settings);
    }

    data_make->main->setting.state.status = F_okay;
  }
#endif // _di_fake_make_load_fakefile_

#ifndef _di_fake_make_load_fakefile_setting_build_
  void fake_make_load_fakefile_setting_build(fake_make_data_t * const data_make, f_string_range_t * const object, f_string_ranges_t * const content) {

    if (!data_make || !data_make->data || !data_make->main || !object || !content) return;

    if (content->used) {
      if (f_compare_dynamic_partial_string(fake_common_setting_bool_yes_s.string, data_make->main->buffer, fake_common_setting_bool_yes_s.used, content->array[0]) == F_equal_to) {
        data_make->setting_make.load_build = F_true;
      }
      else if (f_compare_dynamic_partial_string(fake_common_setting_bool_no_s.string, data_make->main->buffer, fake_common_setting_bool_no_s.used, content->array[0]) == F_equal_to) {
        data_make->setting_make.load_build = F_false;
      }
      else {
        fake_make_print_warning_setting_content_invalid(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, content->array[0], fake_make_item_settings_s);
      }

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, fake_make_setting_load_build_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, fake_make_setting_load_build_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_build_

#ifndef _di_fake_make_load_fakefile_setting_compiler_
  void fake_make_load_fakefile_setting_compiler(fake_make_data_t * const data_make, f_string_range_t * const object, f_string_ranges_t * const content, f_string_range_t **range_compiler) {

    if (!data_make || !data_make->data || !data_make->main || !object || !content || !range_compiler) return;

    if (content->used) {
      *range_compiler = &content->array[content->used - 1];

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, fake_make_setting_compiler_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, fake_make_setting_compiler_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_compiler_

#ifndef _di_fake_make_load_fakefile_setting_define_and_parameter_
  void fake_make_load_fakefile_setting_define_and_parameter(fake_make_data_t * const data_make, f_fss_set_t * const settings) {

    if (!data_make || !data_make->data || !data_make->data || !data_make->main || !settings) return;

    f_string_map_multis_t define = f_string_map_multis_t_initialize;

    // Load the fakefile "settings" as if they are build "settings".
    fake_build_load_setting_process(data_make->data, F_false, data_make->data->file_data_build_fakefile, 0, data_make->main->buffer, settings->objects, settings->contents, &data_make->setting_build);

    if (F_status_is_error_not(data_make->main->setting.state.status) && settings->objects.used) {
      const f_string_static_t settings_name[] = {
        fake_make_setting_define_s,
        fake_make_setting_parameter_s,
      };

      f_string_map_multis_t *settings_value[] = {
        &define,
        &data_make->setting_make.parameter,
      };

      data_make->main->setting.state.status = fll_fss_snatch_map_apart(data_make->main->buffer, settings->objects, settings->contents, settings_name, 2, settings_value, 0, 0);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        fake_print_error(&data_make->main->program.error, macro_fake_f(fll_fss_snatch_map_apart));

        f_string_map_multis_resize(0, &define);

        return;
      }
    }

    if (define.used) {
      f_string_dynamic_t combined = f_string_dynamic_t_initialize;

      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;

      for (; i < define.used; ++i) {

        if (fake_make_operate_validate_define_name(define.array[i].name) == F_true) {
          combined.used = 0;

          for (j = 0; j < define.array[i].value.used; ++j) {

            data_make->main->setting.state.status = f_string_dynamic_mash(f_string_space_s, define.array[i].value.array[j], &combined);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_mash));

              break;
            }
          } // for

          if (F_status_is_error(data_make->main->setting.state.status)) break;

          data_make->main->setting.state.status = f_environment_set(define.array[i].name, combined, F_true);

          if (F_status_is_error(data_make->main->setting.state.status)) {
            fake_print_error(&data_make->main->program.error, macro_fake_f(f_environment_set));

            break;
          }
        }
        else {
          fake_make_print_error_define_invalid_character(&data_make->main->program.error, define.array[i].name);

          data_make->main->setting.state.status = F_status_set_error(F_failure);

          break;
        }
      } // for

      f_memory_array_resize(0, sizeof(f_char_t), (void **) &combined.string, &combined.used, &combined.size);
    }

    f_string_map_multis_resize(0, &define);

    if (F_status_is_error(data_make->main->setting.state.status)) return;

    data_make->main->setting.state.status = F_okay;
  }
#endif // _di_fake_make_load_fakefile_setting_define_and_parameter_

#ifndef _di_fake_make_load_fakefile_setting_environment_
  void fake_make_load_fakefile_setting_environment(fake_make_data_t * const data_make, f_string_ranges_t * const content) {

    if (!data_make || !data_make->data || !data_make->data || !data_make->main || !content) return;

    f_string_dynamic_t name_define = f_string_dynamic_t_initialize;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    data_make->setting_build.flag |= data_build_setting_flag_has_environment_e;

    for (; i < content->used; ++i) {

      data_make->main->setting.state.status = f_string_dynamic_partial_append_nulless(data_make->main->buffer, content->array[i], &name_define);

      if (F_status_is_error(data_make->main->setting.state.status)) {
        fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_partial_append_nulless));

        break;
      }

      // The environment settings are stored in the build settings rather than the make settings.
      if (fake_make_operate_validate_define_name(name_define) == F_true) {
        for (j = 0; j < data_make->setting_build.environment.used; ++j) {
          if (f_compare_dynamic(name_define, data_make->setting_build.environment.array[j]) == F_equal_to) break;
        } // for

        if (j == data_make->setting_build.environment.used) {
          data_make->main->setting.state.status = f_memory_array_increase(fake_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &data_make->setting_build.environment.array, &data_make->setting_build.environment.used, &data_make->setting_build.environment.size);

          if (F_status_is_error(data_make->main->setting.state.status)) {
            fake_print_error(&data_make->main->program.error, macro_fake_f(f_memory_array_increase));

            break;
          }

          data_make->setting_build.environment.array[j].used = 0;

          data_make->main->setting.state.status = f_memory_array_increase_by(name_define.used + 1, sizeof(f_char_t), (void **) &data_make->setting_build.environment.array[j].string, &data_make->setting_build.environment.array[j].used, &data_make->setting_build.environment.array[j].size);

          if (F_status_is_error(data_make->main->setting.state.status)) {
            fake_print_error(&data_make->main->program.error, macro_fake_f(f_memory_array_increase_by));

            break;
          }

          data_make->main->setting.state.status = f_string_dynamic_append_nulless(name_define, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(data_make->main->setting.state.status)) {
            fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }

          ++data_make->setting_build.environment.used;
        }
        else if (j < data_make->setting_build.environment.used) {
          fake_make_print_warning_environment_name_already_added(&data_make->main->program.warning, name_define);

          data_make->setting_build.environment.array[j].used = 0;

          data_make->main->setting.state.status = f_string_dynamic_append_nulless(name_define, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(data_make->main->setting.state.status)) {
            fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }
        }
      }
      else if (data_make->main->program.warning.verbosity >= f_console_verbosity_verbose_e) {
        fake_make_print_warning_environment_name_invalid(&data_make->main->program.warning, name_define);
      }

      name_define.used = 0;
    } // for

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &name_define.string, &name_define.used, &name_define.size);

    if (F_status_is_error(data_make->main->setting.state.status)) return;

    data_make->main->setting.state.status = F_okay;
  }
#endif // _di_fake_make_load_fakefile_setting_environment_

#ifndef _di_fake_make_load_fakefile_setting_fail_
  void fake_make_load_fakefile_setting_fail(fake_make_data_t * const data_make, f_string_range_t * const object, f_string_ranges_t * const content) {

    if (!data_make || !data_make->data || !data_make->data || !data_make->main || !object || !content) return;

    if (content->used) {
      if (f_compare_dynamic_partial_string(fake_make_operation_argument_exit_s.string, data_make->main->buffer, fake_make_operation_argument_exit_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_exit_e;
      }
      else if (f_compare_dynamic_partial_string(fake_make_operation_argument_warn_s.string, data_make->main->buffer, fake_make_operation_argument_warn_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_warn_e;
      }
      else if (f_compare_dynamic_partial_string(fake_make_operation_argument_ignore_s.string, data_make->main->buffer, fake_make_operation_argument_ignore_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_ignore_e;
      }
      else {
        fake_make_print_warning_setting_content_invalid(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, content->array[content->used - 1], fake_make_item_settings_s);
      }

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, fake_make_setting_fail_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, fake_make_setting_fail_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_fail_

#ifndef _di_fake_make_load_fakefile_setting_indexer_
  void fake_make_load_fakefile_setting_indexer(fake_make_data_t * const data_make, f_string_range_t * const object, f_string_ranges_t * const content, f_string_range_t **range_indexer) {

    if (!data_make || !data_make->data || !data_make->data || !data_make->main || !object || !content || !range_indexer) return;

    if (content->used) {
      *range_indexer = &content->array[content->used - 1];

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, fake_make_setting_indexer_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, fake_make_setting_indexer_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_indexer_

#ifndef _di_fake_make_load_fakefile_setting_parameter_
  void fake_make_load_fakefile_setting_parameter(fake_make_data_t * const data_make, f_string_range_t * const object, f_string_ranges_t * const content) {

    if (!data_make || !data_make->data || !data_make->data || !data_make->main || !object || !content) return;

    if (content->used) {
      if (f_compare_dynamic_partial_string(fake_make_setting_return_s.string, data_make->main->buffer, fake_make_setting_return_s.used, content->array[0]) == F_equal_to) {
        if (content->used > 1) {

          // Each "return" define replaces the previous "return" define.
          data_make->setting_make.parameter.array[0].value.array[0].used = 0;

          for (f_number_unsigned_t i = 1; i < content->used; ++i) {

            data_make->main->setting.state.status = f_string_dynamic_partial_append_nulless(data_make->main->buffer, content->array[i], &data_make->setting_make.parameter.array[0].value.array[0]);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_partial_append_nulless));

              break;
            }

            data_make->main->setting.state.status = f_string_dynamic_append_assure(f_string_space_s, &data_make->setting_make.parameter.array[0].value.array[0]);

            if (F_status_is_error(data_make->main->setting.state.status)) {
              fake_print_error(&data_make->main->program.error, macro_fake_f(f_string_dynamic_append_assure));

              break;
            }
          } // for

          if (F_status_is_error(data_make->main->setting.state.status)) return;
        }
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(&data_make->main->program.warning, data_make->data->file_data_build_fakefile, data_make->main->buffer, *object, fake_make_setting_return_s);
    }

    data_make->main->setting.state.status = F_okay;
  }
#endif // _di_fake_make_load_fakefile_setting_parameter_

#ifdef __cplusplus
} // extern "C"
#endif
