#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-load_parameters.h"
#include "private-make-load_fakefile.h"
#include "private-make-operate.h"
#include "private-make-operate_process.h"
#include "private-make-operate_process_type.h"
#include "private-make-operate_validate.h"
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

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%c%[Making project.%]%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, main->context.set.important, f_string_eol_s[0]);
    }

    f_status_t status = F_none;
    f_mode_t mode = f_mode_t_initialize;

    f_array_lengths_t section_stack = f_array_lengths_t_initialize;
    fake_make_data_t data_make = fake_make_data_t_initialize;

    data_make.main = main;

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

    fake_make_load_parameters(&data_make, &status);

    fake_make_load_fakefile(&data_make, &status);

    if (F_status_is_error(status)) {
      macro_fake_make_data_t_delete_simple(data_make)

      return status;
    }

    if (data_make.setting_make.fail == fake_make_operation_fail_type_exit_e) {
      data_make.error.prefix = fl_print_error_s;
      data_make.error.suffix = 0;
      data_make.error.context = main->context.set.error;
      data_make.error.notable = main->context.set.notable;
      data_make.error.to.stream = F_type_error_d;
      data_make.error.to.id = F_type_descriptor_error_d;
      data_make.error.set = &main->context.set;
    }
    else if (data_make.setting_make.fail == fake_make_operation_fail_type_warn_e) {
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
      const int result = fake_make_operate_section(&data_make, data_make.id_main, &section_stack, &status);

      if (status == F_child) {
        main->child = result;
      }
    }

    if (status != F_child) {
      f_status_t status_path = f_path_change_at(data_make.path.top.id);

      if (F_status_is_error(status_path) && main->warning.verbosity == f_console_verbosity_verbose_e) {
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
  void fake_make_operate_expand(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_array_length_t operation, const f_fss_content_t content, const f_fss_quotes_t quotes, f_string_dynamics_t *arguments, f_status_t *status) {

    if (F_status_is_error(*status)) return;
    if (!content.used) return;

    // Pre-allocate the known arguments size.
    *status = f_string_dynamics_increase_by(content.used, arguments);

    if (F_status_is_error(*status) || *status == F_string_too_large) {
      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase_by", F_true);

      return;
    }

    const f_string_static_t vocabulary_context = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_context_s, F_iki_vocabulary_0002_context_s_length);
    const f_string_static_t vocabulary_define = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_define_s, F_iki_vocabulary_0002_define_s_length);
    const f_string_static_t vocabulary_parameter = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_parameter_s, F_iki_vocabulary_0002_parameter_s_length);

    const f_string_range_t range_context = macro_f_string_range_t_initialize(F_iki_vocabulary_0002_context_s_length);
    const f_string_range_t range_define = macro_f_string_range_t_initialize(F_iki_vocabulary_0002_define_s_length);
    const f_string_range_t range_parameter = macro_f_string_range_t_initialize(F_iki_vocabulary_0002_parameter_s_length);

    f_iki_variable_t iki_variable = f_iki_variable_t_initialize;
    f_iki_vocabulary_t iki_vocabulary = f_iki_vocabulary_t_initialize;
    f_iki_content_t iki_content = f_iki_content_t_initialize;
    f_iki_delimits_t iki_delimits = f_iki_delimits_t_initialize;

    f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, &fake_signal_state_interrupt_iki, 0, (void *) data_make->main, 0);

    f_string_range_t range = f_string_range_t_initialize;
    f_string_map_multis_t *parameter = &data_make->setting_make.parameter;

    // 1 = is parameter, 2 = is defined, 3 = is context.
    uint8_t is = 0;

    bool unmatched = F_true;

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

          is = 0;

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
            is = 2;
          }
          else if (*status == F_equal_to_not) {
            *status = fl_string_dynamic_partial_compare(vocabulary_parameter, data_make->buffer, range_parameter, iki_vocabulary.array[j]);

            if (*status == F_equal_to) {
              is = 1;
            }
            else if (*status == F_equal_to_not) {
              *status = fl_string_dynamic_partial_compare(vocabulary_context, data_make->buffer, range_context, iki_vocabulary.array[j]);

              if (*status == F_equal_to) {
                is = 3;
              }
            }
          }

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "fl_string_dynamic_partial_compare", F_true);

            break;
          }

          if (is == 1) {
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
              *status = fake_make_operate_expand_build(data_make, quotes.array[i], iki_content.array[j], arguments);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_build", F_true);

                break;
              }
            }
          }
          else if (is == 2) {
            if (data_make->setting_make.load_build) {
              *status = fake_make_operate_expand_environment(data_make, quotes.array[i], iki_content.array[j], arguments);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_environment", F_true);

                break;
              }
            }
          }
          else if (is == 3) {
            *status = fake_make_operate_expand_context(data_make, quotes.array[i], iki_content.array[j], arguments);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_context", F_true);

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
  f_status_t fake_make_operate_expand_build(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) {

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

    if (F_status_is_error(status)) return status;

    return F_true;
  }
#endif // _di_fake_make_operate_expand_build_

#ifndef _di_fake_make_operate_expand_context_
  f_status_t fake_make_operate_expand_context(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) {

    f_status_t status = F_none;
    const f_string_static_t *context = 0;

    const f_string_t context_name[] = {
      fake_make_context_reset_s,
      fake_make_context_warning_s,
      fake_make_context_error_s,
      fake_make_context_title_s,
      fake_make_context_notable_s,
      fake_make_context_important_s,
      fake_make_context_standout_s,
      fake_make_context_success_s,
      fake_make_context_normal_s,
    };

    const f_array_length_t context_length[] = {
      fake_make_context_reset_s_length,
      fake_make_context_warning_s_length,
      fake_make_context_error_s_length,
      fake_make_context_title_s_length,
      fake_make_context_notable_s_length,
      fake_make_context_important_s_length,
      fake_make_context_standout_s_length,
      fake_make_context_success_s_length,
      fake_make_context_normal_s_length,
    };

    const f_color_set_t context_value[] = {
      data_make->main->context.set.reset,
      data_make->main->context.set.warning,
      data_make->main->context.set.error,
      data_make->main->context.set.title,
      data_make->main->context.set.notable,
      data_make->main->context.set.important,
      data_make->main->context.set.standout,
      data_make->main->context.set.success,
      data_make->main->context.set.normal,
    };

    for (f_array_length_t i = 0; i < 9; ++i) {

      if (fl_string_dynamic_partial_compare_string(context_name[i], data_make->buffer, context_length[i], range_name) == F_equal_to) {
        context = context_value[i].before;

        break;
      }
    } // for

    if (context) {
      if (quoted) {
        status = f_string_dynamic_append_nulless(*context, &arguments->array[arguments->used]);
      }
      else {
        status = f_string_dynamics_increase_by(F_memory_default_allocation_small_d, arguments);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_append_nulless(*context, &arguments->array[arguments->used]);

          if (F_status_is_error_not(status)) {
            status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);

            if (F_status_is_error_not(status)) {
              ++arguments->used;
            }
          }
        }
      }

      if (F_status_is_error(status)) return status;
    }

    return F_true;
  }
