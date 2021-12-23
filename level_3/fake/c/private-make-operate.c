#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-load_parameters.h"
#include "private-make-load_fakefile.h"
#include "private-make-operate.h"
#include "private-make-operate-type.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_
  f_status_t fake_make_operate(fake_main_t * const main) {

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    if (main->output.verbosity != f_console_verbosity_quiet) {
      fll_print_format("%c%[Making project.%]%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, main->context.set.important, f_string_eol_s[0]);
    }

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    f_array_lengths_t section_stack = f_array_lengths_t_initialize;
    fake_make_data_t data_make = fake_make_data_t_initialize;

    status = f_string_dynamics_increase(F_memory_default_allocation_small_d, &data_make.path.stack);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

      return status;
    }

    status = f_path_current(F_true, &data_make.path.stack.array[0]);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_path_current", F_true);

      macro_fake_make_data_t_delete_simple(data_make);

      return status;
    }

    status = f_directory_open(data_make.path.stack.array[0].string, F_false, &data_make.path.top.id);

    if (F_status_is_error(status)) {
      fll_error_print(main->error, F_status_set_fine(status), "f_directory_open", F_true);

      macro_fake_make_data_t_delete_simple(data_make);

      return status;
    }

    data_make.path.stack.used = 1;

    macro_f_mode_t_set_default_umask(mode, main->umask);

    fake_make_load_parameters(main, &data_make, &status);

    fake_make_load_fakefile(main, &data_make, &status);

    if (F_status_is_error(status)) {
      macro_fake_make_data_t_delete_simple(data_make)

      return status;
    }

    if (data_make.setting_make.fail == fake_make_operation_fail_type_exit) {
      data_make.error.prefix = fl_print_error_s;
      data_make.error.suffix = 0;
      data_make.error.context = main->context.set.error;
      data_make.error.notable = main->context.set.notable;
      data_make.error.to.stream = F_type_error_d;
      data_make.error.to.id = F_type_descriptor_error_d;
      data_make.error.set = &main->context.set;
    }
    else if (data_make.setting_make.fail == fake_make_operation_fail_type_warn) {
      data_make.error.prefix = fl_print_warning_s;
      data_make.error.suffix = 0;
      data_make.error.context = main->context.set.warning;
      data_make.error.notable = main->context.set.notable;
      data_make.error.to.stream = F_type_warning_d;
      data_make.error.to.id = F_type_descriptor_warning_d;
      data_make.error.set = &main->context.set;
    }
    else {
      data_make.error.to.stream = 0;
      data_make.error.prefix = 0;
      data_make.error.suffix = 0;
      data_make.error.to.id = -1;
      data_make.error.set = &main->context.set;
    }

    {
      const int result = fake_make_operate_section(main, &data_make, data_make.main, &section_stack, &status);

      if (status == F_child) {
        main->child = result;
      }
    }

    if (status != F_child) {
      f_status_t status_path = f_path_change_at(data_make.path.top.id);

      if (F_status_is_error(status_path) && main->warning.verbosity == f_console_verbosity_verbose) {
        flockfile(main->warning.to.stream);

        fl_print_format("%c%[%SFailed change back to orignal path '%]", main->warning.to.stream, f_string_eol_s[0], main->warning.context, main->warning.prefix, main->warning.context);
        fl_print_format("%[%Q%]", main->warning.to.stream, main->warning.notable, data_make.path.stack.array[0], main->warning.notable);
        fl_print_format("%[', status code =%] ", main->warning.to.stream, main->warning.context, main->warning.context);
        fl_print_format("%[%ui%]", main->warning.to.stream, main->warning.notable, F_status_set_fine(status_path), main->warning.notable);
        fl_print_format("%['.%]%c", main->warning.to.stream, main->warning.context, main->warning.context, f_string_eol_s[0]);

        funlockfile(main->warning.to.stream);
      }
    }

    f_file_stream_close(F_true, &data_make.path.top);

    macro_f_array_lengths_t_delete_simple(section_stack)
    macro_fake_make_data_t_delete_simple(data_make)

    return status;
  }
#endif // _di_fake_make_operate_

#ifndef _di_fake_make_operate_expand_
  void fake_make_operate_expand(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_range_t section_name, const f_array_length_t operation, const f_fss_content_t content, const f_fss_quotes_t quotes, f_string_dynamics_t *arguments, f_status_t *status) {

    if (F_status_is_error(*status)) return;
    if (!content.used) return;

    // Pre-allocate the known arguments size.
    *status = f_string_dynamics_increase_by(content.used, arguments);

    if (F_status_is_error(*status) || *status == F_string_too_large) {
      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase_by", F_true);

      return;
    }

    const f_string_static_t vocabulary_define = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_define_s, F_iki_vocabulary_0002_define_s_length);
    const f_string_static_t vocabulary_parameter = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_parameter_s, F_iki_vocabulary_0002_parameter_s_length);

    const f_string_range_t range_define = macro_f_string_range_t_initialize(F_iki_vocabulary_0002_define_s_length);
    const f_string_range_t range_parameter = macro_f_string_range_t_initialize(F_iki_vocabulary_0002_parameter_s_length);

    f_iki_variable_t iki_variable = f_iki_variable_t_initialize;
    f_iki_vocabulary_t iki_vocabulary = f_iki_vocabulary_t_initialize;
    f_iki_content_t iki_content = f_iki_content_t_initialize;
    f_iki_delimits_t iki_delimits = f_iki_delimits_t_initialize;

    f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, &fake_signal_state_interrupt_iki, 0, (void *) main, 0);

    f_string_range_t range = f_string_range_t_initialize;
    f_string_map_multis_t *parameter = &data_make->setting_make.parameter;

    bool unmatched = F_true;
    bool parameter_is = F_false;
    bool define_is = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;

    f_array_length_t used_arguments = 0;
    f_array_length_t previous = 0;

    const f_string_t reserved_name[] = {
      fake_make_parameter_variable_build_s,
      fake_make_parameter_variable_color_s,
      fake_make_parameter_variable_data_s,
      fake_make_parameter_variable_define_s,
      fake_make_parameter_variable_fakefile_s,
      fake_make_parameter_variable_mode_s,
      fake_make_parameter_variable_process_s,
      fake_make_parameter_variable_settings_s,
      fake_make_parameter_variable_sources_s,
      fake_make_parameter_variable_verbosity_s,
      fake_make_parameter_variable_work_s,
      fake_make_parameter_variable_option_build_s,
      fake_make_parameter_variable_option_color_s,
      fake_make_parameter_variable_option_data_s,
      fake_make_parameter_variable_option_define_s,
      fake_make_parameter_variable_option_fakefile_s,
      fake_make_parameter_variable_option_mode_s,
      fake_make_parameter_variable_option_process_s,
      fake_make_parameter_variable_option_settings_s,
      fake_make_parameter_variable_option_sources_s,
      fake_make_parameter_variable_option_verbosity_s,
      fake_make_parameter_variable_option_work_s,
      fake_make_parameter_variable_value_build_s,
      fake_make_parameter_variable_value_color_s,
      fake_make_parameter_variable_value_data_s,
      fake_make_parameter_variable_value_define_s,
      fake_make_parameter_variable_value_fakefile_s,
      fake_make_parameter_variable_value_mode_s,
      fake_make_parameter_variable_value_process_s,
      fake_make_parameter_variable_value_settings_s,
      fake_make_parameter_variable_value_sources_s,
      fake_make_parameter_variable_value_verbosity_s,
      fake_make_parameter_variable_value_work_s,
    };

    const f_array_length_t reserved_length[] = {
      fake_make_parameter_variable_build_s_length,
      fake_make_parameter_variable_color_s_length,
      fake_make_parameter_variable_data_s_length,
      fake_make_parameter_variable_define_s_length,
      fake_make_parameter_variable_fakefile_s_length,
      fake_make_parameter_variable_mode_s_length,
      fake_make_parameter_variable_process_s_length,
      fake_make_parameter_variable_settings_s_length,
      fake_make_parameter_variable_sources_s_length,
      fake_make_parameter_variable_verbosity_s_length,
      fake_make_parameter_variable_work_s_length,
      fake_make_parameter_variable_build_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_color_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_data_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_define_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_fakefile_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_mode_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_process_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_settings_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_sources_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_verbosity_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_work_s_length + fake_make_parameter_iki_option_s_length,
      fake_make_parameter_variable_build_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_color_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_data_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_define_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_fakefile_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_mode_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_process_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_settings_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_sources_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_verbosity_s_length + fake_make_parameter_iki_value_s_length,
      fake_make_parameter_variable_work_s_length + fake_make_parameter_iki_value_s_length,
    };

    f_string_dynamics_t * const reserved_value[] = {
      &data_make->parameter.build,
      &data_make->parameter.color,
      &data_make->parameter.data,
      &data_make->parameter.define,
      &data_make->parameter.fakefile,
      &data_make->parameter.mode,
      &data_make->parameter.process,
      &data_make->parameter.settings,
      &data_make->parameter.sources,
      &data_make->parameter.verbosity,
      &data_make->parameter.work,
      &data_make->parameter_option.build,
      &data_make->parameter_option.color,
      &data_make->parameter_option.data,
      &data_make->parameter_option.define,
      &data_make->parameter_option.fakefile,
      &data_make->parameter_option.mode,
      &data_make->parameter_option.process,
      &data_make->parameter_option.settings,
      &data_make->parameter_option.sources,
      &data_make->parameter_option.verbosity,
      &data_make->parameter_option.work,
      &data_make->parameter_value.build,
      &data_make->parameter_value.color,
      &data_make->parameter_value.data,
      &data_make->parameter_value.define,
      &data_make->parameter_value.fakefile,
      &data_make->parameter_value.mode,
      &data_make->parameter_value.process,
      &data_make->parameter_value.settings,
      &data_make->parameter_value.sources,
      &data_make->parameter_value.verbosity,
      &data_make->parameter_value.work,
    };

    for (; i < content.used; ++i) {

      if (content.array[i].start > content.array[i].stop) continue;

      range = content.array[i];

      used_arguments = arguments->used;

      *status = fl_iki_read(state, &data_make->buffer, &range, &iki_variable, &iki_vocabulary, &iki_content, &iki_delimits);

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) != F_interrupt) {
          fll_error_print(data_make->error, F_status_set_fine(*status), "fl_iki_read", F_true);
        }

        break;
      }

      for (k = 0; k < iki_delimits.used; ++k) {
        data_make->buffer.string[iki_delimits.array[k]] = f_iki_syntax_placeholder_s[0];
      } // for

      *status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, arguments);

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase_by", F_true);

        break;
      }

      if (iki_variable.used) {
        if (iki_variable.array[0].start > 0 && content.array[i].start < iki_variable.array[0].start) {
          range.start = content.array[i].start;
          range.stop = iki_variable.array[0].start - 1;

          *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

            break;
          }
        }

        for (j = 0, previous = iki_variable.array[0].start; j < iki_variable.used; ++j) {

          parameter_is = F_false;
          define_is = F_false;

          if (previous + 1 < iki_variable.array[j].start) {
            range.start = previous + 1;
            range.stop = iki_variable.array[j].start - 1;

            *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

              break;
            }
          }

          *status = fl_string_dynamic_partial_compare(vocabulary_define, data_make->buffer, range_define, iki_vocabulary.array[j]);

          if (*status == F_equal_to) {
            define_is = F_true;
          }
          else if (*status == F_equal_to_not) {
            *status = fl_string_dynamic_partial_compare(vocabulary_parameter, data_make->buffer, range_parameter, iki_vocabulary.array[j]);

            if (*status == F_equal_to) {
              parameter_is = F_true;
            }
          }

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "fl_string_dynamic_partial_compare", F_true);

            break;
          }

          if (parameter_is) {
            unmatched = F_true;

            // Check against reserved parameter names and if matches use them instead.
            if (fl_string_dynamic_partial_compare_string(fake_make_parameter_variable_return_s, data_make->buffer, fake_make_parameter_variable_return_s_length, iki_content.array[j]) == F_equal_to) {
              if (data_make->setting_make.parameter.array[0].value.array[0].used) {
                *status = f_string_dynamic_append(data_make->setting_make.parameter.array[0].value.array[0], &arguments->array[arguments->used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                  break;
                }
              }
              else {
                *status = f_string_append("0", 1, &arguments->array[arguments->used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_append", F_true);

                  break;
                }
              }

              *status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_terminate_after", F_true);

                break;
              }

              ++arguments->used;
              unmatched = F_false;
            }
            else {
              for (k = 0; k < 33; ++k) {

                if (fl_string_dynamic_partial_compare_string(reserved_name[k], data_make->buffer, reserved_length[k], iki_content.array[j]) != F_equal_to) {
                  continue;
                }

                unmatched = F_false;

                *status = f_string_dynamics_increase(F_memory_default_allocation_small_d, arguments);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);

                  return;
                }

                for (l = 0; l < reserved_value[k]->used; ++l) {

                  if (!reserved_value[k]->array[l].used) continue;

                  if (l) {
                    *status = f_string_append(f_string_space_s, 1, &arguments->array[arguments->used]);

                    if (F_status_is_error(*status)) {
                      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_append", F_true);

                      break;
                    }
                  }

                  *status = f_string_dynamic_append(reserved_value[k]->array[l], &arguments->array[arguments->used]);

                  if (F_status_is_error(*status)) {
                    fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                    break;
                  }
                } // for

                if (F_status_is_error_not(*status) && !unmatched) {
                  *status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

                  if (F_status_is_error(*status)) {
                    fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_terminate_after", F_true);

                    break;
                  }

                  ++arguments->used;
                }
                else {
                  break;
                }
              } // for
            }

            if (unmatched && parameter->used) {
              for (k = 0; k < parameter->used; ++k) {

                // Check against iki variable list.
                *status = fl_string_dynamic_partial_compare_dynamic(parameter->array[k].name, data_make->buffer, iki_content.array[j]);

                if (*status == F_equal_to) {
                  unmatched = F_false;

                  if (parameter->array[k].value.used) {
                    if (quotes.array[i]) {
                      for (l = 0; l < parameter->array[k].value.used; ++l) {

                        if (l > 0) {
                          *status = f_string_append(f_string_space_s, 1, &arguments->array[arguments->used]);

                          if (F_status_is_error(*status)) {
                            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_append", F_true);

                            break;
                          }
                        }

                        *status = f_string_dynamic_append_nulless(parameter->array[k].value.array[l], &arguments->array[arguments->used]);

                        if (F_status_is_error(*status)) {
                          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

                          break;
                        }
                      } // for
                    }
                    else {
                      *status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, arguments);

                      if (F_status_is_error(*status)) {
                        fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase_by", F_true);

                        break;
                      }

                      for (l = 0; l < parameter->array[k].value.used; ++l) {

                        *status = f_string_dynamic_append_nulless(parameter->array[k].value.array[l], &arguments->array[arguments->used]);

                        if (F_status_is_error(*status)) {
                          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

                          break;
                        }

                        *status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

                        if (F_status_is_error(*status)) {
                          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_terminate_after", F_true);

                          break;
                        }

                        ++arguments->used;
                      } // for
                    }
                  }

                  break;
                }
                else if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "fl_string_dynamic_compare", F_true);

                  break;
                }
              } // for
            }

            if (F_status_is_error(*status)) break;

            if (unmatched) {
              *status = fake_make_operate_expand_build(main, data_make, quotes.array[i], iki_content.array[j], arguments);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_build", F_true);

                break;
              }
            }
          }
          else if (define_is && data_make->setting_make.load_build) {
            *status = fake_make_operate_expand_environment(main, data_make, quotes.array[i], iki_content.array[j], arguments);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_environment", F_true);

              break;
            }
          }

          previous = iki_variable.array[j].stop;
        } // for

        if (F_status_is_error(*status)) break;

        if (iki_variable.array[iki_variable.used - 1].stop < content.array[i].stop) {
          range.start = iki_variable.array[iki_variable.used - 1].stop + 1;
          range.stop = content.array[i].stop;

          // If arguments->used was not incremented, then use the value, otherwise arguments->used is past the value to append to, so subtract 1.
          if (used_arguments == arguments->used) {
            *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used]);
          }
          else {
            *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &arguments->array[arguments->used - 1]);

            if (F_status_is_error_not(*status)) {
              *status = f_string_dynamic_terminate_after(&arguments->array[arguments->used - 1]);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_terminate_after", F_true);

                break;
              }
            }
          }

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

            break;
          }
        }
      }
      else {
        *status = f_string_dynamic_partial_append_nulless(data_make->buffer, content.array[i], &arguments->array[arguments->used]);

        if (F_status_is_error(*status)) {
          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_append_nulless", F_true);

          break;
        }
      }

      // If iki variable did not match (results in empty string) or iki variable is inside quotes, then increment.
      if (used_arguments == arguments->used) {
        *status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

        if (F_status_is_error(*status)) {
          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_terminate_after", F_true);

          break;
        }

        ++arguments->used;
      }

      macro_f_iki_variable_t_delete_simple(iki_variable);
      macro_f_iki_vocabulary_t_delete_simple(iki_vocabulary);
      macro_f_iki_content_t_delete_simple(iki_content);
      macro_f_iki_delimits_t_delete_simple(iki_delimits);
    } // for

    macro_f_iki_variable_t_delete_simple(iki_variable);
    macro_f_iki_vocabulary_t_delete_simple(iki_vocabulary);
    macro_f_iki_content_t_delete_simple(iki_content);
    macro_f_iki_delimits_t_delete_simple(iki_delimits);
  }
