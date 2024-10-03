/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:43:02 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/03 22:06:51 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	fish_eye_fix(t_cam	*cam, t_ray *ray)
{
	ray->ca = cam->a - ray->ra;
	if (ray->ca < 0)
		ray->ca += 2 * PI;
	if (ray->ca < 2 * PI)
		ray->ca -= 2 * PI;
	ray->tdis *= cos(ray->ca);
}

void	wall_size_and_place(t_cam	*cam, t_ray *ray)
{
	ray->lineh = (cam->map_s * W_Y) / ray->tdis;
	if (ray->lineh > W_Y)
		ray->lineh = W_Y;
	ray->lineo = ((W_Y / 2) - (ray->lineh / 2));
}

void	print_wall(t_cam *cam, t_mlx *mlx, t_ray *ray)
{
	int	xau;
	int	yau;

	(void)cam;
	yau = -1;
	while (++yau < ray->lineh)
	{
		xau = -1;
		while (++xau < (W_X) / RAY_NUMBER)
			my_mlx_pixel_put(&mlx->img, xau + ray->i
				* (W_X / RAY_NUMBER), yau + ray->lineo, ray->color);
	}
}