#endif // _di_fake_make_operate_expand_context_

#ifndef _di_fake_make_operate_expand_environment_
  f_status_t fake_make_operate_expand_environment(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name, f_string_dynamics_t *arguments) {

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

    if (F_status_is_error(status)) return status;

    return F_true;
  }
#endif // _di_fake_make_operate_expand_environment_

#ifndef _di_fake_make_operate_section_
  int fake_make_operate_section(fake_make_data_t * const data_make, const f_array_length_t id_section, f_array_lengths_t *section_stack, f_status_t *status) {

    if (F_status_is_error(*status) || *status == F_child) return data_make->main->child;

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

    if (data_make->main->output.verbosity != f_console_verbosity_quiet_e) {
      flockfile(data_make->main->output.to.stream);

      fl_print_format("%c%[Processing Section '%]", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.important, data_make->main->context.set.important);
      fl_print_format("%[%/Q%]", data_make->main->output.to.stream, data_make->main->context.set.notable, data_make->buffer, section->name, data_make->main->context.set.notable);
      fl_print_format("%['.%]%c", data_make->main->output.to.stream, data_make->main->context.set.important, data_make->main->context.set.important, f_string_eol_s[0]);

      funlockfile(data_make->main->output.to.stream);
    }

    if (!section->objects.used) {
      --section_stack->used;

      return 0;
    }

    const f_string_t operations_name[] = {
      fake_make_operation_and_s,
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
      fake_make_operation_or_s,
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
      fake_make_operation_and_s_length,
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
      fake_make_operation_or_s_length,
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
      fake_make_operation_type_and_e,
      fake_make_operation_type_break_e,
      fake_make_operation_type_build_e,
      fake_make_operation_type_clean_e,
      fake_make_operation_type_clone_e,
      fake_make_operation_type_compile_e,
      fake_make_operation_type_copy_e,
      fake_make_operation_type_define_e,
      fake_make_operation_type_delete_e,
      fake_make_operation_type_deletes_e,
      fake_make_operation_type_else_e,
      fake_make_operation_type_exit_e,
      fake_make_operation_type_fail_e,
      fake_make_operation_type_group_e,
      fake_make_operation_type_groups_e,
      fake_make_operation_type_if_e,
      fake_make_operation_type_index_e,
      fake_make_operation_type_link_e,
      fake_make_operation_type_mode_e,
      fake_make_operation_type_modes_e,
      fake_make_operation_type_move_e,
      fake_make_operation_type_operate_e,
      fake_make_operation_type_or_e,
      fake_make_operation_type_owner_e,
      fake_make_operation_type_owners_e,
      fake_make_operation_type_parameter_e,
      fake_make_operation_type_pop_e,
      fake_make_operation_type_print_e,
      fake_make_operation_type_run_e,
      fake_make_operation_type_shell_e,
      fake_make_operation_type_skeleton_e,
      fake_make_operation_type_to_e,
      fake_make_operation_type_top_e,
      fake_make_operation_type_touch_e,
    };

    fake_state_process_t state_process = fake_state_process_t_initialize;
    bool success = F_true;
    int result;

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (i = 0; i < section->objects.used; ++i, *status = F_none) {

      for (j = 0; j < arguments.size; ++j) {
        arguments.array[j].used = 0;
      } // for

      arguments.used = 0;
      state_process.condition = 0;
      state_process.condition_result = 0;
      state_process.operation_previous = state_process.operation;
      state_process.operation = 0;

      if (!(i % fake_signal_check_short_d) && fake_signal_received(data_make->main)) {
        *status = F_status_set_error(F_interrupt);

        break;
      }

      for (j = 0; j < fake_make_operation_total_d; ++j) {

        if (fl_string_dynamic_partial_compare_string(operations_name[j], data_make->buffer, operations_length[j], section->objects.array[i]) == F_equal_to) {
          state_process.operation = operations_type[j];

          break;
        }
      } // for

      if (!state_process.operation) {
        fake_print_message_section_operation_unknown(data_make->main, data_make->error, data_make->buffer, section->name, section->objects.array[i]);

        *status = F_status_set_error(F_valid_not);
      }
      else if (state_process.operation == fake_make_operation_type_operate_e) {
        if (section_stack->used == fake_make_section_stack_max_d) {
          fake_print_message_section_operation_stack_max(data_make->main, data_make->error, data_make->buffer, section->name, section->objects.array[i], fake_make_section_stack_max_d);

          *status = F_status_set_error(F_recurse);
        }
      }

      if (F_status_is_error_not(*status)) {
        fake_make_operate_expand(data_make, section->name, state_process.operation, section->contents.array[i], section->quotess.array[i], &arguments, status);
      }

      if (F_status_is_error_not(*status)) {
        fake_make_operate_validate(data_make, section->name, arguments, &state_process, section_stack, status);
      }

      // Block is set to the synthetic done type when an if-condition completes in order to inform any subsequent else condition.
      // If there is no follow-up else condition, then reset the block (there is no condition block at this point).
      if (state_process.block == fake_make_operation_if_type_done_e) {
        if (state_process.operation != fake_make_operation_type_else_e) {
          state_process.block = 0;
          state_process.block_result = 0;
        }
      }

      if (F_status_is_error(*status)) {
        if (state_process.block) {

          // Reset the block information for a completely processed block.
          if (state_process.block == fake_make_operation_if_type_done_e && state_process.operation != fake_make_operation_type_else_e) {
            state_process.block = 0;
            state_process.block_result = 0;
          }

          // Always set the condition result to done on error for unfinished blocks as there is no way to determine truth at this point.
          else {
            state_process.block_result = fake_condition_result_done_e;
          }
        }
      }
      else {
        if (!(state_process.operation == fake_make_operation_type_if_e || state_process.operation == fake_make_operation_type_else_e || state_process.operation == fake_make_operation_type_and_e || state_process.operation == fake_make_operation_type_or_e)) {

          // Only process a non-if-condition operation following an if condition, if the block result is true.
          if (state_process.block == fake_make_operation_if_type_if_e) {
            if (state_process.block_result != fake_condition_result_true_e) {
              state_process.block = fake_make_operation_if_type_done_e;

              success = F_true;

              continue;
            }
          }

          // Only process a non-if-condition operation following an else condition, if the block result is false.
          else if (state_process.block == fake_make_operation_if_type_else_e) {
            if (state_process.block_result != fake_condition_result_false_e) {
              state_process.block = 0;
              state_process.block_result = 0;

              success = F_true;

              continue;
            }
          }
        }

        result = fake_make_operate_process(data_make, section->name, arguments, success, &state_process, section_stack, status);

        if (*status == F_child) {
          f_string_dynamics_resize(0, &arguments);

          return result;
        }

        // When done processing an operation within a block, continue onto next block stage or exit the block.
        if (!(state_process.operation == fake_make_operation_type_if_e || state_process.operation == fake_make_operation_type_else_e || state_process.operation == fake_make_operation_type_and_e || state_process.operation == fake_make_operation_type_or_e)) {
          if (state_process.block == fake_make_operation_if_type_if_e) {
            state_process.block = fake_make_operation_if_type_done_e;
          }
          else if (state_process.block == fake_make_operation_if_type_else_e) {
            state_process.block = 0;
            state_process.block_result = 0;
          }
        }
      }

      if (F_status_set_fine(*status) == F_interrupt) break;

      if (F_status_is_error(*status)) {
        success = F_false;

        // Break acts identical to fail when at the top of the stack.
        if (F_status_set_fine(*status) == F_signal_abort && !section_stack->used) {
          data_make->setting_make.fail = fake_make_operation_fail_type_exit_e;
          data_make->error.prefix = fl_print_error_s;
          data_make->error.suffix = 0;
          data_make->error.context = data_make->main->context.set.error;
          data_make->error.notable = data_make->main->context.set.notable;
          data_make->error.to.stream = F_type_error_d;
          data_make->error.to.id = F_type_descriptor_error_d;
          data_make->error.set = &data_make->main->context.set;
        }

        fake_print_message_section_operation_failed(data_make->main, data_make->error, data_make->buffer, section->name, section->objects.array[i]);

        // F_signal_abort is used by the break section operation.
        if (F_status_set_fine(*status) == F_signal_abort) break;

        // F_signal_abort is used by the exit section operation.
        if (F_status_set_fine(*status) == F_signal_quit) {
          if (!section_stack->used) {
            *status = F_status_set_error(F_failure);
          }

          break;
        }

        if (data_make->setting_make.fail == fake_make_operation_fail_type_exit_e) {
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

        // F_signal_quit is used by the exit section operation.
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

    if (i == section->objects.used && F_status_is_error_not(*status) && state_process.condition) {
      if (data_make->main->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%c%[%SIncomplete '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);

        if (state_process.condition == fake_make_operation_type_if_e) {
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
        }
        else if (state_process.condition == fake_make_operation_type_and_e) {
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
        }
        else if (state_process.condition == fake_make_operation_type_or_e) {
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
        }
        else {
          fl_print_format("%[%s%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_else_s, data_make->error.notable);
        }

        fl_print_format("%[' at end of section.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

        funlockfile(data_make->error.to.stream);
      }

      fake_print_message_section_operation_failed(data_make->main, data_make->error, data_make->buffer, section->name, section->objects.array[section->objects.used - 1]);

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

#ifdef __cplusplus
} // extern "C"
#endif
