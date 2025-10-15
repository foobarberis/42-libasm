/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:03:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/04 00:03:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "libasm.h"

int compare_int(void *a, void *b) {
  return (*(int *)a - *(int *)b);
}

void free_list(t_list *head) {
  t_list *tmp;
  while (head) {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}

int my_strcmp(const void *s1, const void *s2) {
  if (s1 == NULL || s2 == NULL) {
    return 1;
  }
  return strcmp(s1, s2);
}
