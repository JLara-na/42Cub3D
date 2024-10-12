/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_movements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:40:05 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 14:53:01 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	collision_init(t_cub3d	*cub3d, t_ray	*collision, int key, int c)
{
	if (cub3d->cam.dx < 0)
		collision->xo = -c;
	else
		collision->xo = c;
	if (cub3d->cam.dy < 0)
		collision->yo = -c;
	else
		collision->yo = c;
	if (key == XK_a || key == XK_d)
	{
		if (cub3d->cam.dy < 0)
			collision->xo = -c;
		else
			collision->xo = c;
		if (cub3d->cam.dx < 0)
			collision->yo = -c;
		else
			collision->yo = c;
	}
	collision->mx = cub3d->cam.x / 64;
	collision->mx_axo = (cub3d->cam.x + collision->xo) / 64;
	collision->mx_sxo = (cub3d->cam.x - collision->xo) / 64;
	collision->my = cub3d->cam.y / 64;
	collision->my_ayo = (cub3d->cam.y + collision->yo) / 64;
	collision->my_syo = (cub3d->cam.y - collision->yo) / 64;
}

void	move_cam(t_cub3d	*cub3d, int key)
{
	t_ray	c;

	ft_bzero(&c, sizeof(t_ray));
	collision_init(cub3d, &c, key, COLISION_DISTANCE);
	if (key == XK_s && !ft_strchr("1D", get_map(&cub3d->cam, c.mx_sxo, c.my)))
		cub3d->cam.x -= cub3d->cam.dx;
	if (key == XK_s && !ft_strchr("1D", get_map(&cub3d->cam, c.mx, c.my_syo)))
		cub3d->cam.y -= cub3d->cam.dy;
	if (key == XK_w && !ft_strchr("1D", get_map(&cub3d->cam, c.mx_axo, c.my)))
		cub3d->cam.x += cub3d->cam.dx;
	if (key == XK_w && !ft_strchr("1D", get_map(&cub3d->cam, c.mx, c.my_ayo)))
		cub3d->cam.y += cub3d->cam.dy;
	if (key == XK_d && !ft_strchr("1D", get_map(&cub3d->cam, c.mx_sxo, c.my)))
		cub3d->cam.x -= cub3d->cam.dy;
	if (key == XK_d && !ft_strchr("1D", get_map(&cub3d->cam, c.mx, c.my_ayo)))
		cub3d->cam.y += cub3d->cam.dx;
	if (key == XK_a && !ft_strchr("1D", get_map(&cub3d->cam, c.mx_axo, c.my)))
		cub3d->cam.x += cub3d->cam.dy;
	if (key == XK_a && !ft_strchr("1D", get_map(&cub3d->cam, c.mx, c.my_syo)))
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

void	open_door(t_cub3d *cub3d, int key)
{
	t_ray	collision;

	if (key == 1 || key == XK_e)
	{
		ft_bzero(&collision, sizeof(t_ray));
		if (cub3d->cam.dx < 0)
			collision.xo = -20;
		else
			collision.xo = 20;
		if (cub3d->cam.dy < 0)
			collision.yo = -20;
		else
			collision.yo = 20;
		collision.mx = cub3d->cam.x / 64;
		collision.mx_axo = (cub3d->cam.x + collision.xo) / 64;
		collision.my = cub3d->cam.y / 64;
		collision.my_ayo = (cub3d->cam.y + collision.yo) / 64;
		if (ft_strchr("D", get_map(&cub3d->cam, collision.mx_axo,
					collision.my_ayo)) != NULL)
			cub3d->cam.map_c[collision.my_ayo][collision.mx_axo] = 'O';
		else if (ft_strchr("O", get_map(&cub3d->cam, collision.mx_axo,
					collision.my_ayo)) && get_map(&cub3d->cam, collision.mx,
				collision.my) != 'O')
			cub3d->cam.map_c[collision.my_ayo][collision.mx_axo] = 'D';
	}
}

void	change_cam(t_cub3d	*cub3d, int key, float sensitivity)
{
	move_cam(cub3d, key);
	rotate_cam(cub3d, key, sensitivity);
	open_door(cub3d, key);
}
