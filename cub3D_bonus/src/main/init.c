/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:24:36 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/23 21:18:56 by jlara-na         ###   ########.fr       */
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

void	load_sprites(char **map, t_mlx	*mlx)
{
	int	x;
	int	i;

	x = 64;
	i = -1;
	while (++i < 4)
	{
		mlx->img_wall[i].img_instance = mlx_xpm_file_to_image
			(mlx->mlx_instance, map[i], &x, &x);
		mlx->img_wall[i].addr = mlx_get_data_addr
			(mlx->img_wall[i].img_instance, &mlx->img_wall[i].bppx,
				&mlx->img_wall[i].line_length, &mlx->img_wall[i].endian);
	}
	mlx->img_door.img_instance = mlx_xpm_file_to_image
		(mlx->mlx_instance, "./cub3D_bonus/resources/textures/door_closed.xpm", &x, &x);
	mlx->img_door.addr = mlx_get_data_addr
		(mlx->img_door.img_instance, &mlx->img_door.bppx,
			&mlx->img_door.line_length, &mlx->img_door.endian);
	mlx->map.img_instance = mlx_xpm_file_to_image
		(mlx->mlx_instance, "./cub3D_bonus/resources/textures/map_border.xpm", &x, &x);
	mlx->map.addr = mlx_get_data_addr
		(mlx->map.img_instance, &mlx->map.bppx,
			&mlx->map.line_length, &mlx->map.endian);
	mlx->floor.img_instance = mlx_xpm_file_to_image
		(mlx->mlx_instance, "./cub3D_bonus/resources/textures/map_border.xpm", &x, &x);
	mlx->floor.addr = mlx_get_data_addr
		(mlx->floor.img_instance, &mlx->floor.bppx,
			&mlx->floor.line_length, &mlx->floor.endian);
	mlx->ceiling.img_instance = mlx_xpm_file_to_image
		(mlx->mlx_instance, "./cub3D_bonus/resources/textures/test_wall_N.xpm", &x, &x);
	mlx->ceiling.addr = mlx_get_data_addr
		(mlx->ceiling.img_instance, &mlx->ceiling.bppx,
			&mlx->ceiling.line_length, &mlx->ceiling.endian);
}

void	start_cam(t_cub3d	*cub3d)
{
	if (cub3d->cam.init_angle == 'N')
		cub3d->cam.a = _3PI2;
	if (cub3d->cam.init_angle == 'S')
		cub3d->cam.a = PI2;
	if (cub3d->cam.init_angle == 'W')
		cub3d->cam.a = PI;
	if (cub3d->cam.init_angle == 'E')
		cub3d->cam.a = _2PI;
	cub3d->cam.map_s = 64;
	cub3d->cam.dx = cos(cub3d->cam.a) * 5;
	cub3d->cam.dy = sin(cub3d->cam.a) * 5;
}

//Sets up the initial state of the program
int	init_all(t_cub3d	*cub3d)
{
	if (start_mlx(&cub3d->mlx))
		terminate(ERROR_MLX_START, EXIT_FAILURE);
	load_sprites(cub3d->texture_path, &cub3d->mlx);
	start_cam(cub3d);
	return (0);
}