#endif // _di_fake_make_operate_expand_

#ifndef _di_fake_make_operate_expand_build_
  f_status_t fake_make_operate_expand_build(fake_main_t * const main, fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) {

    f_status_t status = F_none;
    f_string_dynamic_t value = f_string_dynamic_t_initialize;

    bool unmatched = F_true;

    {
      const f_string_t uint8_name[] = {
        fake_build_setting_name_build_language_s,
        fake_build_setting_name_version_file_s,
        fake_build_setting_name_version_target_s,
      };

      const f_array_length_t uint8_length[] = {
        fake_build_setting_name_build_language_s_length,
        fake_build_setting_name_version_file_s_length,
        fake_build_setting_name_version_target_s_length,
      };

      const uint8_t uint8_value[] = {
        data_make->setting_build.build_language,
        data_make->setting_build.version_file,
        data_make->setting_build.version_target,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        status = fl_string_dynamic_partial_compare_string(uint8_name[i], data_make->buffer, uint8_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          status = f_conversion_number_unsigned_to_string(uint8_value[i], f_conversion_data_base_10_s, &value);
          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string_t bool_name[] = {
        fake_build_setting_name_build_script_s,
        fake_build_setting_name_build_shared_s,
        fake_build_setting_name_build_static_s,
        fake_build_setting_name_path_standard_s,
        fake_build_setting_name_search_exclusive_s,
        fake_build_setting_name_search_shared_s,
        fake_build_setting_name_search_static_s,
      };

      const f_array_length_t bool_length[] = {
        fake_build_setting_name_build_script_s_length,
        fake_build_setting_name_build_shared_s_length,
        fake_build_setting_name_build_static_s_length,
        fake_build_setting_name_path_standard_s_length,
        fake_build_setting_name_search_exclusive_s_length,
        fake_build_setting_name_search_shared_s_length,
        fake_build_setting_name_search_static_s_length,
      };

      const bool bool_value[] = {
        data_make->setting_build.build_script,
        data_make->setting_build.build_shared,
        data_make->setting_build.build_static,
        data_make->setting_build.path_standard,
        data_make->setting_build.search_exclusive,
        data_make->setting_build.search_shared,
        data_make->setting_build.search_static,
      };

      for (uint8_t i = 0; i < 7; ++i) {

        status = fl_string_dynamic_partial_compare_string(bool_name[i], data_make->buffer, bool_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          if (bool_value[i]) {
            status = f_string_append(fake_common_setting_bool_yes_s, fake_common_setting_bool_yes_s_length, &value);
          }
          else {
            status = f_string_append(fake_common_setting_bool_no_s, fake_common_setting_bool_no_s_length, &value);
          }

          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string_t dynamic_name[] = {
        fake_build_setting_name_build_compiler_s,
        fake_build_setting_name_build_indexer_s,
        fake_build_setting_name_path_headers_s,
        fake_build_setting_name_path_language_s,
        fake_build_setting_name_path_library_script_s,
        fake_build_setting_name_path_library_shared_s,
        fake_build_setting_name_path_library_static_s,
        fake_build_setting_name_path_program_script_s,
        fake_build_setting_name_path_program_shared_s,
        fake_build_setting_name_path_program_static_s,
        fake_build_setting_name_path_sources_s,
        fake_build_setting_name_process_post_s,
        fake_build_setting_name_process_pre_s,
        fake_build_setting_name_project_name_s,
        fake_build_setting_name_version_major_s,
        fake_build_setting_name_version_micro_s,
        fake_build_setting_name_version_minor_s,
      };

      const f_array_length_t dynamic_length[] = {
        fake_build_setting_name_build_compiler_s_length,
        fake_build_setting_name_build_indexer_s_length,
        fake_build_setting_name_path_headers_s_length,
        fake_build_setting_name_path_language_s_length,
        fake_build_setting_name_path_library_script_s_length,
        fake_build_setting_name_path_library_shared_s_length,
        fake_build_setting_name_path_library_static_s_length,
        fake_build_setting_name_path_program_script_s_length,
        fake_build_setting_name_path_program_shared_s_length,
        fake_build_setting_name_path_program_static_s_length,
        fake_build_setting_name_path_sources_s_length,
        fake_build_setting_name_process_post_s_length,
        fake_build_setting_name_process_pre_s_length,
        fake_build_setting_name_project_name_s_length,
        fake_build_setting_name_version_major_s_length,
        fake_build_setting_name_version_micro_s_length,
        fake_build_setting_name_version_minor_s_length,
      };

      const f_string_dynamic_t dynamic_value[] = {
        data_make->setting_build.build_compiler,
        data_make->setting_build.build_indexer,
        data_make->setting_build.path_headers,
        data_make->setting_build.path_language,
        data_make->setting_build.path_library_script,
        data_make->setting_build.path_library_shared,
        data_make->setting_build.path_library_static,
        data_make->setting_build.path_program_script,
        data_make->setting_build.path_program_shared,
        data_make->setting_build.path_program_static,
        data_make->setting_build.path_sources,
        data_make->setting_build.process_post,
        data_make->setting_build.process_pre,
        data_make->setting_build.project_name,
        data_make->setting_build.version_major,
        data_make->setting_build.version_micro,
        data_make->setting_build.version_minor,
      };

      for (uint8_t i = 0; i < 17; ++i) {

        status = fl_string_dynamic_partial_compare_string(dynamic_name[i], data_make->buffer, dynamic_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          status = f_string_dynamic_append(dynamic_value[i], &value);
          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string_t dynamics_name[] = {
        fake_build_setting_name_build_libraries_s,
        fake_build_setting_name_build_libraries_shared_s,
        fake_build_setting_name_build_libraries_static_s,
        fake_build_setting_name_build_sources_headers_s,
        fake_build_setting_name_build_sources_headers_shared_s,
        fake_build_setting_name_build_sources_headers_static_s,
        fake_build_setting_name_build_sources_library_s,
        fake_build_setting_name_build_sources_library_shared_s,
        fake_build_setting_name_build_sources_library_static_s,
        fake_build_setting_name_build_sources_program_s,
        fake_build_setting_name_build_sources_program_shared_s,
        fake_build_setting_name_build_sources_program_static_s,
        fake_build_setting_name_build_sources_settings_s,
        fake_build_setting_name_build_sources_script_s,
        fake_build_setting_name_defines_s,
        fake_build_setting_name_defines_library_s,
        fake_build_setting_name_defines_library_shared_s,
        fake_build_setting_name_defines_library_static_s,
        fake_build_setting_name_defines_program_s,
        fake_build_setting_name_defines_program_shared_s,
        fake_build_setting_name_defines_program_static_s,
        fake_build_setting_name_defines_shared_s,
        fake_build_setting_name_defines_static_s,
        fake_build_setting_name_environment_s,
        fake_build_setting_name_flags_s,
        fake_build_setting_name_flags_library_s,
        fake_build_setting_name_flags_library_shared_s,
        fake_build_setting_name_flags_library_static_s,
        fake_build_setting_name_flags_program_s,
        fake_build_setting_name_flags_program_shared_s,
        fake_build_setting_name_flags_program_static_s,
        fake_build_setting_name_flags_shared_s,
        fake_build_setting_name_flags_static_s,
        fake_build_setting_name_modes_s,
        fake_build_setting_name_modes_default_s,
      };

      const f_array_length_t dynamics_length[] = {
        fake_build_setting_name_build_libraries_s_length,
        fake_build_setting_name_build_libraries_shared_s_length,
        fake_build_setting_name_build_libraries_static_s_length,
        fake_build_setting_name_build_sources_headers_s_length,
        fake_build_setting_name_build_sources_headers_shared_s_length,
        fake_build_setting_name_build_sources_headers_static_s_length,
        fake_build_setting_name_build_sources_library_s_length,
        fake_build_setting_name_build_sources_library_shared_s_length,
        fake_build_setting_name_build_sources_library_static_s_length,
        fake_build_setting_name_build_sources_program_s_length,
        fake_build_setting_name_build_sources_program_shared_s_length,
        fake_build_setting_name_build_sources_program_static_s_length,
        fake_build_setting_name_build_sources_settings_s_length,
        fake_build_setting_name_build_sources_script_s_length,
        fake_build_setting_name_defines_s_length,
        fake_build_setting_name_defines_library_s_length,
        fake_build_setting_name_defines_library_shared_s_length,
        fake_build_setting_name_defines_library_static_s_length,
        fake_build_setting_name_defines_program_s_length,
        fake_build_setting_name_defines_program_shared_s_length,
        fake_build_setting_name_defines_program_static_s_length,
        fake_build_setting_name_defines_shared_s_length,
        fake_build_setting_name_defines_static_s_length,
        fake_build_setting_name_environment_length_s,
        fake_build_setting_name_flags_s_length,
        fake_build_setting_name_flags_library_s_length,
        fake_build_setting_name_flags_library_shared_s_length,
        fake_build_setting_name_flags_library_static_s_length,
        fake_build_setting_name_flags_program_s_length,
        fake_build_setting_name_flags_program_shared_s_length,
        fake_build_setting_name_flags_program_static_s_length,
        fake_build_setting_name_flags_shared_s_length,
        fake_build_setting_name_flags_static_s_length,
        fake_build_setting_name_modes_s_length,
        fake_build_setting_name_modes_default_s_length,
      };

      const f_string_dynamics_t dynamics_value[] = {
        data_make->setting_build.build_libraries,
        data_make->setting_build.build_libraries_shared,
        data_make->setting_build.build_libraries_static,
        data_make->setting_build.build_sources_headers,
        data_make->setting_build.build_sources_headers_shared,
        data_make->setting_build.build_sources_headers_static,
        data_make->setting_build.build_sources_library,
        data_make->setting_build.build_sources_library_shared,
        data_make->setting_build.build_sources_library_static,
        data_make->setting_build.build_sources_program,
        data_make->setting_build.build_sources_program_shared,
        data_make->setting_build.build_sources_program_static,
        data_make->setting_build.build_sources_setting,
        data_make->setting_build.build_sources_script,
        data_make->setting_build.defines,
        data_make->setting_build.defines_library,
        data_make->setting_build.defines_library_shared,
        data_make->setting_build.defines_library_static,
        data_make->setting_build.defines_program,
        data_make->setting_build.defines_program_shared,
        data_make->setting_build.defines_program_static,
        data_make->setting_build.defines_shared,
        data_make->setting_build.defines_static,
        data_make->setting_build.environment,
        data_make->setting_build.flags,
        data_make->setting_build.flags_library,
        data_make->setting_build.flags_library_shared,
        data_make->setting_build.flags_library_static,
        data_make->setting_build.flags_program,
        data_make->setting_build.flags_program_shared,
        data_make->setting_build.flags_program_static,
        data_make->setting_build.flags_shared,
        data_make->setting_build.flags_static,
        data_make->setting_build.modes,
        data_make->setting_build.modes_default,
      };

      for (uint8_t i = 0; i < 35; ++i) {

        status = fl_string_dynamic_partial_compare_string(dynamics_name[i], data_make->buffer, dynamics_length[i], range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          for (f_array_length_t j = 0; j < dynamics_value[i].used; ++j) {

            status = f_string_dynamic_mash(f_string_space_s, 1, dynamics_value[i].array[j], &value);

            if (F_status_is_error(status)) {
              break;
            }
          } // for

          break;
        }
      } // for
    }

    if (F_status_is_error(status)) {
      macro_f_string_dynamic_t_delete_simple(value);

      return status;
    }

    if (unmatched) {
      macro_f_string_dynamic_t_delete_simple(value);

      return F_false;
    }

    if (quoted) {
      status = f_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);
    }
    else {
      status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, arguments);

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

          if (F_status_is_error_not(status)) {
            ++arguments->used;
          }
        }
      }
    }

    macro_f_string_dynamic_t_delete_simple(value);

    if (F_status_is_error_not(status)) {
      return F_true;
    }

    return status;
  }
#endif // _di_fake_make_operate_expand_build_

#ifndef _di_fake_make_operate_expand_environment_
  f_status_t fake_make_operate_expand_environment(fake_main_t * const main, fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) {

    f_status_t status = F_none;
    f_string_dynamic_t value = f_string_dynamic_t_initialize;

    bool unmatched = F_false;

    {
      f_string_dynamic_t name = f_string_dynamic_t_initialize;

      status = f_string_dynamic_partial_append_nulless(data_make->buffer, range_name, &name);
      if (F_status_is_error(status)) return status;

      status = f_environment_get(name.string, &value);

      macro_f_string_dynamic_t_delete_simple(name);
    }

    if (F_status_is_error(status)) {
      macro_f_string_dynamic_t_delete_simple(value);

      return status;
    }
    else if (status == F_exist_not) {
      macro_f_string_dynamic_t_delete_simple(value);

      return F_false;
    }

    if (quoted) {
      status = f_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);
    }
    else {
      status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, arguments);

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append_nulless(value, &arguments->array[arguments->used]);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

          if (F_status_is_error_not(status)) {
            ++arguments->used;
          }
        }
      }
    }

    macro_f_string_dynamic_t_delete_simple(value);

    if (F_status_is_error_not(status)) {
      return F_true;
    }

    return status;
  }
