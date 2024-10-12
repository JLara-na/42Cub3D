/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:54:09 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 15:16:49 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	pitagoras(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

char	get_map(t_cam *cam, int x, int y)
{
	if (x < 0 || y < 0 || x > cam->map_w || y > cam->map_h)
		return (0);
	return (cam->map_c[y][x]);
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
