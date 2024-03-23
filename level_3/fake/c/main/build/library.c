#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_library_script_
  int fake_build_library_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;

    fake_build_touch(data, file_stage);

    return 0;
  }
#endif // _di_fake_build_library_script_

#ifndef _di_fake_build_library_shared_
  int fake_build_library_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_library.used && !data_build->setting.build_sources_library_shared.used) return 0;

    fake_main_t * const main = data->main;

    fake_build_print_compile_library_shared(&main->program.message);

    fake_string_dynamics_reset(&main->cache_arguments);

    fake_build_objects_add(data, data_build, &data->path_build_objects_shared, &data_build->setting.build_objects_library, &data_build->setting.build_objects_library_shared);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fake_build_objects_add));

      return 0;
    }

    fake_build_sources_add(data, data_build, &data_build->setting.path_sources_library, &data_build->setting.build_sources_library, &data_build->setting.build_sources_library_shared);

    if (F_status_is_error(main->setting.state.status)) {
      fake_print_error(&main->program.error, macro_fake_f(fake_build_sources_add));

      return 0;
    }

    f_string_static_t parameter_file_name = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_major = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_minor = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_micro = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_nano = f_string_static_t_initialize;

    f_number_unsigned_t strings_length = 1;

    parameter_file_name.used = fake_build_parameter_library_name_prefix_s.used + data_build->setting.build_name.used + fake_build_parameter_library_name_suffix_shared_s.used;

    if (data_build->setting.version_major.used) {
      parameter_file_name_major.used = parameter_file_name.used + data_build->setting.version_major_prefix.used + data_build->setting.version_major.used;
      strings_length = 2;

      if (data_build->setting.version_minor.used) {
        parameter_file_name_minor.used = parameter_file_name_major.used + data_build->setting.version_minor_prefix.used + data_build->setting.version_minor.used;
        strings_length = 3;

        if (data_build->setting.version_micro.used) {
          parameter_file_name_micro.used = parameter_file_name_minor.used + data_build->setting.version_micro_prefix.used + data_build->setting.version_micro.used;
          strings_length = 4;

          if (data_build->setting.version_nano.used) {
            parameter_file_name_nano.used =  parameter_file_name_micro.used + data_build->setting.version_nano_prefix.used + data_build->setting.version_nano.used;
            strings_length = 5;
          }
        }
      }
    }

    f_char_t parameter_file_name_string[parameter_file_name.used + 1];
    f_char_t parameter_file_name_major_string[parameter_file_name_major.used + 1];
    f_char_t parameter_file_name_minor_string[parameter_file_name_minor.used + 1];
    f_char_t parameter_file_name_micro_string[parameter_file_name_micro.used + 1];
    f_char_t parameter_file_name_nano_string[parameter_file_name_nano.used + 1];

    parameter_file_name.string = parameter_file_name_string;
    parameter_file_name_major.string = parameter_file_name_major_string;
    parameter_file_name_minor.string = parameter_file_name_minor_string;
    parameter_file_name_micro.string = parameter_file_name_micro_string;
    parameter_file_name_nano.string = parameter_file_name_nano_string;

    parameter_file_name.used = 0;
    parameter_file_name_major.used = 0;
    parameter_file_name_minor.used = 0;
    parameter_file_name_micro.used = 0;
    parameter_file_name_nano.used = 0;

    f_string_static_t *strings[5] = {
      &parameter_file_name,
      &parameter_file_name_major,
      &parameter_file_name_minor,
      &parameter_file_name_micro,
      &parameter_file_name_nano,
    };

    uint8_t i = 0;

    {
      for (; i < strings_length; ++i) {

        memcpy(strings[i]->string, fake_build_parameter_library_name_prefix_s.string, sizeof(f_char_t) * fake_build_parameter_library_name_prefix_s.used);

        strings[i]->used += fake_build_parameter_library_name_prefix_s.used;
      } // for

      for (i = 0; i < strings_length; ++i) {

        memcpy(strings[i]->string + strings[i]->used, data_build->setting.build_name.string, sizeof(f_char_t) * data_build->setting.build_name.used);

        strings[i]->used += data_build->setting.build_name.used;
      } // for

      for (i = 0; i < strings_length; ++i) {

        memcpy(strings[i]->string + strings[i]->used, fake_build_parameter_library_name_suffix_shared_s.string, sizeof(f_char_t) * fake_build_parameter_library_name_suffix_shared_s.used);

        strings[i]->used += fake_build_parameter_library_name_suffix_shared_s.used;
      } // for

      if (data_build->setting.version_major.used) {
        if (data_build->setting.version_major_prefix.used) {
          for (i = 1; i < strings_length; ++i) {

            memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_major_prefix.string, sizeof(f_char_t) * data_build->setting.version_major_prefix.used);

            strings[i]->used += data_build->setting.version_major_prefix.used;
          } // for
        }

        for (i = 1; i < strings_length; ++i) {

          memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_major.string, sizeof(f_char_t) * data_build->setting.version_major.used);

          strings[i]->used += data_build->setting.version_major.used;
        } // for

        if (data_build->setting.version_minor.used) {
          if (data_build->setting.version_minor_prefix.used) {
            for (i = 2; i < strings_length; ++i) {

              memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_minor_prefix.string, sizeof(f_char_t) * data_build->setting.version_minor_prefix.used);

              strings[i]->used += data_build->setting.version_minor_prefix.used;
            } // for
          }

          for (i = 2; i < strings_length; ++i) {

            memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_minor.string, sizeof(f_char_t) * data_build->setting.version_minor.used);

            strings[i]->used += data_build->setting.version_minor.used;
          } // for

          if (data_build->setting.version_micro.used) {
            if (data_build->setting.version_micro_prefix.used) {
              for (i = 3; i < strings_length; ++i) {

                memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_micro_prefix.string, sizeof(f_char_t) * data_build->setting.version_micro_prefix.used);

                strings[i]->used += data_build->setting.version_micro_prefix.used;
              } // for
            }

            for (i = 3; i < strings_length; ++i) {

              memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_micro.string, sizeof(f_char_t) * data_build->setting.version_micro.used);

              strings[i]->used += data_build->setting.version_micro.used;
            } // for

            if (data_build->setting.version_nano.used) {
              if (data_build->setting.version_nano_prefix.used) {
                for (i = 4; i < strings_length; ++i) {

                  memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_nano_prefix.string, sizeof(f_char_t) * data_build->setting.version_nano_prefix.used);

                  strings[i]->used += data_build->setting.version_nano_prefix.used;
                } // for
              }

              for (i = 4; i < strings_length; ++i) {

                memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_nano.string, sizeof(f_char_t) * data_build->setting.version_nano.used);

                strings[i]->used += data_build->setting.version_nano.used;
              } // for
            }
          }
        }
      }

      parameter_file_name_string[parameter_file_name.used] = 0;
      parameter_file_name_major_string[parameter_file_name_major.used] = 0;
      parameter_file_name_minor_string[parameter_file_name_minor.used] = 0;
      parameter_file_name_micro_string[parameter_file_name_micro.used] = 0;
      parameter_file_name_nano_string[parameter_file_name_nano.used] = 0;
    }

    {
      main->setting.state.status = fll_execute_arguments_add(fake_build_parameter_library_shared_s, &main->cache_arguments);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

        return 0;
      }

      fake_string_dynamic_reset(&main->cache_argument);

      main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_library_shared_prefix_s, &main->cache_argument);

      if (F_status_is_error_not(main->setting.state.status)) {
        if (data_build->setting.version_target == fake_build_version_major_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_major, &main->cache_argument);
        }
        else if (data_build->setting.version_target == fake_build_version_minor_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_minor, &main->cache_argument);
        }
        else if (data_build->setting.version_target == fake_build_version_micro_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_micro, &main->cache_argument);
        }
        else if (data_build->setting.version_target == fake_build_version_nano_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_nano, &main->cache_argument);
        }
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        return 0;
      }

      main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = fll_execute_arguments_add(fake_build_parameter_library_output_s, &main->cache_arguments);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

        return 0;
      }

      fake_string_dynamic_reset(&main->cache_argument);

      main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_libraries_shared, &main->cache_argument);

      if (F_status_is_error_not(main->setting.state.status)) {
        if (data_build->setting.version_file == fake_build_version_major_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_major, &main->cache_argument);
        }
        else if (data_build->setting.version_file == fake_build_version_minor_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_minor, &main->cache_argument);
        }
        else if (data_build->setting.version_file == fake_build_version_micro_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_micro, &main->cache_argument);
        }
        else if (data_build->setting.version_file == fake_build_version_nano_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter_file_name_nano, &main->cache_argument);
        }
      }

      main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);

      if (F_status_is_error_not(main->setting.state.status)) {
        fake_build_arguments_standard_add(data, data_build, F_true, fake_build_type_library_e);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

        return 0;
      }
    }

    {
      const int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler);

      if (F_status_is_error(main->setting.state.status)) return 0;
      if (main->setting.state.status == F_child) return result;
    }

    {
      bool dont_links[] = {
        !parameter_file_name_major.used,
        data_build->setting.version_file == fake_build_version_major_e || !parameter_file_name_major.used,
        data_build->setting.version_file == fake_build_version_minor_e || !parameter_file_name_minor.used,
        data_build->setting.version_file == fake_build_version_micro_e || !parameter_file_name_micro.used,
      };

      const f_string_static_t points[] = {
        parameter_file_name,
        parameter_file_name_major,
        parameter_file_name_minor,
        parameter_file_name_micro,
      };

      const f_string_static_t targets[] = {
        parameter_file_name_major,
        parameter_file_name_minor,
        parameter_file_name_micro,
        parameter_file_name_nano,
      };

      for (i = 0; i < 4; ++i) {

        if (dont_links[i]) break;

        fake_string_dynamic_reset(&main->cache_argument);

        main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_libraries_shared, &main->cache_argument);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(points[i], &main->cache_argument);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return 0;
        }

        main->setting.state.status = f_file_link(targets[i], main->cache_argument);

        if (F_status_is_error_not(main->setting.state.status)) {
          fake_build_print_verbose_linked_file(&main->program.message, main->cache_argument, targets[i]);
        }
        else {
          if (F_status_set_fine(main->setting.state.status) == F_file_found) {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_link), main->cache_argument, f_file_operation_link_s, fll_error_file_type_file_e);
          }
          else {
            fake_print_error_file(&main->program.error, macro_fake_f(f_file_link), targets[i], f_file_operation_link_s, fll_error_file_type_file_e);
          }

          return 0;
        }
      } // for
    }

    fake_build_touch(data, file_stage);

    return 0;
  }
