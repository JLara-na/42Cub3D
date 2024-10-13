/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:18:55 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/13 20:00:38 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;
	int	a;
	int	b;

	i = 0;
	b = 0;
	while (i < 386)
	{
		j = 0;
		a = 0;
		while (j < 386)
		{
			my_mlx_pixel_put(dst, x + i, y + j, get_pixel_img(src, b, a));
			j++;
			if (j % 6 == 0)
				a++;
		}
		i++;
		if (i % 6 == 0)
			b++;
	}
}
