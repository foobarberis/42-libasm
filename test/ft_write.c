/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:55:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/04 16:55:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "utest.h"

UTEST(ft_write, empty_string) {
  char s[] = "";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], s, sizeof(s));
  char buf[100];
  ASSERT_NE_MSG(read(fds[0], buf, sizeof(s)), -1, "read() failed");
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_write, simple_string) {
  char s[] = "1";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], s, sizeof(s));
  char buf[100];
  ASSERT_NE_MSG(read(fds[0], buf, sizeof(s)), -1, "read() failed");
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_write, odd_string) {
  char s[] = "something";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], s, sizeof(s));
  char buf[100];
  ASSERT_NE_MSG(read(fds[0], buf, sizeof(s)), -1, "read() failed");
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_write, even_string) {
  char s[] = "something1";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], s, sizeof(s));
  char buf[100];
  ASSERT_NE_MSG(read(fds[0], buf, sizeof(s)), -1, "read() failed");
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_write, long_string) {
  char s[] = "This is a long string with a lot of characters";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], s, sizeof(s));
  char buf[100];
  ASSERT_NE_MSG(read(fds[0], buf, sizeof(s)), -1, "read() failed");
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_write, invalid_fd) {
  char s[] = "This is a long string with a lot of characters";
  errno = 0;
  ssize_t return_code = ft_write(-1, s, sizeof(s));
  ASSERT_EQ(return_code, -1);
  ASSERT_EQ(errno, EBADF);
}

UTEST(ft_write, close_fd) {
  char s[] = "This is a long string with a lot of characters";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(close(fds[1]), -1, "close() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], s, sizeof(s));
  ASSERT_EQ(return_code, -1);
  ASSERT_EQ(errno, EBADF);
}

UTEST(ft_write, invalid_buf) {
  char s[] = "This is a long string with a lot of characters";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ssize_t return_code = ft_write(fds[1], NULL, sizeof(s));
  ASSERT_EQ(return_code, -1);
  ASSERT_EQ(errno, EFAULT);
}
