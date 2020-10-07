/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 17:38:07 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/29 22:44:28 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        check_common(char *str)
{
     if (str)
     {
         if (str[0] == ';' || str[1] == '|' || str[ft_strlen(str)] == '|' || str[ft_strlen(str)] == ';')
         {
             exit_error_message("Bad syntax. check_common()");
         }
     }
}

_Bool		is_valid_syntax(char pre, char cur, char next)
{
	if (cur == '|' && (pre == '|' || next == '|' || pre == '<' ||  pre == '>' ||  next == '<' || next == '>' || !pre || !next))
		return (0);
	else if (cur == '>' && (pre == '|' || next == '|' || pre == '<' || next == '<' || !pre || !next))
		return (0);
	else if (cur == '<' && (pre == '|' || next == '|' || pre == '>' || next == '>' || !pre || !next))
		return (0);
	return (1);
}

_Bool		is_redir_or_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void		set_nl_cpy(char **str, int i)
{
	char 	*tmp;
	char	*new;

	tmp = *(str);
	new = malloc(ft_strlen(tmp) + 2);
	ft_alloc_check(new);
	ft_memcpy(new, tmp, i);
	new[i] = '\n';
	ft_memcpy(new + i + 1, tmp + i, ft_strlen(tmp) - i + 2);
	free(tmp);
	*(str) = new;
}

char		**split_command(t_mshell *sv, char *str)
{
	int 	i;
	char	**split_by_command;

	i = 0;
	while (str[i])
	{
		set_backslash_state(sv->state, str[i], i);
		set_quotes_state(sv, sv->state, i, str);
		if (is_any_quote_open(sv->state))
		{
			i++;
			continue ;
		}
		if ((str[i] == ' ' || str[i] == '\t') && !is_backslash_pressed(sv->state))
			str[i] = '\n';
		else if (i > 0 && (str[i] == '|' || str[i] == '<' || str[i] == '>') && \
				(is_valid_syntax(str[i - 1], str[i], str[i + 1])) && \
				(str[i - 1] != '\n'))
		{
			set_nl_cpy(&str, i);
			i++;
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			exit_error_message("bad syntax");
		else if (i > 0 && str[i] != ' ' && str[i] != 34 && str[i] != 39 && is_redir_or_pipe(str[i - 1]))
		{
			set_nl_cpy(&str, i);
			i++;
		}
		i++;
	}
	split_by_command = ft_split(str, '\n');
	ft_alloc_check(split_by_command);
	return (split_by_command);
}

void		parse_start(t_mshell *sv)
{
	char	*tmp;
	char	**semicolons2d;
	static int case_num;
	case_num++;
//	split_sh(sv);  Make one function to split elegantly

	// STEP 0: trim
	char	*input_str = ft_strtrim(sv->content, " \t");
	ft_alloc_check(input_str);
	printf("\ncase: %d, str: [%s]\nafter split by semicolons:\n", case_num, input_str);
    check_common(input_str);
	// STEP 1.0: split by semicolons
	semicolons2d = split_by_char(sv, ';', input_str);
	ft_trim_2d(&semicolons2d);

	print_2d_array(semicolons2d);
    printf("\nDONE\n\nnext split by pipes:\n\n");

	t_dlist	*dlst;
    t_dlist	*dlst_head;
	void	*tmp_ptr2d;
	int j = 0;

	dlst = ft_dlstnew(NULL, NULL);
	ft_alloc_check(dlst);

    dlst_head = dlst;
	while (semicolons2d[j])
	{
		state_bzero(sv->state);
		tmp_ptr2d = (void *)split_command(sv, semicolons2d[j]);
//		ft_alloc_check(tmp_ptr2d);
		dlst->content = (void *)ft_dlstnew(tmp_ptr2d, NULL);
        tmp_ptr2d = NULL;
        char **ptr = (char **)((t_dlist *)dlst->content)->content;
        ft_trim_2d(&ptr);
		print_2d_array((char **)((t_dlist *)dlst->content)->content);
		dlst->next = ft_dlstnew(NULL, NULL);
		dlst = dlst->next;
		j++;
	}
	ft_free2d(semicolons2d);
	semicolons2d = NULL;

//	char	**pipes1 = split_by_char(sv, '|', semicolons2d[j]);
//	print_2d_array(pipes1);


//	// STEP 1: split by quotes
//	printf("case: %d, str: %s\nafter split by quotes:\n", case_num, sv->content);
//	quotes2d = split_by_quotes(sv);
//	print_2d_array(quotes2d);
//	ft_putchar('\n');
//
//	// STEP 2: trim
//	ft_trim_2d(&quotes2d);
//	print_2d_array(quotes2d);
//	ft_putchar('\n');
//
//	// STEP 3: split by semicolons
//
//	ft_free2d(quotes2d);
}