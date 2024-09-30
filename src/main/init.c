/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:24:36 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/30 12:49:55 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	start_mlx(t_mlx	*mlx)
{
	mlx->mlx_instance = mlx_init();
	if (mlx->mlx_instance)
	{
		mlx->mlx_window = mlx_new_window(mlx->mlx_instance, W_X, W_Y, "cub3D");
		mlx->img.img_instance = mlx_new_image(mlx->mlx_instance, W_X, W_Y);
		mlx->img.addr = mlx_get_data_addr(mlx->img.img_instance, &mlx->img.bppx,
				&mlx->img.line_length, &mlx->img.endian);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	start_cam(t_cub3d	*cub3d)
{
	cub3d->cam.map_s = 64;
	cub3d->cam.x = 32 * 8;
	cub3d->cam.y = 32 * 8;
	cub3d->cam.dx = cos(cub3d->cam.a) * 5;
	cub3d->cam.dy = sin(cub3d->cam.a) * 5;
}

//Sets up the initial state of the program
int	init_all(t_cub3d	*cub3d)
{
	ft_bzero(cub3d, sizeof(t_cub3d));
	if (start_mlx(&cub3d->mlx))
		terminate(ERROR_MLX_START, EXIT_FAILURE);
	start_cam(cub3d);
	return (0);
}