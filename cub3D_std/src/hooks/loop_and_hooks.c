/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:18:10 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 17:22:42 by jlara-na         ###   ########.fr       */
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

/*Hook function containing all key events*/
int	controls(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
		close_w(&cub3d->mlx);
	change_cam(cub3d, keycode, SENSITIVITY);
	return (0);
}

int	hook_animate(void *data)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)data;
	put_frame(cub3d);
	return (0);
}

void	loop_and_hooks(t_cub3d	*cub3d)
{
	mlx_hook(cub3d->mlx.mlx_window, 2, 1, controls, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 17, 0, close_w, &cub3d->mlx);
	mlx_loop_hook(cub3d->mlx.mlx_instance, hook_animate, cub3d);
	mlx_loop(cub3d->mlx.mlx_instance);
}
