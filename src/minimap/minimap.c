/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:17:08 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/09 21:37:37 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	square_wall(t_cub3d	*cub3d, int x, int y, int color)
{
	int	xau;
	int	yau;

	yau = -1;
	while (++yau < 9)
	{
		xau = -1;
		while (++xau < 9)
			my_mlx_pixel_put(&cub3d->mlx.img, xau + (10 * x),
				yau + (10 * y), color);
	}
}

void	map_backgrownd(t_cub3d	*cub3d)
{
	int	x;
	int	y;

	y = 10;
	while (++y < 22 * (MP_SIDE + 1))
	{
		x = 10;
		while (++x < 22 * (MP_SIDE + 1))
			my_mlx_pixel_put(&cub3d->mlx.img, x, y, 0x575757);
	}
	y = 20;
	while (++y < 21 * (MP_SIDE + 1))
	{
		x = 20;
		while (++x < 21 * (MP_SIDE + 1))
			my_mlx_pixel_put(&cub3d->mlx.img, x, y, 0xA4A4A4);
	}
}

void	minimap_wall(void	*data, int x, int y)
{
	t_cub3d	*cub3d;
	int		mpx;
	int		mpy;

	cub3d = (t_cub3d *)data;
	mpx = (cub3d->cam.x / 64);
	mpy = (cub3d->cam.y / 64);
	if ((x <= mpx + MP_SIDE) && (y <= mpy + MP_SIDE)
		&& x >= mpx - MP_SIDE && y >= mpy - MP_SIDE)
	{
		if (cub3d->cam.map_c[y][x] == '1')
			square_wall(cub3d, x - mpx + MP_SIDE + 2,
				y - mpy + MP_SIDE + 2, 0x000000);
		if (cub3d->cam.map_c[y][x] == '0')
			square_wall(cub3d, x - mpx + MP_SIDE + 2,
				y - mpy + MP_SIDE + 2, 0xFFFFFF);
		if (cub3d->cam.map_c[y][x] == 'D')
			square_wall(cub3d, x - mpx + MP_SIDE + 2,
				y - mpy + MP_SIDE + 2, 0x0000FF);
		if (cub3d->cam.map_c[y][x] == 'D')
			square_wall(cub3d, x - mpx + MP_SIDE + 2,
				y - mpy + MP_SIDE + 2, 0x0000FF);
		if (ft_chrpos("NSWE", cub3d->cam.map_c[y][x]) != -1)
			square_wall(cub3d, x - mpx + MP_SIDE + 2,
				y - mpy + MP_SIDE + 2, 0xFF00FF);
	}
	square_wall(cub3d, MP_SIDE + 2, MP_SIDE + 2, 0x0000FF00);
}

void	minimap(t_cub3d	*cub3d)
{
	map_backgrownd(cub3d);
	map_iter_context(cub3d->cam.map_c, minimap_wall, cub3d);
}
