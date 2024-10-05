/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:32:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/05 21:32:36 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	alphabet_init(t_automata *a)
{
	a->alphabet = malloc(6 * (sizeof(char *)));
	a->alphabet[0] = ft_strdup(" \t");
	a->alphabet[1] = ft_strdup("NOSWEA");
	a->alphabet[2] = ft_strdup("FC");
	a->alphabet[3] = ft_strdup("0123456789");
	a->alphabet[4] = ft_strdup(",");
	a->alphabet[5] = NULL;
}

void	errors_init(t_automata *a)
{
	a->errors = malloc(11 * (sizeof(char *)));
	a->errors[0] = ft_strdup("");
	a->errors[1] = ft_strdup("");
	a->errors[2] = ft_strdup("");
	a->errors[3] = ft_strdup("INVALID FILE SYNTAX\n");
	a->errors[4] = ft_strdup("FLAG 1 OPEN\n");
	a->errors[5] = ft_strdup("FLAG 2 OPEN\n");
	a->errors[6] = ft_strdup("COLOR FLAG OPEN\n");
	a->errors[7] = ft_strdup("COMMA OPEN\n");
	a->errors[8] = ft_strdup("NO PATH ENCOUNTERED\n");
	a->errors[9] = ft_strdup("NO COLOR ENCOUNTERED\n");
	a->errors[10] = NULL;
	a->errorlen = 2;
}

void	sactions_init(t_automata *a)
{
	a->fsa[INVALID] = automata_terminate;
}

void	tactions_init(t_automata *a)
{
	a->fta[FLAG2][SPACE_FP] = flag_identifier;
	a->fta[SPACE_FP][PATH] = store_path;
	a->fta[COLOR][SPACE_CN] = color_identifier;
	a->fta[SPACE_CN][NUM_VALUE] = store_color;
}

void	automata_init(t_automata *a, void *data)
{
	ft_bzero(a, sizeof(t_automata));
	a->data = data;
	alphabet_init(a);
	errors_init(a);
	sactions_init(a);
	tactions_init(a);
	a->get_state = get_state;
}