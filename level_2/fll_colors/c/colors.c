#include <level_2/colors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_colors_load_context_
  f_return_status fll_colors_load_context(fl_color_context *data, f_bool use_light_colors) {
    #ifndef _di_level_2_parameter_checking_
      if (data == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status status = f_none;

    // switch to the appropriate terminal color mode
    {
      char *environment = getenv("TERM");

      if (!environment || strncmp(environment, "linux", 6) == 0) {
        data->color_list = f_colors_linux;
      }
      else {
        data->color_list = f_colors_xterminal;
      }
    }

    // load the colors
    if (use_light_colors) {
      status = fl_save_color1(&data->reset, data->color_format, data->color_list.reset);

      if (f_error_is_not_error(status)) status = fl_save_color1(&data->warning,   data->color_format, data->color_list.yellow);
      if (f_error_is_not_error(status)) status = fl_save_color2(&data->error,     data->color_format, data->color_list.bold, data->color_list.red);
      if (f_error_is_not_error(status)) status = fl_save_color2(&data->title,     data->color_format, data->color_list.bold, data->color_list.blue);
      if (f_error_is_not_error(status)) status = fl_save_color1(&data->notable,   data->color_format, data->color_list.bold);
      if (f_error_is_not_error(status)) status = fl_save_color1(&data->important, data->color_format, data->color_list.blue);
      if (f_error_is_not_error(status)) status = fl_save_color1(&data->standout,  data->color_format, data->color_list.purple);
    }
    else {
      status = fl_save_color1(&data->reset, data->color_format, data->color_list.reset);

      if (f_error_is_not_error(status)) status = fl_save_color1(&data->warning,   data->color_format, data->color_list.yellow);
      if (f_error_is_not_error(status)) status = fl_save_color2(&data->error,     data->color_format, data->color_list.bold, data->color_list.red);
      if (f_error_is_not_error(status)) status = fl_save_color2(&data->title,     data->color_format, data->color_list.bold, data->color_list.yellow);
      if (f_error_is_not_error(status)) status = fl_save_color1(&data->notable,   data->color_format, data->color_list.bold);
      if (f_error_is_not_error(status)) status = fl_save_color2(&data->important, data->color_format, data->color_list.bold, data->color_list.green);
      if (f_error_is_not_error(status)) status = fl_save_color1(&data->standout,  data->color_format, data->color_list.green);
    }

    return status;
  }
#endif // _di_fll_colors_load_context_

#ifdef __cplusplus
} // extern "C"
#endif
