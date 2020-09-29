#include "libft/libft.h"
#include "includes/minishell.h"

size_t		max_len(size_t len_a, size_t len_b)
{
	if (len_a > len_b)
		return(len_a);
	return(len_b);
}

int		compare_key(t_envar *a, t_envar *b)
{
	return(ft_strncmp(a->key, b->key, max_len(ft_strlen(a->key), ft_strlen(b->key))));
}

int		first_swap(t_list **iter1, t_list **iter2)
{
	struct s_list *tmp = NULL;

	tmp = *iter1;
	(*iter1)->next = (*iter2)->next;
	(*iter2)->next = tmp;
	return 2;
}

int		swap(t_list **iter0, t_list **iter1, t_list **iter2)
{
	struct s_list *tmp = NULL;

	tmp = (*iter0)->next;
	(*iter0)->next = (*iter1)->next;
	(*iter1)->next = (*iter2)->next;
	(*iter2)->next = tmp;
	return 1;
}

void		ft_list_sort(t_list **begin_list, int (*cmp)())
{
	int i = 0;
	int swp = 0;
	t_list *iter0;
	t_list *iter1;
	t_list *iter2;

	if (!(*begin_list) || !(*begin_list)->next)
		return ;
	iter0 = *begin_list;
	while (iter0)
	{
		iter0 = iter0->next;
		i++;
	}
	while (i > 1)
	{
		iter0 = NULL;
		iter1 = *begin_list;
		iter2 = iter1->next;
		while (iter2)
		{
			if(cmp(iter1->content, iter2->content) > 0)
			{
				if (!iter0)
					swp = first_swap(&iter1, &iter2);
				else
					swp = swap(&iter0, &iter1, &iter2);
			}
			if (!swp)
			{
				iter0 = iter1;
				iter1 = iter1->next;
				iter2 = iter2->next;
			}
			else
			{
				iter0 = iter2;
				iter1 = iter2->next;
				iter2 = iter1->next;
			}
			if (swp == 2)
				*begin_list = iter0;
			swp = 0;
		}
		i--;
	}
}

int main()
{
	t_list *list;

	t_envar first = {"xyz", "999"};
	t_envar second = {"def", "555"};
	t_envar last = {"abc", "000"};
	list = ft_lstnew((void *)&first);
	ft_lstadd_back(&list, ft_lstnew((void *)&second));
	ft_lstadd_back(&list, ft_lstnew((void *)&last));
	printf("%s\n", ((t_envar *)list->content)->key);
	printf("%s\n", ((t_envar *)list->next->content)->key);
	printf("%s\n", ((t_envar *)list->next->next->content)->key);
	//ft_list_sort(&list, strcmp);
	ft_list_sort(&list, compare_key);
	printf("%s\n", ((t_envar *)list->content)->key);
	printf("%s\n", ((t_envar *)list->next->content)->key);
	printf("%s\n", ((t_envar *)list->next->next->content)->key);
	return 0;
}
