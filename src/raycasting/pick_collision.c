/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:25:57 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/08 14:30:04 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*Pick between the horizontal or the vertical cast depending on wich one
intersects with a wall closer to the cam and sets the wall color*/
void	pick_collision(t_cam *cam, t_ray *ray)
{
	(void)cam;
	if (ray->vdis < ray->hdis)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->tdis = ray->vdis;
	}
	if (ray->hdis < ray->vdis)
	{
		ray->rx = ray->hx;
		ray->ry = ray->hy;
		ray->tdis = ray->hdis;
	}
}
