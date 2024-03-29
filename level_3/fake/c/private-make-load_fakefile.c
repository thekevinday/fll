#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build-load.h"
#include "private-make-load_fakefile.h"
#include "private-make-operate_validate.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_load_fakefile_
  void fake_make_load_fakefile(fake_make_data_t * const data_make, const bool process_pipe, f_status_t * const status) {

    if (F_status_is_error(*status)) return;

    if (fll_program_standard_signal_received(data_make->main)) {
      fake_print_signal_received(data_make->data);

      *status = F_status_set_error(F_interrupt);

      return;
    }

    data_make->fakefile.used = 0;

    if (process_pipe) {
      *status = fake_pipe_buffer(data_make->data, &data_make->buffer);

      if (F_status_is_error(*status)) {
        data_make->buffer.used = 0;
      }
      else {
        *status = f_string_dynamic_append_assure(f_string_eol_s, &data_make->buffer);
      }
    }

    if (F_status_is_error_not(*status)) {
      *status = fake_file_buffer(data_make->data, data_make->data->file_data_build_fakefile, process_pipe ? F_false : F_true, &data_make->buffer);
    }

    if (F_status_is_error(*status)) return;

    if (!data_make->buffer.used) {
      if (data_make->main->error.verbosity >= f_console_verbosity_verbose_e) {
        flockfile(data_make->main->warning.to.stream);

        fl_print_format("%r%[%QThe fakefile '%]", data_make->main->warning.to.stream, f_string_eol_s, data_make->main->warning.context, data_make->main->warning.prefix, data_make->main->warning.context);
        fl_print_format("%[%Q%]", data_make->main->warning.to.stream, data_make->main->warning.notable, data_make->data->file_data_build_fakefile, data_make->main->warning.notable);
        fl_print_format("%[' is empty.%]%r", data_make->main->warning.to.stream, data_make->main->warning.context, data_make->main->warning.context, f_string_eol_s);

        funlockfile(data_make->main->warning.to.stream);
      }

      return;
    }

    f_fss_objects_t list_objects = f_fss_objects_t_initialize;
    f_fss_contents_t list_contents = f_fss_contents_t_initialize;
    f_fss_delimits_t delimits = f_fss_delimits_t_initialize;

    {
      f_string_range_t range = macro_f_string_range_t_initialize2(data_make->buffer.used);
      f_fss_comments_t comments = f_fss_comments_t_initialize;
      f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) data_make->main, 0);

      *status = fll_fss_basic_list_read(data_make->buffer, state, &range, &list_objects, &list_contents, &delimits, 0, &comments);

      if (F_status_is_error(*status)) {
        fake_print_error_fss(data_make->data, F_status_set_fine(*status), "fll_fss_basic_list_read", data_make->data->file_data_build_fakefile, range, F_true);
      }
      else {
        *status = f_fss_apply_delimit(state, delimits, &data_make->buffer);

        if (F_status_is_error(*status)) {
          fll_error_print(data_make->main->error, F_status_set_fine(*status), "f_fss_apply_delimit", F_true);
        }

        delimits.used = 0;
      }

      macro_f_fss_comments_t_delete_simple(comments);

      if (F_status_is_error(*status)) {
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
      f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) data_make->main, 0);

      if (list_objects.used > data_make->fakefile.size) {
        macro_f_fss_nameds_t_resize((*status), data_make->fakefile, list_objects.used);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->main->error, F_status_set_fine(*status), "macro_f_fss_nameds_t_resize", F_true);

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
              fake_print_signal_received(data_make->data);

              *status = F_status_set_error(F_interrupt);

              break;
            }

            data_make->main->signal_check = 0;
          }

          if (fl_string_dynamic_partial_compare_string(fake_make_section_settings_s.string, data_make->buffer, fake_make_section_settings_s.used, list_objects.array[i]) == F_equal_to) {
            if (!missing_settings) {
              fake_print_warning_settings_object_multiple(data_make->data, data_make->data->file_data_build_fakefile, fake_common_setting_list_s, fake_make_section_settings_s);

              continue;
            }

            delimits.used = 0;
            content_range = list_contents.array[i].array[0];

            *status = fll_fss_extended_read(data_make->buffer, state, &content_range, &settings.objects, &settings.contents, 0, 0, &delimits, 0);

            if (F_status_is_error(*status)) {
              fake_print_error_fss(data_make->data, F_status_set_fine(*status), "fll_fss_extended_read", data_make->data->file_data_build_fakefile, content_range, F_true);

              break;
            }

            *status = f_fss_apply_delimit(state, delimits, &data_make->buffer);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->main->error, F_status_set_fine(*status), "f_fss_apply_delimit", F_true);

              break;
            }

            missing_settings = F_false;

            continue;
          }

          if (fl_string_dynamic_partial_compare_string(fake_make_section_main_s.string, data_make->buffer, fake_make_section_main_s.used, list_objects.array[i]) == F_equal_to) {
            if (!missing_main) {
              fake_print_warning_settings_object_multiple(data_make->data, data_make->data->file_data_build_fakefile, fake_common_setting_list_s, fake_make_section_main_s);

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

            *status = fll_fss_extended_read(data_make->buffer, state, &content_range, &data_make->fakefile.array[data_make->fakefile.used].objects, &data_make->fakefile.array[data_make->fakefile.used].contents, 0, &data_make->fakefile.array[data_make->fakefile.used].quotess, &delimits, 0);

            if (F_status_is_error(*status)) {
              fake_print_error_fss(data_make->data, F_status_set_fine(*status), "fll_fss_extended_read", data_make->data->file_data_build_fakefile, content_range, F_true);

              break;
            }

            *status = f_fss_apply_delimit(state, delimits, &data_make->buffer);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->main->error, F_status_set_fine(*status), "f_fss_apply_delimit", F_true);

              break;
            }
          }

          ++data_make->fakefile.used;
        } // for
      }

      macro_f_fss_objects_t_delete_simple(list_objects);
      macro_f_fss_contents_t_delete_simple(list_contents);
      macro_f_fss_delimits_t_delete_simple(delimits);

      if (F_status_is_error(*status)) {
        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      // Set the id out of range to designate that it is missing.
      if (missing_main) {
        data_make->id_main = data_make->fakefile.used;
      }

      // Always have the parameter variable "return" map at index 0 and be pre-initialized.
      {
        char *function_name = "macro_f_string_map_multis_t_resize";

        macro_f_string_map_multis_t_resize(*status, data_make->setting_make.parameter, fake_default_allocation_small_d);

        if (F_status_is_error_not(*status)) {
          data_make->setting_make.parameter.used = 1;

          function_name = "f_string_dynamic_append";
          *status = f_string_dynamic_append(fake_make_setting_return_s, &data_make->setting_make.parameter.array[0].name);
        }

        if (F_status_is_error_not(*status)) {
          function_name = "f_string_dynamics_resize";
          *status = f_string_dynamics_resize(1, &data_make->setting_make.parameter.array[0].value);
        }

        if (F_status_is_error(*status)) {
          fll_error_print(data_make->main->error, F_status_set_fine(*status), function_name, F_true);

          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      f_string_range_t *range_compiler = 0;
      f_string_range_t *range_indexer = 0;

      data_make->setting_make.parameter.array[0].value.used = 1;
      data_make->setting_make.load_build = F_false;
      data_make->setting_make.fail = fake_make_operation_fail_type_exit_e;

      if (settings.objects.used) {
        for (f_array_length_t i = 0; i < settings.objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_string(fake_make_setting_load_build_s.string, data_make->buffer, fake_make_setting_load_build_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_build(data_make, &settings.objects.array[i], &settings.contents.array[i]);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_compiler_s.string, data_make->buffer, fake_make_setting_compiler_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_compiler(data_make, &settings.objects.array[i], &settings.contents.array[i], &range_compiler);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_environment_s.string, data_make->buffer, fake_make_setting_environment_s.used, settings.objects.array[i]) == F_equal_to) {
            *status = fake_make_load_fakefile_setting_environment(data_make, &settings.contents.array[i]);
            if (F_status_is_error(*status)) break;
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_fail_s.string, data_make->buffer, fake_make_setting_fail_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_fail(data_make, &settings.objects.array[i], &settings.contents.array[i]);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_indexer_s.string, data_make->buffer, fake_make_setting_indexer_s.used, settings.objects.array[i]) == F_equal_to) {
            fake_make_load_fakefile_setting_indexer(data_make, &settings.objects.array[i], &settings.contents.array[i], &range_indexer);
          }
          else if (fl_string_dynamic_partial_compare_string(fake_make_setting_parameter_s.string, data_make->buffer, fake_make_setting_parameter_s.used, settings.objects.array[i]) == F_equal_to) {
            *status = fake_make_load_fakefile_setting_parameter(data_make, &settings.objects.array[i], &settings.contents.array[i]);
            if (F_status_is_error(*status)) break;
          }
        } // for

        if (F_status_is_error(*status)) {
          macro_f_fss_set_t_delete_simple(settings);

          return;
        }
      }

      if (F_status_is_error_not(*status) && data_make->setting_make.load_build) {
        fake_build_load_setting(data_make->data, 0, F_false, &data_make->setting_build, status);

        if (F_status_is_error(*status) && *status != F_status_set_error(F_interrupt)) {
          fll_error_print(data_make->main->error, F_status_set_fine(*status), "fake_build_load_setting", F_true);
        }
      }

      if (F_status_is_error(*status)) {
        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      // If either compiler or indexer is specified, each will replace any existing build_compiler or build_indexer, respectively.
      if (range_compiler) {
        data_make->setting_build.build_compiler.used = 0;

        *status = f_string_dynamic_partial_append(data_make->buffer, *range_compiler, &data_make->setting_build.build_compiler);
      }

      if (F_status_is_error_not(*status) && range_indexer) {
        data_make->setting_build.build_indexer.used = 0;

        *status = f_string_dynamic_partial_append(data_make->buffer, *range_indexer, &data_make->setting_build.build_indexer);
      }

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) != F_interrupt) {
          fll_error_print(data_make->main->error, F_status_set_fine(*status), "f_string_dynamic_partial_append", F_true);
        }

        macro_f_fss_set_t_delete_simple(settings);

        return;
      }

      *status = fake_make_load_fakefile_setting_define_and_parameter(data_make->data, data_make, &settings);

      macro_f_fss_set_t_delete_simple(settings);
    }
  }
