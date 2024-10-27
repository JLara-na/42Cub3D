/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:24:36 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/27 19:34:39 by jlara-na         ###   ########.fr       */
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

void	load_static_sprites(t_mlx	*mlx, int *x)
{
	int			i;
	char		**paths;

	paths = malloc(7 * (sizeof(char *)));
	paths[0] = ft_strdup(FLOOR_PATH);
	paths[1] = ft_strdup(CEILING_PATH);
	paths[2] = ft_strdup(DOOR_PATH);
	paths[3] = ft_strdup(MAPT_PATH);
	paths[4] = ft_strdup(MENU_PATH_1);
	paths[5] = ft_strdup(MENU_PATH_2);
	paths[6] = NULL;

	i = -1;
	while (++i < 6)
	{
		mlx->textures[i].img_instance = mlx_xpm_file_to_image
			(mlx->mlx_instance, paths[i], x, x);
		mlx->textures[i].addr = mlx_get_data_addr
			(mlx->textures[i].img_instance, &mlx->textures[i].bppx,
				&mlx->textures[i].line_length, &mlx->textures[i].endian);
	}
	ft_free_sarray(paths);
}

void	load_sprites(char **map, t_mlx	*mlx)
{
	int	x;
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx->img_wall[i].img_instance = mlx_xpm_file_to_image
			(mlx->mlx_instance, map[i], &x, &x);
		mlx->img_wall[i].addr = mlx_get_data_addr
			(mlx->img_wall[i].img_instance, &mlx->img_wall[i].bppx,
				&mlx->img_wall[i].line_length, &mlx->img_wall[i].endian);
	}
	load_static_sprites(mlx, &x);
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
