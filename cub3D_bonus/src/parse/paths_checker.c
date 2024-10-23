/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 21:12:19 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/19 21:14:09 by jlara-na         ###   ########.fr       */
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
		fd = open(cub3d->texture_path[i], O_RDONLY);
		if (fd == -1)
			return (1);
		close(fd);
	}
	return (0);
}
