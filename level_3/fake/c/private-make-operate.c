#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-make-load_parameters.h"
#include "private-make-load_fakefile.h"
#include "private-make-operate.h"
#include "private-make-operate_block.h"
#include "private-make-operate_process.h"
#include "private-make-operate_validate.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_
  f_status_t fake_make_operate(fake_data_t * const data) {

    if (fll_program_standard_signal_received(data->main)) {
      fake_print_signal_received(data);

      return F_status_set_error(F_interrupt);
    }

    if (data->main->output.verbosity != f_console_verbosity_quiet_e && data->main->output.verbosity != f_console_verbosity_error_e) {
      flockfile(data->main->output.to.stream);

      fl_print_format("%r%[Now making using '%]", data->main->output.to.stream, f_string_eol_s, data->main->context.set.important, data->main->context.set.important);
      fl_print_format("%[%Q%]", data->main->output.to.stream, data->main->context.set.notable, data->fakefile, data->main->context.set.notable);
      fl_print_format("%['.%]%r", data->main->output.to.stream, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);

      funlockfile(data->main->output.to.stream);
    }

    f_status_t status = F_none;

    f_array_lengths_t section_stack = f_array_lengths_t_initialize;
    fake_make_data_t data_make = fake_make_data_t_initialize;

    data_make.data = data;
    data_make.main = data->main;

    status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make.path.stack);

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

      return status;
    }

    status = f_path_current(F_true, &data_make.path.stack.array[0]);

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "f_path_current", F_true);

      fake_make_data_delete(&data_make);

      return status;
    }

    status = f_directory_open(data_make.path.stack.array[0], F_false, &data_make.path.top.id);

    if (F_status_is_error(status)) {
      fll_error_print(data->main->error, F_status_set_fine(status), "f_directory_open", F_true);

      fake_make_data_delete(&data_make);

      return status;
    }

    data_make.path.stack.used = 1;

    fake_make_load_parameters(&data_make, &status);

    fake_make_load_fakefile(&data_make, &status);

    if (F_status_is_error(status)) {
      fake_make_data_delete(&data_make);

      return status;
    }

    if (data_make.setting_make.fail == fake_make_operation_fail_type_exit_e) {
      data_make.error.prefix = fl_print_error_s;
      data_make.error.suffix = f_string_empty_s;
      data_make.error.context = data->main->context.set.error;
      data_make.error.notable = data->main->context.set.notable;
      data_make.error.to.stream = F_type_error_d;
      data_make.error.to.id = F_type_descriptor_error_d;
      data_make.error.set = &data->main->context.set;
    }
    else if (data_make.setting_make.fail == fake_make_operation_fail_type_warn_e) {
      data_make.error.prefix = fl_print_warning_s;
      data_make.error.suffix = f_string_empty_s;
      data_make.error.context = data->main->context.set.warning;
      data_make.error.notable = data->main->context.set.notable;
      data_make.error.to.stream = F_type_warning_d;
      data_make.error.to.id = F_type_descriptor_warning_d;
      data_make.error.set = &data->main->context.set;
    }
    else {
      data_make.error.to.stream = 0;
      data_make.error.prefix = f_string_empty_s;
      data_make.error.suffix = f_string_empty_s;
      data_make.error.to.id = -1;
      data_make.error.set = &data->main->context.set;
    }

    data_make.error.verbosity = data->main->output.verbosity;

    {
      const int result = fake_make_operate_section(&data_make, data_make.id_main, &section_stack, &status);

      if (status == F_child) {
        data->main->child = result;
      }
    }

    if (status != F_child) {
      const f_status_t status_path = f_path_change_at(data_make.path.top.id);

      if (F_status_is_error(status_path) && data->main->warning.verbosity >= f_console_verbosity_verbose_e) {
        flockfile(data->main->warning.to.stream);

        fl_print_format("%r%[%QFailed change back to orignal path '%]", data->main->warning.to.stream, f_string_eol_s, data->main->warning.context, data->main->warning.prefix, data->main->warning.context);
        fl_print_format("%[%Q%]", data->main->warning.to.stream, data->main->warning.notable, data_make.path.stack.array[0], data->main->warning.notable);
        fl_print_format("%[', status code =%] ", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context);
        fl_print_format("%[%ui%]", data->main->warning.to.stream, data->main->warning.notable, F_status_set_fine(status_path), data->main->warning.notable);
        fl_print_format("%['.%]%r", data->main->warning.to.stream, data->main->warning.context, data->main->warning.context, f_string_eol_s);

        funlockfile(data->main->warning.to.stream);
      }
    }

    f_file_stream_close(F_true, &data_make.path.top);

    f_array_lengths_resize(0, &section_stack);
    fake_make_data_delete(&data_make);

    return status;
  }
