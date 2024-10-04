/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:40:05 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/04 03:40:31 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	collision_init(t_cub3d	*cub3d, t_ray	*collision, int key)
{
	if (cub3d->cam.dx < 0)
		collision->xo = -COLISION_DISTANCE;
	else
		collision->xo = COLISION_DISTANCE;
	if (cub3d->cam.dy < 0)
		collision->yo = -COLISION_DISTANCE;
	else
		collision->yo = COLISION_DISTANCE;
	if (key == XK_a || key == XK_d)
	{
		if (cub3d->cam.dy < 0)
			collision->xo = -COLISION_DISTANCE;
		else
			collision->xo = COLISION_DISTANCE;
		if (cub3d->cam.dx < 0)
			collision->yo = -COLISION_DISTANCE;
		else
			collision->yo = COLISION_DISTANCE;
	}
	collision->mx = cub3d->cam.x / 64;
	collision->mx_add_xo = (cub3d->cam.x + collision->xo) / 64;
	collision->mx_sub_xo = (cub3d->cam.x - collision->xo) / 64;
	collision->my = cub3d->cam.y / 64;
	collision->my_add_yo = (cub3d->cam.y + collision->yo) / 64;
	collision->my_sub_yo = (cub3d->cam.y - collision->yo) / 64;
}

void	move_cam(t_cub3d	*cub3d, int key)
{
	t_ray	c;

	ft_bzero(&c, sizeof(t_ray));
	collision_init(cub3d, &c, key);
	if (key == XK_s && get_map(c.mx_sub_xo, c.my) == 0)
		cub3d->cam.x -= cub3d->cam.dx;
	if (key == XK_s && get_map(c.mx, c.my_sub_yo) == 0)
		cub3d->cam.y -= cub3d->cam.dy;
	if (key == XK_w && get_map(c.mx_add_xo, c.my) == 0)
		cub3d->cam.x += cub3d->cam.dx;
	if (key == XK_w && get_map(c.mx, c.my_add_yo) == 0)
		cub3d->cam.y += cub3d->cam.dy;
	if (key == XK_d && get_map(c.mx_sub_xo, c.my) == 0)
		cub3d->cam.x -= cub3d->cam.dy;
	if (key == XK_d && get_map(c.mx, c.my_add_yo) == 0)
		cub3d->cam.y += cub3d->cam.dx;
	if (key == XK_a && get_map(c.mx_add_xo, c.my) == 0)
		cub3d->cam.x += cub3d->cam.dy;
	if (key == XK_a && get_map(c.mx, c.my_sub_yo) == 0)
		cub3d->cam.y -= cub3d->cam.dx;
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
	put_frame(cub3d);
}
