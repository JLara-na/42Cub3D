/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:52:27 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/14 14:26:30 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	return (0);
}
