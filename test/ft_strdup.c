/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:43:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/04 16:43:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libasm.h"
#include "utest.h"

UTEST(ft_strdup, empty_string) {
  char s1[] = "";
  char *s2 = ft_strdup(s1);
  ASSERT_STREQ(s1, s2);
  free(s2);
}

UTEST(ft_strdup, simple_string) {
  char s1[] = "1";
  char *s2 = ft_strdup(s1);
  ASSERT_STREQ(s1, s2);
  free(s2);
}

UTEST(ft_strdup, odd_string) {
  char s1[] = "something";
  char *s2 = ft_strdup(s1);
  ASSERT_STREQ(s1, s2);
  free(s2);
}

UTEST(ft_strdup, even_string) {
  char s1[] = "something1";
  char *s2 = ft_strdup(s1);
  ASSERT_STREQ(s1, s2);
  free(s2);
}

UTEST(ft_strdup, long_string) {
  char s1[] = "This is a long string with a lot of characters";
  char *s2 = ft_strdup(s1);
  ASSERT_STREQ(s1, s2);
  free(s2);
}
