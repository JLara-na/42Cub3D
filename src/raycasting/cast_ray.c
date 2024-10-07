/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:59:52 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/07 04:17:49 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*set the starting coordinates of the horizontal and vertical ray at the cam 
coordinates, also set the colision distance to a big number(so its always bigger
than the result of its calculation).*/
void	init_ray(t_cam	*cam, t_ray *ray)
{
	ray->hdis = 1000000;
	ray->hx = cam->x;
	ray->hy = cam->y;
	ray->atan = -1 / tan(ray->ra);
	ray->vdis = 1000000;
	ray->vx = cam->x;
	ray->vy = cam->y;
	ray->ntan = -tan(ray->ra);
}

/*get the position of the ray in the map if it is a 1(WALL) it calculates the
distance to the cam using pitagoras theorem as it is the hypotenuse of the
triangle formed by the two cathetus being increments in x and y*/
void	look_for_horizontal_walls(t_cam	*cam, t_ray *ray)
{
	ray->mx = (int)(ray->rx) / 64;
	ray->my = (int)(ray->ry) / 64;
	ray->mp = ray->my * cam->map_w + ray->mx;
	if (ray->mp < cam->map_h * cam->map_w
		&& get_map(cam, ray->mx, ray->my) == '1')
	{
		ray->hx = ray->rx;
		ray->hy = ray->ry;
		ray->hdis = pitagoras(cam->x, cam->y, ray->hx, ray->hy);
		ray->dof = DEPTH_OF_FIELD;
	}
	else
	{
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->dof += 1;
	}
}

/*get the position of the ray in the map if it is a 1(WALL) it calculates the
distance to the cam using pitagoras theorem as it is the hypotenuse of the
triangle formed by the two cathetus being increments in x and y*/
void	look_for_vertical_walls(t_cam	*cam, t_ray *ray)
{
	ray->mx = (int)(ray->rx) / 64;
	ray->my = (int)(ray->ry) / 64;
	ray->mp = ray->my * cam->map_w + ray->mx;
	if (ray->mp < cam->map_h * cam->map_w
		&& get_map(cam, ray->mx, ray->my) == '1')
	{
		ray->vx = ray->rx;
		ray->vy = ray->ry;
		ray->vdis = pitagoras(cam->x, cam->y, ray->vx, ray->vy);
		ray->dof = DEPTH_OF_FIELD;
	}
	else
	{
		ray->rx += ray->xo;
		ray->ry += ray->yo;
		ray->dof += 1;
	}
}

/*depending on the angle of the ray(be it bigger than PI, smoller, 0 or PI rads)
it will look for colisions between the ray and any horizontal walls a m=number
of times equal to the DEPTH_OF_FIELD*/
void	cast_horizontal(t_cam	*cam, t_ray *ray)
{
	ray->dof = 0;
	if (ray->ra > PI)
	{
		ray->ry = (((int)cam->y >> 6) << 6) - 0.0001;
		ray->rx = (cam->y - ray->ry) * ray->atan + cam->x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->atan;
	}
	if (ray->ra < PI)
	{
		ray->ry = (((int)cam->y >> 6) << 6) + 64;
		ray->rx = (cam->y - ray->ry) * ray->atan + cam->x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->atan;
	}
	if (ray->ra == 0 || ray->ra == PI)
	{
		ray->rx = cam->x;
		ray->ry = cam->y;
		ray->dof = DEPTH_OF_FIELD;
	}
	while (ray->dof < DEPTH_OF_FIELD)
		look_for_horizontal_walls(cam, ray);
}

/*depending on the angle of the ray (be it between PI/2 and 3*PI/2, between
3*PI/2 and PI/2, PI/2 or 3*PI/2 rads), it will look for colisions between the
ray and any horizontal walls a m=number of times equal to the DEPTH_OF_FIELD*/
void	cast_vertical(t_cam	*cam, t_ray *ray)
{
	ray->dof = 0;
	if (ray->ra > PI2 && ray->ra < _3PI2)
	{
		ray->rx = (((int)cam->x >> 6) << 6) - 0.0001;
		ray->ry = (cam->x - ray->rx) * ray->ntan + cam->y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->ntan;
	}
	if (ray->ra < PI2 || ray->ra > _3PI2)
	{
		ray->rx = (((int)cam->x >> 6) << 6) + 64;
		ray->ry = (cam->x - ray->rx) * ray->ntan + cam->y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->ntan;
	}
	if (ray->ra == PI2 || ray->ra == _3PI2)
	{
		ray->rx = cam->x;
		ray->ry = cam->y;
		ray->dof = DEPTH_OF_FIELD;
	}
	while (ray->dof < DEPTH_OF_FIELD)
		look_for_vertical_walls(cam, ray);
}
