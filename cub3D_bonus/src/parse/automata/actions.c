/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:37:58 by jlara-na          #+#    #+#             */
/*   Updated: 2025/04/14 15:25:10 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	automata_terminate(t_automata	*a, void	*data)
{
	(void)data;
	terminate(a->errors[INVALID], 1);
}

void	flag_identifier(t_automata	*a, void	*data)
{
	t_cub3d			*cub3d;
	t_parse_flags	f;

	cub3d = (t_cub3d *)data;
	f = cub3d->p_f;
	if (a->str[a->i - 2] == 'N' && a->str[a->i - 1] == 'O' && !f.n_f)
		cub3d->p_f.n_f = 1;
	else if (a->str[a->i - 2] == 'S' && a->str[a->i - 1] == 'O' && !f.s_f)
		cub3d->p_f.s_f = 1;
	else if (a->str[a->i - 2] == 'W' && a->str[a->i - 1] == 'E' && !f.w_f)
		cub3d->p_f.w_f = 1;
	else if (a->str[a->i - 2] == 'E' && a->str[a->i - 1] == 'A' && !f.e_f)
		cub3d->p_f.e_f = 1;
	else
		terminate(a->errors[INVALID], 1);
}

void	store_path(t_automata	*a, void	*data)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)data;
	if (cub3d->p_f.n_f == 1)
	{
		cub3d->texture_path[NORTH] = ft_strdup(a->str + a->i);
		cub3d->p_f.n_f = 2;
	}
	else if (cub3d->p_f.s_f == 1)
	{
		cub3d->texture_path[SOUTH] = ft_strdup(a->str + a->i);
		cub3d->p_f.s_f = 2;
	}
	else if (cub3d->p_f.w_f == 1)
	{
		cub3d->texture_path[WEST] = ft_strdup(a->str + a->i);
		cub3d->p_f.w_f = 2;
	}
	else if (cub3d->p_f.e_f == 1)
	{
		cub3d->texture_path[EAST] = ft_strdup(a->str + a->i);
		cub3d->p_f.e_f = 2;
	}
	else
		terminate(a->errors[INVALID], 1);
}

void	color_identifier(t_automata	*a, void	*data)
{
	t_cub3d			*cub3d;
	t_parse_flags	f;

	cub3d = (t_cub3d *)data;
	f = cub3d->p_f;
	if (a->str[a->i - 1] == 'F' && !f.f_f)
		cub3d->p_f.f_f = 1;
	else if (a->str[a->i - 1] == 'C' && !f.c_f)
		cub3d->p_f.c_f = 1;
	else
		terminate(a->errors[INVALID], 1);
}

void	store_color(t_automata	*a, void	*data)
{
	t_cub3d	*cub3d;
	char	*rgb;

	cub3d = (t_cub3d *)data;
	if (cub3d->p_f.f_f == 1)
	{
		rgb = ft_strdup(a->str + a->i);
		cub3d->color[FLOOR] = rgb_ok(rgb);
		cub3d->p_f.f_f = 2;
		free(rgb);
	}
	else if (cub3d->p_f.c_f == 1)
	{
		rgb = ft_strdup(a->str + a->i);
		cub3d->color[CEILING] = rgb_ok(rgb);
		cub3d->p_f.c_f = 2;
		free(rgb);
	}
	else
		terminate(a->errors[INVALID], 1);
}
