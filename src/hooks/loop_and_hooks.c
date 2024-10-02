/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:18:10 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/02 22:21:09 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*Destroys the window free vars and exits the program. It is used in a hook*/
int	close_w(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_instance, mlx->mlx_window);
	terminate(BYE_MSG, EXIT_SUCCESS);
	return (0);
}

int	put_menu(t_cub3d	*cub3d)
{
	int	x;
	int	y;

	y = W_Y / 4 * 3;
	while (y-- >  W_Y / 4)
	{
		x = W_X / 4 * 3;
		while (x-- >  W_X / 4)
				my_mlx_pixel_put(&cub3d->mlx.img, x, y, 0xFDD44D);
	}
	mlx_put_image_to_window(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
	 	cub3d->mlx.img.img_instance, 0, 0);
	mlx_set_font(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window, "12x24romankana");
	mlx_string_put(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
		W_X / 2 - 100, W_Y / 2 - 24, 0 , "PRESS Q TO EXIT");
	mlx_string_put(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
		W_X / 2 - 100, W_Y / 2 + 24, 0 , "PRESS ENTER TO CONTINUE");
	mlx_mouse_show(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window);
	return (1);
}

int	controls_mouse(int key, int x, int y, t_cub3d *cub3d)
{
	if (cub3d->cam.menu_flag)
		return (1);
	(void)x;
	(void)y;
	if (key == 4)
		move_cam(cub3d, XK_Left, SENSITIVITY);
	if (key == 5)
		move_cam(cub3d, XK_Right, SENSITIVITY);
	return (0);
}

int	mouse_speed(int	prev, int new, int speed_cap)
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
			move_cam(cub3d, XK_Left, SENSITIVITY * speed * -1);
		if (prevx < x)
			move_cam(cub3d, XK_Right, SENSITIVITY * speed);
		if (y < WH_Y - 5 || y > WH_Y + 5 || x < WH_X - 5 || x > WH_X + 5)
			mlx_mouse_move(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
				WH_X, WH_Y);
	}
	if (inputs > 800)
		inputs = 0;
	prevx = x;
	return (0);
}

int	reset_mouse_position(t_cub3d	*cub3d)
{
	return (mlx_mouse_move(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window, W_X / 2, W_Y/ 2));
}

/*Hook function containing all key events*/
int	controls(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
	{
		mlx_hook(cub3d->mlx.mlx_window, 8, (1L<<5), NULL, &cub3d->mlx);
		cub3d->cam.menu_flag = 1;
		put_menu(cub3d);
	}
	if (!cub3d->cam.menu_flag)
	{
		if (keycode == XK_a)
			move_cam(cub3d, XK_a, SENSITIVITY);
		if (keycode == XK_w)
			move_cam(cub3d, XK_w, SENSITIVITY);
		if (keycode == XK_d)
			move_cam(cub3d, XK_d, SENSITIVITY);
		if (keycode == XK_s)
			move_cam(cub3d, XK_s, SENSITIVITY);
		if (keycode == XK_Left)
			move_cam(cub3d, XK_Left, SENSITIVITY);
		if (keycode == XK_Right)
			move_cam(cub3d, XK_Right, SENSITIVITY);
	}
	else
	{
		if (keycode == XK_q)
			close_w(&cub3d->mlx);
		if (keycode == XK_Return)
		{
			cub3d->cam.menu_flag = 0;
			mlx_mouse_hide(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window);
			mlx_hook(cub3d->mlx.mlx_window, 8, (1L<<5), reset_mouse_position, &cub3d->mlx);
			test(cub3d);
		}
	}
	return (0);
}



void	loop_and_hooks(t_cub3d	*cub3d)
{
	mlx_hook(cub3d->mlx.mlx_window, 2, 1, controls, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 4, 4, controls_mouse, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 6, (1L<<6), mouse_pointer, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 8, (1L<<5), reset_mouse_position, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 17, 0, close_w, &cub3d->mlx);
	mlx_loop(cub3d->mlx.mlx_instance);
}