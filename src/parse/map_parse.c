/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:33:46 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/05 23:02:53 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_str_end_with(const char *str, const char *end)
{
	int	len_a;
	int	len_b;

	len_a = ft_strlen(str);
	len_b = ft_strlen(end);
	if (len_b > len_a)
		return (0);
	while (len_b > 0)
	{
		if (str[len_a] != end[len_b])
			return (0);
		len_a--;
		len_b--;
	}
	return (1);
}

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

int	extract_data(char	**file, t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (file[++i] && (!cub3d->p_f.c_f || !cub3d->p_f.f_f
			|| !cub3d->p_f.n_f || !cub3d->p_f.s_f || !cub3d->p_f.w_f
			|| !cub3d->p_f.e_f))
		extract_elements(file[i], cub3d);
	printf("la linea -> %d\n", i);
	// extract_map(file += i);
	return (0);
}

int	parse(int ac, char	**av, t_cub3d	*cub3d)
{
	char	**file;

	file = NULL;
	ft_bzero(cub3d, sizeof(t_cub3d));
	cub3d->texture_path = calloc(5, sizeof(char *));
	if (ac != 2 || !ft_str_end_with(av[1], ".cub"))
		return (EXIT_FAILURE); // ERROR DE ARGUMENTOS
	if (store_file(av, &file))
		return (EXIT_FAILURE); // ERROR DE LECTURA (mapa vacio o error de open)
	if (extract_data(file, cub3d))
	 	return (EXIT_FAILURE);
	for(int i = -1; file[++i]; NULL)
		printf("%s", file[i]);
	ft_free_sarray(file);
	return (EXIT_SUCCESS);
}
