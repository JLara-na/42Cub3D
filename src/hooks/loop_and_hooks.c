/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:18:10 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/30 22:16:09 by jlara-na         ###   ########.fr       */
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
		move_cam(cub3d, XK_Left);
	if (key == 5)
		move_cam(cub3d, XK_Right);
	return (0);
}

int	mouse_pointer(int x, int y, t_cub3d *cub3d)
{
	static int	inputs;
	static int	prevx;

	(void)y;
	if (cub3d->cam.menu_flag)
		return (1);
	inputs++;
	mlx_mouse_hide(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window);
	if (inputs % 8 == 0)
	{
		if (prevx > x && x < W_X / 2 - 5)
		{
			move_cam(cub3d, 0);
			mlx_mouse_move(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window, W_X / 2, W_Y/ 2);
		}
		if (prevx < x && x > W_X / 2 + 5)
		{
			move_cam(cub3d, 1);
			mlx_mouse_move(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window, W_X / 2, W_Y/ 2);
		}
	}
	if (inputs > 800)
		inputs = 0;
	prevx = x;
	return (0);
}


/*Hook function containing all key events*/
int	controls(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
	{
		cub3d->cam.menu_flag = 1;
		put_menu(cub3d);
	}
	if (!cub3d->cam.menu_flag)
	{
		if (keycode == XK_a)
			move_cam(cub3d, XK_a);
		if (keycode == XK_w)
			move_cam(cub3d, XK_w);
		if (keycode == XK_d)
			move_cam(cub3d, XK_d);
		if (keycode == XK_s)
			move_cam(cub3d, XK_s);
		if (keycode == XK_Left)
			move_cam(cub3d, XK_Left);
		if (keycode == XK_Right)
			move_cam(cub3d, XK_Right);
	}
	else
	{
		if (keycode == XK_q)
			close_w(&cub3d->mlx);
		if (keycode == XK_Return)
		{
			cub3d->cam.menu_flag = 0;
			mlx_mouse_hide(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window);
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
	mlx_hook(cub3d->mlx.mlx_window, 17, 0, close_w, &cub3d->mlx);
	mlx_loop(cub3d->mlx.mlx_instance);
}