#endif // _di_fake_make_operate_expand_environment_

#ifndef _di_fake_make_operate_section_
  int fake_make_operate_section(fake_main_t * const main, fake_make_data_t * const data_make, const f_array_length_t id_section, f_array_lengths_t *section_stack, f_status_t *status) {

    if (F_status_is_error(*status) || *status == F_child) return main->child;

    if (id_section > data_make->fakefile.used) {
      *status = F_status_set_error(F_parameter);

      fll_error_print(data_make->error, F_parameter, "fake_make_operate_section", F_true);

      return 0;
    }

    // Add the operation id to the operation stack.
    *status = f_type_array_lengths_increase(fake_default_allocation_small_d, section_stack);

    if (F_status_is_error(*status)) {
      fll_error_print(data_make->error, F_status_set_fine(*status), "f_type_array_lengths_increase", F_true);

      return 0;
    }

    section_stack->array[section_stack->used++] = id_section;

    const f_fss_named_t *section = &data_make->fakefile.array[id_section];

    if (main->output.verbosity != f_console_verbosity_quiet) {
      flockfile(main->output.to.stream);

      fl_print_format("%c%[Processing Section '%]", main->output.to.stream, f_string_eol_s[0], main->context.set.important, main->context.set.important);
      fl_print_format("%[%/Q%]", main->output.to.stream, main->context.set.notable, data_make->buffer, section->name, main->context.set.notable);
      fl_print_format("%['.%]%c", main->output.to.stream, main->context.set.important, main->context.set.important, f_string_eol_s[0]);

      funlockfile(main->output.to.stream);
    }

    if (!section->objects.used) {
      --section_stack->used;

      return 0;
    }

    const f_string_t operations_name[] = {
      fake_make_operation_break_s,
      fake_make_operation_build_s,
      fake_make_operation_clean_s,
      fake_make_operation_clone_s,
      fake_make_operation_compile_s,
      fake_make_operation_copy_s,
      fake_make_operation_define_s,
      fake_make_operation_delete_s,
      fake_make_operation_deletes_s,
      fake_make_operation_else_s,
      fake_make_operation_exit_s,
      fake_make_operation_fail_s,
      fake_make_operation_group_s,
      fake_make_operation_groups_s,
      fake_make_operation_if_s,
      fake_make_operation_index_s,
      fake_make_operation_link_s,
      fake_make_operation_mode_s,
      fake_make_operation_modes_s,
      fake_make_operation_move_s,
      fake_make_operation_operate_s,
      fake_make_operation_owner_s,
      fake_make_operation_owners_s,
      fake_make_operation_parameter_s,
      fake_make_operation_pop_s,
      fake_make_operation_print_s,
      fake_make_operation_run_s,
      fake_make_operation_shell_s,
      fake_make_operation_skeleton_s,
      fake_make_operation_to_s,
      fake_make_operation_top_s,
      fake_make_operation_touch_s,
    };

    const f_array_length_t operations_length[] = {
      fake_make_operation_break_s_length,
      fake_make_operation_build_s_length,
      fake_make_operation_clean_s_length,
      fake_make_operation_clone_s_length,
      fake_make_operation_compile_s_length,
      fake_make_operation_copy_s_length,
      fake_make_operation_define_s_length,
      fake_make_operation_delete_s_length,
      fake_make_operation_deletes_s_length,
      fake_make_operation_else_s_length,
      fake_make_operation_exit_s_length,
      fake_make_operation_fail_s_length,
      fake_make_operation_group_s_length,
      fake_make_operation_groups_s_length,
      fake_make_operation_if_s_length,
      fake_make_operation_index_s_length,
      fake_make_operation_link_s_length,
      fake_make_operation_mode_s_length,
      fake_make_operation_modes_s_length,
      fake_make_operation_move_s_length,
      fake_make_operation_operate_s_length,
      fake_make_operation_owner_s_length,
      fake_make_operation_owners_s_length,
      fake_make_operation_parameter_s_length,
      fake_make_operation_pop_s_length,
      fake_make_operation_print_s_length,
      fake_make_operation_run_s_length,
      fake_make_operation_shell_s_length,
      fake_make_operation_skeleton_s_length,
      fake_make_operation_to_s_length,
      fake_make_operation_top_s_length,
      fake_make_operation_touch_s_length,
    };

    const uint8_t operations_type[] = {
      fake_make_operation_type_break,
      fake_make_operation_type_build,
      fake_make_operation_type_clean,
      fake_make_operation_type_clone,
      fake_make_operation_type_compile,
      fake_make_operation_type_copy,
      fake_make_operation_type_define,
      fake_make_operation_type_delete,
      fake_make_operation_type_deletes,
      fake_make_operation_type_else,
      fake_make_operation_type_exit,
      fake_make_operation_type_fail,
      fake_make_operation_type_group,
      fake_make_operation_type_groups,
      fake_make_operation_type_if,
      fake_make_operation_type_index,
      fake_make_operation_type_link,
      fake_make_operation_type_mode,
      fake_make_operation_type_modes,
      fake_make_operation_type_move,
      fake_make_operation_type_operate,
      fake_make_operation_type_owner,
      fake_make_operation_type_owners,
      fake_make_operation_type_parameter,
      fake_make_operation_type_pop,
      fake_make_operation_type_print,
      fake_make_operation_type_run,
      fake_make_operation_type_shell,
      fake_make_operation_type_skeleton,
      fake_make_operation_type_to,
      fake_make_operation_type_top,
      fake_make_operation_type_touch,
    };

    uint8_t operation = 0;
    uint8_t operations[section->objects.used];
    uint8_t operation_if = 0;

    bool success = F_true;

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    memset(operations, 0, section->objects.used);

    for (i = 0; i < section->objects.used; ++i, *status = F_none) {

      for (j = 0; j < arguments.size; ++j) {
        arguments.array[j].used = 0;
      } // for

      arguments.used = 0;
      operation = 0;

      if (!(i % fake_signal_check_short_d) && fake_signal_received(main)) {
        *status = F_status_set_error(F_interrupt);

        break;
      }

      for (j = 0; j < fake_make_operation_total_d; ++j) {

        if (fl_string_dynamic_partial_compare_string(operations_name[j], data_make->buffer, operations_length[j], section->objects.array[i]) == F_equal_to) {
          operation = operations_type[j];

          break;
        }
      } // for

      if (!operation) {
        fake_print_message_section_operation_unknown(main, data_make->error, data_make->buffer, section->name, section->objects.array[i]);

        *status = F_status_set_error(F_valid_not);
      }
      else if (operation == fake_make_operation_type_operate) {
        if (section_stack->used == fake_make_section_stack_max_d) {
          fake_print_message_section_operation_stack_max(main, data_make->error, data_make->buffer, section->name, section->objects.array[i], fake_make_section_stack_max_d);

          *status = F_status_set_error(F_recurse);
        }
      }

      if (F_status_is_error_not(*status)) {
        operations[i] = operation;

        fake_make_operate_expand(main, data_make, section->name, operation, section->contents.array[i], section->quotess.array[i], &arguments, status);
      }

      if (operation_if == fake_make_operation_if_type_true_next) {
        operation_if = fake_make_operation_if_type_true;
      }
      else if (operation_if == fake_make_operation_if_type_false_next) {
        operation_if = fake_make_operation_if_type_false;
      }
      else if (operation_if == fake_make_operation_if_type_false_always_next) {
        operation_if = fake_make_operation_if_type_false_always;
      }

      fake_make_operate_validate(main, data_make, section->name, operation, arguments, &operation_if, section_stack, status);

      if (F_status_is_error_not(*status)) {
        if (operation_if == fake_make_operation_if_type_false) {
          operation_if = fake_make_operation_if_type_else_true_next;

          continue;
        }
        else if (operation_if == fake_make_operation_if_type_false_always) {
          operation_if = fake_make_operation_if_type_else_false_next_always;

          continue;
        }
        else if (operation_if == fake_make_operation_if_type_else_false) {
          operation_if = 0;

          continue;
        }

        const int result = fake_make_operate_process(main, data_make, section->name, operation, arguments, success, &operation_if, section_stack, status);

        if (*status == F_child) {
          f_string_dynamics_resize(0, &arguments);

          return result;
        }
      }
      else {
        if (operation == fake_make_operation_type_if) {
          switch (operation_if) {
            case fake_make_operation_if_type_if_defined:
            case fake_make_operation_if_type_if_equal:
            case fake_make_operation_if_type_if_equal_not:
            case fake_make_operation_if_type_if_exists:
            case fake_make_operation_if_type_if_failure:
            case fake_make_operation_if_type_if_greater:
            case fake_make_operation_if_type_if_greater_equal:
            case fake_make_operation_if_type_if_group:
            case fake_make_operation_if_type_if_is:
            case fake_make_operation_if_type_if_less:
            case fake_make_operation_if_type_if_less_equal:
            case fake_make_operation_if_type_if_mode:
            case fake_make_operation_if_type_if_not:
            case fake_make_operation_if_type_if_not_defined:
            case fake_make_operation_if_type_if_not_exists:
            case fake_make_operation_if_type_if_not_group:
            case fake_make_operation_if_type_if_not_is:
            case fake_make_operation_if_type_if_not_mode:
            case fake_make_operation_if_type_if_not_owner:
            case fake_make_operation_if_type_if_owner:
            case fake_make_operation_if_type_if_success:
              operation_if = 0;
              break;
          }
        }

        if (operation_if == fake_make_operation_if_type_false) {
          operation_if = fake_make_operation_if_type_else_true_next;
        }
        else if (operation_if == fake_make_operation_if_type_false_always) {
          operation_if = fake_make_operation_if_type_else_false_next_always;
        }
        else if (operation_if == fake_make_operation_if_type_else_false) {
          operation_if = 0;
        }
      }

      if (F_status_set_fine(*status) == F_interrupt) break;

      if (operation_if == fake_make_operation_if_type_else_true || operation_if == fake_make_operation_if_type_else_false) {

        // No else condition provided, so clear the operation_if state.
        if (operation != fake_make_operation_type_else) {
          operation_if = 0;
        }
      }
      else if (operation_if == fake_make_operation_if_type_true) {
        operation_if = fake_make_operation_if_type_else_false_next;
      }
      else if (operation_if == fake_make_operation_if_type_false_always) {
        operation_if = fake_make_operation_if_type_else_false_next_always;
      }

      if (F_status_is_error(*status)) {
        success = F_false;

        // Break acts identical to fail when at the top of the stack.
        if (F_status_set_fine(*status) == F_signal_abort && !section_stack->used) {
          data_make->setting_make.fail = fake_make_operation_fail_type_exit;
          data_make->error.prefix = fl_print_error_s;
          data_make->error.suffix = 0;
          data_make->error.context = main->context.set.error;
          data_make->error.notable = main->context.set.notable;
          data_make->error.to.stream = F_type_error_d;
          data_make->error.to.id = F_type_descriptor_error_d;
          data_make->error.set = &main->context.set;
        }

        fake_print_message_section_operation_failed(main, data_make->error, data_make->buffer, section->name, section->objects.array[i]);

        // F_signal_abort is used by the break section operation.
        if (F_status_set_fine(*status) == F_signal_abort) break;

        // F_signal_abort is used by the exit section operation.
        if (F_status_set_fine(*status) == F_signal_quit) {
          if (!section_stack->used) {
            *status = F_status_set_error(F_failure);
          }

          break;
        }

        if (data_make->setting_make.fail == fake_make_operation_fail_type_exit) {
          operation_if = 0;

          break;
        }
      }
      else if (*status == F_signal_abort) {
        success = F_true;

        // F_signal_abort is used by the break section operation.
        break;
      }
      else if (*status == F_signal_quit) {
        success = F_true;

        // F_signal_abort is used by the exit section operation.
        if (!section_stack->used) {
          *status = F_none;
        }

        break;
      }
      else {
        success = F_true;
      }
    } // for

    if (F_status_set_error(*status) == F_interrupt) {
      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    if (i == section->objects.used && (operation_if == fake_make_operation_if_type_true_next || operation_if == fake_make_operation_if_type_false_next || operation_if == fake_make_operation_if_type_else_true || operation_if == fake_make_operation_if_type_else_false)) {

      if (main->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%c%[%SIncomplete '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);

        if (operation_if == fake_make_operation_if_type_true_next || operation_if == fake_make_operation_if_type_false_next) {
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
        }
        else {
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_else_s, data_make->error.notable);
        }

        fl_print_format("%[' at end of section.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

        funlockfile(data_make->error.to.stream);
      }

      fake_print_message_section_operation_failed(main, data_make->error, data_make->buffer, section->name, section->objects.array[section->objects.used - 1]);

      *status = F_status_set_error(F_failure);
    }

    // Ensure an error is returned during recursion if the last known section operation failed, except for the main operation.
    if (success == F_false && F_status_is_error_not(*status) && section_stack->used > 1) {
      *status = F_status_set_error(F_failure);
    }

    f_string_dynamics_resize(0, &arguments);

    --section_stack->used;

    return 0;
  }
#endif // _di_fake_make_operate_section_

#ifndef _di_fake_make_operate_process_
  int fake_make_operate_process(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_range_t section_name, const uint8_t operation, const f_string_dynamics_t arguments, const bool success, uint8_t *operation_if, f_array_lengths_t *section_stack, f_status_t *status) {

    if (*status == F_child) return main->child;

    if (operation == fake_make_operation_type_index) {
      const f_status_t result = fake_execute(main, data_make->environment, data_make->setting_build.build_indexer, arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "fake_execute", F_true);
      }

      if (*status == F_child) {
        return result;
      }

      *status = fake_make_operate_process_return(main, data_make, result);

      return 0;
    }

    if (operation == fake_make_operation_type_break) {

      if (!arguments.used || fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to) {
        *status = F_signal_abort;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to) {
        *status = F_status_set_error(F_signal_abort);
      }
      else {
        return 0;
      }

      if (main->error.verbosity == f_console_verbosity_verbose) {
        flockfile(main->output.to.stream);

        fl_print_format("%cBreaking as '", main->output.to.stream, f_string_eol_s[0]);
        fl_print_format("%[%S%]", main->output.to.stream, main->context.set.notable, arguments.used ? arguments.array[0].string : fake_make_operation_argument_success_s, main->context.set.notable);
        fl_print_format("'.%c", main->output.to.stream, f_string_eol_s[0]);

        funlockfile(main->output.to.stream);
      }

      return 0;
    }

    if (operation == fake_make_operation_type_build) {
      f_string_static_t stub = f_string_static_t_initialize;

      *status = fake_build_operate(arguments.used ? arguments.array[0] : stub, main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(main, data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (operation == fake_make_operation_type_clean) {
      *status = fake_clean_operate(main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(main, data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (operation == fake_make_operation_type_clone) {
      *status = fake_make_operate_process_type_copy(main, data_make, arguments, F_true);

      return 0;
    }

    if (operation == fake_make_operation_type_compile) {
      const int result = fake_execute(main, data_make->environment, data_make->setting_build.build_compiler, arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "fake_execute", F_true);
      }

      if (*status == F_child) {
        return result;
      }

      *status = fake_make_operate_process_return(main, data_make, result);

      return 0;
    }

    if (operation == fake_make_operation_type_copy) {
      *status = fake_make_operate_process_type_copy(main, data_make, arguments, F_false);

      return 0;
    }

    if (operation == fake_make_operation_type_define) {

      if (arguments.used > 1) {
        *status = f_environment_set(arguments.array[0].string, arguments.array[1].string, F_true);
      }
      else {
        *status = f_environment_set(arguments.array[0].string, f_string_empty_s, F_true);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "f_environment_set", F_true);
      }
      else if (main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("%cDefined environment variable '%[%Q%]'.%c", main->output.to.stream, f_string_eol_s[0], main->context.set.notable, arguments.array[0], main->context.set.notable, f_string_eol_s[0]);
      }

      return 0;
    }

    if (operation == fake_make_operation_type_delete) {
      *status = fake_make_operate_process_type_deletes(main, data_make, arguments, F_false);

      return 0;
    }

    if (operation == fake_make_operation_type_deletes) {
      *status = fake_make_operate_process_type_deletes(main, data_make, arguments, F_true);

      return 0;
    }

    if (operation == fake_make_operation_type_else) {

      if (*operation_if == fake_make_operation_if_type_else_false_next || *operation_if == fake_make_operation_if_type_else_false_next_always) {
        *operation_if = fake_make_operation_if_type_else_false;
      }
      else if (*operation_if != fake_make_operation_if_type_else_true_next) {
        *operation_if = fake_make_operation_if_type_else_true;
      }

      return 0;
    }

    if (operation == fake_make_operation_type_exit) {

      if (!arguments.used || fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to) {
        *status = F_signal_quit;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to) {
        *status = F_status_set_error(F_signal_quit);

        // Forcing exit forces fail mode.
        data_make->setting_make.fail = fake_make_operation_fail_type_exit;
        data_make->error.prefix = fl_print_error_s;
        data_make->error.suffix = 0;
        data_make->error.context = main->context.set.error;
        data_make->error.notable = main->context.set.notable;
        data_make->error.to.stream = F_type_error_d;
        data_make->error.to.id = F_type_descriptor_error_d;
        data_make->error.set = &main->context.set;
      }
      else {
        return 0;
      }

      if (main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("%cExiting as '%[%S%]'.%c", main->output.to.stream, f_string_eol_s[0], main->context.set.notable, arguments.used ? arguments.array[0].string : fake_make_operation_argument_success_s, main->context.set.notable, f_string_eol_s[0]);
      }

      return 0;
    }

    if (operation == fake_make_operation_type_fail) {
      fake_make_operate_process_type_fail(main, data_make, arguments);

      return 0;
    }

    if (operation == fake_make_operation_type_group) {
      *status = fake_make_operate_process_type_groups(main, data_make, arguments, F_false);

      return 0;
    }

    if (operation == fake_make_operation_type_groups) {
      *status = fake_make_operate_process_type_groups(main, data_make, arguments, F_true);

      return 0;
    }

    if (operation == fake_make_operation_type_if) {
      if (*operation_if == fake_make_operation_if_type_if_success) {
        if (success) {
          *operation_if = fake_make_operation_if_type_true_next;
        }
        else {
          *operation_if = fake_make_operation_if_type_false_next;
        }

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_defined) {
        fake_make_operate_process_type_if_defined(main, data_make, arguments, F_false, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_exists) {
        *status = fake_make_operate_process_type_if_exists(main, data_make, arguments, F_false, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_failure) {
        if (success) {
          *operation_if = fake_make_operation_if_type_false_next;
        }
        else {
          *operation_if = fake_make_operation_if_type_true_next;
        }

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_group) {
        *status = fake_make_operate_process_type_if_group(main, data_make, arguments, F_false, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_is) {
        *status = fake_make_operate_process_type_if_is(main, data_make, arguments, F_false, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_mode) {
        *status = fake_make_operate_process_type_if_mode(main, data_make, arguments, F_false, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_not_defined) {
        fake_make_operate_process_type_if_defined(main, data_make, arguments, F_true, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_equal) {
        *operation_if = fake_make_operation_if_type_true_next;

        for (f_array_length_t i = 2; i < arguments.used; ++i) {

          if (fl_string_dynamic_compare(arguments.array[1], arguments.array[i]) == F_equal_to_not) {
            *operation_if = fake_make_operation_if_type_false_next;

            break;
          }
        } // for

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_equal_not) {
        *operation_if = fake_make_operation_if_type_true_next;

        f_array_length_t i = 1;
        f_array_length_t j = 0;

        for (; i < arguments.used; ++i) {

          for (j = i + 1; j < arguments.used; ++j) {

            if (fl_string_dynamic_compare(arguments.array[i], arguments.array[j]) == F_equal_to) {
              *operation_if = fake_make_operation_if_type_false_next;
              i = arguments.used;

              break;
            }
          } // for
        } // for

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_greater || *operation_if == fake_make_operation_if_type_if_greater_equal || *operation_if == fake_make_operation_if_type_if_less || *operation_if == fake_make_operation_if_type_if_less_equal) {
        *status = fake_make_operate_process_type_if_greater_if_lesser(main, data_make, arguments, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_not_exists) {
        *status = fake_make_operate_process_type_if_exists(main, data_make, arguments, F_true, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_not_group) {
        *status = fake_make_operate_process_type_if_group(main, data_make, arguments, F_true, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_not_is) {
        *status = fake_make_operate_process_type_if_is(main, data_make, arguments, F_true, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_not_mode) {
        *status = fake_make_operate_process_type_if_mode(main, data_make, arguments, F_true, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_not_owner) {
        *status = fake_make_operate_process_type_if_owner(main, data_make, arguments, F_true, operation_if);

        return 0;
      }

      if (*operation_if == fake_make_operation_if_type_if_owner) {
        *status = fake_make_operate_process_type_if_owner(main, data_make, arguments, F_false, operation_if);

        return 0;
      }

      return 0;
    }

    if (operation == fake_make_operation_type_link) {
      *status = f_file_link(arguments.array[0].string, arguments.array[1].string);

      if (F_status_is_error(*status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_link", F_true, arguments.array[1].string, "create link", fll_error_file_type_file);
      }
      else if (main->error.verbosity == f_console_verbosity_verbose) {
        flockfile(main->output.to.stream);

        fl_print_format("Created symbolic link from '%[%Q%]", main->output.to.stream, main->context.set.notable, arguments.array[1], main->context.set.notable);
        fl_print_format("' to %[%Q%].%c", main->output.to.stream, main->context.set.notable, arguments.array[0], main->context.set.notable, f_string_eol_s[0]);

        funlockfile(main->output.to.stream);
      }

      return 0;
    }

    if (operation == fake_make_operation_type_mode) {
      *status = fake_make_operate_process_type_modes(main, data_make, arguments, F_false);

      return 0;
    }

    if (operation == fake_make_operation_type_modes) {
      *status = fake_make_operate_process_type_modes(main, data_make, arguments, F_true);

      return 0;
    }

    if (operation == fake_make_operation_type_move) {
      *status = fake_make_operate_process_type_move(main, data_make, arguments);

      return 0;
    }

    if (operation == fake_make_operation_type_operate) {
      f_array_length_t id_section = 0;

      for (; id_section < data_make->fakefile.used; ++id_section) {

        if (fl_string_dynamic_partial_compare_string(arguments.array[0].string, data_make->buffer, arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
          break;
        }
      } // for

      if (id_section == data_make->fakefile.used) {
        return 0;
      }

      const int result = fake_make_operate_section(main, data_make, id_section, section_stack, status);

      // Ensure that a break only happens within its active operation stack.
      if (*status == F_signal_abort) {
        *status = F_none;
      }
      else if (F_status_set_fine(*status) == F_signal_abort) {
        *status = F_status_set_error(F_failure);
      }

      return result;
    }

    if (operation == fake_make_operation_type_owner) {
      *status = fake_make_operate_process_type_owners(main, data_make, arguments, F_false);

      return 0;
    }

    if (operation == fake_make_operation_type_owners) {
      *status = fake_make_operate_process_type_owners(main, data_make, arguments, F_true);

      return 0;
    }

    if (operation == fake_make_operation_type_parameter) {
      *status = fake_make_operate_process_type_parameter(main, data_make, arguments);

      return 0;
    }

    if (operation == fake_make_operation_type_pop) {
      *status = fake_make_operate_process_type_pop(main, data_make, arguments);

      return 0;
    }

    if (operation == fake_make_operation_type_print) {
      flockfile(main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        f_print_dynamic(arguments.array[i], main->output.to.stream);

        if (i + 1 < arguments.used) {
          f_print_character(f_string_space_s[0], main->output.to.stream);
        }
      } // for

      f_print_character(f_string_space_s[0], main->output.to.stream);
      f_print_character(f_string_eol_s[0], main->output.to.stream);

      funlockfile(main->output.to.stream);

      return 0;
    }

    if (operation == fake_make_operation_type_run) {
      *status = fake_make_operate_process_run(main, data_make, arguments, F_false);

      return 0;
    }

    if (operation == fake_make_operation_type_shell) {
      *status = fake_make_operate_process_run(main, data_make, arguments, F_true);

      return 0;
    }

    if (operation == fake_make_operation_type_skeleton) {
      *status = fake_skeleton_operate(main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(main, data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (operation == fake_make_operation_type_to) {
      *status = fake_make_operate_process_type_to(main, data_make, arguments);

      return 0;
    }

    if (operation == fake_make_operation_type_top) {
      *status = fake_make_operate_process_type_top(main, data_make, arguments);

      return 0;
    }

    if (operation == fake_make_operation_type_touch) {
      *status = fake_make_operate_process_type_touch(main, data_make, arguments);
    }

    return 0;
  }
#endif // _di_fake_make_operate_process_

#ifndef _di_fake_make_operate_process_execute_
  f_status_t fake_make_operate_process_execute(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell) {

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_none;

    // reset the environment.
    for (f_array_length_t i = 0; i < data_make->environment.used; ++i) {

      data_make->environment.array[i].name.used = 0;
      data_make->environment.array[i].value.used = 0;
    } // for

    data_make->environment.used = 0;

    status = fl_environment_load_names(data_make->setting_build.environment, &data_make->environment);

    if (F_status_is_error(status)) {
      fll_error_print(data_make->error, F_status_set_fine(status), "fl_environment_load_names", F_true);

      return status;
    }

    if (main->error.verbosity == f_console_verbosity_verbose) {
      flockfile(main->output.to.stream);

      f_print_dynamic_safely(program, main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        if (arguments.array[i].used) {
          fll_print_format(" %Q", main->output.to.stream, arguments.array[i]);
        }
      } // for

      f_print_character(f_string_eol_s[0], main->output.to.stream);

      funlockfile(main->output.to.stream);

      // flush to stdout before executing command.
      fflush(main->output.to.stream);
    }

    int return_code = 0;

    // child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(as_shell ? 0 : FL_execute_parameter_option_path_d, 0, &data_make->environment, &signals, 0);

    status = fll_execute_program(program.string, arguments, &parameter, 0, (void *) &return_code);

    if (fake_signal_received(main)) {
      return F_status_set_error(F_interrupt);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_interrupt) {
        return status;
      }

      if (F_status_set_fine(status) == F_file_found_not) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SFailed to find program '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, program, data_make->error.notable);
          fl_print_format("%[' for executing.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }
      }
      else if (F_status_set_fine(status) != F_failure) {
        fll_error_print(data_make->error, F_status_set_fine(status), "fll_execute_program", F_true);
      }
    }

    return fake_make_operate_process_return(main, data_make, return_code);
  }
#endif // _di_fake_make_operate_process_execute_

#ifndef _di_fake_make_operate_process_return_
  f_status_t fake_make_operate_process_return(fake_main_t * const main, fake_make_data_t * const data_make, const int return_code) {

    f_status_t status = F_none;

    data_make->setting_make.parameter.array[0].value.array[0].used = 0;

    if (!return_code) {
      if (F_status_is_error(status)) {
        status = f_string_append("1", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }
      else {
        status = f_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_append", F_true);
      }

      return status;
    }

    if (return_code) {
      f_string_dynamic_t number = f_string_dynamic_t_initialize;

      status = f_conversion_number_signed_to_string(WEXITSTATUS(return_code), f_conversion_data_base_10_s, &number);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_conversion_number_signed_to_string", F_true);

        f_string_dynamic_resize(0, &number);

        return status;
      }

      status = f_string_dynamic_append(number, &data_make->setting_make.parameter.array[0].value.array[0]);

      f_string_dynamic_resize(0, &number);
    }
    else {
      status = f_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data_make->error, F_status_set_fine(status), "f_string_append", F_true);

      return status;
    }

    status = f_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);

    if (F_status_is_error(status)) {
      fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

      return status;
    }

    if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
      flockfile(data_make->error.to.stream);

      fl_print_format("%c%[%SFailed with return code %]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
      fl_print_format("%[%i%]", data_make->error.to.stream, data_make->error.notable, return_code, data_make->error.notable);
      fl_print_format("%[.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

      funlockfile(data_make->error.to.stream);
    }

    if (data_make->setting_make.fail == fake_make_operation_fail_type_exit) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_return_

#ifndef _di_fake_make_operate_process_run_
  f_status_t fake_make_operate_process_run(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_statics_t arguments, const bool as_shell) {

    const f_string_static_t *program = &arguments.array[0];

    f_status_t status = F_none;
    f_string_dynamics_t args = f_string_dynamics_t_initialize;

    if (arguments.used > 1) {
      status = f_string_dynamics_resize(arguments.used - 1, &args);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamics_resize", F_true);
        return status;
      }

      for (f_array_length_t i = 0; i < args.size; ++i) {

        status = f_string_dynamic_append(arguments.array[i + 1], &args.array[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

          f_string_dynamics_resize(0, &args);

          return status;
        }

        status = f_string_dynamic_terminate(&args.array[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_terminate", F_true);

          f_string_dynamics_resize(0, &args);

          return status;
        }

        ++args.used;
      } // for
    }

    status = fake_make_operate_process_execute(main, data_make, *program, args, as_shell);

    f_string_dynamics_resize(0, &args);

    return status;
  }
#endif // _di_fake_make_operate_process_run_

#ifndef _di_fake_make_operate_validate_
  void fake_make_operate_validate(fake_main_t * const main, fake_make_data_t * const data_make, const f_string_range_t section_name, const f_array_length_t operation, const f_string_dynamics_t arguments, uint8_t *operation_if, f_array_lengths_t *section_stack, f_status_t *status) {

    if (F_status_is_error(*status)) return;

    if (operation == fake_make_operation_type_index || operation == fake_make_operation_type_run || operation == fake_make_operation_type_shell) {
      if (!arguments.used) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (operation == fake_make_operation_type_index) {
        if (!data_make->setting_build.build_indexer.used) {
          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SNo indexer has been specified, cannot perform '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_index_s, data_make->error.notable);
            fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_break) {
      if (arguments.used > 1) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to_not) {

            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported break type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_build) {
      if (arguments.used > 1) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (arguments.array[0].used) {
          char path_file[main->path_data_build.used + arguments.array[0].used + 1];

          memcpy(path_file, main->path_data_build.string, main->path_data_build.used);
          memcpy(path_file + main->path_data_build.used, arguments.array[0].string, arguments.array[0].used);

          path_file[main->path_data_build.used + arguments.array[0].used] = 0;

          f_status_t status_file = f_file_is(path_file, F_file_type_regular_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%S%]", data_make->error.to.stream, data_make->error.notable, path_file, data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_is", F_true, path_file, "find", fll_error_file_type_file);
            *status = status_file;
          }
          else if (!status_file) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, path_file, data_make->error.notable);
              fl_print_format("%[' must be a regular file.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
        else {
          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            fll_print_format("%c%[%SFilename argument must not be an empty string.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_clean || operation == fake_make_operation_type_pop || operation == fake_make_operation_type_top || operation == fake_make_operation_type_skeleton) {
      if (arguments.used) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (operation == fake_make_operation_type_pop) {
        if (data_make->path.stack.used == 1) {

          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            fll_print_format("%c%[%SMust not attempt to pop project root off of path stack.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }

          *status = F_status_set_error(F_failure);
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_clone) {
      if (arguments.used > 1) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for

        for (f_array_length_t i = 0; i < arguments.used - 1; ++i) {

          if (f_file_exists(arguments.array[i].string) != F_true) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        if (arguments.used > 2) {

          // the last file must be a directory.
          f_status_t status_file = f_directory_is(arguments.array[arguments.used - 1].string);

          if (status_file == F_false || status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[arguments.used - 1].string, "find", fll_error_file_type_directory);
            *status = F_status_set_error(F_failure);
          }
        }
        else {

          // when the first file is a directory, then the second, if it exists, must also be a directory.
          f_status_t status_file = f_directory_is(arguments.array[0].string);

          if (status_file == F_true) {
            status_file = f_directory_is(arguments.array[1].string);

            if (status_file == F_false) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[1], data_make->error.notable);
                fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_compile) {
      if (!arguments.used) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (data_make->setting_build.build_compiler.used) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SNo compiler has been specified, cannot perform '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_compile_s, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_copy) {
      if (arguments.used > 1) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for

        for (f_array_length_t i = 0; i < arguments.used - 1; ++i) {

          if (f_file_exists(arguments.array[i].string) != F_true) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        if (arguments.used > 2) {

          // the last file must be a directory.
          f_status_t status_file = f_directory_is(arguments.array[arguments.used - 1].string);

          if (status_file == F_false || status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[arguments.used - 1].string, "identify", fll_error_file_type_directory);
            *status = F_status_set_error(F_failure);
          }
        }
        else {

          // when the first file is a directory, then the second, if it exists, must also be a directory.
          f_status_t status_file = f_directory_is(arguments.array[0].string);

          if (status_file == F_true) {
            status_file = f_directory_is(arguments.array[1].string);

            if (status_file == F_false) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[1], data_make->error.notable);
                fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_define) {
      if (arguments.used) {
        *status = fake_make_operate_validate_define_name(arguments.array[0]);

        if (*status == F_none) {
          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            fll_print_format("%c%[%SDefine name must not be an empty string.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }

          *status = F_status_set_error(F_failure);
        }
        else if (*status == F_false) {
          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SInvalid characters in the define setting name '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
            fl_print_format("%[', only alpha-numeric ASCII characters and underscore (without a leading digit) is allowed.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_delete || operation == fake_make_operation_type_deletes) {
      if (arguments.used) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_else) {
      if (*operation_if == fake_make_operation_if_type_else_true || *operation_if == fake_make_operation_if_type_else_false) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SMust not be used after another '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[else%]", data_make->error.to.stream, data_make->error.notable, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (*operation_if == fake_make_operation_if_type_true || *operation_if == fake_make_operation_if_type_false || *operation_if == fake_make_operation_if_type_false_always) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SMust not be used inside an '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[if%]", data_make->error.to.stream, data_make->error.notable, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (*operation_if != fake_make_operation_if_type_else_true_next && *operation_if != fake_make_operation_if_type_else_false_next && *operation_if != fake_make_operation_if_type_else_false_next_always) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas no preceding if condition.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (arguments.used) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;
      }

      return;
    }

    if (operation == fake_make_operation_type_exit) {
      if (arguments.used > 1) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported exit type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
      }

      return;
    }

    if (operation == fake_make_operation_type_fail) {
      if (arguments.used) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_exit_s, arguments.array[0], fake_make_operation_argument_exit_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_warn_s, arguments.array[0], fake_make_operation_argument_warn_s_length) == F_equal_to_not) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_ignore_s, arguments.array[0], fake_make_operation_argument_ignore_s_length) == F_equal_to_not) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SUnsupported fail type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
                fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_group || operation == fake_make_operation_type_groups || operation == fake_make_operation_type_mode || operation == fake_make_operation_type_modes || operation == fake_make_operation_type_owner || operation == fake_make_operation_type_owners) {
      if (arguments.used > 1) {
        f_status_t status_file = F_none;

        for (f_array_length_t i = 1; i < arguments.used; ++i) {

          status_file = f_file_is(arguments.array[i].string, F_file_type_regular_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_is", F_true, arguments.array[i].string, "find", fll_error_file_type_directory);
            }

            *status = status_file;
          }
        }

        return;
      }

      if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
        fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
      }

      *status = F_status_set_error(F_failure);

      return;
    }

    if (operation == fake_make_operation_type_if) {
      if (*operation_if == fake_make_operation_if_type_true || *operation_if == fake_make_operation_if_type_false || *operation_if == fake_make_operation_if_type_false_always) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SMust not be used after another '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[if%]", data_make->error.to.stream, data_make->error.notable, data_make->error.notable);
          fl_print_format("%[' section operation.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }

        *status = F_status_set_error(F_failure);
        *operation_if = 0;

        return;
      }

      if (arguments.used) {
        const f_string_t if_type_strings[] = {
          fake_make_operation_argument_if_defined_s,
          fake_make_operation_argument_if_equal_s,
          fake_make_operation_argument_if_equal_not_s,
          fake_make_operation_argument_if_exists_s,
          fake_make_operation_argument_if_failure_s,
          fake_make_operation_argument_if_greater_s,
          fake_make_operation_argument_if_greater_equal_s,
          fake_make_operation_argument_if_group_s,
          fake_make_operation_argument_if_is_s,
          fake_make_operation_argument_if_less_s,
          fake_make_operation_argument_if_less_equal_s,
          fake_make_operation_argument_if_mode_s,
          fake_make_operation_argument_if_not_s,
          fake_make_operation_argument_if_defined_s, // if not defined, represented by just "defined".
          fake_make_operation_argument_if_exists_s,  // if not exists, represented by just "exists".
          fake_make_operation_argument_if_group_s,   // if not group, represented by just "group".
          fake_make_operation_argument_if_is_s,      // if not is, represented by just "is".
          fake_make_operation_argument_if_mode_s,    // if not mode, represented by just "mode".
          fake_make_operation_argument_if_owner_s,   // if not owner, represented by just "owner".
          fake_make_operation_argument_if_owner_s,
          fake_make_operation_argument_if_success_s,
        };

        const f_array_length_t if_type_lengths[] = {
          fake_make_operation_argument_if_defined_s_length,
          fake_make_operation_argument_if_equal_s_length,
          fake_make_operation_argument_if_equal_not_s_length,
          fake_make_operation_argument_if_exists_s_length,
          fake_make_operation_argument_if_failure_s_length,
          fake_make_operation_argument_if_greater_s_length,
          fake_make_operation_argument_if_greater_equal_s_length,
          fake_make_operation_argument_if_group_s_length,
          fake_make_operation_argument_if_is_s_length,
          fake_make_operation_argument_if_less_s_length,
          fake_make_operation_argument_if_less_equal_s_length,
          fake_make_operation_argument_if_mode_s_length,
          fake_make_operation_argument_if_not_s_length,
          fake_make_operation_argument_if_defined_s_length, // if not defined, represented by just "defined".
          fake_make_operation_argument_if_exists_s_length,  // if not exists, represented by just "exists".
          fake_make_operation_argument_if_group_s_length,   // if not group, represented by just "group".
          fake_make_operation_argument_if_is_s_length,      // if not is, represented by just "is".
          fake_make_operation_argument_if_mode_s_length,    // if not mode, represented by just "mode".
          fake_make_operation_argument_if_owner_s_length,   // if not owner, represented by just "owner".
          fake_make_operation_argument_if_owner_s_length,
          fake_make_operation_argument_if_success_s_length,
        };

        const uint8_t if_type_codes[] = {
          fake_make_operation_if_type_if_defined,
          fake_make_operation_if_type_if_equal,
          fake_make_operation_if_type_if_equal_not,
          fake_make_operation_if_type_if_exists,
          fake_make_operation_if_type_if_failure,
          fake_make_operation_if_type_if_greater,
          fake_make_operation_if_type_if_greater_equal,
          fake_make_operation_if_type_if_group,
          fake_make_operation_if_type_if_is,
          fake_make_operation_if_type_if_less,
          fake_make_operation_if_type_if_less_equal,
          fake_make_operation_if_type_if_mode,
          fake_make_operation_if_type_if_not,
          fake_make_operation_if_type_if_not_defined,
          fake_make_operation_if_type_if_not_exists,
          fake_make_operation_if_type_if_not_group,
          fake_make_operation_if_type_if_not_is,
          fake_make_operation_if_type_if_not_mode,
          fake_make_operation_if_type_if_not_owner,
          fake_make_operation_if_type_if_owner,
          fake_make_operation_if_type_if_success,
        };

        const uint8_t if_type_minimum[] = {
          3, // If defined.
          2, // If equal (==).
          2, // If equal not (<>).
          2, // If exists.
          1, // If failure.
          2, // If greater (>).
          2, // If greater equal (>=).
          3, // If group.
          3, // If is.
          2, // If less (<).
          2, // If less equal (<=).
          4, // If mode.
          3, // If not.
          5, // If not defined.
          3, // If not exists.
          4, // If not group.
          4, // If not is.
          5, // If not mode.
          4, // If not owner.
          3, // If owner.
          1, // If success.
        };

        const f_string_t if_not_type_strings[] = {
          fake_make_operation_argument_if_defined_s,
          fake_make_operation_argument_if_exists_s,
          fake_make_operation_argument_if_group_s,
          fake_make_operation_argument_if_is_s,
          fake_make_operation_argument_if_mode_s,
          fake_make_operation_argument_if_owner_s,
        };

        const f_array_length_t if_not_type_lengths[] = {
          fake_make_operation_argument_if_defined_s_length,
          fake_make_operation_argument_if_exists_s_length,
          fake_make_operation_argument_if_group_s_length,
          fake_make_operation_argument_if_is_s_length,
          fake_make_operation_argument_if_mode_s_length,
          fake_make_operation_argument_if_owner_s_length,
        };

        const uint8_t if_not_type_codes[] = {
          fake_make_operation_if_type_if_not_defined,
          fake_make_operation_if_type_if_not_exists,
          fake_make_operation_if_type_if_not_group,
          fake_make_operation_if_type_if_not_is,
          fake_make_operation_if_type_if_not_mode,
          fake_make_operation_if_type_if_not_owner,
        };

        const uint8_t if_not_type_minimum[] = {
          4, // If not defined.
          3, // If not exists.
          4, // If not group.
          4, // If not is.
          5, // If not mode.
          4, // If not owner.
        };

        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < 21; ++i) {

          // Skip the "if not XXX" types as they are determined later on.
          if (i > 12 && i < 19) continue;

          if (fl_string_dynamic_compare_string(if_type_strings[i], arguments.array[0], if_type_lengths[i]) == F_equal_to) {
            *operation_if = if_type_codes[i];

            break;
          }
        } // for

        if (i == 21) {
          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            flockfile(data_make->error.to.stream);

            fl_print_format("%c%[%SUnsupported if type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
            fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
            fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

            funlockfile(data_make->error.to.stream);
          }

          *status = F_status_set_error(F_failure);
          *operation_if = fake_make_operation_if_type_false_always_next;

          return;
        }

        // Identify and convert to the appropriate if not condition.
        if (*operation_if == fake_make_operation_if_type_if_not) {
          if (arguments.used < 2) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
            }

            *status = F_status_set_error(F_failure);
            *operation_if = fake_make_operation_if_type_false_always_next;

            return;
          }

          for (; j < 6; ++j) {

            if (fl_string_dynamic_compare_string(if_not_type_strings[j], arguments.array[1], if_not_type_lengths[j]) == F_equal_to) {
              *operation_if = if_not_type_codes[j];

              break;
            }
          } // for

          if (j == 6) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported if not type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
            *operation_if = fake_make_operation_if_type_false_always_next;

            return;
          }
        }
        else {
          j = 6;
        }

        if (j == 6 && arguments.used >= if_type_minimum[i] || arguments.used >= if_not_type_minimum[j]) {
          if (*operation_if == fake_make_operation_if_type_if_success || *operation_if == fake_make_operation_if_type_if_failure) {
            if (arguments.used > if_type_minimum[i]) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
              }

              *status = F_status_set_error(F_failure);
              *operation_if = fake_make_operation_if_type_false_always_next;
            }

            return;
          }

          if (*operation_if == fake_make_operation_if_type_if_defined || *operation_if == fake_make_operation_if_type_if_not_defined) {
            if (fl_string_dynamic_compare_string(fake_make_operation_argument_environment_s, j == 6 ? arguments.array[1] : arguments.array[2], fake_make_operation_argument_environment_s_length) == F_equal_to_not) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_parameter_s, j == 6 ? arguments.array[1] : arguments.array[2], fake_make_operation_argument_parameter_s_length) == F_equal_to_not) {
                if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                  flockfile(data_make->error.to.stream);

                  fl_print_format("%c%[%SUnsupported define type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                  fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, j == 6 ? arguments.array[1] : arguments.array[2], data_make->error.notable);
                  fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                  funlockfile(data_make->error.to.stream);
                }

                *status = F_status_set_error(F_failure);
                *operation_if = fake_make_operation_if_type_false_always_next;
              }
            }

            return;
          }
          else if (*operation_if == fake_make_operation_if_type_if_equal || *operation_if == fake_make_operation_if_type_if_equal_not) {
            if (arguments.used < 3) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
              }

              *status = F_status_set_error(F_failure);
              *operation_if = fake_make_operation_if_type_false_always_next;
            }

            return;
          }
          else if (*operation_if == fake_make_operation_if_type_if_exists || *operation_if == fake_make_operation_if_type_if_not_exists) {
            return;
          }
          else if (*operation_if == fake_make_operation_if_type_if_group || *operation_if == fake_make_operation_if_type_if_is || *operation_if == fake_make_operation_if_type_if_mode || *operation_if > fake_make_operation_if_type_if_not_exists && *operation_if < fake_make_operation_if_type_if_success) {

            if (*operation_if == fake_make_operation_if_type_if_mode || *operation_if == fake_make_operation_if_type_if_not_mode) {
              if (fl_string_dynamic_compare_string(fake_make_operation_argument_is_s, j == 6 ? arguments.array[1] : arguments.array[2], fake_make_operation_argument_is_s_length) == F_equal_to_not) {
                if (fl_string_dynamic_compare_string(fake_make_operation_argument_has_s, j == 6 ? arguments.array[1] : arguments.array[2], fake_make_operation_argument_has_s_length) == F_equal_to_not) {
                  if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                    flockfile(data_make->error.to.stream);

                    fl_print_format("%c%[%SUnsupported %smode type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, j == 6 ? "" : "not ", data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, j == 6 ? arguments.array[1] : arguments.array[2], data_make->error.notable);
                    fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                    funlockfile(data_make->error.to.stream);
                  }

                  *status = F_status_set_error(F_failure);
                  *operation_if = fake_make_operation_if_type_false_always_next;

                  return;
                }
              }

              f_file_mode_t mode_rule = 0;
              uint8_t replace = 0;

              *status = fake_make_get_id_mode(main, data_make->error, j == 6 ? arguments.array[2] : arguments.array[3], &mode_rule, &replace);

              if (F_status_is_error(*status)) {
                *operation_if = fake_make_operation_if_type_false_always_next;

                return;
              }

              i = j == 6 ? 3 : 4;
            }
            else if (*operation_if == fake_make_operation_if_type_if_group || *operation_if == fake_make_operation_if_type_if_not_group) {
              gid_t id = 0;

              *status = fake_make_get_id_group(main, data_make->error, j == 6 ? arguments.array[1] : arguments.array[2], &id);

              if (F_status_is_error(*status)) {
                *operation_if = fake_make_operation_if_type_false_always_next;

                return;
              }

              i = j == 6 ? 2 : 3;
            }
            else if (*operation_if == fake_make_operation_if_type_if_is || *operation_if == fake_make_operation_if_type_if_not_is) {

              // block     = 0x1 (0000 0001) link    = 0x10 (0001 0000)
              // character = 0x2 (0000 0010) regular = 0x20 (0010 0000)
              // directory = 0x4 (0000 0100) socket  = 0x40 (0100 0000)
              // fifo      = 0x8 (0000 1000) invalid = 0x80 (1000 0000)
              uint8_t type_file = 0;

              for (i = j == 6 ? 1 : 2; i < arguments.used; ++i) {

                if (fl_string_dynamic_compare_string(fake_make_operation_argument_if_is_for_s, arguments.array[i], fake_make_operation_argument_if_is_for_s_length) == F_equal_to) {
                  ++i;

                  break;
                }

                if (fl_string_dynamic_compare_string(F_file_type_name_block_s, arguments.array[i], F_file_type_name_block_s_length) == F_equal_to) {
                  type_file |= 0x1;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_character_s, arguments.array[i], F_file_type_name_character_s_length) == F_equal_to) {
                  type_file |= 0x2;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_directory_s, arguments.array[i], F_file_type_name_directory_s_length) == F_equal_to) {
                  type_file |= 0x4;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_fifo_s, arguments.array[i], F_file_type_name_fifo_s_length) == F_equal_to) {
                  type_file |= 0x8;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_link_s, arguments.array[i], F_file_type_name_link_s_length) == F_equal_to) {
                  type_file |= 0x10;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_regular_s, arguments.array[i], F_file_type_name_regular_s_length) == F_equal_to) {
                  type_file |= 0x20;
                }
                else if (fl_string_dynamic_compare_string(F_file_type_name_socket_s, arguments.array[i], F_file_type_name_socket_s_length) == F_equal_to) {
                  type_file |= 0x40;
                }
                else {
                  if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                    flockfile(data_make->error.to.stream);

                    fl_print_format("%c%[%SUnsupported file type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
                    fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                    funlockfile(data_make->error.to.stream);
                  }

                  type_file |= 0x80;
                }
              } // for

              if (type_file & 0x80) {
                *status = F_status_set_error(F_failure);
                *operation_if = fake_make_operation_if_type_false_always_next;

                return;
              }
            }
            else if (*operation_if == fake_make_operation_if_type_if_owner || *operation_if == fake_make_operation_if_type_if_not_owner) {
              uid_t id = 0;

              *status = fake_make_get_id_owner(main, data_make->error, j == 6 ? arguments.array[1] : arguments.array[2], &id);

              if (F_status_is_error(*status)) {
                *operation_if = fake_make_operation_if_type_false_always_next;

                return;
              }

              i = j == 6 ? 2 : 3;
            }

            if (i < arguments.used) {
              for (f_status_t status_file = F_none; i < arguments.used; ++i) {

                status_file = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

                if (F_status_is_error(status_file)) {
                  fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(status_file), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

                  *operation_if = fake_make_operation_if_type_false_always_next;

                  if (F_status_is_error_not(*status)) {
                    if (F_status_set_fine(status_file) == F_false) {
                      *status = F_status_set_error(F_failure);
                      *operation_if = fake_make_operation_if_type_false_always_next;
                    }
                    else {
                      *status = status_file;
                    }
                  }
                }
                else if (*operation_if != fake_make_operation_if_type_if_exists && *operation_if != fake_make_operation_if_type_if_is) {

                  // The existence tests do not need to happen here for *_if_exists and *_if_is as those two types will handle performing them during the process stage.
                  status_file = f_file_exists(arguments.array[i].string);

                  if (status_file == F_false) {
                    status_file = F_status_set_error(F_file_found_not);
                  }

                  if (F_status_is_error(status_file)) {
                    fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_file_exists", F_true, arguments.array[i].string, "find", fll_error_file_type_file);

                    *operation_if = fake_make_operation_if_type_false_always_next;

                    if (F_status_is_error_not(*status)) {
                      *status = F_status_set_error(status_file);
                    }
                  }
                }
              } // for

              return;
            }
          }
          else if (*operation_if == fake_make_operation_if_type_if_greater || *operation_if == fake_make_operation_if_type_if_greater_equal || *operation_if == fake_make_operation_if_type_if_less || *operation_if == fake_make_operation_if_type_if_less_equal) {
            if (arguments.used < 3) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
              }

              *status = F_status_set_error(F_failure);
              *operation_if = fake_make_operation_if_type_false_always_next;

              return;
            }

            f_status_t status_number = F_none;
            f_string_range_t range = f_string_range_t_initialize;
            f_number_unsigned_t number = 0;
            bool is_negative = F_false;

            // @fixme there needs to handle converting numbers with decimals (like 1.01), perhaps operate on them as strings or provide a special processor.
            for (i = 1; i < arguments.used; ++i, status_number = F_none) {

              if (arguments.array[i].used) {
                range.start = 0;
                range.stop = arguments.array[i].used - 1;

                if (arguments.array[i].string[0] == '+') {
                  range.start = 1;
                }
                else if (arguments.array[i].string[0] == '-') {
                  range.start = 1;
                  is_negative = F_true;
                }

                if (range.start > range.stop) {
                  status_number = F_status_set_error(F_failure);
                }
                else {
                  status_number = fl_conversion_string_to_number_unsigned(arguments.array[i].string, range, &number);
                }
              }
              else {
                status_number = F_status_set_error(F_failure);
              }

              if (F_status_is_error(status_number)) {
                *status = F_status_set_error(F_failure);
                *operation_if = fake_make_operation_if_type_false_always_next;

                if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                  flockfile(data_make->error.to.stream);

                  if (number > F_number_t_size_unsigned_d) {
                    fl_print_format("%c%[%SThe number '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
                    fl_print_format("%[' may only be between the ranges -%un to %un.%]%c", data_make->error.to.stream, data_make->error.context, F_number_t_size_unsigned_d, F_number_t_size_unsigned_d, data_make->error.context, f_string_eol_s[0]);
                  }
                  else {
                    fl_print_format("%c%[%SInvalid or unsupported number provided '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                    fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
                    fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);
                  }

                  funlockfile(data_make->error.to.stream);
                }
              }
            } // for

            return;
          }
        }
      }

      if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
        fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
      }

      *status = F_status_set_error(F_failure);
      *operation_if = fake_make_operation_if_type_false_always_next;

      return;
    }

    if (operation == fake_make_operation_type_link) {
      if (arguments.used > 2) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 2) {
        *status = fake_make_assure_inside_project(main, data_make, arguments.array[0]);

        if (F_status_is_error(*status)) {
          fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[0].string);

          if (F_status_set_fine(*status) == F_false) {
            *status = F_status_set_error(F_failure);
          }
        }

        *status = fake_make_assure_inside_project(main, data_make, arguments.array[1]);

        if (F_status_is_error(*status)) {
          fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[1].string);

          if (F_status_set_fine(*status) == F_false) {
            *status = F_status_set_error(F_failure);
          }
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_move) {
      if (arguments.used > 1) {
        for (f_array_length_t i = 0; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for

        for (f_array_length_t i = 0; i < arguments.used - 1; ++i) {

          if (f_file_exists(arguments.array[i].string) != F_true) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[i], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        } // for

        if (arguments.used > 2) {

          // the last file must be a directory.
          f_status_t status_file = f_directory_is(arguments.array[arguments.used - 1].string);

          if (status_file == F_false || status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
              fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
          else if (F_status_is_error(status_file)) {
            fll_error_file_print(data_make->error, F_status_set_fine(status_file), "f_directory_is", F_true, arguments.array[arguments.used - 1].string, "identify", fll_error_file_type_directory);
            *status = F_status_set_error(F_failure);
          }
        }
        else {

          // when the first file is a directory, then the second, if it exists, must also be a directory.
          f_status_t status_file = f_directory_is(arguments.array[0].string);

          if (status_file == F_true) {
            status_file = f_directory_is(arguments.array[1].string);

            if (status_file == F_false) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe last file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[arguments.used - 1], data_make->error.notable);
                fl_print_format("%[' must be a valid directory.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
            }
          }
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_operate) {
      if (arguments.used > 1) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used == 1) {
        f_array_length_t id_section = 0;

        for (; id_section < data_make->fakefile.used; ++id_section) {

          if (fl_string_dynamic_partial_compare_string(arguments.array[0].string, data_make->buffer, arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
            break;
          }
        } // for

        if (id_section == data_make->fakefile.used) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SNo operation section named '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
          fl_print_format("%[' was found.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

          funlockfile(data_make->error.to.stream);
        }
        else {
          for (f_array_length_t i = 0; i < section_stack->used; ++i) {

            if (section_stack->array[i] == id_section) {
              if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
                flockfile(data_make->error.to.stream);

                fl_print_format("%c%[%SThe section operation '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
                fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, data_make->fakefile.array[id_section].name, data_make->error.notable);
                fl_print_format("%[' is already in the operation stack, recursion is not allowed.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

                funlockfile(data_make->error.to.stream);
              }

              *status = F_status_set_error(F_failure);
              break;
            }
          } // for
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_parameter) {
      if (arguments.used) {
        const f_string_t reserved_name[] = {
          fake_make_parameter_variable_build_s,
          fake_make_parameter_variable_color_s,
          fake_make_parameter_variable_data_s,
          fake_make_parameter_variable_define_s,
          fake_make_parameter_variable_fakefile_s,
          fake_make_parameter_variable_mode_s,
          fake_make_parameter_variable_process_s,
          fake_make_parameter_variable_settings_s,
          fake_make_parameter_variable_sources_s,
          fake_make_parameter_variable_verbosity_s,
          fake_make_parameter_variable_work_s,
          fake_make_parameter_variable_option_build_s,
          fake_make_parameter_variable_option_color_s,
          fake_make_parameter_variable_option_data_s,
          fake_make_parameter_variable_option_define_s,
          fake_make_parameter_variable_option_fakefile_s,
          fake_make_parameter_variable_option_mode_s,
          fake_make_parameter_variable_option_process_s,
          fake_make_parameter_variable_option_settings_s,
          fake_make_parameter_variable_option_sources_s,
          fake_make_parameter_variable_option_verbosity_s,
          fake_make_parameter_variable_option_work_s,
          fake_make_parameter_variable_value_build_s,
          fake_make_parameter_variable_value_color_s,
          fake_make_parameter_variable_value_data_s,
          fake_make_parameter_variable_value_define_s,
          fake_make_parameter_variable_value_fakefile_s,
          fake_make_parameter_variable_value_mode_s,
          fake_make_parameter_variable_value_process_s,
          fake_make_parameter_variable_value_settings_s,
          fake_make_parameter_variable_value_sources_s,
          fake_make_parameter_variable_value_verbosity_s,
          fake_make_parameter_variable_value_work_s,
        };

        const f_array_length_t reserved_length[] = {
          fake_make_parameter_variable_build_s_length,
          fake_make_parameter_variable_color_s_length,
          fake_make_parameter_variable_data_s_length,
          fake_make_parameter_variable_define_s_length,
          fake_make_parameter_variable_fakefile_s_length,
          fake_make_parameter_variable_mode_s_length,
          fake_make_parameter_variable_process_s_length,
          fake_make_parameter_variable_settings_s_length,
          fake_make_parameter_variable_sources_s_length,
          fake_make_parameter_variable_verbosity_s_length,
          fake_make_parameter_variable_work_s_length,
          fake_make_parameter_variable_build_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_color_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_data_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_define_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_fakefile_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_mode_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_process_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_settings_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_sources_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_verbosity_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_work_s_length + fake_make_parameter_iki_option_s_length,
          fake_make_parameter_variable_build_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_color_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_data_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_define_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_fakefile_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_mode_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_process_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_settings_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_sources_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_verbosity_s_length + fake_make_parameter_iki_value_s_length,
          fake_make_parameter_variable_work_s_length + fake_make_parameter_iki_value_s_length,
        };

        for (f_array_length_t i = 0; i < 33; ++i) {

          if (fl_string_dynamic_compare_string(reserved_name[i], arguments.array[0], reserved_length[i]) == F_equal_to) {
            fll_print_format("%c%[%SCannot assign a value to the parameter name '%s' because it is a reserved parameter name.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);

            *status = F_status_set_error(F_failure);

            return;
          }
        } // for
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_to) {
      if (arguments.used > 1) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SHas too many arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }
      else if (arguments.used) {
        if (arguments.array[0].used) {
          f_status_t status_file = f_file_is(arguments.array[0].string, F_file_type_directory_d, F_false);

          if (status_file == F_file_found_not) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SFailed to find file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(status_file);
          }
          else if (F_status_is_error(status_file)) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_is", F_true, main->file_data_build_fakefile.string, "find", fll_error_file_type_file);
            }

            *status = status_file;
          }
          else if (!status_file) {
            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SThe file '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%[' must be a directory file.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }
        else {
          if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
            fll_print_format("%c%[%SFilename argument must not be an empty string.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
          }
        }
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    if (operation == fake_make_operation_type_touch) {
      if (arguments.used > 1) {
        if (fl_string_dynamic_compare_string(fake_make_operation_argument_file_s, arguments.array[0], fake_make_operation_argument_file_s_length) == F_equal_to_not) {
          if (fl_string_dynamic_compare_string(fake_make_operation_argument_directory_s, arguments.array[0], fake_make_operation_argument_directory_s_length) == F_equal_to_not) {

            if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
              flockfile(data_make->error.to.stream);

              fl_print_format("%c%[%SUnsupported file type '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
              fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, arguments.array[0], data_make->error.notable);
              fl_print_format("%['.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

              funlockfile(data_make->error.to.stream);
            }

            *status = F_status_set_error(F_failure);
          }
        }

        for (f_array_length_t i = 1; i < arguments.used; ++i) {

          *status = fake_make_assure_inside_project(main, data_make, arguments.array[i]);

          if (F_status_is_error(*status)) {
            fake_print_message_section_operation_path_outside(main, data_make->error, F_status_set_fine(*status), "fake_make_assure_inside_project", data_make->path_cache.used ? data_make->path_cache.string : arguments.array[i].string);

            if (F_status_set_fine(*status) == F_false) {
              *status = F_status_set_error(F_failure);
            }
          }
        } // for
      }
      else {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          fll_print_format("%c%[%SRequires more arguments.%]%c", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context, f_string_eol_s[0]);
        }

        *status = F_status_set_error(F_failure);
      }

      return;
    }

    // Note: there is nothing to validate for fake_make_operation_type_print.
  }
#endif // _di_fake_make_operate_validate_

#ifndef _di_fake_make_operate_validate_define_name_
  f_status_t fake_make_operate_validate_define_name(const f_string_static_t name) {

    if (!name.used) return F_none;

    if (!(isalpha(name.string[0]) || name.string[0] == '_')) {
      return F_false;
    }

    for (f_array_length_t i = 0; i < name.used; ++i) {

      if (!(isalnum(name.string[i]) || name.string[i] == '_')) {
        return F_false;
      }
    } // for

    return F_true;
  }
#endif // _di_fake_make_operate_validate_define_name_

#ifdef __cplusplus
} // extern "C"
#endif
