/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:06:26 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/25 15:23:36 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_game *game)
{
	if (game->player)
		mlx_delete_image(game->mlx, game->player);
	if (game->floor)
		mlx_delete_image(game->mlx, game->floor);
	if (game->wall)
		mlx_delete_image(game->mlx, game->wall);
	if (game->door)
		mlx_delete_image(game->mlx, game->door);
	if (game->collc)
		mlx_delete_image(game->mlx, game->collc);
}

void	free_map(char ***map)
{
	int	i;

	i = 0;
	if (map && *map)
	{
		while ((*map)[i])
		{
			free((*map)[i]);
			i++;
		}
		free(*map);
		*map = NULL;
	}
}

void	error_and_cleanup(t_game *game, const char *msg)
{
	if (msg)
		ft_printf("\033[31mError:\n%s\033[0m\n", msg);
	free_images(game);
	if (game->map)
		free_map(&game->map);
	if (game->map_copy)
		free_map(&game->map_copy);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(EXIT_FAILURE);
}
