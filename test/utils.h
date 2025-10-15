/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 00:03:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/08/04 00:03:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INC_42_LIBASM_TEST_UTILS_H_
#define INC_42_LIBASM_TEST_UTILS_H_

#include "libasm.h"

int compare_int(void *a, void *b);

void free_list(t_list *head);

int my_strcmp(const void *s1, const void *s2);

#endif