#endif // _di_fake_make_operate_

#ifndef _di_fake_make_operate_expand_
  void fake_make_operate_expand(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_fss_content_t content, const f_fss_quotes_t quotes, f_status_t * const status) {

    if (F_status_is_error(*status)) return;
    if (!content.used) return;

    // Pre-allocate the known arguments size.
    *status = f_string_dynamics_increase_by(content.used, &data_make->cache_arguments);

    if (F_status_is_error(*status) || *status == F_string_too_large) {
      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase_by", F_true);

      return;
    }

    const f_string_static_t vocabulary_context = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_context_s, 0, F_iki_vocabulary_0002_context_s_length);
    const f_string_static_t vocabulary_define = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_define_s, 0, F_iki_vocabulary_0002_define_s_length);
    const f_string_static_t vocabulary_parameter = macro_f_string_static_t_initialize(F_iki_vocabulary_0002_parameter_s, 0, F_iki_vocabulary_0002_parameter_s_length);

    f_iki_data_t *iki_data = &data_make->cache_iki;

    f_state_t state = macro_f_state_t_initialize(fake_common_allocation_large_d, fake_common_allocation_small_d, 0, 0, &fll_program_standard_signal_state, 0, (void *) data_make->main, 0);

    f_string_range_t range = f_string_range_t_initialize;
    f_string_map_multis_t *parameter = &data_make->setting_make.parameter;

    // 1 = is parameter, 2 = is define, 3 = is context.
    uint8_t is = 0;

    bool unmatched = F_true;
    bool separate = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;
    f_array_length_t l = 0;
    f_array_length_t m = 0;

    const f_string_static_t reserved_name[] = {
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

      iki_data->variable.used = 0;
      iki_data->vocabulary.used = 0;
      iki_data->content.used = 0;
      iki_data->delimits.used = 0;

      // Skip content that is unused, but quoted content, even if empty, should remain.
      if (content.array[i].start > content.array[i].stop) {
        if (quotes.array[i]) {
          ++data_make->cache_arguments.used;

          *status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->cache_arguments);

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);

            break;
          }
        }

        continue;
      }

      range = content.array[i];

      *status = fl_iki_read(state, &data_make->buffer, &range, iki_data);

      if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) != F_interrupt) {
          fll_error_print(data_make->error, F_status_set_fine(*status), "fl_iki_read", F_true);
        }

        break;
      }

      // Apply the IKI delimits to the buffer.
      for (j = 0; j < iki_data->delimits.used; ++j) {
        data_make->buffer.string[iki_data->delimits.array[j]] = f_iki_syntax_placeholder_s.string[0];
      } // for

      if (iki_data->variable.used) {

        // Copy everything up to the start of the first IKI variable.
        if (iki_data->variable.array[0].start && content.array[i].start < iki_data->variable.array[0].start) {
          range.start = content.array[i].start;
          range.stop = iki_data->variable.array[0].start - 1;

          *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

            break;
          }
        }

        for (j = 0; j < iki_data->variable.used; ++j) {

          is = 0;

          *status = fl_string_dynamic_partial_compare_string(vocabulary_define.string, data_make->buffer, vocabulary_define.used, iki_data->vocabulary.array[j]);

          if (*status == F_equal_to) {
            is = 2;
          }
          else if (*status == F_equal_to_not) {
            *status = fl_string_dynamic_partial_compare_string(vocabulary_parameter.string, data_make->buffer, vocabulary_parameter.used, iki_data->vocabulary.array[j]);

            if (*status == F_equal_to) {
              is = 1;
            }
            else if (*status == F_equal_to_not) {
              *status = fl_string_dynamic_partial_compare_string(vocabulary_context.string, data_make->buffer, vocabulary_context.used, iki_data->vocabulary.array[j]);

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
            if (fl_string_dynamic_partial_compare_string(fake_make_parameter_variable_return_s.string, data_make->buffer, fake_make_parameter_variable_return_s.used, iki_data->content.array[j]) == F_equal_to) {

              if (data_make->setting_make.parameter.array[0].value.array[0].used) {
                *status = f_string_dynamic_append_nulless(data_make->setting_make.parameter.array[0].value.array[0], &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

                  break;
                }
              }
              else {
                *status = f_string_dynamic_append(f_string_ascii_0_s, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                  break;
                }
              }

              unmatched = F_false;
            }
            else if (fl_string_dynamic_partial_compare_string(fake_make_parameter_variable_top_s.string, data_make->buffer, fake_make_parameter_variable_top_s.used, iki_data->content.array[j]) == F_equal_to) {

              if (data_make->path.stack.used) {
                *status = f_string_dynamic_increase_by(data_make->path.stack.array[0].used + f_path_separator_s.used + 1, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_increase_by", F_true);

                  break;
                }

                *status = f_string_dynamic_append(data_make->path.stack.array[0], &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                  break;
                }

                // For safe path handling, always append the trailing slash.
                *status = f_string_dynamic_append(f_path_separator_s, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                if (F_status_is_error(*status)) {
                  fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                  break;
                }
              }

              unmatched = F_false;
            }
            else {
              for (k = 0; k < 33; ++k) {

                if (fl_string_dynamic_partial_compare_string(reserved_name[k].string, data_make->buffer, reserved_name[k].used, iki_data->content.array[j]) != F_equal_to) {
                  continue;
                }

                unmatched = F_false;
                separate = F_false;

                // Quoted IKI Content or unquoted IKI Content that are reserved words and entirely represent a single parameter should expand into a single argument.
                if (content.array[i].start == iki_data->variable.array[0].start && content.array[i].stop == iki_data->variable.array[0].stop || quotes.array[i]) {

                  // Pre-allocate memory to reduce number of allocations.
                  m = parameter->array[k].value.used;

                  for (l = 0; l < parameter->array[k].value.used; ++l) {
                    m += parameter->array[k].value.array[l].used;
                  } // for

                  *status = f_string_dynamic_increase_by(m, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                  if (F_status_is_error(*status)) {
                    fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_increase_by", F_true);

                    break;
                  }

                  for (l = 0; l < reserved_value[k]->used; ++l) {

                    if (!reserved_value[k]->array[l].used) continue;

                    if (separate) {
                      *status = f_string_dynamic_append(f_string_space_s, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                      if (F_status_is_error(*status)) {
                        fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                        break;
                      }
                    }

                    *status = f_string_dynamic_append_nulless(reserved_value[k]->array[l], &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                    if (F_status_is_error(*status)) {
                      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

                      break;
                    }

                    separate = F_true;
                  } // for
                }
                else {

                  for (l = 0; l < reserved_value[k]->used; ++l) {

                    if (!reserved_value[k]->array[l].used) continue;

                    // Unquoted use separate parameters rather then being separated by a space.
                    if (separate) {
                      ++data_make->cache_arguments.used;

                      *status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->cache_arguments);

                      if (F_status_is_error(*status)) {
                        fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);

                        break;
                      }

                    }

                    *status = f_string_dynamic_append_nulless(reserved_value[k]->array[l], &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                    if (F_status_is_error(*status)) {
                      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

                      break;
                    }

                    separate = F_true;
                  } // for
                }

                break;
              } // for

              if (F_status_is_error(*status)) break;
            }

            if (unmatched && F_status_is_error_not(*status)) {
              for (k = 0; k < parameter->used; ++k) {

                // Check against IKI variable list.
                if (fl_string_dynamic_partial_compare_dynamic(parameter->array[k].name, data_make->buffer, iki_data->content.array[j]) != F_equal_to) {
                  continue;
                }

                unmatched = F_false;
                separate = F_false;

                if (parameter->array[k].value.used) {

                  // Pre-allocate memory to reduce number of allocations.
                  if (quotes.array[i]) {
                    m = parameter->array[k].value.used;

                    for (l = 0; l < parameter->array[k].value.used; ++l) {
                      m += parameter->array[k].value.array[l].used;
                    } // for

                    *status = f_string_dynamic_increase_by(m, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                    if (F_status_is_error(*status)) {
                      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_increase_by", F_true);

                      break;
                    }
                  }

                  for (l = 0; l < parameter->array[k].value.used; ++l) {

                    if (!parameter->array[k].value.array[l].used) continue;

                    if (separate) {
                      if (quotes.array[i]) {
                        *status = f_string_dynamic_append(f_string_space_s, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                        if (F_status_is_error(*status)) {
                          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append", F_true);

                          break;
                        }
                      }

                      // Unquoted use separate parameters rather then being separated by a space.
                      else {
                        ++data_make->cache_arguments.used;

                        *status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->cache_arguments);

                        if (F_status_is_error(*status)) {
                          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);

                          break;
                        }
                      }
                    }

                    *status = f_string_dynamic_append_nulless(parameter->array[k].value.array[l], &data_make->cache_arguments.array[data_make->cache_arguments.used]);

                    if (F_status_is_error(*status)) {
                      fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_append_nulless", F_true);

                      break;
                    }

                    separate = F_true;
                  } // for

                  if (F_status_is_error(*status)) break;
                }

                break;
              } // for
            }

            if (F_status_is_error(*status)) break;

            if (unmatched) {
              *status = fake_make_operate_expand_build(data_make, quotes.array[i], iki_data->content.array[j]);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_build", F_true);

                break;
              }
            }
          }
          else if (is == 2) {
            *status = fake_make_operate_expand_environment(data_make, quotes.array[i], iki_data->content.array[j]);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_environment", F_true);

              break;
            }
          }
          else if (is == 3) {
            *status = fake_make_operate_expand_context(data_make, quotes.array[i], iki_data->content.array[j]);

            if (F_status_is_error(*status)) {
              fll_error_print(data_make->error, F_status_set_fine(*status), "fake_make_operate_expand_context", F_true);

              break;
            }
          }

          // Make sure to copy content between multiple IKI variables within the same content.
          if (j + 1 < iki_data->variable.used) {
            if (iki_data->variable.array[j].stop + 1 < iki_data->variable.array[j + 1].start && iki_data->variable.array[j + 1].stop <= content.array[i].stop) {
              range.start = iki_data->variable.array[j].stop + 1;
              range.stop = iki_data->variable.array[j + 1].start - 1;

              *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

              if (F_status_is_error(*status)) {
                fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

                break;
              }
            }
          }
        } // for

        if (F_status_is_error(*status)) break;

        // Copy everything after the last IKI variable to the end of the content.
        if (iki_data->variable.used && content.array[i].stop > iki_data->variable.array[iki_data->variable.used - 1].stop) {
          range.start = iki_data->variable.array[iki_data->variable.used - 1].stop + 1;
          range.stop = content.array[i].stop;

          *status = f_string_dynamic_partial_append_nulless(data_make->buffer, range, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

            break;
          }
        }

        if (!(content.array[i].start == iki_data->variable.array[0].start && content.array[i].stop == iki_data->variable.array[0].stop && !quotes.array[i]) || !quotes.array[i] || i + 1 == content.used) {
          ++data_make->cache_arguments.used;

          *status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->cache_arguments);

          if (F_status_is_error(*status)) {
            fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);

            break;
          }
        }
      }
      else {
        *status = f_string_dynamic_partial_append_nulless(data_make->buffer, content.array[i], &data_make->cache_arguments.array[data_make->cache_arguments.used]);

        if (F_status_is_error(*status)) {
          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamic_partial_append_nulless", F_true);

          break;
        }

        ++data_make->cache_arguments.used;

        *status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->cache_arguments);

        if (F_status_is_error(*status)) {
          fll_error_print(data_make->error, F_status_set_fine(*status), "f_string_dynamics_increase", F_true);

          break;
        }
      }
    } // for
  }
