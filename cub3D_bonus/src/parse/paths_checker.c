/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:12:19 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/14 15:33:54 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_path(char *path)
{
	int			fd;

	if (!ft_str_end_with(path, ".xpm"))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

void	check_path_list(void)
{
	int			resources[19];
	static int	i;

	resources[0] = check_path(FLOOR_PATH);
	resources[1] = check_path(CEILING_PATH);
	resources[2] = check_path(DOOR_PATH);
	resources[3] = check_path(MAPT_PATH);
	resources[4] = check_path(MENU_PATH_1);
	resources[5] = check_path(MENU_PATH_2);
	resources[6] = check_path(ANIM_PATH_1);
	resources[7] = check_path(ANIM_PATH_2);
	resources[8] = check_path(ANIM_PATH_3);
	resources[9] = check_path(ANIM_PATH_4);
	resources[10] = check_path(ANIM_PATH_5);
	resources[11] = check_path(ANIM_PATH_6);
	resources[12] = check_path(ANIM_PATH_7);
	resources[13] = check_path(ANIM_PATH_8);
	resources[14] = check_path(ANIM_PATH_9);
	resources[15] = check_path(ANIM_PATH_10);
	resources[16] = check_path(ANIM_PATH_11);
	resources[17] = check_path(ANIM_PATH_12);
	resources[18] = check_path(ANIM_PATH_13);
	while (i++ < 18)
		if (resources[i] == 1)
			terminate("Error loading or finding textures PATHCHECKER", 1);
}

int	paths_checker(t_cub3d	*cub3d)
{
	int	i;
	int	fd;

	i = -1;
	while (cub3d->texture_path[++i])
	{
		if (!ft_str_end_with(cub3d->texture_path[i], ".xpm"))
			return (1);
		fd = open(cub3d->texture_path[i], O_RDONLY);
		if (fd == -1)
			return (1);
		close(fd);
	}
	check_path_list();
	return (0);
}
