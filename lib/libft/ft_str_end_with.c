/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 01:01:49 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/06 01:02:03 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_end_with(const char *str, const char *end)
{
	int	len_a;
	int	len_b;

	len_a = ft_strlen(str);
	len_b = ft_strlen(end);
	if (len_b > len_a)
		return (0);
	while (len_b > 0)
	{
		if (str[len_a] != end[len_b])
			return (0);
		len_a--;
		len_b--;
	}
	return (1);
}
