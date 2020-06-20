#include <level_1/fss_extended.h>
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_extended_object_read_
  f_return_status fl_fss_extended_object_read(f_string_dynamic *buffer, f_string_range *range, f_fss_object *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (range->stop < range->start) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    return private_fl_fss_basic_object_read(F_false, buffer, range, found);
  }
#endif // _di_fl_fss_extended_object_read_

#ifndef _di_fl_fss_extended_content_read_
  f_return_status fl_fss_extended_content_read(f_string_dynamic *buffer, f_string_range *range, f_fss_content *found) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
      if (buffer->used == 0) return F_status_set_error(F_parameter);
      if (range == 0) return F_status_set_error(F_parameter);
      if (found == 0) return F_status_set_error(F_parameter);
      if (range->stop < range->start) return F_status_set_error(F_parameter);
      if (range->start >= buffer->used) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;

    // delimits must only be applied once a valid object is found.
    f_string_lengths delimits = f_string_lengths_initialize;

    status = f_fss_skip_past_space(*buffer, range);
    if (F_status_is_error(status)) return status;

    // return found nothing if this line only contains whitespace and delimit placeholders.
    if (status == F_none_eol) {
      range->start++;
      return FL_fss_found_content_not;
    }
    else if (status == F_none_eos) {
      return F_data_not_eos;
    }
    else if (status == F_none_stop) {
      return F_data_not_stop;
    }

    bool has_delimit = F_false;
    int8_t quoted = 0;

    bool continue_main_loop = F_false;

    f_string_length location = 0;
    f_array_length already_used = found->used;

    while (range->start <= range->stop && range->start < buffer->used) {
      quoted = 0;

      if (found->used >= found->size) {
        f_macro_fss_content_resize(status, (*found), found->size + f_fss_default_allocation_step);

        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }
      }

      // begin the search.
      found->array[found->used].start = range->start;
      found->array[found->used].stop = 0;

      // identify where the content begins.
      if (buffer->string[range->start] == f_fss_delimit_slash) {
        f_string_length last_slash = range->start;

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }

        // @fixme: count each slash.
        while (range->start <= range->stop && range->start < buffer->used) {
          if (buffer->string[range->start] == f_fss_delimit_placeholder) {
            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }

            continue;
          }

          status = f_fss_is_space(*buffer, *range);

          if (status == F_true) {
            found->array[found->used].stop = range->start - 1;

            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }

            found->used++;

            if (buffer->string[range->start] == f_fss_extended_close) {
              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              return FL_fss_found_content;
            }

            continue_main_loop = F_true;
            break;
          }
          else if (F_status_is_error(status)) {
            return status;
          }
          else if (buffer->string[range->start] != f_fss_delimit_slash) {
            break;
          }

          last_slash = range->start;

          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) return status;
        } // while

        if (continue_main_loop) {
          continue_main_loop = F_false;
          continue;
        }

        fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

        if (buffer->string[range->start] == f_fss_delimit_single_quote || buffer->string[range->start] == f_fss_delimit_double_quote) {
          // @fixme: use slash count to determine if a slash needs to be delimited and if this quote is escaped or not.
          if (delimits.used >= delimits.size) {
            f_macro_string_lengths_resize(status, delimits, delimits.size + f_fss_default_allocation_step);

            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }
          }

          delimits.array[delimits.used] = last_slash;
          delimits.used++;

          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            return status;
          }
        }
      }
      else if (buffer->string[range->start] == f_fss_delimit_single_quote || buffer->string[range->start] == f_fss_delimit_double_quote) {
        quoted = buffer->string[range->start];

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }

        found->array[found->used].start = range->start;
      }

      // identify where the content ends.
      if (quoted == 0) {
        status = F_none;

        for (;;) {
          status = f_fss_is_space(*buffer, *range);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            return status;
          }

          if (status == F_true) break;

          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            return status;
          }

          fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)
        } // for

        found->array[found->used].stop = range->start - 1;
        found->used++;

        if (buffer->string[range->start] == f_fss_extended_close) {
          fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

          range->start++;
          return FL_fss_found_content;
        }

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) {
          f_macro_string_lengths_delete_simple(delimits);
          return status;
        }

        continue;
      }
      else {
        while (range->start <= range->stop && range->start < buffer->used) {

          if (buffer->string[range->start] == f_fss_delimit_slash) {
            f_string_length first_slash = range->start;
            f_string_length slash_count = 1;

            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }

            while (range->start <= range->stop && range->start < buffer->used) {
              if (buffer->string[range->start] == f_fss_delimit_placeholder) {
                status = f_fss_increment_buffer(*buffer, range, 1);
                if (F_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(delimits);
                  return status;
                }

                continue;
              }
              else if (buffer->string[range->start] != f_fss_delimit_slash) {
                break;
              }

              slash_count++;

              status = f_fss_increment_buffer(*buffer, range, 1);
              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }
            } // while

            fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_unterminated_group_eos, F_unterminated_group_stop)

            if (buffer->string[range->start] == quoted) {
              location = range->start;
              range->start = first_slash;

              if (slash_count % 2 == 0) {
                if (delimits.used + (slash_count / 2) >= delimits.size) {
                  f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }
                }

                while (slash_count > 0) {
                  if (buffer->string[range->start] == f_fss_delimit_slash) {
                    if (slash_count % 2 == 1) {
                      delimits.array[delimits.used] = range->start;
                      delimits.used++;
                    }

                    slash_count--;
                  }

                  status = f_fss_increment_buffer(*buffer, range, 1);
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }
                } // while

                range->start = location + 1;

                fl_macro_fss_skip_past_delimit_placeholders((*buffer), (*range));
                fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

                status = f_fss_is_graph(*buffer, *range);

                if (status == F_true) {
                  while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
                    status = f_fss_increment_buffer(*buffer, range, 1);
                    if (F_status_is_error(status)) {
                      f_macro_string_lengths_delete_simple(delimits);
                      return status;
                    }
                  } // while

                  fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_unterminated_group_eos, F_unterminated_group_stop)

                  status = f_fss_increment_buffer(*buffer, range, 1);
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }

                  return F_unterminated_group;
                }
                else if (F_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(delimits);
                  return status;
                }
                else if (buffer->string[range->start] == f_fss_extended_close) {
                  fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                  found->array[found->used].stop = location - 1;

                  range->start++;
                  found->used++;
                  return FL_fss_found_content;
                }

                found->array[found->used].stop = location - 1;

                status = f_fss_increment_buffer(*buffer, range, 1);
                if (F_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(delimits);
                  return status;
                }

                found->used++;
                continue;
              }
              else {
                if (delimits.used + (slash_count / 2) >= delimits.size) {
                  f_macro_string_lengths_resize(status, delimits, delimits.size + (slash_count / 2) + f_fss_default_allocation_step);

                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }
                }

                while (slash_count > 0) {
                  if (buffer->string[range->start] == f_fss_delimit_slash) {
                    if (slash_count % 2 == 1) {
                      delimits.array[delimits.used] = range->start;
                      delimits.used++;
                    }

                    slash_count--;
                  }

                  status = f_fss_increment_buffer(*buffer, range, 1);
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }
                } // while

                range->start = location;
              }
            }
          }
          else if (buffer->string[range->start] == quoted) {
            found->array[found->used].stop = range->start - 1;

            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(delimits);
              return status;
            }

            while (range->start <= range->stop && range->start < buffer->used) {

              if (buffer->string[range->start] == f_fss_extended_close) {
                fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

                range->start++;
                found->used++;
                return FL_fss_found_content;
              }

              status = f_fss_is_space(*buffer, *range);

              if (status == F_true) {
                status = f_fss_increment_buffer(*buffer, range, 1);
                if (F_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(delimits);
                  return status;
                }

                found->used++;
                continue_main_loop = F_true;
                break;
              }
              else if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }
              else if (buffer->string[range->start] != f_fss_delimit_placeholder) {

                while (range->start < buffer->used && range->start <= range->stop) {
                  status = f_fss_increment_buffer(*buffer, range, 1);
                  if (F_status_is_error(status)) {
                    f_macro_string_lengths_delete_simple(delimits);
                    return status;
                  }

                  fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_unterminated_group_eos, F_unterminated_group_stop)

                  if (buffer->string[range->start] == f_string_eol[0]) break;
                } // while

                status = f_fss_increment_buffer(*buffer, range, 1);
                if (F_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(delimits);
                  return status;
                }

                return F_unterminated_group;
              }

              status = f_fss_increment_buffer(*buffer, range, 1);
              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }

              fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)
            } // while

            if (continue_main_loop) break;

            fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)
          }
          else if (buffer->string[range->start] == f_fss_extended_close) {

            if (found->used == already_used) {
              range->start++;
              return FL_fss_found_content_not;
            }
            else {
              fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

              found->array[found->used].stop = range->start - 1;

              status = f_fss_increment_buffer(*buffer, range, 1);
              if (F_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(delimits);
                return status;
              }

              found->used++;

              return FL_fss_found_content;
            }
          }

          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(delimits);
            return status;
          }
        } // while

        fl_macro_fss_content_return_on_overflow((*buffer), (*range), (*found), delimits, F_unterminated_group_eos, F_unterminated_group_stop)
      }

      if (continue_main_loop) {
        continue_main_loop = F_false;
        continue;
      }

      break;
    } // while

    fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

    // seek to the end of the line when no valid content is found
    while (range->start < buffer->used && range->start <= range->stop && buffer->string[range->start] != f_string_eol[0]) {
      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) {
        f_macro_string_lengths_delete_simple(delimits);
        return status;
      }
    } // while

    fl_macro_fss_content_delimited_return_on_overflow((*buffer), (*range), (*found), delimits, F_none_eos, F_none_stop)

    if (found->used == already_used) {
      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) {
        f_macro_string_lengths_delete_simple(delimits);
        return status;
      }

      return FL_fss_found_content_not;
    }

    fl_macro_fss_apply_delimit_placeholders((*buffer), delimits);

    status = f_fss_increment_buffer(*buffer, range, 1);
    if (F_status_is_error(status)) {
      f_macro_string_lengths_delete_simple(delimits);
      return status;
    }

    return FL_fss_found_content;
  }
