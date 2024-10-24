/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebrani <asebrani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 20:20:17 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/23 21:29:26 by asebrani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*ft_lstnew(char *content)
{
	t_node	*head;

	head = c_malloc(sizeof(t_node), 1);
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

t_node	*ft_lstlast(t_node *lst)
{
	t_node	*last;

	if (!lst)
		return (NULL);
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

int	ft_lstsize(t_node *lst)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = lst;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// int	iss_space(int c)
// {
// 	return (c == 32 || (c >= 9 && c <= 13));
// }

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (is_space(((char* )str)))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (result > 922337203685477580
			|| (result == 922337203685477580 && *str - '0' > 7))
			return (-1 * (sign == 1));
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (result * sign);
}

static int	ft_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size = 1;
	while (n)
	{
		size += 1;
		n /= 10;
	}
	return (size);
}

static char	*ft_printy(char *u, int b, long nbr)
{
	while (nbr)
	{
		u[--b] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (u);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ptr;
	long	nb;

	count = ft_size(n);
	nb = n;
	ptr = c_malloc(count + 1, 1);
	if (ptr == 0)
		return (0);
	ptr[count] = '\0';
	if (nb == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0' ;
		return (ptr);
	}
	if (nb < 0)
	{
		nb *= -1;
		ptr[0] = '-';
	}
	ptr = ft_printy(ptr, count, nb);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	sizetotal = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = c_malloc(sizeof(char) * (sizetotal + 1), 1);
	if (!res || !s1 || !s2)
		return (NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[sizetotal] = 0;
	return (res);
}
