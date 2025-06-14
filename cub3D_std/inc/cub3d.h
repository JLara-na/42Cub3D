/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:55:53 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/19 20:57:38 by jlara-na         ###   ########.fr       */
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
# include "automata.h"
# include "ansi_defines.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
//-----------------------------------DEFINES----------------------------------//

//42 settings
// # define W_X					2160
// # define W_Y					1080
// # define WH_X					1080
// # define WH_Y					540
// # define RAY_NUMBER				2160

# define W_X					1440
# define W_Y					720
# define WH_X					960
# define WH_Y					360
# define RAY_NUMBER				1440

//Home settings
// # define W_X					960
// # define W_Y					540
// # define WH_X					480
// # define WH_Y					270
// # define RAY_NUMBER				960

# define PI						3.14159265359
# define _2PI					6.28318530718
# define PI2					1.57079632679	//	PI / 2
# define _3PI2					4.71238898038	//	(3 * PI) / 2
# define DR						0.0174533	//	One degree in radians
# define FOV					1.57079632679	//	FOV in radians (90º)
# define SENSITIVITY			0.05
# define SENSITIVITYX_CAP		10
# define DEPTH_OF_FIELD			100
# define COLISION_DISTANCE		10
# define MP_CUBE				8
# define MP_SIDE				8

# define ERROR_LOCATION			"Error location: "
# define ERROR_WRITE			"Error write()"
# define ERROR_MLX_START		"start_mlx() in src/main/main.c:17:9"

# define BYE_MSG				"Bye!"

//-----------------------------------STRUCTS----------------------------------//

typedef enum e_cardinal
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_cardinal;

typedef enum e_color_fc
{
	FLOOR,
	CEILING
}	t_color_fc;

typedef struct s_parse_flags
{
	int				n_f;
	int				s_f;
	int				w_f;
	int				e_f;
	int				f_f;
	int				c_f;
	int				map_f;

}				t_parse_flags;

typedef struct s_ray
{
	int				color;		//color
	int				i;			//iter
	int				mx;			//map x
	int				my;			//map y
	int				mx_sxo;		//map x - xo
	int				my_syo;		//map y - yo
	int				mx_axo;		//map x + xo
	int				my_ayo;		//map y + yo
	int				mp;			//map pos (ver si la vamos a necesitar)
	int				dof;		//depth of field
	float			rx;			//ray x
	float			ry;			//ray y
	float			ra;			//ray angle
	float			dra;		//ray angle delta
	float			xo;			//x offset
	float			yo;			//y offset
	float			atan;		//tangent of a
	float			ntan;		//negative tangent of a
	float			hdis;		//distancia horizontal
	float			hx;			//x de la colision horizontal
	float			hy;			//y de la colision horizontal
	float			vdis;		//distancia vertical
	float			vx;			//x de la colision vertical
	float			vy;			//y de la colision vertical
	float			tdis;		//distancia mas corta de las dos
	float			lineh;		//altura de la pared 3D
	float			lineo;		//offset de la pared 3D
	float			ca;			//angulo resultante de la resta del angulo de
								//camara y el del rayo (para quitar fish-eye)
	float			tx;			//textura x
	float			ty;			//textura y
	float			tx_step;	//textura x_step
	float			ty_step;	//textura y_step
	float			tx_o;		//textura x_offset
	float			ty_o;		//textura y_offset
}				t_ray;

typedef struct s_cam
{
	char			**map_c;
	char			init_angle;
	int				map_surface;
	int				map_h;
	int				map_w;
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
	t_img	img_wall[4];
}				t_mlx;

typedef struct s_cub3d
{
	t_mlx			mlx;
	t_cam			cam;
	t_parse_flags	p_f;
	int				color[2];
	char			**texture_path;
}				t_cub3d;

//----------------------------------FUNCTIONS---------------------------------//

void	terminate(char *msg, int exit_status);
void	put_frame(t_cub3d	*cub3d);
int		init_all(t_cub3d	*cub3d);
int		parse(int ac, char	**av, t_cub3d	*cub3d);
int		map_checker(t_cub3d	*cub3d);
int		paths_checker(t_cub3d	*cub3d);

//----------------------------------RAYCAST FT--------------------------------//

void	raycast_frame(t_cam	*cam, t_mlx	*mlx);
void	init_ray(t_cam	*cam, t_ray *ray);
void	cast_horizontal(t_cam	*cam, t_ray *ray);
void	cast_vertical(t_cam	*cam, t_ray *ray);
void	pick_collision(t_cam *cam, t_ray *ray);
void	fish_eye_fix(t_cam	*cam, t_ray *ray);
void	wall_size_and_place(t_cam	*cam, t_ray *ray);
void	print_wall(t_cam *cam, t_mlx *mlx, t_ray *ray);

//----------------------------------UTILS FT----------------------------------//

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	get_sizes(t_cub3d	*cub3d);
char	get_map(t_cam *cam, int x, int y);
int		valid_map_line(char *line);
int		ft_sarray_size(char	**sarr);
int		get_pixel_img(t_img *img, int x, int y);
float	pitagoras(float ax, float ay, float bx, float by);

//--------------------------------HOOK FUNCTIONS------------------------------//

void	change_cam(t_cub3d	*cub3d, int side, float sensitivity);
void	loop_and_hooks(t_cub3d	*cub3d);

#endif