#endif // _di_fl_fss_extended_content_read_

#ifndef _di_fl_fss_extended_object_write_
  f_return_status fl_fss_extended_object_write(const f_string_static object, f_string_range *range, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;
    bool quoted = F_false;

    f_string_range buffer_position = f_string_range_initialize;
    f_string_length start_position = f_string_initialize;
    f_string_length pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(object, (*range))

    if (range->start > range->stop) return F_data_not_stop;
    else if (range->start >= object.used) return F_data_not_eos;

    start_position = range->start;

    // add an additional 3 to ensure that there is room for the start and stop quotes or a slash delimit and the object open character.
    pre_allocate_size = buffer->used + (range->stop - range->start) + 3 + f_fss_default_allocation_step_string;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);
      if (F_status_is_error(status)) return status;
    }

    buffer_position.start = buffer->used;
    buffer_position.stop  = buffer->used;

    if (object.string[range->start] == f_fss_delimit_slash) {
      while (range->start <= range->stop && range->start < object.used) {
        if (object.string[range->start] == f_fss_delimit_placeholder) {
          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          continue;
        } else if (object.string[range->start] != f_fss_delimit_slash) {
          break;
        }

        buffer->string[buffer_position.stop] = object.string[range->start];
        buffer_position.stop++;

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      if (object.string[range->start] == f_fss_delimit_single_quote || object.string[range->start] == f_fss_delimit_double_quote) {
        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

          if (F_status_is_error(status)) return status;
        }

        buffer->string[buffer_position.stop] = f_fss_delimit_slash;
        buffer->string[buffer_position.stop + 1] = object.string[range->start];
        buffer_position.stop += 2;

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      }
    }
    else if (object.string[range->start] == f_fss_delimit_single_quote || object.string[range->start] == f_fss_delimit_double_quote) {
      pre_allocate_size++;

      if (pre_allocate_size > buffer->size) {
        f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
        if (F_status_is_error(status)) return status;
      }

      buffer->string[buffer_position.stop] = f_fss_delimit_slash;
      buffer->string[buffer_position.stop + 1] = object.string[range->start];
      buffer_position.stop += 2;

      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    }
    else if (object.string[range->start] == f_fss_comment) {
      quoted = F_true;
    }

    while (range->start <= range->stop && range->start < object.used) {
      if (object.string[range->start] == f_fss_delimit_placeholder) {
        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) return status;

        continue;
      }
      else if (object.string[range->start] == f_string_eol[0]) {
        if (quoted) {
          buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
          buffer_position.stop++;
        }

        buffer->string[buffer_position.stop] = f_fss_basic_open;
        buffer->used = buffer_position.stop + 1;

        return F_none_eol;
      }
      else if ((status = f_fss_is_space(*buffer, *range)) == F_true || quoted) {
        f_string_length first_space = range->start;

        if (!quoted) {
          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < object.used && isspace(object.string[range->start])) {
            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (range->start > range->stop || range->start >= object.used) {
            buffer->string[first_space] = f_fss_extended_open;
            buffer->used = buffer_position.stop + 1;
            break;
          }
        }

        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

          if (F_status_is_error(status)) return status;
        }

        // restart the loop searching for f_fss_delimit_double_quote.
        range->start = start_position;
        buffer_position.stop = buffer_position.start;

        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer_position.stop++;

        while (range->start <= range->stop && range->start < object.used) {
          if (object.string[range->start] == f_fss_delimit_placeholder) {
            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) return status;

            continue;
          }
          else if (object.string[range->start] == f_fss_delimit_double_quote) {
            pre_allocate_size++;

            if (pre_allocate_size > buffer->size) {
              f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);

              if (F_status_is_error(status)) return status;
            }

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
          }
          else if (object.string[range->start] == f_fss_delimit_slash) {
            f_string_length slash_count = 0;

            for (;;) {
              buffer->string[buffer_position.stop] = object.string[range->start];
              buffer_position.stop++;
              slash_count++;

              status = f_fss_increment_buffer(*buffer, range, 1);
              if (F_status_is_error(status)) return status;

              fl_macro_fss_skip_past_delimit_placeholders(object, (*range));

              if (range->start > range->stop || range->start >= object.used) {
                break;
              }

              if (object.string[range->start] == f_fss_delimit_double_quote) {
                pre_allocate_size += slash_count;

                if (pre_allocate_size > buffer->size) {
                  f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
                  if (F_status_is_error(status)) return status;
                }

                break;
              }
              else if (object.string[range->start] != f_fss_delimit_slash) {
                slash_count = 0;
                break;
              }
            } // for

            while (slash_count > 0) {
              buffer->string[buffer_position.stop] = f_fss_delimit_slash;
              buffer_position.stop++;
              slash_count--;
            } // while

            continue;
          }
          else if (object.string[range->start] == f_string_eol[0]) {
            buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
            buffer_position.stop++;

            buffer->string[buffer_position.stop] = f_fss_basic_open;
            buffer->used = buffer_position.stop + 1;

            return F_none_eol;
          }

          buffer->string[buffer_position.stop] = object.string[range->start];

          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          buffer_position.stop++;
        } // while

        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer->string[buffer_position.stop + 1] = f_fss_extended_open;
        buffer->used = buffer_position.stop + 2;
        break;
      }
      else if (F_status_is_error(status)) {
        return status;
      }

      buffer->string[buffer_position.stop] = object.string[range->start];

      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      buffer_position.stop++;
    } // while

    if (buffer->used < buffer_position.stop) {
      buffer->string[buffer_position.stop] = f_fss_extended_open;
      buffer->used = buffer_position.stop + 1;
    }

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= object.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_extended_object_write_

