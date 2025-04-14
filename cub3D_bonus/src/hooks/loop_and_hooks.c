/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:18:10 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/14 02:59:19 by jlara-na         ###   ########.fr       */
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

void	create_anim(t_cub3d *cub3d, int x, int y)
{
	static int	i;
	static int	j;

	put_img_to_img(&cub3d->mlx.img, &cub3d->mlx.animation[i], x, y);
	if (i <= 12)
	{
		if (j % 2 == 0)
			i++;
		j++;
	}
	else
		i = 0;
	if (i == 13)
	{
		i = 0;
		j = 0;
	}
}

int	hook_frame(void *data)
{
	t_cub3d		*cub3d;
	static int	loops;

	cub3d = (t_cub3d *)data;
	if (!cub3d->cam.menu_flag && loops++ % 99 == 0)
	{
		put_frame(cub3d);
		create_anim(cub3d, W_X - 550, W_Y - 375);
	}
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
