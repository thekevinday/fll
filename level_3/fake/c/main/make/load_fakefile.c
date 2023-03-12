#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_load_fakefile_
  void fake_make_load_fakefile(fake_make_data_t * const data_make, const bool process_pipe) {

    if (!data_make) return;
    if (F_status_is_error(data->setting->state.status)) return;

    if (fll_program_standard_signal_received(data_make->main)) {
      fll_program_print_signal_received(data_make->main->warning, data_make->data->setting->line_first, data_make->main->signal_received);

      data->setting->state.status = F_status_set_error(F_interrupt);

      return;
    }

    data_make->fakefile.used = 0;

    if (process_pipe) {
      fake_pipe_buffer(data_make->data, &data_make->buffer);

      if (F_status_is_error(data->setting->state.status)) {
        data_make->buffer.used = 0;
      }
      else {
        data->setting->state.status = f_string_dynamic_append_assure(f_string_eol_s, &data_make->buffer);
      }
    }

    if (F_status_is_error_not(data->setting->state.status)) {
      fake_file_buffer(data_make->data, data_make->data->file_data_build_fakefile, process_pipe ? F_false : F_true, &data_make->buffer);
    }

    if (F_status_is_error(data->setting->state.status)) return;

    if (!data_make->buffer.used) {
      fake_make_print_warning_fakefile_empty(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile);

      return;
    }

    f_fss_objects_t list_objects = f_fss_objects_t_initialize;
    f_fss_contents_t list_contents = f_fss_contents_t_initialize;
    f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

    {
      f_string_range_t range = macro_f_string_range_t_initialize2(data_make->buffer.used);
      f_fss_comments_t comments = f_fss_comments_t_initialize;

      fll_fss_basic_list_read(data_make->buffer, data->setting->state, &range, &list_objects, &list_contents, &delimits, 0, &comments);

      if (F_status_is_error(data->setting->state.status)) {
        fake_print_error_fss(data_make->setting, data_make->main->error, macro_fake_f(fll_fss_basic_list_read), data_make->data->file_data_build_fakefile, range, F_true);
      }
      else {
        data->setting->state.status = f_fss_apply_delimit(state, delimits, &data_make->buffer);

        if (F_status_is_error(data->setting->state.status)) {
          fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_fss_apply_delimit));
        }

        delimits.used = 0;
      }

      macro_f_fss_comments_t_delete_simple(comments);

      if (F_status_is_error(data->setting->state.status)) {
        macro_f_fss_objects_t_delete_simple(list_objects);
        macro_f_fss_contents_t_delete_simple(list_contents);
        macro_f_fss_delimits_t_delete_simple(delimits);

        return;
      }
    }

    {
      bool missing_main = F_true;
      bool missing_settings = F_true;

      f_fss_set_t settings = f_fss_set_t_initialize;

      if (list_objects.used > data_make->fakefile.size) {
        macro_f_fss_nameds_t_resize((data->setting->state.status), data_make->fakefile, list_objects.used);
      }

      if (F_status_is_error(data->setting->state.status)) {
        fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(macro_f_fss_nameds_t_resize));

        macro_f_fss_set_t_delete_simple(settings);
        macro_f_fss_objects_t_delete_simple(list_objects);
        macro_f_fss_contents_t_delete_simple(list_contents);
        macro_f_fss_delimits_t_delete_simple(delimits);

        return;
      }

      {
        f_string_range_t content_range = f_string_range_t_initialize;

        for (f_array_length_t i = 0; i < list_objects.used; ++i) {

          if (!(i % fake_signal_check_short_d)) {
            if (fll_program_standard_signal_received(data_make->main)) {
              fll_program_print_signal_received(data_make->main->warning, data_make->data->setting->line_first, data_make->main->signal_received);

              data->setting->state.status = F_status_set_error(F_interrupt);

              break;
            }

            data_make->main->signal_check = 0;
          }

          if (fl_string_dynamic_partial_compare_string(fake_make_item_settings_s.string, data_make->buffer, fake_make_item_settings_s.used, list_objects.array[i]) == F_equal_to) {
            if (!missing_settings) {
              fake_make_print_warning_setting_object_multiple(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_item_settings_s);

              continue;
            }

            delimits.used = 0;
            content_range = list_contents.array[i].array[0];

            data->setting->state.status = fll_fss_extended_read(data_make->buffer, &content_range, &settings.objects, &settings.contents, 0, 0, &delimits, 0, &data->setting->state);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error_fss(data_make->setting, data_make->main->error, macro_fake_f(fll_fss_extended_read), data_make->data->file_data_build_fakefile, content_range, F_true);

              break;
            }

            data->setting->state.status = f_fss_apply_delimit(state, delimits, &data_make->buffer);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_fss_apply_delimit));

              break;
            }

            missing_settings = F_false;

            continue;
          }

          if (fl_string_dynamic_partial_compare_string(fake_make_item_main_s.string, data_make->buffer, fake_make_item_main_s.used, list_objects.array[i]) == F_equal_to) {
            if (!missing_main) {
              fake_make_print_warning_setting_object_multiple(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_item_main_s);

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

            fll_fss_extended_read(data_make->buffer, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, &data_make->fakefile.array[data_make->fakefile.used].quotess, &delimits, 0, &data->setting->state);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error_fss(data_make->setting, data_make->main->error, macro_fake_f(fll_fss_extended_read), data_make->data->file_data_build_fakefile, content_range, F_true);

              break;
            }

            data->setting->state.status = f_fss_apply_delimit(state, delimits, &data_make->buffer);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_fss_apply_delimit));

              break;
            }
          }

          ++data_make->fakefile.used;
        } // for
      }

      macro_f_fss_objects_t_delete_simple(list_objects);
      macro_f_fss_contents_t_delete_simple(list_contents);
      macro_f_fss_delimits_t_delete_simple(delimits);

      if (F_status_is_error(data->setting->state.status)) {
        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      if (missing_main) {
        fake_make_print_error_fakefile_section_missing(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_item_main_s);

        data->setting->state.status = F_status_set_error(F_failure);

        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      // Always have the parameter variable "return" map at index 0 and be pre-initialized.
      {
        f_string_t function_name = macro_fake_f(macro_f_string_map_multis_t_resize);

        data->setting->state.status = f_string_map_multis_resize(data->setting->state.step_small, &data_make->setting_make.parameter);

        if (F_status_is_error_not(data->setting->state.status)) {
          data_make->setting_make.parameter.used = 1;

          function_name = macro_fake_f(f_string_dynamic_append);
          data->setting->state.status = f_string_dynamic_append(fake_make_setting_return_s, &data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_error_not(data->setting->state.status)) {
          function_name = macro_fake_f(f_string_dynamics_resize);
          data->setting->state.status = f_string_dynamics_resize(1, &data_make->setting_make.parameter.array[0].value);
        }

        if (F_status_is_error(data->setting->state.status)) {
          fake_print_error(data_make->setting, data_make->main->error, function_name);

          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      f_string_range_t *range_compiler = 0;
      f_string_range_t *range_indexer = 0;

      data_make->setting_make.parameter.array[0].value.used = 1;
      data_make->setting_make.load_build = F_false;
      data_make->setting_make.fail = fake_make_operation_fail_exit_e;

      if (settings.objects.used) {
        for (f_array_length_t i = 0; i < settings.objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_string(fake_make_setting_load_build_s.string, data_make->buffer, fake_make_setting_load_build_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_build(data_make, &settings.objects.array[i], &settings.contents.array[i]);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_compiler_s.string, data_make->buffer, fake_make_setting_compiler_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_compiler(data_make, &settings.objects.array[i], &settings.contents.array[i], &range_compiler);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_environment_s.string, data_make->buffer, fake_make_setting_environment_s.used, settings.objects.array[i]) == F_equal_to) {
            data->setting->state.status = fake_make_load_fakefile_setting_environment(data_make, &settings.contents.array[i]);
            if (F_status_is_error(data->setting->state.status)) break;
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_fail_s.string, data_make->buffer, fake_make_setting_fail_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_fail(data_make, &settings.objects.array[i], &settings.contents.array[i]);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_indexer_s.string, data_make->buffer, fake_make_setting_indexer_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_indexer(data_make, &settings.objects.array[i], &settings.contents.array[i], &range_indexer);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_parameter_s.string, data_make->buffer, fake_make_setting_parameter_s.used, settings.objects.array[i]) == F_equal_to) {
            data->setting->state.status = fake_make_load_fakefile_setting_parameter(data_make, &settings.objects.array[i], &settings.contents.array[i]);
            if (F_status_is_error(data->setting->state.status)) break;
          }
        } // for

        if (F_status_is_error(data->setting->state.status)) {
          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      if (F_status_is_error_not(data->setting->state.status) && data_make->setting_make.load_build) {
        fake_build_load_setting(data_make->data, 0, F_false, &data_make->setting_build);

        if (F_status_is_error(data->setting->state.status) && data->setting->state.status != F_status_set_error(F_interrupt)) {
          fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(fake_build_load_setting));
        }
      }

      if (F_status_is_error(data->setting->state.status)) {
        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      // If either compiler or indexer is specified, each will replace any existing build_compiler or build_indexer, respectively.
      if (range_compiler) {
        data_make->setting_build.build_compiler.used = 0;

        data->setting->state.status = f_string_dynamic_partial_append(data_make->buffer, *range_compiler, &data_make->setting_build.build_compiler);
      }

      if (F_status_is_error_not(data->setting->state.status) && range_indexer) {
        data_make->setting_build.build_indexer.used = 0;

        data->setting->state.status = f_string_dynamic_partial_append(data_make->buffer, *range_indexer, &data_make->setting_build.build_indexer);
      }

      if (F_status_is_error(data->setting->state.status)) {
        if (F_status_set_fine(data->setting->state.status) != F_interrupt) {
          fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_partial_append));
        }

        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      data->setting->state.status = fake_make_load_fakefile_setting_define_and_parameter(data_make->data, data_make, &settings);

      macro_f_fss_set_t_delete_simple(settings);
    }

    data->setting->state.status = F_none;
  }
#endif // _di_fake_make_load_fakefile_

#ifndef _di_fake_make_load_fakefile_setting_build_
  void fake_make_load_fakefile_setting_build(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content) {

    if (!data_make || !object || !content) return;

    if (content->used) {
      if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_yes_s.string, data_make->buffer, fake_common_setting_bool_yes_s.used, content->array[0]) == F_equal_to) {
        data_make->setting_make.load_build = F_true;
      }
      else if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_no_s.string, data_make->buffer, fake_common_setting_bool_no_s.used, content->array[0]) == F_equal_to) {
        data_make->setting_make.load_build = F_false;
      }
      else {
        fake_make_print_warning_setting_content_invalid(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, content->array[0], fake_make_item_settings_s);
      }

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_setting_load_build_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_load_build_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_build_

