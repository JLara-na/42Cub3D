/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:18:55 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/16 20:56:01 by jlara-na         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= W_X || y < 0 || y >= W_Y)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bppx / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_img(t_img *img, int x, int y)
{
	if (x > 64 || y > 64)
		return (0xFF0000);
	return (*(unsigned int *)((img->addr + (y * img->line_length)
			+ (x * img->bppx / 8))));
}
