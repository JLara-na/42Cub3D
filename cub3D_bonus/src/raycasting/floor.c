/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:46 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/27 19:20:27 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_floor_ceiling(t_cam *cam, t_mlx *mlx, t_ray *ray)
{
	int		y;

	y = ray->lineo + ray->lineh;
	while (++y < W_Y)
	{
		ray->dy = y - (WH_Y);
		ray->rafix = cos(cam->a - ray->ra);
		ray->tx = (cam->x) * 1.1
			+ (cos(ray->ra) * (160 * 160)) / ray->dy / ray->rafix;
		ray->ty = (cam->y) * 1.1
			+ (sin(ray->ra) * (160 * 160)) / ray->dy / ray->rafix;
		ray->color = get_pixel_img(&mlx->textures[FLOOR], ((int)(ray->tx) & 63),
				((int)(ray->ty) & 63));
		my_mlx_pixel_put(&mlx->img, ray->i, y, ray->color);
		ray->color = get_pixel_img(&mlx->textures[CEILING],
				((int)(ray->tx) & 63), ((int)(ray->ty) & 63));
		my_mlx_pixel_put(&mlx->img, ray->i, W_Y - y, ray->color);
	}
}
