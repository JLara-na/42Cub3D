/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:17:08 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/14 02:51:50 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	square_wall(t_cub3d	*cub3d, int x, int y, int color)
{
	int	xau;
	int	yau;

	yau = 32;
	while (++yau < 49)
	{
		xau = 32;
		while (++xau < 49)
			my_mlx_pixel_put(&cub3d->mlx.img, xau + (19 * x),
				yau + (19 * y), color);
	}
}

void	map_backgrownd(t_cub3d	*cub3d)
{
	int	x;
	int	y;

	y = 29;
	while (++y < 355)
	{
		x = 29;
		while (++x < 355)
			my_mlx_pixel_put(&cub3d->mlx.img, x, y, 0x0C0B0C);
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
			square_wall(cub3d, x - mpx + MP_SIDE, y - mpy + MP_SIDE, 0x41280B);
		if (cub3d->cam.map_c[y][x] == '0')
			square_wall(cub3d, x - mpx + MP_SIDE, y - mpy + MP_SIDE, 0xA29571);
		if (cub3d->cam.map_c[y][x] == 'D')
			square_wall(cub3d, x - mpx + MP_SIDE, y - mpy + MP_SIDE, 0x546565);
		if (cub3d->cam.map_c[y][x] == 'O')
			square_wall(cub3d, x - mpx + MP_SIDE, y - mpy + MP_SIDE, 0x87B9B9);
		if (ft_chrpos("NSWE", cub3d->cam.map_c[y][x]) != -1)
			square_wall(cub3d, x - mpx + MP_SIDE, y - mpy + MP_SIDE, 0x3CA276);
	}
}

void	minimap(t_cub3d	*cub3d)
{
	map_backgrownd(cub3d);
	map_iter_context(cub3d->cam.map_c, minimap_wall, cub3d);
	square_wall(cub3d, 8, 8, 0xC95133);
	put_img_to_img(&cub3d->mlx.img, &cub3d->mlx.textures[MAP], 0, 0);
}
