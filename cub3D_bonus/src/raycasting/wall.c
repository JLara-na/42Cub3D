/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:43:02 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/13 23:01:48 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	fish_eye_fix(t_cam	*cam, t_ray *ray)
{
	ray->ca = cam->a - ray->ra;
	if (ray->ca < 0)
		ray->ca += _2PI;
	if (ray->ca < _2PI)
		ray->ca -= _2PI;
	ray->tdis *= cos(ray->ca);
}

void	wall_size_and_place(t_cam	*cam, t_ray *ray)
{
	ray->lineh = (cam->map_s * W_Y) / ray->tdis;
	ray->ty_step = 64 / ray->lineh;
	ray->ty_o = 0;
	if (ray->lineh > W_Y)
	{
		ray->ty_o = (ray->lineh - W_Y) / 2;
		ray->lineh = W_Y;
	}
	ray->lineo = ((float)(WH_Y) - (ray->lineh / 2));
	ray->ty = ray->ty_o * ray->ty_step;
	if (ray->hdis < ray->vdis)
	{
		ray->tx = (int)(ray->rx) % 64;
		if (ray->ra >= PI)
			ray->tx = 63 - ray->tx;
	}
	else
	{
		ray->tx = (int)(ray->ry) % 64;
		if (ray->ra > PI2 && ray->ra < _3PI2)
			ray->tx = 63 - ray->tx;
	}
}

void	draw_wall(t_mlx *mlx, t_ray *ray, int xau, int yau)
{
	if (ray->hdis < ray->vdis)
	{
		if (ray->ra > 0 && ray->ra < PI)
			ray->color = get_pixel_img(&mlx->img_wall[SOUTH],
					64 - ray->tx, ray->ty);
		else
			ray->color = get_pixel_img(&mlx->img_wall[NORTH],
					64 - ray->tx, ray->ty);
	}
	else
	{
		if (ray->ra < PI2 || ray->ra > _3PI2)
			ray->color = get_pixel_img(&mlx->img_wall[EAST], ray->tx, ray->ty);
		else
			ray->color = get_pixel_img(&mlx->img_wall[WEST], ray->tx, ray->ty);
	}
	my_mlx_pixel_put(&mlx->img, xau + ray->i
		* (W_X / RAY_NUMBER), yau + ray->lineo, ray->color);
}

void	draw_door(t_mlx *mlx, t_ray *ray, int xau, int yau)
{
	if (ray->hdis < ray->vdis)
		ray->color = get_pixel_img(&mlx->textures[DOOR], 64 - ray->tx, ray->ty);
	else
		ray->color = get_pixel_img(&mlx->textures[DOOR], ray->tx, ray->ty);
	my_mlx_pixel_put(&mlx->img, xau + ray->i
		* (W_X / RAY_NUMBER), yau + ray->lineo, ray->color);
}

void	print_wall(t_cam *cam, t_mlx *mlx, t_ray *ray)
{
	int	xau;
	int	yau;

	yau = -1;
	while (++yau < ray->lineh)
	{
		xau = -1;
		while (++xau < (W_X) / RAY_NUMBER)
		{
			if (get_map(cam, ray->rx / 64, ray->ry / 64) == '1')
				draw_wall(mlx, ray, xau, yau);
			if (get_map(cam, ray->rx / 64, ray->ry / 64) == 'D')
				draw_door(mlx, ray, xau, yau);
		}
		ray->ty += ray->ty_step;
	}
}
