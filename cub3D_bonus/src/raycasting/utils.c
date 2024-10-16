/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:54:09 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/15 00:08:24 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float	pitagoras(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

char	get_map(t_cam *cam, int x, int y)
{
	if (x < 0 || y < 0 || x > cam->map_w || y > cam->map_h)
		return (0);
	return (cam->map_c[y][x]);
}

float	deg_to_rad(float a)
{
	return (a * PI / 180.0);
}

float	fix_ang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}
