/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 01:35:16 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/25 20:05:30 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*Prints custom msg or ERROR_MSG, exit the program setting exit_status*/
void	terminate(char *msg, int exit_status)
{
	if (exit_status != EXIT_SUCCESS)
	{
		if (write(2, ERROR_LOCATION, ft_strlen(ERROR_LOCATION)))
			perror(msg);
		else
			perror(ERROR_WRITE);
	}
	else
		printf("%s\n", msg);
	exit(exit_status);
}

void	free_all(t_cub3d	*cub3d)
{
	ft_free_sarray(cub3d->texture_path);
	ft_free_sarray(cub3d->cam.map_c);
}

void	put_frame(t_cub3d	*cub3d)
{
	put_backgrownd(cub3d);
	raycast_frame(&cub3d->cam, &cub3d->mlx);
	minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx_instance, cub3d->mlx.mlx_window,
		cub3d->mlx.img.img_instance, 0, 0);
}

int	main(int ac, char	**av)
{
	t_cub3d	cub3d;

	(void)ac;
	(void)av;
	if (!parse(ac, av, &cub3d))
	{
		init_all(&cub3d);
		put_frame(&cub3d);
		loop_and_hooks(&cub3d);
	}
	else
		return (free_all(&cub3d), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
