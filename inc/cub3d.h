/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:55:53 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/04 03:36:30 by jlara-na         ###   ########.fr       */
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

// # define W_X					3840
// # define W_Y					1920
// # define WH_X					1920
// # define WH_Y					960
//42 settings
// # define W_X					2160
// # define W_Y					1080
// # define WH_X					1080
// # define WH_Y					540
// # define RAY_NUMBER				2160

//Home settings
# define W_X					960
# define W_Y					540
# define WH_X					480
# define WH_Y					270
# define RAY_NUMBER				960

# define PI						3.14159265359
# define _2PI					6.28318530718
# define PI2					1.57079632679	//	PI / 2
# define _3PI2					4.71238898038	//	(3 * PI) / 2
// # define DR						0.0174533	//	One degree in radians
# define FOV					1.57079632679	//	FOV in radians (90)
# define SENSITIVITY			0.05
# define SENSITIVITYX_CAP		10
# define DEPTH_OF_FIELD			100
# define COLISION_DISTANCE		10

# define ERROR_LOCATION			"Error location: "
# define ERROR_WRITE			"Error write()"
# define ERROR_MLX_START		"start_mlx() in src/main/main.c:17:9"

# define BYE_MSG				"Bye!"

//-----------------------------------STRUCTS----------------------------------//

typedef struct s_ray
{
	int				color;			//color del sombreado
	int				i;				//iter
	int				mx;				//map x
	int				my;				//map y
	int				mx_sub_xo;		//map x - xo
	int				my_sub_yo;		//map y - yo
	int				mx_add_xo;		//map x + xo
	int				my_add_yo;		//map y + yo
	int				mp;				//map pos (ver si la vamos a necesitar)
	int				dof;			//depth of field
	float			rx;				//ray x
	float			ry;				//ray y
	float			ra;				//ray angle
	float			dra;			//ray angle delta
	float			xo;				//x offset
	float			yo;				//y offset
	float			atan;			//tangent of a
	float			ntan;			//negative tangent of a
	float			hdis;			//distancia horizontal
	float			hx;				//x de la colision horizontal
	float			hy;				//y de la colision horizontal
	float			vdis;			//distancia vertical
	float			vx;				//x de la colision vertical
	float			vy;				//y de la colision vertical
	float			tdis;			//distancia mas corta de las dos
	float			lineh;			//altura de la pared 3D
	float			lineo;			//offset de la pared 3D
	float			ca;			//angulo resultante de la resta del angulo de
								//camara y el del rayo (para quitar fish-eye)
}				t_ray;

typedef struct s_cam
{
	int				menu_flag;	//Flag que indica que el menu esta activo
	int				**map;		//Mapa en forma de matriz 2D
	int				map_s;		//
	float			dx;			//
	float			dy;			//
	float			a;			//Angulo camara
	float			x;			//Posicion camara x
	float			y;			//Posicion camara y
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

//----------------------------------RAYCAST FT--------------------------------//

void	init_ray(t_cam	*cam, t_ray *ray);
void	look_for_horizontal_walls(t_cam	*cam, t_ray *ray);
void	look_for_vertical_walls(t_cam	*cam, t_ray *ray);
void	cast_horizontal(t_cam	*cam, t_ray *ray);
void	cast_vertical(t_cam	*cam, t_ray *ray);
void	pick_collision(t_cam *cam, t_ray *ray);
void	fish_eye_fix(t_cam	*cam, t_ray *ray);
void	wall_size_and_place(t_cam	*cam, t_ray *ray);
void	print_wall(t_cam *cam, t_mlx *mlx, t_ray *ray);
void	raycast_frame(t_cam	*cam, t_mlx	*mlx);

//----------------------------------UTILS FT----------------------------------//

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
float	pitagoras(float ax, float ay, float bx, float by);

//--------------------------------HOOK FUNCTIONS------------------------------//

void	loop_and_hooks(t_cub3d	*cub3d);

int		controls(int keycode, t_cub3d *cub3d);
int		menu(t_cub3d *cub3d);

// TEST FUNCTIONS

void	put_frame(t_cub3d	*cub3d);
int		get_map(int x, int y);
void	change_cam(t_cub3d	*cub3d, int side, float sensitivity);

#endif