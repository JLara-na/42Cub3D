/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:14:22 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 17:17:53 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

void	free_alph_err(t_automata *a)
{
	int	i;

	i = -1;
	if (a->alphabet)
	{
		while (a->alphabet[++i])
			free(a->alphabet[i]);
		free(a->alphabet);
	}
	i = -1;
	if (a->errors)
	{
		while (a->errors[++i])
			free(a->errors[i]);
		free(a->errors);
	}
}

int	idx(char *alphabet[], char c)
{
	int	i;

	i = -1;
	while (alphabet[++i])
		if (ft_chrpos(alphabet[i], c) != -1)
			return (i);
	return (i);
}

int	evaluate(t_automata *a)
{
	a->ostate = 0;
	a->i = -1;
	while (++a->i < (int)ft_strlen(a->str))
	{
		a->state = a->get_state(a->state, idx(a->alphabet, a->str[a->i]));
		if (a->fsa[a->state])
			a->fsa[a->state](a, a->data);
		if (a->fta[a->ostate][a->state])
			a->fta[a->ostate][a->state](a, a->data);
		a->ostate = a->state;
	}
	return (a->state);
}
