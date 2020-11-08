/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/11/06 15:54:13 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static _Bool	is_invalid_char_unset(char *arg)
{
	size_t		len;
	size_t		i;

	len = ft_strlen(".~,@#%^-+={}[]");
	i = 0;
	while (i < len)
	{
		if ((ft_strchr(arg, ".~,@#%^-+={}[]"[i])))
			return (1);
		i++;
	}
	if (!ft_strcmp(g_home, arg))
		return (1);
	return (0);
}

static void		put_not_a_valid_identifier(char *arg)
{
	ft_putstr_fd("bash: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	g_exit = 1;
}

static	int		check_args(char **arg)
{
	int i;

	i = 1;
	while (arg[i])
	{
		if (is_invalid_char_unset(arg[i]))
		{
			put_not_a_valid_identifier(arg[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void		del_node(t_list **env_key_value, char **keys, \
									int *first, t_list **prev)
{
	t_list *temp;

	temp = *env_key_value;
	if (!ft_strcmp(((t_envar *)temp->content)->key, *keys) && !*first)
	{
		*env_key_value = (*env_key_value)->next;
		free(((t_envar *)(temp->content))->key);
		free(((t_envar *)(temp->content))->value);
		free(temp->content);
		free(temp);
		(*prev)->next = *env_key_value;
	}
	else if (!ft_strcmp(((t_envar *)temp->content)->key, *keys) && *first)
	{
		*env_key_value = (*env_key_value)->next;
		free(((t_envar *)(temp->content))->key);
		free(((t_envar *)(temp->content))->value);
		free(temp->content);
		free(temp);
	}
	if (!*first)
		*prev = *env_key_value;
	*first = 0;
	if (*env_key_value)
		*env_key_value = (*env_key_value)->next;
}

void			ft_unset(char **arg)
{
	char		**keys;
	t_list		*env_key_value;
	t_list		*prev;
	int			first;

	keys = arg;
	keys++;
	if (arg[1])
	{
		if (check_args(arg))
			return ;
		while (keys && *keys)
		{
			env_key_value = g_env;
			prev = env_key_value;
			first = 1;
			while (env_key_value)
				del_node(&env_key_value, keys, &first, &prev);
			keys++;
		}
	}
}
