/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:33:46 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/06 20:41:04 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	store_file(char	**av, char	***file)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	*file = ft_add_to_sarray(*file, line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		*file = ft_add_to_sarray(*file, line);
		free(line);
	}
	close(fd);
	if (*file)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	extract_elements(char	*str, t_cub3d *cub3d)
{
	t_automata	a;
	int			state;

	if (ft_samestr(str, "\n"))
		return (1);
	automata_init(&a, cub3d);
	a.str = ft_strtrim(str, "\n");
	state = evaluate(&a);
	if (state > a.errorlen)
		printf("%s in %s", a.errors[state], str);
	free_alph_err(&a);
	free(a.str);
	return (1);
}

int	extract_map(char	**file, t_cub3d *cub3d)
{
	int	i;

	(void)cub3d;
	i = 0;
	cub3d->cam.map_c = calloc(1, sizeof(char **));
	while (file[i] && ft_samestr(file[i], "\n"))
		i++;
	while (file[i])
	{
		if (valid_map_line(file[i]) != 0)
			cub3d->cam.map_c = ft_add_to_sarray(cub3d->cam.map_c, file[i]);
		else
			terminate("Map contains invalid characters\n", 1);
		i++;
	}
	return (0);
}

int	extract_data(char	**file, t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (file[++i] && (!cub3d->p_f.c_f || !cub3d->p_f.f_f
			|| !cub3d->p_f.n_f || !cub3d->p_f.s_f || !cub3d->p_f.w_f
			|| !cub3d->p_f.e_f))
		extract_elements(file[i], cub3d);
	extract_map(file += i, cub3d);
	return (0);
}

int	parse(int ac, char	**av, t_cub3d	*cub3d)
{
	char	**file;

	file = NULL;
	ft_bzero(cub3d, sizeof(t_cub3d));
	cub3d->texture_path = calloc(5, sizeof(char *));
	if (ac != 2 || !ft_str_end_with(av[1], ".cub"))
		return (EXIT_FAILURE);
	if (store_file(av, &file))
		return (EXIT_FAILURE);
	if (extract_data(file, cub3d))
		return (EXIT_FAILURE);
	ft_free_sarray(file);
	if (map_checker(cub3d))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
