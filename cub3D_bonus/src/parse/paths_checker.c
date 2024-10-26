/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:12:19 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/26 02:16:54 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_path(char *path)
{
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	paths_checker(t_cub3d	*cub3d)
{
	int	i;
	int	fd;

	i = -1;
	while (cub3d->texture_path[++i])
	{
		fd = open(cub3d->texture_path[i], O_RDONLY);
		if (fd == -1)
			return (1);
		close(fd);
	}
	if (check_path(DOOR_PATH))
		return (1);
	if (check_path(MAPT_PATH))
		return (1);
	if (check_path(FLOOR_PATH))
		return (1);
	if (check_path(CEILING_PATH))
		return (1);
	if (check_path(MENU_PATH))
		return (1);
	return (0);
}
