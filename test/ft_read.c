/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/04 17:28:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libasm.h"
#include "utest.h"

UTEST(ft_read, empty_string) {
  char s[] = "";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(write(fds[1], s, sizeof(s)), -1, "write() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(s));
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_read, simple_string) {
  char s[] = "1";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(write(fds[1], s, sizeof(s)), -1, "write() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(s));
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_read, odd_string) {
  char s[] = "something";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(write(fds[1], s, sizeof(s)), -1, "write() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(s));
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_read, even_string) {
  char s[] = "something1";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(write(fds[1], s, sizeof(s)), -1, "write() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(s));
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_read, long_string) {
  char s[] = "This is a long string with a lot of characters";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(write(fds[1], s, sizeof(s)), -1, "write() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(s));
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s));
  ASSERT_EQ(errno, 0);
  ASSERT_STREQ(s, buf);
}

UTEST(ft_read, long_string_partial) {
  char s[] = "This is a long string with a lot of characters";
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(write(fds[1], s, sizeof(s)), -1, "write() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(s) - 1);
  ASSERT_GE(return_code, 0);
  ASSERT_EQ((size_t)return_code, sizeof(s) - 1);
  ASSERT_EQ(errno, 0);
  buf[sizeof(s) - 1] = '\0';
  ASSERT_STREQ(s, buf);
}

UTEST(ft_read, invalid_fd) {
  char buf[100];
  errno = 0;
  ssize_t return_code = ft_read(-1, buf, sizeof(buf));
  ASSERT_EQ(return_code, -1);
  ASSERT_EQ(errno, EBADF);
}

UTEST(ft_read, close_fd) {
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  ASSERT_NE_MSG(close(fds[0]), -1, "close() failed");
  errno = 0;
  char buf[100];
  ssize_t return_code = ft_read(fds[0], buf, sizeof(buf));
  ASSERT_EQ(return_code, -1);
  ASSERT_EQ(errno, EBADF);
}

UTEST(ft_read, invalid_buf_with_EOF) {
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ASSERT_NE_MSG(close(fds[1]), -1, "close() failed");
  ssize_t return_code = ft_read(fds[0], NULL, 100);
  ASSERT_EQ(return_code, 0);
  ASSERT_EQ(errno, 0);
}

UTEST(ft_read, invalid_buf) {
  int fds[2];
  ASSERT_NE_MSG(pipe(fds), -1, "pipe() failed");
  errno = 0;
  ASSERT_NE_MSG(write(fds[1], "1", 1), -1, "write() failed");
  ASSERT_NE_MSG(close(fds[1]), -1, "close() failed");
  ssize_t return_code = ft_read(fds[0], NULL, 100);
  ASSERT_EQ(return_code, -1);
  ASSERT_EQ(errno, EFAULT);
}
