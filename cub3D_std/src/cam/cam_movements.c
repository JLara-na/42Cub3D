/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:40:05 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 16:23:29 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_cam(t_cub3d	*cub3d, int key)
{
	t_ray	c;

	ft_bzero(&c, sizeof(t_ray));
	if (key == XK_s)
	{
		cub3d->cam.x -= cub3d->cam.dx;
		cub3d->cam.y -= cub3d->cam.dy;
	}
	if (key == XK_w)
	{
		cub3d->cam.x += cub3d->cam.dx;
		cub3d->cam.y += cub3d->cam.dy;
	}
	if (key == XK_d)
	{
		cub3d->cam.x -= cub3d->cam.dy;
		cub3d->cam.y += cub3d->cam.dx;
	}
	if (key == XK_a)
	{
		cub3d->cam.x += cub3d->cam.dy;
		cub3d->cam.y -= cub3d->cam.dx;
	}
}

void	rotate_cam(t_cub3d	*cub3d, int key, float sensitivity)
{
	if (key == XK_Left)
	{
		cub3d->cam.a -= sensitivity;
		if (cub3d->cam.a < 0)
			cub3d->cam.a += 2 * PI;
		cub3d->cam.dx = cos(cub3d->cam.a) * 5;
		cub3d->cam.dy = sin(cub3d->cam.a) * 5;
	}
	if (key == XK_Right)
	{
		cub3d->cam.a += sensitivity;
		if (cub3d->cam.a > (2 * PI))
			cub3d->cam.a -= 2 * PI;
		cub3d->cam.dx = cos(cub3d->cam.a) * 5;
		cub3d->cam.dy = sin(cub3d->cam.a) * 5;
	}
}

void	change_cam(t_cub3d	*cub3d, int key, float sensitivity)
{
	move_cam(cub3d, key);
	rotate_cam(cub3d, key, sensitivity);
}
