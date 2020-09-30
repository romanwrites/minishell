/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:33:29 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/30 16:36:47 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_echo(char *str, int flag_n) //"" '' \n \t \0!!!!!!!!!!!!!!!!!!!!!!!!!
{
	write(1, str, ft_strlen(str));
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_exit(int exit_code)
{
	//ft_lstclear()
	exit(exit_code);
}

void	ft_pwd()
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

void	ft_cd(char *str)
{
	DIR *dir;
	struct dirent *entry;
	
	dir = NULL;
	dir = opendir(str);
	if (!dir)
	{
		write(1, "cd: ", ft_strlen("cd: "));
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, ": ", ft_strlen(": "));
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return ;
	}
	closedir(dir);
	ft_pwd();//
	chdir(str);
	ft_pwd();//
}

void	ft_env()
{
	t_list *list;

	list = g_list;
	while(list)
	{
		write(1, ((t_envar *)list->content)->key, ft_strlen(((t_envar *)list->content)->key));
		write(1, "=", 1);
		write(1, ((t_envar *)list->content)->value, ft_strlen(((t_envar *)list->content)->value));
		write(1, "\n", 1);
		list = list->next;
	}
}
/*
void	free_env(char **env_array, int lines)
{
	while (lines >= 0)
	{
		free(env_array[lines]);
		lines--;
	}
	free(env_array);
}

char	**alloc_mem_env(int lines, int max_len, char *arg)
{
	char	**env_array;
	int		i;

	i = 0;

	env_array = (char **)malloc(sizeof(char *) * lines + 1);
	if (!env_array)
		return (env_array);
	while (i < lines)
	{
		env_array[i] = malloc(max_len + 1);
		if (!(env_array[i]))
		{
			free_env(env_array, i);
			return(NULL);
		}
		i++;
	}
	return(env_array);
}

void	fill_env(char **env_array, char *arg)
{
	char	**env;
	
	env = g_envp;
	while((*env))
	{
		ft_strlcat((*env_array), (*env), ft_strlen(*env) + 1);
		env_array++;
		env++;
	}
	if (arg)
	{
		ft_strlcat((*env_array), arg, ft_strlen(arg) + 1);
		env_array++;
	}
	*env_array = NULL;
}

void	sort_env(char **env_array, int lines, int max_len)
{
	char *tmp;
	int i;

	i = 0;
	while(lines > 1)
	{
		while  (i < lines - 1)
		{
			if (ft_strncmp(env_array[i], env_array[i + 1], max_len) > 0)
			{
				tmp = env_array[i];
				env_array[i] = env_array[i + 1];
				env_array[i + 1] = tmp;
			}
			i++;
		}
		i = 0;
		lines--;
	}
}

void	print_env(char **env_array)
{
	while (*env_array)
	{
		write(1, *env_array, ft_strlen(*env_array));
		write(1, "\n", 1);
		env_array++;
	}
}

void	count_lines(int *lines, int *max_len, char *arg)
{
	char	**env;

	env = g_envp;
	while((*env))
	{
		*max_len = (*max_len > ft_strlen(*env)) ? *max_len : ft_strlen(*env);
		env++;
		(*lines)++;
	}
	if (arg)
		(*lines)++;
}
*/

void	ft_export(char *arg) //handle ='' & many varS using ft_split(' ')
{
	//char	**env_array;
	//int		lines;
	//int		max_len;

	//lines = 0;
	//max_len = 0;
	//env_array = NULL;

	//count_lines(&lines, &max_len, arg);
	//env_array = alloc_mem_env(lines, max_len, arg);
	//if (env_array == NULL)
	//	return ;
	//fill_env(env_array, arg);
	//sort_env(env_array, lines, max_len);
	//print_env(env_array);
	//free_env(env_array, lines);//place at EXIT

	t_list	*list;
	t_envar kv[256];
	int		i;
	char	**pair;
	char	*value;
	int		value_flag;
	
	list = g_list;
	pair = ft_split(arg, ' ');
	i = 0;
	value_flag = 0;
	while(*pair)
	{
		value = ft_strchr(*pair, '=');
		if (value == NULL || value + 1 == '\0')
		{
			kv[i].value = ft_strdup("''");
			value_flag = 1;
		}
		else
			kv[i].value = ft_strdup(++value);//???
		if (!kv[i].value)
			return ;//what to do if malloc fails
		if (!value_flag)
			kv[i].key = malloc(ft_strlen(*pair) - ft_strlen(kv[i].value));
		else
			kv[i].key = malloc(ft_strlen(*pair) + 1);
		if (!kv[i].key)
			return ;//what to do if malloc fails
		if (!value_flag)
			ft_strlcpy(kv[i].key, *pair, ft_strlen(*pair) - ft_strlen(kv[i].value));
		else
			ft_strlcpy(kv[i].key, *pair, ft_strlen(*pair) + 1);
		if (!list)
			list = ft_lstnew((void *)&(kv[i]));
		else
			ft_lstadd_back(&list, ft_lstnew((void *)&(kv[i])));
		pair++;
		i++;
		value_flag = 0;
	}
	ft_list_sort(&list, compare_key);
	while(list)
	{
		write(1, ((t_envar *)list->content)->key, ft_strlen(((t_envar *)list->content)->key));
		write(1, "=", 1);
		write(1, ((t_envar *)list->content)->value, ft_strlen(((t_envar *)list->content)->value));
		write(1, "\n", 1);
		list = list->next;
	}
}

void	ft_unset(char *arg) //revome varS
{
	if (!arg)
	{
		write(1, "unset: not enough arguments", ft_strlen("unset: not enough arguments"));
		write(1, "\n", 1);
	}
	else if (ft_strchr(arg, '.') || ft_strchr(arg, '~') || ft_strchr(arg, ',') || ft_strchr(arg, '@') || ft_strchr(arg, '#') || ft_strchr(arg, '%') || ft_strchr(arg, '^') || ft_strchr(arg, '-') || ft_strchr(arg, '+') || ft_strchr(arg, '=') || ft_strchr(arg, '{') || ft_strchr(arg, '}') || ft_strchr(arg, '[') || ft_strchr(arg, ']'))
	{
		write(1, "unset: ", ft_strlen("unset: "));
		write(1, arg, ft_strlen("arg"));//HEL.L -> HEL
		write(1, ": ", ft_strlen(": "));
		write(1, "invalid parameter name", ft_strlen("invalid parameter name"));
		write(1, "\n", 1);
	}
}

t_list	*env_to_list(char **envp)
{
	char	**env;
	char	*value;
	t_list	*list;
	t_envar	kv[256];//WHY NOT 32??
	int i;

	env = envp;
	list = NULL;
	i = 0;
	while (*env)
	{
		value = ft_strchr(*env, '=');
		value++;
		kv[i].key = malloc(ft_strlen(*env) - ft_strlen(value));
		if (!kv[i].key)
			return (NULL);
		ft_strlcpy(kv[i].key, *env, ft_strlen(*env) - ft_strlen(value));
		kv[i].value = ft_strdup(value);
		if (!kv[i].value)
			return (NULL);
		if (!list)
			list = ft_lstnew((void *)&(kv[i]));
		else
			ft_lstadd_back(&list, ft_lstnew((void *)&(kv[i])));
		env++;
		i++;
		//printf("LIST: %s=%s\n", ((t_envar *)list->content)->key, ((t_envar *)list->content)->value);
	}
	return(list);
}

void	free_content(t_envar *content) //should be pointed be del() in ft_lstclear()
{
	free(content->key);
	free(content->value);
}
