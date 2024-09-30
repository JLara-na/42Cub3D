/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 01:00:26 by jlara-na          #+#    #+#             */
/*   Updated: 2024/09/30 16:51:38 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	if (x < 0 || x >= W_X || y < 0 || y >= W_Y)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bppx / 8));
	*(unsigned int *)dst = color;
}

float	pitagoras(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	get_map(int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	const int	states[8][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	};

	return (states[y][x]);
}

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
				my_mlx_pixel_put(&cub3d->mlx.img, x, y, 0x0016c148);
			else
				my_mlx_pixel_put(&cub3d->mlx.img, x, y, 0x00169fcf);
		}
	}
}

void	square_wall(t_cub3d	*cub3d, int x, int y, int color)
{
	int	xau;
	int	yau;

	yau = -1;
	while (++yau < cub3d->cam.map_s - 1)
	{
		xau = -1;
		while (++xau < cub3d->cam.map_s - 1)
			my_mlx_pixel_put(&cub3d->mlx.img, xau + (cub3d->cam.map_s * x),
				yau + (cub3d->cam.map_s * y), color);
	}
}

void	put_walls(t_cub3d	*cub3d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 8)
	{
		x = -1;
		while (++x < 8)
		{
			if (get_map(x, y) == 1)
				square_wall(cub3d, x, y, 0x00ff9836);
			else
				square_wall(cub3d, x, y, 0x00ffad6c);
		}
	}
}

void	put_player(t_cub3d	*cub3d)
{
	int	side;

	side = -1;
	while (++side < 16)
		my_mlx_pixel_put(&cub3d->mlx.img, cub3d->cam.x - 8 + side, cub3d->cam.y - 8, 0x0000FFFF);
	side = -1;
	while (++side < 16)
		my_mlx_pixel_put(&cub3d->mlx.img, cub3d->cam.x - 8 + side, cub3d->cam.y + 8, 0x0000FFFF);
	side = -1;
	while (++side < 16)
		my_mlx_pixel_put(&cub3d->mlx.img, cub3d->cam.x - 8, cub3d->cam.y - 8  + side, 0x0000FFFF);
	side = -1;
	while (++side < 16)
		my_mlx_pixel_put(&cub3d->mlx.img, cub3d->cam.x + 8, cub3d->cam.y - 8  + side, 0x0000FFFF);
	int	xau;
	int	yau;

	yau = -3;
	while (++yau < 3)
	{
		xau = -3;
		while (++xau < 3)
			my_mlx_pixel_put(&cub3d->mlx.img, cub3d->cam.x + cub3d->cam.dx + xau, cub3d->cam.y + cub3d->cam.dy + yau, 0x00FF0000);
	}
}

void	draw_ray(t_cam	*cam, t_mlx	*mlx)
{
	t_ray	r;

	ft_bzero(&r, sizeof(t_ray));
	r.ra = cam->a - (DR * (CUB3D_FOV / 2));
	if (r.ra < 0)
		r.ra += 2 * PI;
	if (r.ra > 2 * PI)
		r.ra -= 2 * PI;
	while (r.i++ < CUB3D_FOV) // AQUI LE DECIMOS EL ANGULO DEL FOV
	{
		//comprobar horizontales----------------------------------------------------------------------
		r.dof = 0;
		r.hdis = 1000000; // al buscar la distancia mas corta lo iniciamos con un valor alto
		r.hx = cam->x;
		r.hy = cam->y;
		r.atan = -1 / tan(r.ra);
		if (r.ra > PI) // looking up
		{
			r.ry = (((int)cam->y >> 6) << 6) - 0.0001;
			r.rx = (cam->y - r.ry) * r.atan + cam->x;
			r.yo = -64;
			r.xo = -r.yo * r.atan;
		}
		if (r.ra < PI)// looking down
		{
			r.ry = (((int)cam->y >> 6) << 6) + 64;
			r.rx = (cam->y - r.ry) * r.atan + cam->x;
			r.yo = 64;
			r.xo = -r.yo * r.atan;
		}
		if (r.ra == 0 || r.ra == PI) // looing right or left
		{
			r.rx = cam->x;
			r.ry = cam->y;
			r.dof = 8;
		}
		while (r.dof < 8)
		{
			r.mx = (int)(r.rx) >> 6;
			r.my = (int)(r.ry) >> 6;
			r.mp = r.my * 8 + r.mx;
			if (r.mp < 64 && get_map(r.mx, r.my) == 1)
			{
				r.hx = r.rx;
				r.hy = r.ry;
				r.hdis = pitagoras(cam->x, cam->y, r.hx, r.hy);
				r.dof = 8;
			}
			else
			{
				r.rx += r.xo;
				r.ry += r.yo;
				r.dof += 1;
			}
		}
		//comprobar verticales--------------------------------------------------------------------------
		r.dof = 0;
		r.vdis = 1000000; // al buscar la distancia mas corta lo iniciamos con un valor alto
		r.vx = cam->x;
		r.vy = cam->y;
		r.ntan = -tan(r.ra);
		if (r.ra > P2 && r.ra < P3) // looking left
		{
			r.rx = (((int)cam->x >> 6) << 6) - 0.0001;
			r.ry = (cam->x - r.rx) * r.ntan + cam->y;
			r.xo = -64;
			r.yo = -r.xo * r.ntan;
		}
		if (r.ra < P2 || r.ra > P3)// looking rigth
		{
			r.rx = (((int)cam->x >> 6) << 6) + 64;
			r.ry = (cam->x - r.rx) * r.ntan + cam->y;
			r.xo = 64;
			r.yo = -r.xo * r.ntan;
		}
		if (r.ra == 0 || r.ra == PI) // looing up or down
		{
			r.rx = cam->x;
			r.ry = cam->y;
			r.dof = 8;
		}
		while (r.dof < 8)
		{
			r.mx = (int)(r.rx) >> 6;
			r.my = (int)(r.ry) >> 6;
			r.mp = r.my * 8 + r.mx;
			if (r.mp < 64 && get_map(r.mx, r.my) == 1)
			{
				r.vx = r.rx;
				r.vy = r.ry;
				r.vdis = pitagoras(cam->x, cam->y, r.vx, r.vy);
				r.dof = 8;
			}
			else
			{
				r.rx += r.xo;
				r.ry += r.yo;
				r.dof += 1;
			}
		}
		//AQUI COMPROBAMOS CUAL DE LAS DOS ES LA DISTANCIA MAS CORTA Y LA ELEGIMOS COMO DEFAULT
		if (r.vdis < r.hdis)
		{
			r.rx = r.vx;
			r.ry = r.vy;
			r.tdis = r.vdis;
			r.color = 0x0080aaff; // COLOR DE LA PARED VERTICAL
		}
		if (r.hdis < r.vdis)
		{
			r.rx = r.hx;
			r.ry = r.hy;
			r.tdis = r.hdis;
			r.color = 0x00809bff; // COLOR DE LA PARED HORIZONTAL
		}
		//AQUI IMPRIMIMOS EL PUNTO DONDE TOCA LA PARED---------------------------------
		int	xau;
		int	yau;
		yau = -3;
		while (++yau < 3)
		{
			xau = -3;
			while (++xau < 3)
				my_mlx_pixel_put(&mlx->img, r.rx + xau, r.ry + yau, 0x00FF0000);
		}
		//AQUI ES DONDE HAREMOS EL 3D--------------------------------------------OJITO
		r.ca = cam->a - r.ra; // ARREGLO DEL FISH-EYE
		if (r.ca < 0)
			r.ca += 2 * PI;
		if (r.ca < 2 * PI)
			r.ca -= 2 * PI;
		r.tdis *= cos(r.ca);
		r.lineh = (cam->map_s * W_Y) / r.tdis;	// CALCULO DE LA ALTURA DE LA PARED
		if (r.lineh > W_Y)
			r.lineh = W_Y;
		r.lineo = ((W_Y / 2) - (r.lineh / 2));	// CALCULO DEL OFFSET DE LA PARED
		//IMPRIMIMOS LINEA
		yau = -1;
		while (++yau < r.lineh)
		{
			xau = -1;
			while (++xau < (W_X) / CUB3D_FOV)
				my_mlx_pixel_put(&mlx->img, xau + r.i * ((W_X) / CUB3D_FOV) , yau + r.lineo, r.color);
		}

		//-----------------------------------------------------------------------------
		//AQUI VOLVEMOS A ANADIR UN GRADO MAS Y COMPROBAMOS LIMITES
		r.ra += DR;
		if (r.ra < 0)
			r.ra += 2 * PI;
		if (r.ra > 2 * PI)
			r.ra -= 2 * PI;
	}
}

void	test(t_cub3d	*cub3d)
{
	put_backgrownd(cub3d);
	draw_ray(&cub3d->cam, &cub3d->mlx);
	put_walls(cub3d);
	put_player(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
	 	cub3d->mlx.img.img_instance, 0, 0);
}

void	wasd(t_cub3d	*cub3d, int key)
{
	if (key == XK_a)
	{
		cub3d->cam.x += cub3d->cam.dy;
		cub3d->cam.y -= cub3d->cam.dx;
	}
	if (key == XK_w)
	{
		cub3d->cam.x += cub3d->cam.dx;
		cub3d->cam.y += cub3d->cam.dy;
	}
	if (key == XK_d)
	{
		cub3d->cam.x -= cub3d->cam.dy;
		cub3d->cam.y += cub3d->cam.dx;
	}
	if (key == XK_s)
	{
		cub3d->cam.x -= cub3d->cam.dx;
		cub3d->cam.y -= cub3d->cam.dy;
	}
}

void	lurd(t_cub3d	*cub3d, int key)
{
	if (key == XK_Left)
	{
		cub3d->cam.a -= 0.1;
		if (cub3d->cam.a < 0)
			cub3d->cam.a += 2 * PI;
		cub3d->cam.dx = cos(cub3d->cam.a) * 5;
		cub3d->cam.dy = sin(cub3d->cam.a) * 5;
	}
	if (key == XK_Right)
	{
		cub3d->cam.a += 0.1;
		if (cub3d->cam.a > (2 * PI))
			cub3d->cam.a -= 2 * PI;
		cub3d->cam.dx = cos(cub3d->cam.a) * 5;
		cub3d->cam.dy = sin(cub3d->cam.a) * 5;
	}
}

void	move_cam(t_cub3d	*cub3d, int key)
{
	wasd(cub3d, key);
	lurd(cub3d, key);
	test(cub3d);
}
