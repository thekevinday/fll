/**
 * FLL - Level 0
 *
 * Project: Iki
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides a Wiki-Like syntax meant to be much simpler.
 *
 * This simpler Wiki-Like syntax, called Iki, focuses just on simply adding context.
 * The context itself is not explicitly define but a few common standards are provided.
 *
 * The example syntax:
 *   - url:"http:// a b c/"
 *   - code:" code goes here"
 *   - quote:"This is a quote"
 *   - var:"some_variable_name"
 *   - emphasis:"This text is important"
 *
 * Which is: (word character, no whitespace, '-', '_', and '+')(colon ':')(quote, either single (') or double ("))(anything goes and closing quotes must be escaped)(closing quote, must match openening quote)
 *
 * Escaping only needs to be done like these three cases:
 * 1) escaping main syntax:
 *   - url\:"http:// a b c/"
 *   - after the first '\:', every '\' is a literal '\'.
 *     - url\\\\\:"http:// a b c/" would be read as: 'url\\\\:"http:// a b c/"'.
 * 2) escaping the quoted part, but only for the closing quote that matches the opening quote:
 *   - quote:"This is a \"quote\""
 *   - There is no way to know the terminating quote so all quotes matching the opening quote inside must be escaped.
 *     - emphasis:"\"This is some Text with a slash before quote: \\\"" would be read as: emphasis, with value: "This is some Text with a slash before quote: \".
 * - Create this as a new FSS format, FSS-Text (FSS-000D).
 *
 * IKI-0000 (Basic) provides the following vocabulary:
 *   - emphasis: Providing emphasis on text, such as bold.
 *   - code: Representing code (formatting preserved or otherwise presented literally).
 *   - quote: Representing quoted text.
 *   - uri: Representing a URI (This is a superset of URL and URN).
 *   - url: Representing a URL.
 *   - urn: Representing a URN.
 *   - var: Representing a variable name.
 *
 * IKI-0001 (Variable) provides the following vocabulary:
 *   - var: Representing a variable name.
 *
 * This is intended to also be used by FSS-Iki_Text (FSS-000D), which focuses on the format and not the context.
 * Wherease, IKI-0000 (Basic) represents the vocabulary and its respective context.
 * Therefore an FSS-000D may have any IKI-???? format within it.
 *
 * A format header such as "# fss-000d iki-0001\n" would represent an IKI format of IKI-0001 (Variable).
 */
#ifndef _F_iki_h
#define _F_iki_h

// libc includes
#include <stdio.h>
#include <sys/stat.h>

// fll-0 includes
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_iki_h