#ifndef _di_fake_make_load_fakefile_setting_compiler_
  void fake_make_load_fakefile_setting_compiler(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content, f_string_range_t **range_compiler) {

    if (!data_make || !object || !content || !range_compiler) return;

    if (content->used) {
      *range_compiler = &content->array[content->used - 1];

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_setting_compiler_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_compiler_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_compiler_

#ifndef _di_fake_make_load_fakefile_setting_define_and_parameter_
  void fake_make_load_fakefile_setting_define_and_parameter(fake_data_t * const data, fake_make_data_t * const data_make, f_fss_set_t * const settings) {

    if (!data || !data_make || !settings) return;
;
    f_string_map_multis_t define = f_string_map_multis_t_initialize;

    // Load the fakefile "settings" as if they are build "settings".
    fake_build_load_setting_process(data, F_false, data->file_data_build_fakefile, 0, data_make->buffer, settings->objects, settings->contents, &data_make->setting_build);

    if (F_status_is_error_not(data->setting->state.status) && settings->objects.used) {
      const f_string_static_t settings_name[] = {
        fake_make_setting_define_s,
        fake_make_setting_parameter_s,
      };

      f_string_map_multis_t *settings_value[] = {
        &define,
        &data_make->setting_make.parameter,
      };

      data->setting->state.status = fll_fss_snatch_map_apart(data_make->buffer, settings->objects, settings->contents, settings_name, 2, settings_value, 0, 0);

      if (F_status_is_error(data->setting->state.status)) {
        fake_print_error(data->setting, data->main->error, macro_fake_f(fll_fss_snatch_map_apart));

        f_string_map_multis_resize(0, &define);

        return;
      }
    }

    if (define.used) {
      f_string_dynamic_t combined = f_string_dynamic_t_initialize;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < define.used; ++i) {

        fake_make_operate_validate_define_name(define.array[i].name);

        if (data->setting->state.status) {
          combined.used = 0;

          for (j = 0; j < define.array[i].value.used; ++j) {

            data->setting->state.status = f_string_dynamic_mash(f_string_space_s, define.array[i].value.array[j], &combined);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error(data->setting, data->main->error, macro_fake_f(f_string_dynamic_mash));

              break;
            }
          } // for

          if (F_status_is_error(data->setting->state.status)) break;

          data->setting->state.status = f_environment_set(define.array[i].name, combined, F_true);

          if (F_status_is_error(data->setting->state.status)) {
            fake_print_error(data->setting, data->main->error, macro_fake_f(f_environment_set));

            break;
          }
        }
        else {
          fake_make_print_error_define_invalid_character(data_make->setting, data_make->main->error, define.array[i].name);

          data->setting->state.status = F_status_set_error(F_failure);

          break;
        }
      } // for

      f_string_dynamic_resize(0, &combined);
    }

    f_string_map_multis_resize(0, &define);

    if (F_status_is_error(data->setting->state.status)) return;

    data->setting->state.status = F_none;
  }
