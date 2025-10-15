/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 23:20:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/04/05 23:20:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

#include <sys/types.h>

typedef struct s_list
{
   void *data;
   struct s_list *next;
} t_list;


ssize_t ft_read(int fd, void *buf, size_t count);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dst, const char *src);
char *ft_strdup(const char *s1);
size_t ft_strlen(const char *str);
ssize_t ft_write(int fd, const void *buf, size_t count);

t_list *ft_create_elem(void *data);
void ft_list_push_front(t_list **begin_list, void *data);
int ft_list_size(t_list *begin_list);
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void ft_list_sort(t_list **begin_list, int (*cmp)());
int ft_atoi_base(char *str, char *base);
#endif