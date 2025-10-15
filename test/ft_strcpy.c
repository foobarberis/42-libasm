/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:35:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/04 16:35:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libasm.h"
#include "utest.h"

UTEST(ft_strcpy, empty_string) {
  char s1[] = "";
  char s2[100];
  char s3[100];
  ASSERT_EQ(ft_strcpy(s2, s1), s2);
  ASSERT_EQ(strcpy(s3, s1), s3);
  ASSERT_STREQ(s1, s3);
}

UTEST(ft_strcpy, simple_string) {
  char s1[] = "1";
  char s2[100];
  char s3[100];
  ASSERT_EQ(ft_strcpy(s2, s1), s2);
  ASSERT_EQ(strcpy(s3, s1), s3);
  ASSERT_STREQ(s1, s3);
}

UTEST(ft_strcpy, odd_string) {
  char s1[] = "something";
  char s2[100];
  char s3[100];
  ASSERT_EQ(ft_strcpy(s2, s1), s2);
  ASSERT_EQ(strcpy(s3, s1), s3);
  ASSERT_STREQ(s1, s3);
}

UTEST(ft_strcpy, even_string) {
  char s1[] = "something1";
  char s2[100];
  char s3[100];
  ASSERT_EQ(ft_strcpy(s2, s1), s2);
  ASSERT_EQ(strcpy(s3, s1), s3);
  ASSERT_STREQ(s1, s3);
}

UTEST(ft_strcpy, long_string) {
  char s1[] = "This is a long string with a lot of characters";
  char s2[100];
  char s3[100];
  ASSERT_EQ(ft_strcpy(s2, s1), s2);
  ASSERT_EQ(strcpy(s3, s1), s3);
  ASSERT_STREQ(s1, s3);
}
