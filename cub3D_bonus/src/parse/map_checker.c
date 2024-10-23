/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:58:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/19 21:25:31 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	one_player(t_cub3d	*cub3d)
{
	int	i;
	int	j;
	int	player_n;

	i = -1;
	player_n = 0;
	while (cub3d->cam.map_c[++i])
	{
		j = -1;
		while (cub3d->cam.map_c[i][++j])
		{
			if (ft_chrpos("NSEW", cub3d->cam.map_c[i][j]) != -1)
			{
				cub3d->cam.init_angle = cub3d->cam.map_c[i][j];
				player_n++;
			}
		}
	}
	if (player_n != 1)
		return (1);
	return (0);
}

void	make_square(t_cub3d	*cub3d)
{
	int		i;
	char	*trim;
	size_t	longer;

	i = -1;
	longer = ft_strlen(cub3d->cam.map_c[i+1]);
	while (cub3d->cam.map_c[++i])
		if (longer < ft_strlen(cub3d->cam.map_c[i]))
			longer = ft_strlen(cub3d->cam.map_c[i]);
	i = -1;
	while (cub3d->cam.map_c[++i])
	{
		if (longer >= ft_strlen(cub3d->cam.map_c[i]))
		{
			trim = ft_strtrim(cub3d->cam.map_c[i], "\n");
			free(cub3d->cam.map_c[i]);
			cub3d->cam.map_c[i] = trim;
			while (longer > ft_strlen(cub3d->cam.map_c[i]))
				cub3d->cam.map_c[i] = ft_strjoinfree(cub3d->cam.map_c[i],
						" ", 0);
			cub3d->cam.map_c[i] = ft_strjoinfree(cub3d->cam.map_c[i], "\n", 0);
		}
	}
	cub3d->cam.map_w = longer;
	cub3d->cam.map_h = i;
}

void	the_flood(char	**map, int s, int c, int size)
{
	if (map[s][c] != ' ')
		terminate("No esta bien cerrado", 1);
	map[s][c] = '.';
	if (map[s][c + 1] && ft_chrpos("1.\n", map[s][c + 1]) == -1)
		the_flood(map, s, c + 1, size);
	if (c && map[s][c - 1] && ft_chrpos("1.\n", map[s][c - 1]) == -1)
		the_flood(map, s, c - 1, size);
	if (s != size && map[s + 1][c] && ft_chrpos("1.\n", map[s + 1][c]) == -1)
		the_flood(map, s + 1, c, size);
	if (s && map[s - 1][c] && ft_chrpos("1.\n", map[s - 1][c]) == -1)
		the_flood(map, s - 1, c, size);
}

void	flood_space(t_cub3d	*cub3d)
{
	int	size;
	int	i;
	int	j;

	size = ft_sarray_size(cub3d->cam.map_c);
	i = -1;
	while (cub3d->cam.map_c[++i])
	{
		j = -1;
		while (cub3d->cam.map_c[i][++j])
			if (cub3d->cam.map_c[i][j] == ' ')
				the_flood(cub3d->cam.map_c, i, j, size - 1);
	}
}

int	map_checker(t_cub3d	*cub3d)
{
	if (one_player(cub3d))
		return (EXIT_FAILURE);
	make_square(cub3d);
	flood_space(cub3d);
	get_sizes(cub3d);
	return (EXIT_SUCCESS);
}