#endif // _di_fake_make_load_fakefile_

#ifndef _di_fake_make_load_fakefile_setting_build_
  void fake_make_load_fakefile_setting_build(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content) {

    if (content->used) {
      if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_yes_s.string, data_make->buffer, fake_common_setting_bool_yes_s.used, content->array[0]) == F_equal_to) {
        data_make->setting_make.load_build = F_true;
      }
      else if (fl_string_dynamic_partial_compare_string(fake_common_setting_bool_no_s.string, data_make->buffer, fake_common_setting_bool_no_s.used, content->array[0]) == F_equal_to) {
        data_make->setting_make.load_build = F_false;
      }
      else {
        fake_print_warning_settings_content_invalid(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, content->array[0], fake_make_section_settings_s);
      }

      if (content->used > 1) {
        fake_print_warning_settings_content_multiple(data_make->data, data_make->data->file_data_build_fakefile, fake_make_setting_load_build_s);
      }
    }
    else {
      fake_print_warning_settings_content_empty(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_load_build_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_build_

#ifndef _di_fake_make_load_fakefile_setting_compiler_
  void fake_make_load_fakefile_setting_compiler(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content, f_string_range_t **range_compiler) {

    if (content->used) {
      *range_compiler = &content->array[content->used - 1];

      if (content->used > 1) {
        fake_print_warning_settings_content_multiple(data_make->data, data_make->data->file_data_build_fakefile, fake_make_setting_compiler_s);
      }
    }
    else {
      fake_print_warning_settings_content_empty(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_compiler_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_compiler_

#ifndef _di_fake_make_load_fakefile_setting_define_and_parameter_
  f_status_t fake_make_load_fakefile_setting_define_and_parameter(fake_data_t * const data, fake_make_data_t * const data_make, f_fss_set_t * const settings) {

    f_status_t status = F_none;
    f_string_map_multis_t define = f_string_map_multis_t_initialize;

    // Load the fakefile "settings" as if they are build "settings".
    fake_build_load_setting_process(data, F_false, data->file_data_build_fakefile, 0, data_make->buffer, settings->objects, settings->contents, &data_make->setting_build, &status);

    if (F_status_is_error_not(status) && settings->objects.used) {
      const f_string_static_t settings_name[] = {
        fake_make_setting_define_s,
        fake_make_setting_parameter_s,
      };

      f_string_map_multis_t *settings_value[] = {
        &define,
        &data_make->setting_make.parameter,
      };

      status = fll_fss_snatch_map_apart(data_make->buffer, settings->objects, settings->contents, settings_name, 2, settings_value, 0, 0);

      if (F_status_is_error(status)) {
        fll_error_print(data->main->error, F_status_set_fine(status), "fll_fss_snatch_map_apart", F_true);

        macro_f_string_map_multis_t_delete_simple(define);

        return status;
      }
    }

    if (define.used) {
      f_status_t status_validate = F_none;
      f_string_dynamic_t combined = f_string_dynamic_t_initialize;

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < define.used; ++i) {

        status_validate = fake_make_operate_validate_define_name(define.array[i].name);

        if (status_validate) {
          combined.used = 0;

          for (j = 0; j < define.array[i].value.used; ++j) {

            status = f_string_dynamic_mash(f_string_space_s, define.array[i].value.array[j], &combined);

            if (F_status_is_error(status)) {
              fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamic_mash", F_true);

              break;
            }
          } // for

          if (F_status_is_error(status)) break;

          status = f_environment_set(define.array[i].name, combined, F_true);

          if (F_status_is_error(status)) {
            fll_error_print(data->main->error, F_status_set_fine(status), "f_environment_set", F_true);

            break;
          }
        }
        else {
          if (data->main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(data->main->error.to.stream);

            fl_print_format("%r%[%QInvalid characters in the define name '%]", data->main->error.to.stream, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
            fl_print_format("%[%Q%]", data->main->error.to.stream, data->main->error.notable, define.array[i].name, data->main->error.notable);
            fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) are allowed.%]%r", data->main->error.to.stream, data->main->error.context, data->main->error.context, f_string_eol_s);

            funlockfile(data->main->error.to.stream);
          }

          status = F_status_set_error(F_failure);

          break;
        }
      } // for

      f_string_dynamic_resize(0, &combined);
    }

    f_string_map_multis_resize(0, &define);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_load_fakefile_setting_define_and_parameter_

#ifndef _di_fake_make_load_fakefile_setting_environment_
  f_status_t fake_make_load_fakefile_setting_environment(fake_make_data_t * const data_make, f_fss_content_t * const content) {

    f_status_t status = F_none;

    f_string_dynamic_t name_define = f_string_dynamic_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    data_make->setting_build.flag |= data_build_setting_flag_has_environment_e;

    for (; i < content->used; ++i) {

      status = f_string_dynamic_partial_append_nulless(data_make->buffer, content->array[i], &name_define);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

        break;
      }

      // The environment settings are stored in the build settings rather than the make settings.
      if (fake_make_operate_validate_define_name(name_define) == F_true) {
        for (j = 0; j < data_make->setting_build.environment.used; ++j) {
          if (fl_string_dynamic_compare(name_define, data_make->setting_build.environment.array[j]) == F_equal_to) break;
        } // for

        if (j == data_make->setting_build.environment.used) {
          status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->setting_build.environment);

          if (F_status_is_error(status)) {
            fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

            break;
          }

          data_make->setting_build.environment.array[j].used = 0;

          status = f_string_dynamic_increase_by(name_define.used + 1, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(status)) {
            fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

            break;
          }

          status = f_string_dynamic_append_nulless(name_define, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(status)) {
            fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            break;
          }

          ++data_make->setting_build.environment.used;
        }
        else if (j < data_make->setting_build.environment.used) {
          if (data_make->main->warning.verbosity >= f_console_verbosity_verbose_e) {
            flockfile(data_make->main->warning.to.stream);

            fl_print_format("%r%[%QThe environment name '%]", data_make->main->warning.to.stream, f_string_eol_s, data_make->main->warning.context, data_make->main->warning.prefix, data_make->main->warning.context);
            fl_print_format("%[%Q%]", data_make->main->warning.to.stream, data_make->main->warning.notable, name_define, data_make->main->warning.notable);
            fl_print_format("%[' is already added, replacing previous value.%]%r", data_make->main->warning.to.stream, data_make->main->warning.context, data_make->main->warning.context, f_string_eol_s);

            funlockfile(data_make->main->warning.to.stream);
          }

          data_make->setting_build.environment.array[j].used = 0;

          status = f_string_dynamic_append_nulless(name_define, &data_make->setting_build.environment.array[j]);

          if (F_status_is_error(status)) {
            fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            break;
          }
        }
      }
      else if (data_make->main->warning.verbosity >= f_console_verbosity_verbose_e) {
        flockfile(data_make->main->warning.to.stream);

        fl_print_format("%r%[%QThe environment name '%]", data_make->main->warning.to.stream, f_string_eol_s, data_make->main->warning.context, data_make->main->warning.prefix, data_make->main->warning.context);
        fl_print_format("%[%Q%]", data_make->main->warning.to.stream, data_make->main->warning.notable, name_define, data_make->main->warning.notable);
        fl_print_format("%[' is invalid, ignoring.%]%r", data_make->main->warning.to.stream, data_make->main->warning.context, data_make->main->warning.context, f_string_eol_s);

        funlockfile(data_make->main->warning.to.stream);
      }

      name_define.used = 0;
    } // for

    f_string_dynamic_resize(0, &name_define);

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_load_fakefile_setting_environment_

#ifndef _di_fake_make_load_fakefile_setting_fail_
  void fake_make_load_fakefile_setting_fail(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content) {

    if (content->used) {
      if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_exit_s.string, data_make->buffer, fake_make_operation_argument_exit_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_type_exit_e;
      }
      else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_warn_s.string, data_make->buffer, fake_make_operation_argument_warn_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_type_warn_e;
      }
      else if (fl_string_dynamic_partial_compare_string(fake_make_operation_argument_ignore_s.string, data_make->buffer, fake_make_operation_argument_ignore_s.used, content->array[content->used - 1]) == F_equal_to) {
        data_make->setting_make.fail = fake_make_operation_fail_type_ignore_e;
      }
      else {
        fake_print_warning_settings_content_invalid(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, content->array[content->used - 1], fake_make_section_settings_s);
      }

      if (content->used > 1) {
        fake_print_warning_settings_content_multiple(data_make->data, data_make->data->file_data_build_fakefile, fake_make_setting_fail_s);
      }
    }
    else {
      fake_print_warning_settings_content_empty(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_fail_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_fail_

#ifndef _di_fake_make_load_fakefile_setting_indexer_
  void fake_make_load_fakefile_setting_indexer(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content, f_string_range_t **range_indexer) {

    if (content->used) {
      *range_indexer = &content->array[content->used - 1];

      if (content->used > 1) {
        fake_print_warning_settings_content_multiple(data_make->data, data_make->data->file_data_build_fakefile, fake_make_setting_indexer_s);
      }
    }
    else {
      fake_print_warning_settings_content_empty(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_indexer_s);
    }
  }
#endif // _di_fake_make_load_fakefile_setting_indexer_

#ifndef _di_fake_make_load_fakefile_setting_parameter_
  f_status_t fake_make_load_fakefile_setting_parameter(fake_make_data_t * const data_make, f_fss_object_t * const object, f_fss_content_t * const content) {

    if (content->used) {
      f_status_t status = F_none;

      if (fl_string_dynamic_partial_compare_string(fake_make_setting_return_s.string, data_make->buffer, fake_make_setting_return_s.used, content->array[0]) == F_equal_to) {
        if (content->used > 1) {

          // Each "return" define replaces the previous "return" define.
          data_make->setting_make.parameter.array[0].value.array[0].used = 0;

          for (f_array_length_t i = 1; i < content->used; ++i) {

            status = f_string_dynamic_partial_append_nulless(data_make->buffer, content->array[i], &data_make->setting_make.parameter.array[0].value.array[0]);

            if (F_status_is_error(status)) {
              fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

              break;
            }

            status = f_string_dynamic_append_assure(f_string_space_s, &data_make->setting_make.parameter.array[0].value.array[0]);

            if (F_status_is_error(status)) {
              fll_error_print(data_make->main->error, F_status_set_fine(status), "f_string_dynamic_append_assure", F_true);

              break;
            }
          } // for

          if (F_status_is_error(status)) return status;
        }
      }
    }
    else {
      fake_print_warning_settings_content_empty(data_make->data, data_make->data->file_data_build_fakefile, data_make->buffer, *object, fake_make_setting_return_s);
    }

    return F_none;
  }
#endif // _di_fake_make_load_fakefile_setting_parameter_

#ifdef __cplusplus
} // extern "C"
#endif
