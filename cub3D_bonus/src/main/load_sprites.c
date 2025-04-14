/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:33:11 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/14 13:48:07 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		if (mlx->textures[i].img_instance == NULL)
			terminate("XPM is in a bad formatting", 1);
		mlx->textures[i].addr = mlx_get_data_addr
			(mlx->textures[i].img_instance, &mlx->textures[i].bppx,
				&mlx->textures[i].line_length, &mlx->textures[i].endian);
	}
	ft_free_sarray(paths);
}

void	mlx_animation_sprite(t_mlx	*mlx, int *x, char **paths)
{
	int			i;

	i = -1;
	while (++i < 13)
	{
		mlx->animation[i].img_instance = mlx_xpm_file_to_image
			(mlx->mlx_instance, paths[i], x, x);
		if (mlx->animation[i].img_instance == NULL)
			terminate("XPM is in a bad formatting", 1);
		mlx->animation[i].addr = mlx_get_data_addr
			(mlx->animation[i].img_instance, &mlx->animation[i].bppx,
				&mlx->animation[i].line_length, &mlx->animation[i].endian);
	}
}

void	load_animation_sprite(t_mlx	*mlx, int *x)
{
	char		**paths;

	paths = malloc(14 * (sizeof(char *)));
	paths[0] = ft_strdup(ANIM_PATH_1);
	paths[1] = ft_strdup(ANIM_PATH_2);
	paths[2] = ft_strdup(ANIM_PATH_3);
	paths[3] = ft_strdup(ANIM_PATH_4);
	paths[4] = ft_strdup(ANIM_PATH_5);
	paths[5] = ft_strdup(ANIM_PATH_6);
	paths[6] = ft_strdup(ANIM_PATH_7);
	paths[7] = ft_strdup(ANIM_PATH_8);
	paths[8] = ft_strdup(ANIM_PATH_9);
	paths[9] = ft_strdup(ANIM_PATH_10);
	paths[10] = ft_strdup(ANIM_PATH_11);
	paths[11] = ft_strdup(ANIM_PATH_12);
	paths[12] = ft_strdup(ANIM_PATH_13);
	paths[13] = NULL;
	mlx_animation_sprite(mlx, x, paths);
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
		if (mlx->img_wall[i].img_instance == NULL)
			terminate("XPM is in a bad formatting", 1);
		mlx->img_wall[i].addr = mlx_get_data_addr
			(mlx->img_wall[i].img_instance, &mlx->img_wall[i].bppx,
				&mlx->img_wall[i].line_length, &mlx->img_wall[i].endian);
	}
	load_static_sprites(mlx, &x);
	load_animation_sprite(mlx, &x);
}
