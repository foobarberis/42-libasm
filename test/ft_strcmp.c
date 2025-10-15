/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:42:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/04 14:42:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libasm.h"
#include "utest.h"

static int32_t normalized_strcmp(const char *s1, const char *s2);
static int32_t normalized_ft_strcmp(const char *s1, const char *s2);
static int32_t normalize_cmp(int32_t strcmp_return);

UTEST(ft_strcmp, empty_string) {
  char s1[] = "";
  char s2[] = "";
  ASSERT_EQ(normalized_ft_strcmp(s1, s2), normalized_strcmp(s1, s2));
  ASSERT_EQ(normalized_ft_strcmp(s2, s1), normalized_strcmp(s2, s1));
}

UTEST(ft_strcmp, upper_string) {
  char s1[] = "SOMETHING";
  char s2[] = "something";
  ASSERT_EQ(normalized_ft_strcmp(s1, s2), normalized_strcmp(s1, s2));
  ASSERT_EQ(normalized_ft_strcmp(s2, s1), normalized_strcmp(s2, s1));
}

UTEST(ft_strcmp, even_string) {
  char s1[] = "SOMETHING1";
  char s2[] = "something1";
  ASSERT_EQ(normalized_ft_strcmp(s1, s2), normalized_strcmp(s1, s2));
  ASSERT_EQ(normalized_ft_strcmp(s2, s1), normalized_strcmp(s2, s1));
}

UTEST(ft_strcmp, simple_string) {
  char s1[] = "1";
  char s2[] = "2";
  ASSERT_EQ(normalized_ft_strcmp(s1, s2), normalized_strcmp(s1, s2));
  ASSERT_EQ(normalized_ft_strcmp(s2, s1), normalized_strcmp(s2, s1));
}

UTEST(ft_strcmp, long_string) {
  char s1[] = "This is a long string with a lot of characters";
  char s2[] = "This is a long string with a lot of characters";
  ASSERT_EQ(normalized_ft_strcmp(s1, s2), normalized_strcmp(s1, s2));
  ASSERT_EQ(normalized_ft_strcmp(s2, s1), normalized_strcmp(s2, s1));
}

UTEST(ft_strcmp, long_string_diff) {
  char s1[] = "This is a long string with a lot of characters";
  char s2[] = "This is a long string with a lot of characters!";
  ASSERT_EQ(normalized_ft_strcmp(s1, s2), normalized_strcmp(s1, s2));
  ASSERT_EQ(normalized_ft_strcmp(s2, s1), normalized_strcmp(s2, s1));
}

static int32_t normalized_strcmp(const char *s1, const char *s2) {
  return (normalize_cmp(strcmp(s1, s2)));
}

static int32_t normalized_ft_strcmp(const char *s1, const char *s2) {
  return (normalize_cmp(ft_strcmp(s1, s2)));
}

static int32_t normalize_cmp(int32_t strcmp_return) {
  if (strcmp_return < 0) {
    return -1;
  } else if (strcmp_return > 0) {
    return 1;
  } else {
    return 0;
  }
}