#endif // _di_fake_build_library_shared_

#ifndef _di_fake_build_library_static_
  int fake_build_library_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_library.used && !data_build->setting.build_sources_library_static.used) return 0;

    fake_main_t * const main = data->main;

    fake_build_print_compile_library_static(&main->program.message);

    fake_string_dynamic_reset(&main->cache_1);
    fake_string_dynamic_reset(&main->cache_2);
    fake_string_dynamics_reset(&main->cache_arguments);

    f_number_unsigned_t i = 0;

    for (; i < data_build->setting.build_indexer_arguments.used; ++i) {

      if (!data_build->setting.build_indexer_arguments.array[i].used) continue;

      main->setting.state.status = fll_execute_arguments_add(data_build->setting.build_indexer_arguments.array[i], &main->cache_arguments);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

        return 0;
      }
    } // for

    if (F_status_is_error_not(main->setting.state.status)) {
      main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_libraries_static, &main->cache_2);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_library_name_prefix_s, &main->cache_2);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(data_build->setting.build_name, &main->cache_2);
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_library_name_suffix_static_s, &main->cache_2);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));
      }
      else {
        main->setting.state.status = fll_execute_arguments_add(main->cache_2, &main->cache_arguments);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

          return 0;
        }
      }
    }

    if (F_status_is_error_not(main->setting.state.status)) {
      f_number_unsigned_t j = 0;

      const f_string_dynamics_t *sources[2] = {
        &data_build->setting.build_sources_library,
        &data_build->setting.build_sources_library_static,
      };

      for (i = 0; i < 2; ++i) {

        for (j = 0; j < sources[i]->used; ++j) {

          fake_string_dynamic_reset(&main->cache_1);
          fake_string_dynamic_reset(&main->cache_2);

          fake_build_get_file_name_without_extension(data, sources[i]->array[j], &main->cache_1);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(fake_build_get_file_name_without_extension));

            break;
          }

          main->setting.state.status = f_file_name_directory(sources[i]->array[j], &main->cache_2);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_file_name_directory));

            break;
          }

          fake_string_dynamic_reset(&main->cache_argument);

          if (main->cache_2.used) {
            main->setting.state.status = f_string_dynamic_prepend(data->path_build_objects, &main->cache_2);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_prepend));

              break;
            }

            main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &main->cache_2);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_assure));

              break;
            }

            main->setting.state.status = f_string_dynamic_append_nulless(main->cache_2, &main->cache_argument);

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_string_dynamic_append_nulless(main->cache_1, &main->cache_argument);
            }

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_object_name_suffix_s, &main->cache_argument);
            }
          }
          else {
            main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_objects, &main->cache_argument);

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_string_dynamic_append_nulless(main->cache_1, &main->cache_argument);
            }

            if (F_status_is_error_not(main->setting.state.status)) {
              main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_object_name_suffix_s, &main->cache_argument);
            }
          }

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            break;
          }

          main->setting.state.status = fll_execute_arguments_add(main->cache_argument, &main->cache_arguments);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(fll_execute_arguments_add));

            break;
          }
        } // for
      } // for
    }

    const int result = F_status_is_error(main->setting.state.status)
      ? main->program.child
      : fake_execute(data, data_build->environment, data_build->setting.build_indexer);

    if (F_status_is_error_not(main->setting.state.status) && main->setting.state.status != F_child) {
      fake_build_touch(data, file_stage);
    }

    return result;
  }
#endif // _di_fake_build_library_static_

#ifdef __cplusplus
} // extern "C"
#endif