#endif // _di_fake_make_load_fakefile_setting_define_and_parameter_

#ifndef _di_fake_make_load_fakefile_setting_environment_
  void fake_make_load_fakefile_setting_environment(fake_make_data_t * const data_make, f_fss_content_t * const content) {

    f_string_dynamic_t name_define = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    data_make->setting_build.flag |= data_build_setting_flag_has_environment_e;

    for (; i < content->used; ++i) {

      data->setting->state.status = f_string_dynamic_partial_append_nulless(data_make->buffer, content->array[i], &name_define);

      if (F_status_is_error(data->setting->state.status)) {
        fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_partial_append_nulless));

        break;
      }

      // The environment settings are stored in the build settings rather than the make settings.
      if (fake_make_operate_validate_define_name(name_define) == F_true) {
        for (j = 0; j < data_make->setting_build.environment.used; ++j) {
          if (fl_string_dynamic_compare(name_define, data_make->setting_build.environment.array[j]) == F_equal_to) break;
        } // for

        if (j == data_make->setting_build.environment.used) {
          data->setting->state.status = f_string_dynamics_increase(fake_allocation_small_d, &data_make->setting_build.environment);

          if (F_status_is_error(data->setting->state.status)) {
            fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamics_increase));

            break;
          }

          data_make->setting_build.environment.array[j].used = 0;

          data->setting->state.status = f_string_dynamic_increase_by(name_define.used + 1, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(data->setting->state.status)) {
            fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_increase_by));

            break;
          }

          data->setting->state.status = f_string_dynamic_append_nulless(name_define, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(data->setting->state.status)) {
            fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }

          ++data_make->setting_build.environment.used;
        }
        else if (j < data_make->setting_build.environment.used) {
          fake_make_print_warning_environment_name_already_added(data_make->setting, data_make->main->warning, name_define);

          data_make->setting_build.environment.array[j].used = 0;

          data->setting->state.status = f_string_dynamic_append_nulless(name_define, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(data->setting->state.status)) {
            fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }
        }
      }
      else if (data_make->main->warning.verbosity >= f_console_verbosity_verbose_e) {
        fake_make_print_warning_environment_name_invalid(data_make->setting, data_make->main->warning, name_define);
      }

      name_define.used = 0;
    } // for

    f_string_dynamic_resize(0, &name_define);

    if (F_status_is_error(data->setting->state.status)) return;

    data->setting->state.status = F_none;
  }
