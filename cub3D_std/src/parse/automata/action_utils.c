/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:59:43 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/19 21:06:50 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

int	check_color(long long int c)
{
	return (c >= 0 && c <= 255);
}

int	rgb_ok(char *rgb)
{
	char	**rgb_char;
	int		rgb_hex;
	int		i;

	rgb_hex = 0;
	i = -1;
	rgb_char = ft_split(rgb, ',');
	while (rgb_char[++i])
	{
		if (!check_color(ft_atoi(rgb_char[i])))
			terminate("BAD_RGB_FORMAT", 1);
	}
	if (i != 3)
		terminate("BAD_RGB_FORMAT", 1);
	rgb_hex += (ft_atoi(rgb_char[0]) << 16);
	rgb_hex += (ft_atoi(rgb_char[1]) << 8);
	rgb_hex += (ft_atoi(rgb_char[2]) << 0);
	ft_free_sarray(rgb_char);
	return (rgb_hex);
}
