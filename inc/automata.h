/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:11:21 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/05 00:39:55 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATA_H
# define AUTOMATA_H

typedef struct s_automata
{
	void	*data;
	char	**alphabet;
	char	**errors;
	char	*str;
	int		state;
	int		ostate;
	int		errorlen;
	int		i;
	int		j;
	void	(*fsa[20])(struct s_automata *a, void *data);
	void	(*fta[20][20])(struct	s_automata
			*a, void
			*data);
	int		(*get_state)(int state, int abc_idx);
}			t_automata;

//---------------------------------AUTOMATA FT--------------------------------//

int			evaluate(t_automata *a);
int			get_state(int i, int j);
void		free_alph_err(t_automata *a);
void		automata_init(t_automata *a, void *data);

//----------------------------------ACTIONS FT--------------------------------//



#endif