#endif // _di_fake_make_load_fakefile_setting_environment_

#ifndef _di_fake_make_load_fakefile_setting_fail_
  void fake_make_load_fakefile_setting_fail(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content) {

    if (content->used) {
      if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_exit_s.string, data_make->buffer, fake_make_operation_argument_exit_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_exit_e;
      }
      else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_warn_s.string, data_make->buffer, fake_make_operation_argument_warn_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_warn_e;
      }
      else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_ignore_s.string, data_make->buffer, fake_make_operation_argument_ignore_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_ignore_e;
      }
      else {
        fake_make_print_warning_setting_content_invalid(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, content->array[content->used - 1], fake_make_item_settings_s);
      }

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_setting_fail_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_fail_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_fail_

#ifndef _di_fake_make_load_fakefile_setting_indexer_
  void fake_make_load_fakefile_setting_indexer(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content, f_string_range_t **range_indexer) {

    if (content->used) {
      *range_indexer = &content->array[content->used - 1];

      if (content->used > 1) {
        fake_make_print_warning_setting_content_multiple(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, fake_make_setting_indexer_s);
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_indexer_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_indexer_

#ifndef _di_fake_make_load_fakefile_setting_parameter_
  void fake_make_load_fakefile_setting_parameter(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content) {

    if (content->used) {
      if (fl_string_dynamic_partial_compare_string(fake_make_setting_return_s.string, data_make->buffer, fake_make_setting_return_s.used, content->array[0]) == F_equal_to) {
        if (content->used > 1) {

          // Each "return" define replaces the previous "return" define.
          data_make->setting_make.parameter.array[0].value.array[0].used = 0;

          for (f_array_length_t i = 1; i < content->used; ++i) {

            data->setting->state.status = f_string_dynamic_partial_append_nulless(data_make->buffer, content->array[i], &data_make->setting_make.parameter.array[0].value.array[0]);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_partial_append_nulless));

              break;
            }

            data->setting->state.status = f_string_dynamic_append_assure(f_string_space_s, &data_make->setting_make.parameter.array[0].value.array[0]);

            if (F_status_is_error(data->setting->state.status)) {
              fake_print_error(data_make->setting, data_make->main->error, macro_fake_f(f_string_dynamic_append_assure));

              break;
            }
          } // for

          if (F_status_is_error(data->setting->state.status)) return;
        }
      }
    }
    else {
      fake_make_print_warning_setting_content_empty(data_make->setting, data_make->main->warning, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_return_s);
    }

    data->setting->state.status = F_none;
  }
#endif // _di_fake_make_load_fakefile_setting_parameter_

#ifdef __cplusplus
} // extern "C"
#endif
