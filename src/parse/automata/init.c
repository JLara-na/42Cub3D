/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 00:32:56 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/05 15:40:05 by jlara-na         ###   ########.fr       */
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
	a->errors[3] = ft_strdup("INVALID FILE SYNTAX");
	a->errors[4] = ft_strdup("FLAG 1 OPEN");
	a->errors[5] = ft_strdup("FLAG 2 OPEN");
	a->errors[6] = ft_strdup("COLOR FLAG OPEN");
	a->errors[7] = ft_strdup("COMMA OPEN");
	a->errors[8] = ft_strdup("NO PATH ENCOUNTERED");
	a->errors[9] = ft_strdup("NO COLOR ENCOUNTERED");
	a->errors[10] = NULL;
	a->errorlen = 2;
}

void	sactions_init(t_automata *a)
{
	(void)a;
}

void	tactions_init(t_automata *a)
{
	(void)a;
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