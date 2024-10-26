/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:18:10 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/25 22:47:57 by jlara-na         ###   ########.fr       */
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

int	hook_frame(void *data)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)data;
	if (!cub3d->cam.menu_flag)
		put_frame(cub3d);
	return (0);
}

void	loop_and_hooks(t_cub3d	*cub3d)
{
	mlx_hook(cub3d->mlx.mlx_window, 2, 1, controls, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 4, 4, controls_mouse, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 6, (1L << 6), mouse_pointer, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 8, (1L << 5), reset_mouse_pos, &cub3d->mlx);
	mlx_hook(cub3d->mlx.mlx_window, 17, 0, close_w, &cub3d->mlx);
	mlx_loop_hook(cub3d->mlx.mlx_instance, hook_frame, cub3d);
	mlx_loop(cub3d->mlx.mlx_instance);
}
