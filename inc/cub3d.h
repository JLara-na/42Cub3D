/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:55:53 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/30 16:45:09 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-----------------------------------INCLUDE----------------------------------//
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include "ansi_defines.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
//-----------------------------------DEFINES----------------------------------//

# define W_X					1910
# define W_Y					1024
# define PI						3.14159265359
# define P2						1.57079632679	//	PI / 2
# define P3						4.71238898038	//	(3 * PI) / 2
# define DR						0.0174533		//	One degree in radians
# define CUB3D_FOV				100

# define ERROR_LOCATION			"Error location: "
# define ERROR_WRITE			"Error write()"
# define ERROR_MLX_START		"start_mlx() in src/main/main.c:17:9"

# define BYE_MSG				"Bye!"

//-----------------------------------STRUCTS----------------------------------//

typedef struct s_ray
{
	int				color;	//color del sombreado
	int				i;		//iter
	int				mx;		//map x
	int				my;		//map y
	int				mp;		//map pos
	int				dof;	//depth of field
	float			rx;		//ray x
	float			ry;		//ray y
	float			ra;		//ray angle
	float			xo;		//x offset
	float			yo;		//y offset
	float			atan;	//tangent of a
	float			ntan;	//negative tangent of a
	float			hdis;	//distancia horizontal
	float			hx;		//x de la colision horizontal
	float			hy;		//y de la colision horizontal
	float			vdis;	//distancia vertical
	float			vx;		//x de la colision vertical
	float			vy;		//y de la colision vertical
	float			tdis;	//distancia mas corta de las dos
	float			lineh;	//altura de la pared 3D
	float			lineo;	//offset de la pared 3D
	float			ca;		//angulo resultante de la resta del angulo de la 
							//camara y el del rayo (para quitar fish-eye)
}				t_ray;

typedef struct s_cam
{
	int				**map;
	int				map_s;
	float			dx;
	float			dy;
	float			a;
	float			x;
	float			y;
}				t_cam;

typedef struct s_img
{
	void	*img_instance;
	char	*addr;
	int		bppx;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	void	*mlx_instance;
	void	*mlx_window;
	t_img	img;
}				t_mlx;

typedef struct s_cub3d
{
	t_mlx	mlx;
	t_cam	cam;
}	t_cub3d;

//----------------------------------FUNCTIONS---------------------------------//

int		init_all(t_cub3d	*cub3d);

void	terminate(char *msg, int exit_status);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//--------------------------------HOOK FUNCTIONS------------------------------//

void	loop_and_hooks(t_cub3d	*cub3d);

int		controls(int keycode, t_cub3d *cub3d);
int		menu(int keycode, t_cub3d *cub3d);

// TEST FUNCTIONS

void	test(t_cub3d	*cub3d);
void	move_cam(t_cub3d	*cub3d, int side);

#endif