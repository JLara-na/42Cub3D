/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:59:29 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 16:10:34 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	valid_map_line(char *line)
{
	int		i;

	if (!line || ft_samestr(line, "\n"))
		return (0);
	i = 0;
	if (ft_chrpos(" 1", line[0]) == -1)
		return (0);
	while (line[i])
	{
		if (ft_chrpos(" 10NSWE\n", line[i]) != -1)
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_sarray_size(char	**sarr)
{
	int	size;
	int	i;

	i = -1;
	size = 0;
	while (sarr[++i])
		size++;
	return (size);
}

void	map_iter_context(char **map, void (*f)(void *, int x, int y),
	void *data)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			f(data, x, y);
			x++;
		}
		y++;
	}
}

void	get_player_pos(void	*data, int x, int y)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)data;
	if (ft_chrpos("NSWE", cub3d->cam.map_c[y][x]) != -1)
	{
		cub3d->cam.x = 32 + (64 * x);
		cub3d->cam.y = 32 + (64 * y);
	}
}

void	get_sizes(t_cub3d	*cub3d)
{
	map_iter_context(cub3d->cam.map_c, get_player_pos, cub3d);
}
