/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbajji <cbajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:35:33 by cbajji            #+#    #+#             */
/*   Updated: 2024/10/30 21:36:32 by cbajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (is_space(((char *)str)))
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
