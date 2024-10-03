/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 03:31:13 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/03 04:05:19 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*Prints the result of the raycast into the mlx img (a frame)*/
void	raycast_frame(t_cam	*cam, t_mlx	*mlx)
{
	t_ray	r;

	ft_bzero(&r, sizeof(t_ray));
	r.ra = cam->a - (DR * (CUB3D_FOV / 2));
	if (r.ra < 0)
		r.ra += _2PI;
	if (r.ra > _2PI)
		r.ra -= _2PI;
	while (r.i++ < CUB3D_FOV)
	{
		init_ray(cam, &r);
		cast_horizontal(cam, &r);
		cast_vertical(cam, &r);
		pick_collision(cam, &r);
		fish_eye_fix(cam, &r);
		wall_size_and_place(cam, &r);
		print_wall(cam, mlx, &r);
		r.ra += DR;
		if (r.ra < 0)
			r.ra += _2PI;
		if (r.ra > _2PI)
			r.ra -= _2PI;
	}
}
