/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:18:10 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/30 16:54:18 by jlara-na         ###   ########.fr       */
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

/*Hook function containing menu key events*/
int	menu(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Return)
		close_w(&cub3d->mlx);
	if (keycode == XK_Escape)
		mlx_key_hook(cub3d->mlx.mlx_window, controls, &cub3d->mlx);
	return (0);
}

/*Hook function containing all key events*/
int	controls(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
		mlx_hook(cub3d->mlx.mlx_window, 2, 1, menu, cub3d);
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
	return (0);
}

int	controls_mouse(int key, int x, int y, t_cub3d *cub3d)
{
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
	inputs++;
	if (inputs % 8 == 0)
	{
		if (prevx > x && x < W_X / 2)
			move_cam(cub3d, XK_Left);
		if (prevx < x && x > W_X / 2)
			move_cam(cub3d, XK_Right);
	}
	if (inputs > 800)
		inputs = 0;
	prevx = x;
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