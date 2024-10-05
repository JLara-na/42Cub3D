/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 23:15:45 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/05 15:28:08 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d.h"

//  \s  F  C 10  c other
int	get_state(int i, int j)
{
	const int	states[][5] = {
	{0, 4, 6, 3, 3, 3},	// 0 looking
	{3, 1, 1, 1, 1, 1},	// 1 PATH
	{3, 3, 3, 2, 7, 3},	// 2 NUM VALUE 
	{3, 3, 3, 3, 3, 3},	// 3 INVALID
	{3, 5, 3, 3, 3, 3},	// 4 FLAG1
	{8, 3, 3, 3, 3, 3},	// 5 FLAG2
	{9, 3, 3, 3, 3, 3},	// 6 COLOR
	{3, 3, 3, 2, 3, 3},	// 7 ,
	{8, 1, 1, 1, 1, 1},	// 8 SPACE_BETWEEN FLAG2 AND PATH
	{9, 3, 3, 2, 3, 3},	// 9 SPACE_BETWEEN COLOR AND NUM_VALUE
	};

	return (states[i][j]);
}
