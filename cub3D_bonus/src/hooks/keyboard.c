/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:44:08 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/26 02:40:05 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	put_menu(t_cub3d	*cub3d)
{
	put_img_to_img(&cub3d->mlx.img, &cub3d->mlx.menu, WH_X - 426, WH_Y - 190);
	mlx_put_image_to_window(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
		cub3d->mlx.img.img_instance, 0, 0);
	return (1);
}

/*Hook function containing all key events*/
int	controls(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape && !cub3d->cam.menu_flag)
	{
		mlx_hook(cub3d->mlx.mlx_window, 8, 0, NULL, NULL);
		cub3d->cam.menu_flag = 1;
		put_menu(cub3d);
	}
	if (!cub3d->cam.menu_flag)
		change_cam(cub3d, keycode, SENSITIVITY);
	else
	{
		if (keycode == XK_q)
			close_w(&cub3d->mlx);
		if (keycode == XK_Return)
		{
			cub3d->cam.menu_flag = 0;
			mlx_mouse_hide(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window);
			mlx_hook(cub3d->mlx.mlx_window, 8, (1L << 5),
				reset_mouse_pos, &cub3d->mlx);
		}
	}
	return (0);
}
