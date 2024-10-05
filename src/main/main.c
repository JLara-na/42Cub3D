/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <jlara-na@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 01:35:16 by jlara-na          #+#    #+#             */
/*   Updated: 2024/10/05 22:53:23 by jlara-na         ###   ########.fr       */
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

int	main(int ac, char	**av)
{
	t_cub3d	cub3d;

	(void)ac;
	(void)av;
	if (!parse(ac, av, &cub3d))
	{
		init_all(&cub3d);
		printf("%s\n", cub3d.texture_path[NORTH]);
		printf("%s\n", cub3d.texture_path[SOUTH]);
		printf("%s\n", cub3d.texture_path[WEST]);
		printf("%s\n", cub3d.texture_path[EAST]);
		printf("%d\n", cub3d.color[FLOOR]);
		printf("%d\n", cub3d.color[CEILING]);
		ft_free_sarray(cub3d.texture_path);
		put_frame(&cub3d);
		loop_and_hooks(&cub3d);
	}
	return (EXIT_SUCCESS);
}
