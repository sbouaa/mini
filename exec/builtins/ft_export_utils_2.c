/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:12:56 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/28 20:13:19 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

t_env	*ft_sort_env(t_env *env)
{
	t_env	*sorted;
	t_env	*ptr;
	t_env	*next;

	sorted = copy_env(env);
	if (!sorted)
		return (NULL);
	ptr = sorted;
	while (ptr)
	{
		next = ptr->next;
		while (next)
		{
			if (ft_strcmp(ptr->key, next->key) > 0)
				swap_env(ptr, next);
			next = next->next;
		}
		ptr = ptr->next;
	}
	return (sorted);
}

char	*expand_var_value(char *value, t_env *env)
{
	t_env	*var;

	if (!value || value[0] != '$')
		return (ft_strdup_env(value));
	var = ft_search_env(value + 1, env);
	if (!var || !var->value)
		return (ft_strdup_env(""));
	return (ft_strdup_env(var->value));
}
