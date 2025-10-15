#include <string.h>
#include "libasm.h"
#include "utest.h"

UTEST(ft_strlen, empty_string) {
  char string[] = "";
  ASSERT_EQ(ft_strlen(string), strlen(string));
}

UTEST(ft_strlen, odd_string) {
  char string[] = "something";
  ASSERT_EQ(ft_strlen(string), strlen(string));
}

UTEST(ft_strlen, even_string) {
  char string[] = "something1";
  ASSERT_EQ(ft_strlen(string), strlen(string));
}

UTEST(ft_strlen, simple_string) {
  char string[] = "1";
  ASSERT_EQ(ft_strlen(string), strlen(string));
}
