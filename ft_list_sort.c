#include "libft/libft.h"
#include "includes/minishell.h"

int compare_int(int a, int b)
{
	return (a - b);
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

	list = ft_lstnew((void *)3);
	ft_lstadd_back(&list, ft_lstnew((void *)2));
	ft_lstadd_back(&list, ft_lstnew((void *)1));
	printf("%d\n", (int)list->content);
	printf("%d\n", (int)list->next->content);
	printf("%d\n", (int)list->next->next->content);
	//ft_list_sort(&list, strcmp);
	ft_list_sort(&list, compare_int);
	printf("%d\n", (int)list->content);
	printf("%d\n", (int)list->next->content);
	printf("%d\n", (int)list->next->next->content);
	return 0;
}

/*
int main()
{
	t_list *list;
	int a = 3;
	int b = 2;
	int c = 1;
	
	list = ft_lstnew(&a);
	ft_lstadd_back(&list, ft_lstnew(&b));
	ft_lstadd_back(&list, ft_lstnew(&c));
	printf("%d\n", *(int *)list->content);
	printf("%d\n", *(int *)list->next->content);
	printf("%d\n", *(int *)list->next->next->content);
	//ft_list_sort(&list, strcmp);
	ft_list_sort(&list, compare_int);
	printf("%d\n", *(int *)list->content);
	printf("%d\n", *(int *)list->next->content);
	printf("%d\n", *(int *)list->next->next->content);
	return 0;
}
*/