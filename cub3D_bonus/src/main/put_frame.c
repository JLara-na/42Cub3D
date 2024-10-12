/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 01:00:26 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/12 17:36:25 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_backgrownd(t_cub3d	*cub3d)
{
	int	x;
	int	y;

	y = W_Y;
	while (y--)
	{
		x = W_X;
		while (x--)
		{
			if (y > W_Y / 2)
				my_mlx_pixel_put(&cub3d->mlx.img, x, y, cub3d->color[FLOOR]);
			else
				my_mlx_pixel_put(&cub3d->mlx.img, x, y, cub3d->color[CEILING]);
		}
	}
}
