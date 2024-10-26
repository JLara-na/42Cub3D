/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:36:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/25 22:38:31 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	controls_mouse(int key, int x, int y, t_cub3d *cub3d)
{
	if (cub3d->cam.menu_flag)
		return (1);
	(void)x;
	(void)y;
	if (key == 1)
		open_door(cub3d, key);
	if (key == 4)
		change_cam(cub3d, XK_Left, SENSITIVITY);
	if (key == 5)
		change_cam(cub3d, XK_Right, SENSITIVITY);
	return (0);
}

int	reset_mouse_pos(t_cub3d	*cub3d)
{
	return (mlx_mouse_move(cub3d->mlx.mlx_instance,
			cub3d->mlx.mlx_window, W_X / 2, W_Y / 2));
}

int	mouse_speed(int prev, int new, int speed_cap)
{
	int	speed;

	speed = (new - prev);
	if (speed > speed_cap)
		speed = speed_cap;
	if (speed < -speed_cap)
		speed = -speed_cap;
	return (speed);
}

int	mouse_pointer(int x, int y, t_cub3d *cub3d)
{
	static int	inputs;
	static int	prevx;
	int			speed;

	if (cub3d->cam.menu_flag)
		return (1);
	speed = mouse_speed(prevx, x, SENSITIVITYX_CAP);
	inputs++;
	mlx_mouse_hide(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window);
	if (inputs % 8 == 0)
	{
		if (prevx > x)
			change_cam(cub3d, XK_Left, SENSITIVITY * speed * -1);
		if (prevx < x)
			change_cam(cub3d, XK_Right, SENSITIVITY * speed);
		if (y < WH_Y - 5 || y > WH_Y + 5 || x < WH_X - 5 || x > WH_X + 5)
			mlx_mouse_move(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
				WH_X, WH_Y);
	}
	if (inputs > 800)
		inputs = 0;
	prevx = x;
	return (0);
}