#endif // _di_fake_make_operate_expand_

#ifndef _di_fake_make_operate_expand_build_
  f_status_t fake_make_operate_expand_build(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name) {

    f_status_t status = F_none;
    f_string_dynamic_t value = f_string_dynamic_t_initialize;

    bool unmatched = F_true;

    {
      const f_string_static_t uint8_name[] = {
        fake_build_setting_name_build_language_s,
        fake_build_setting_name_version_file_s,
        fake_build_setting_name_version_target_s,
      };

      const uint8_t uint8_value[] = {
        data_make->setting_build.build_language,
        data_make->setting_build.version_file,
        data_make->setting_build.version_target,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        status = fl_string_dynamic_partial_compare_string(uint8_name[i].string, data_make->buffer, uint8_name[i].used, range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          status = f_conversion_number_unsigned_to_string(uint8_value[i], f_conversion_data_base_10_c, &value);

          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string_static_t bool_name[] = {
        fake_build_setting_name_build_script_s,
        fake_build_setting_name_build_shared_s,
        fake_build_setting_name_build_static_s,
        fake_build_setting_name_has_path_standard_s,
        fake_build_setting_name_search_exclusive_s,
        fake_build_setting_name_search_shared_s,
        fake_build_setting_name_search_static_s,
      };

      const bool bool_value[] = {
        data_make->setting_build.build_script,
        data_make->setting_build.build_shared,
        data_make->setting_build.build_static,
        data_make->setting_build.has_path_standard,
        data_make->setting_build.search_exclusive,
        data_make->setting_build.search_shared,
        data_make->setting_build.search_static,
      };

      for (uint8_t i = 0; i < 7; ++i) {

        status = fl_string_dynamic_partial_compare_string(bool_name[i].string, data_make->buffer, bool_name[i].used, range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          if (bool_value[i]) {
            status = f_string_dynamic_append(fake_common_setting_bool_yes_s, &value);
          }
          else {
            status = f_string_dynamic_append(fake_common_setting_bool_no_s, &value);
          }

          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string_static_t dynamic_name[] = {
        fake_build_setting_name_build_compiler_s,
        fake_build_setting_name_build_indexer_s,
        fake_build_setting_name_build_name_s,
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
        fake_build_setting_name_version_major_s,
        fake_build_setting_name_version_micro_s,
        fake_build_setting_name_version_minor_s,
      };

      const f_string_dynamic_t dynamic_value[] = {
        data_make->setting_build.build_compiler,
        data_make->setting_build.build_indexer,
        data_make->setting_build.build_name,
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
        data_make->setting_build.version_major,
        data_make->setting_build.version_micro,
        data_make->setting_build.version_minor,
      };

      for (uint8_t i = 0; i < 17; ++i) {

        status = fl_string_dynamic_partial_compare_string(dynamic_name[i].string, data_make->buffer, dynamic_name[i].used, range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          status = f_string_dynamic_append_nulless(dynamic_value[i], &value);

          break;
        }
      } // for
    }

    if (unmatched) {
      const f_string_static_t dynamics_name[] = {
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

      const uint8_t dynamics_flag[] = {
        0,                                         // build_libraries
        0,                                         // build_libraries_shared
        0,                                         // build_libraries_static
        0,                                         // build_sources_headers
        0,                                         // build_sources_headers_shared
        0,                                         // build_sources_headers_static
        0,                                         // build_sources_library
        0,                                         // build_sources_library_shared
        0,                                         // build_sources_library_static
        0,                                         // build_sources_program
        0,                                         // build_sources_program_shared
        0,                                         // build_sources_program_static
        0,                                         // build_sources_setting
        0,                                         // build_sources_script
        0,                                         // defines
        0,                                         // defines_library
        0,                                         // defines_library_shared
        0,                                         // defines_library_static
        0,                                         // defines_program
        0,                                         // defines_program_shared
        0,                                         // defines_program_static
        0,                                         // defines_shared
        0,                                         // defines_static
        data_build_setting_flag_has_environment_e, // environment
        0,                                         // flags
        0,                                         // flags_library
        0,                                         // flags_library_shared
        0,                                         // flags_library_static
        0,                                         // flags_program
        0,                                         // flags_program_shared
        0,                                         // flags_program_static
        0,                                         // flags_shared
        0,                                         // flags_static
        0,                                         // modes
        0,                                         // modes_default
      };

      for (uint8_t i = 0; i < 35; ++i) {

        status = fl_string_dynamic_partial_compare_string(dynamics_name[i].string, data_make->buffer, dynamics_name[i].used, range_name);

        if (status == F_equal_to) {
          unmatched = F_false;

          for (f_array_length_t j = 0; j < dynamics_value[i].used; ++j) {

            status = f_string_dynamic_mash(f_string_space_s, dynamics_value[i].array[j], &value);
            if (F_status_is_error(status)) break;
          } // for

          if (dynamics_flag[i]) {
            data_make->setting_build.flag |= dynamics_flag[i];
          }

          break;
        }
      } // for
    }

    if (F_status_is_error(status)) {
      f_string_dynamic_resize(0, &value);

      return status;
    }

    if (unmatched) {
      f_string_dynamic_resize(0, &value);

      return F_false;
    }

    if (quoted) {
      status = f_string_dynamic_append_nulless(value, &data_make->cache_arguments.array[data_make->cache_arguments.used]);
    }
    else {
      status = f_string_dynamics_increase_by(fake_default_allocation_small_d, &data_make->cache_arguments);

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append_nulless(value, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

        if (F_status_is_error_not(status)) {
          ++data_make->cache_arguments.used;
        }
      }
    }

    f_string_dynamic_resize(0, &value);

    if (F_status_is_error(status)) return status;

    return F_true;
  }
#endif // _di_fake_make_operate_expand_build_

#ifndef _di_fake_make_operate_expand_context_
  f_status_t fake_make_operate_expand_context(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name) {

    f_status_t status = F_none;
    const f_string_static_t *context = 0;

    const f_string_static_t context_name[] = {
      fake_make_context_error_s,
      fake_make_context_important_s,
      fake_make_context_normal_s,
      fake_make_context_notable_s,
      fake_make_context_reset_s,
      fake_make_context_standout_s,
      fake_make_context_success_s,
      fake_make_context_title_s,
      fake_make_context_warning_s,
    };

    const f_color_set_t context_value[] = {
      data_make->main->context.set.error,
      data_make->main->context.set.important,
      data_make->main->context.set.normal,
      data_make->main->context.set.notable,
      data_make->main->context.set.reset,
      data_make->main->context.set.standout,
      data_make->main->context.set.success,
      data_make->main->context.set.title,
      data_make->main->context.set.warning,
    };

    for (f_array_length_t i = 0; i < 9; ++i) {

      if (fl_string_dynamic_partial_compare_string(context_name[i].string, data_make->buffer, context_name[i].used, range_name) == F_equal_to) {
        context = context_value[i].before;

        break;
      }
    } // for

    if (context) {
      if (quoted) {
        status = f_string_dynamic_append_nulless(*context, &data_make->cache_arguments.array[data_make->cache_arguments.used]);
      }
      else {
        status = f_string_dynamics_increase_by(fake_default_allocation_small_d, &data_make->cache_arguments);

        if (F_status_is_error_not(status)) {
          status = f_string_dynamic_append_nulless(*context, &data_make->cache_arguments.array[data_make->cache_arguments.used]);

          if (F_status_is_error_not(status)) {
            ++data_make->cache_arguments.used;
          }
        }
      }

      if (F_status_is_error(status)) return status;
    }

    return F_true;
  }
#endif // _di_fake_make_operate_expand_context_

#ifndef _di_fake_make_operate_expand_environment_
  f_status_t fake_make_operate_expand_environment(fake_make_data_t * const data_make, const f_fss_quote_t quoted, const f_string_range_t range_name) {

    f_status_t status = F_none;

    data_make->cache_1.used = 0;
    data_make->cache_2.used = 0;

    status = f_string_dynamic_increase_by((range_name.stop - range_name.start) + 1, &data_make->cache_1);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_partial_append_nulless(data_make->buffer, range_name, &data_make->cache_1);
    }

    if (F_status_is_error_not(status)) {
      status = f_environment_get(data_make->cache_1, &data_make->cache_2);
    }

    if (F_status_is_error(status)) return status;
    if (status == F_exist_not) return F_false;

    status = f_string_dynamics_increase(fake_default_allocation_small_d, &data_make->cache_arguments);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_increase_by(data_make->cache_2.used + 1, &data_make->cache_arguments.array[data_make->cache_arguments.used]);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append_nulless(data_make->cache_2, &data_make->cache_arguments.array[data_make->cache_arguments.used]);
    }

    if (F_status_is_error(status)) return status;

    if (!quoted) {
      ++data_make->cache_arguments.used;
    }

    return F_true;
  }
#endif // _di_fake_make_operate_expand_environment_

#ifndef _di_fake_make_operate_section_
  int fake_make_operate_section(fake_make_data_t * const data_make, const f_array_length_t id_section, f_array_lengths_t * const section_stack, f_status_t * const status) {

    if (F_status_is_error(*status) || *status == F_child) return data_make->data->main->child;

    if (id_section > data_make->fakefile.used) {
      *status = F_status_set_error(F_parameter);

      fll_error_print(data_make->error, F_parameter, "fake_make_operate_section", F_true);

      return 0;
    }

    // Add the operation id to the operation stack.
    *status = f_array_lengths_increase(fake_default_allocation_small_d, section_stack);

    if (F_status_is_error(*status)) {
      fll_error_print(data_make->error, F_status_set_fine(*status), "f_array_lengths_increase", F_true);

      return 0;
    }

    section_stack->array[section_stack->used++] = id_section;

    const f_fss_named_t *section = &data_make->fakefile.array[id_section];

    if (data_make->main->output.verbosity != f_console_verbosity_quiet_e && data_make->main->output.verbosity != f_console_verbosity_error_e) {
      flockfile(data_make->main->output.to.stream);

      fl_print_format("%r%[Processing Section '%]", data_make->main->output.to.stream, f_string_eol_s, data_make->main->context.set.important, data_make->main->context.set.important);
      fl_print_format("%[%/Q%]", data_make->main->output.to.stream, data_make->main->context.set.notable, data_make->buffer, section->name, data_make->main->context.set.notable);
      fl_print_format("%['.%]%r", data_make->main->output.to.stream, data_make->main->context.set.important, data_make->main->context.set.important, f_string_eol_s);

      funlockfile(data_make->main->output.to.stream);
    }

    if (!section->objects.used) {
      --section_stack->used;

      return 0;
    }

    const f_string_static_t operations_name[] = {
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
      fake_make_operation_write_s,
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
      fake_make_operation_type_write_e,
    };

    fake_state_process_t state_process = fake_state_process_t_initialize;
    int result;
    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (i = 0; i < section->objects.used; ++i, *status = F_none) {

      for (j = 0; j < data_make->cache_arguments.size; ++j) {
        data_make->cache_arguments.array[j].used = 0;
      } // for

      data_make->cache_arguments.used = 0;
      state_process.condition = 0;
      state_process.condition_result = 0;
      state_process.operation_previous = state_process.operation;
      state_process.operation = 0;

      if (!(i % fake_signal_check_short_d)) {
        if (fll_program_standard_signal_received(data_make->main)) {
          fake_print_signal_received(data_make->data);

          *status = F_status_set_error(F_interrupt);

          break;
        }

        data_make->main->signal_check = 0;
      }

      for (j = 0; j < fake_make_operation_total_d; ++j) {

        if (fl_string_dynamic_partial_compare_string(operations_name[j].string, data_make->buffer, operations_name[j].used, section->objects.array[i]) == F_equal_to) {
          state_process.operation = operations_type[j];

          break;
        }
      } // for

      if (!state_process.operation) {
        fake_print_message_section_operation_unknown(data_make->data, data_make->error, data_make->buffer, section->name, section->objects.array[i]);

        *status = F_status_set_error(F_valid_not);
      }
      else if (state_process.operation == fake_make_operation_type_operate_e) {
        if (section_stack->used == fake_make_section_stack_max_d) {
          fake_print_message_section_operation_stack_max(data_make->data, data_make->error, data_make->buffer, section->name, section->objects.array[i], fake_make_section_stack_max_d);

          *status = F_status_set_error(F_recurse);
        }
      }

      fake_make_operate_expand(data_make, section->name, section->contents.array[i], section->quotess.array[i], status);

      fake_make_operate_block_prepare(&state_process);

      if (state_process.block != fake_state_process_block_done_e && state_process.block != fake_state_process_block_skip_e) {
        fake_make_operate_validate(data_make, section->name, &state_process, section_stack, status);
      }

      if (F_status_is_error(*status)) {
        if (state_process.block || state_process.operation == fake_make_operation_type_if_e || state_process.operation == fake_make_operation_type_and_e || state_process.operation == fake_make_operation_type_or_e) {
          state_process.success_block = F_false;

          // Setting error result informs the post-process that the operate process is not run due to an error during the pre-process.
          if (state_process.operation == fake_make_operation_type_if_e || state_process.operation == fake_make_operation_type_and_e || state_process.operation == fake_make_operation_type_or_e || state_process.operation == fake_make_operation_type_else_e) {
            state_process.block_result = fake_condition_result_error_e;
          }
        }
      }
      else {
        if (!state_process.block || state_process.block == fake_state_process_block_operate_e) {
          result = fake_make_operate_process(data_make, section->name, &state_process, section_stack, status);
          if (*status == F_child) return result;
        }

        fake_make_operate_block_postprocess(i == section->objects.used, &state_process, status);
      }

      if (F_status_set_fine(*status) == F_interrupt) break;

      if (F_status_is_error(*status)) {
        state_process.success = F_false;

        // Break acts identical to fail when at the top of the stack.
        if (F_status_set_fine(*status) == F_signal_abort && !section_stack->used) {
          data_make->setting_make.fail = fake_make_operation_fail_type_exit_e;
          data_make->error.prefix = fl_print_error_s;
          data_make->error.suffix = f_string_empty_s;
          data_make->error.context = data_make->main->context.set.error;
          data_make->error.notable = data_make->main->context.set.notable;
          data_make->error.to.stream = F_type_error_d;
          data_make->error.to.id = F_type_descriptor_error_d;
          data_make->error.set = &data_make->main->context.set;
        }

        fake_print_message_section_operation_failed(data_make->data, data_make->error, data_make->buffer, section->name, section->objects.array[i]);

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
        state_process.success = F_true;

        // F_signal_abort is used by the break section operation.
        break;
      }
      else if (*status == F_signal_quit) {
        state_process.success = F_true;

        // F_signal_quit is used by the exit section operation.
        if (!section_stack->used) {
          *status = F_none;
        }

        break;
      }
      else if (*status == F_failure) {

        // When F_failure (without the error bit) is returned, an error occured but the exit mode is not set to exit.
        // Record the success state and set the status to F_none.
        *status = F_none;
        state_process.success = F_false;
      }
      else {
        state_process.success = F_true;
      }
    } // for

    if (F_status_set_error(*status) == F_interrupt) return 0;

    if (i == section->objects.used && F_status_is_error_not(*status) && (state_process.operation == fake_make_operation_type_and_e || state_process.operation == fake_make_operation_type_else_e || state_process.operation == fake_make_operation_type_if_e || state_process.operation == fake_make_operation_type_or_e)) {
      if (data_make->data->main->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QIncomplete '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);

        if (state_process.operation == fake_make_operation_type_and_e) {
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_and_s, data_make->error.notable);
        }
        else if (state_process.operation == fake_make_operation_type_else_e) {
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_else_s, data_make->error.notable);
        }
        else if (state_process.operation == fake_make_operation_type_if_e) {
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_if_s, data_make->error.notable);
        }
        else {
          fl_print_format("%[%r%]", data_make->error.to.stream, data_make->error.notable, fake_make_operation_or_s, data_make->error.notable);
        }

        fl_print_format("%[' at end of the section.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);
      }

      fake_print_message_section_operation_failed(data_make->data, data_make->error, data_make->buffer, section->name, section->objects.array[section->objects.used - 1]);

      *status = F_status_set_error(F_failure);
    }

    // Ensure an error is returned during recursion if the last known section operation failed, except for the main operation.
    if (state_process.success == F_false && F_status_is_error_not(*status) && section_stack->used > 1) {
      *status = F_status_set_error(F_failure);
    }

    --section_stack->used;

    return 0;
  }
#endif // _di_fake_make_operate_section_

#ifdef __cplusplus
} // extern "C"
#endif