#ifndef _di_fl_fss_extended_content_write_
  f_return_status fl_fss_extended_content_write(const f_string_static content, f_string_range *range, f_string_dynamic *buffer) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = F_none;
    int8_t quoted = 0;

    f_string_range buffer_position = f_string_range_initialize;
    f_string_length start_position = 0;
    f_string_length pre_allocate_size = 0;

    fl_macro_fss_skip_past_delimit_placeholders(content, (*range))

    if (range->start > range->stop) return F_data_not_stop;
    else if (range->start >= content.used) return F_data_not_eos;

    // add an additional 1 to ensure that there is room for the terminating newline.
    pre_allocate_size = buffer->used + (content.used) + 1 + f_fss_default_allocation_step_string;

    buffer_position.start = buffer->used;
    buffer_position.stop = buffer->used;

    if (pre_allocate_size > buffer->size) {
      f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size);
      if (F_status_is_error(status)) return status;
    }

    start_position = range->start;

    // if this first slash is followed by a quote, then that quote must be delimited.
    if (content.string[range->start] == f_fss_delimit_slash) {
      buffer->string[buffer_position.stop] = f_fss_delimit_slash;
      buffer_position.stop++;

      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) return status;

      while (range->start <= range->stop && range->start < content.used) {
        if (content.string[range->start] == f_fss_delimit_placeholder) {
          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          continue;
        }

        if (content.string[range->start] != f_fss_delimit_slash) {
          break;
        }

        buffer->string[buffer_position.stop] = f_fss_delimit_slash;
        buffer_position.stop++;

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      if (range->start > range->stop) {
        buffer->string[buffer_position.stop] = ' ';
        buffer->used = buffer_position.stop + 1;
        return F_none_stop;
      }
      else if (range->start >= content.used) {
        buffer->string[buffer_position.stop] = ' ';
        buffer->used = buffer_position.stop + 1;
        return F_none_eos;
      }

      if (content.string[range->start] == f_fss_delimit_single_quote || content.string[range->start] == f_fss_delimit_double_quote) {
        pre_allocate_size++;

        if (pre_allocate_size > buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
          if (F_status_is_error(status)) return status;
        }

        buffer->string[buffer_position.stop] = f_fss_delimit_slash;
        buffer->string[buffer_position.stop + 1] = content.string[range->start];
        buffer_position.stop += 2;

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      }
    }
    else if (content.string[range->start] == f_fss_delimit_single_quote || content.string[range->start] == f_fss_delimit_double_quote) {
      pre_allocate_size++;

      if (pre_allocate_size > buffer->size) {
        f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
        if (F_status_is_error(status)) return status;
      }

      buffer->string[buffer_position.stop] = f_fss_delimit_slash;
      buffer->string[buffer_position.stop + 1] = content.string[range->start];
      buffer_position.stop += 2;

      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    }

    while (range->start <= range->stop && range->start < content.used) {
      if (content.string[range->start] == f_string_eol[0]) {
        buffer->string[buffer_position.stop] = ' ';
        buffer->used = buffer_position.stop + 1;
        return F_none_eol;
      }

      if (content.string[range->start] != f_fss_delimit_placeholder && (status = f_fss_is_space(*buffer, *range)) == F_true) {
        quoted = f_fss_delimit_double_quote;

        pre_allocate_size += 2;

        if (pre_allocate_size > buffer->size) {
          f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
          if (F_status_is_error(status)) return status;
        }

        range->start = start_position;
        buffer_position.stop = buffer_position.start;
        buffer->string[buffer_position.stop] = f_fss_delimit_double_quote;
        buffer_position.stop++;
        break;
      }
      else if (F_status_is_error(status)) {
        return status;
      }

      buffer->string[buffer_position.stop] = content.string[range->start];
      buffer_position.stop++;

      status = f_fss_increment_buffer(*buffer, range, 1);
      if (F_status_is_error(status)) return status;
    } // while

    if (quoted != 0) {
      while (range->start <= range->stop && range->start < content.used) {
        if (content.string[range->start] == f_fss_delimit_slash) {
          f_string_length slash_count = 1;

          buffer->string[buffer_position.stop] = f_fss_delimit_slash;
          buffer_position.stop++;

          status = f_fss_increment_buffer(*buffer, range, 1);
          if (F_status_is_error(status)) return status;

          while (range->start <= range->stop && range->start < content.used) {
            if (content.string[range->start] == f_fss_delimit_placeholder) {
              status = f_fss_increment_buffer(*buffer, range, 1);
              if (F_status_is_error(status)) return status;

              continue;
            }

            if (content.string[range->start] != f_fss_delimit_slash) {
              break;
            }

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer_position.stop++;
            slash_count++;

            status = f_fss_increment_buffer(*buffer, range, 1);
            if (F_status_is_error(status)) return status;
          } // while

          if (content.string[range->start] == quoted || range->start > range->stop || range->start >= content.used) {
            pre_allocate_size += slash_count + 1;

            if (pre_allocate_size > buffer->size) {
              f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
              if (F_status_is_error(status)) return status;
            }

            while (slash_count > 0) {
              buffer->string[buffer_position.stop] = f_fss_delimit_slash;
              buffer_position.stop++;
              slash_count--;
            } // while

            if (range->start > range->stop || range->start >= content.used) {
              break;
            }

            buffer->string[buffer_position.stop] = f_fss_delimit_slash;
            buffer->string[buffer_position.stop + 1] = quoted;
            buffer_position.stop += 2;
          }
          else {
            buffer->string[buffer_position.stop] = content.string[range->start];
            buffer_position.stop++;
          }
        }
        else if (content.string[range->start] == quoted) {
          pre_allocate_size++;

          if (pre_allocate_size > buffer->size) {
            f_macro_string_dynamic_resize(status, (*buffer), pre_allocate_size + f_fss_default_allocation_step_string);
            if (F_status_is_error(status)) return status;
          }

          buffer->string[buffer_position.stop] = f_fss_delimit_slash;
          buffer->string[buffer_position.stop + 1] = quoted;
          buffer_position.stop += 2;
        }
        else if (content.string[range->start] == f_string_eol[0]) {
          buffer->string[buffer_position.stop] = quoted;
          buffer->string[buffer_position.stop + 1] = ' ';
          buffer->used = buffer_position.stop + 2;
          return F_none_eol;
        }
        else if (content.string[range->start] != f_fss_delimit_placeholder) {
          buffer->string[buffer_position.stop] = content.string[range->start];
          buffer_position.stop++;
        }

        status = f_fss_increment_buffer(*buffer, range, 1);
        if (F_status_is_error(status)) return status;
      } // while

      buffer->string[buffer_position.stop] = quoted;
      buffer_position.stop++;
    }

    buffer->string[buffer_position.stop] = ' ';
    buffer->used = buffer_position.stop + 1;

    if (range->start > range->stop) return F_none_stop;
    else if (range->start >= content.used) return F_none_eos;

    return F_none;
  }
#endif // _di_fl_fss_extended_content_write_

#ifdef __cplusplus
} // extern "C"
#endif
