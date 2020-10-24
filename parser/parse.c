/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/10/21 16:59:48 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        append_line(char **ptr, char **append_this)
{
    char    *tmp_ptr;
    char    *new_line;
    char    *tmp_append;

    tmp_ptr = *(ptr);
    new_line = ft_strjoin(tmp_ptr, *(append_this));
    ft_alloc_check(new_line);
    free(tmp_ptr);
    tmp_ptr = NULL;
    *(ptr) = new_line;
    tmp_append = *(append_this);
    free(tmp_append);
    *(append_this) = NULL;
    new_line = NULL;
}

size_t		len_without_newlines(const char *ptr)
{
	size_t	i;
	size_t 	j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] != '\n')
			j++;
		i++;
	}
	return (j);
}



t_token		*alloc_token_list(char **ptr)
{
	t_token	*token;
	t_token	*head;
	int 	i;

	i = 0;
	token = token_new(ptr[i], NULL);
	ft_alloc_check(token);
	head = token;
	while (ptr[++i])
	{
		token->next = token_new(ptr[i], &token);
		ft_alloc_check(token->next);
		token = token->next;
	}
	return (head);
}

t_dlist_pipe	*alloc_pipe_list(char **ptr)
{
	int 		i;
	char 		**tmp_cmd;
	char 		**trim_cmd;
	t_token		*token;
	t_dlist_pipe	*pipe;
	t_dlist_pipe	*head;

	i = 0;
	tmp_cmd = NULL;
	pipe = pipe_new(NULL, NULL);
	ft_alloc_check(pipe);
	head = pipe;
	while (ptr[i])
	{
		tmp_cmd = split_command(ptr[i]);
		ft_alloc_check(tmp_cmd);
		trim_cmd = ft_trim_2d_cpy(tmp_cmd);
		token = alloc_token_list(trim_cmd);
		ft_alloc_check(token);
		ft_free2d(tmp_cmd);
		tmp_cmd = NULL;
		pipe->token = token;
		if (ptr[i + 1])
		{
			pipe->next = pipe_new(NULL, &pipe);
			ft_alloc_check(pipe->next);
			pipe = pipe->next;
		}
		i++;
	}
	return (head);
}

t_dlist_sh			*get_sh_list(char **semicolons2d)
{
	t_dlist_pipe	*dlst_pipe;
	t_dlist_sh		*sh;
	t_dlist_sh		*sh_head;
	char			**tmp_semi;
	int 			i;
	char 			**trim_tmp_semi;

	i = 0;
	sh = sh_new(NULL, NULL);
	ft_alloc_check(sh);
	sh_head = sh;
	tmp_semi = NULL;
	while (semicolons2d[i])
	{
		tmp_semi = split_by_char(PIPE, semicolons2d[i]);//todo alloc
		ft_alloc_check(tmp_semi);
		trim_tmp_semi = ft_trim_2d_cpy(tmp_semi);//todo alloc
		ft_free2d(tmp_semi);
		dlst_pipe = alloc_pipe_list(trim_tmp_semi);//todo alloc
		ft_free2d(trim_tmp_semi);
		tmp_semi = NULL;
		sh->tdlst_pipe = dlst_pipe;
		if (semicolons2d[i + 1])
		{
			sh->next = sh_new(NULL, NULL);//todo alloc
			ft_alloc_check(sh->next);
			sh = sh->next;
		}
		i++;
	}
	return (sh_head);
}

_Bool			check_redirs_only(const char *str)
{
	if (!(ft_strcmp(">>", str)) || !(ft_strcmp(">", str)) || \
		!(ft_strcmp("<", str)) || !(ft_strcmp("<", str)))
	{
		printf("WTF: [%s]\n", str);
		return (1);
	}

	return (0);
}

_Bool			check_syntax_2d(char **ptr)
{
	int			i;

	i = 0;
	while (ptr[i])
	{
		if (check_redirs_only(ptr[i]))
			return (1);
		i++;
	}
	return (0);
}

_Bool		parse_input(char *str, t_mshell *sv)
{
	char	**semicolons2d;
	char	*input_str;
	char	**trim_semi;

	init_globs();
	input_str = ft_strtrim(str, " ");//todo alloc
	ft_alloc_check(input_str);
	if (check_syntax_errors(input_str))
	{
		print_error("syntax error");
		g_exit = 258;
		return (1);
	}
	semicolons2d = split_by_char(SEMICOLON, input_str);//todo alloc
	ft_alloc_check(semicolons2d);
	free(input_str);
	int			i;

	i = 0;
	while (semicolons2d[i])
	{
		printf("SUK: %s\n", semicolons2d[i]);
		i++;
	}
	if (check_syntax_2d(semicolons2d))
	{
		print_error("syntax error");
		g_exit = 258;
		return (1);
	}
	trim_semi = ft_trim_2d_cpy(semicolons2d);//todo alloc
	init_globs();
	sv->sh = get_sh_list(trim_semi);//todo alloc
	ft_free2d(semicolons2d);
	semicolons2d = NULL;
	return (0);
}
