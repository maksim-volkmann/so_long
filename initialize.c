/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:50 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/28 13:41:11 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_variables(t_game *game)
{
	game->mlx = NULL;
	game->player = NULL;
	game->floor = NULL;
	game->wall = NULL;
	game->door = NULL;
	game->collc = NULL;
	game->counter = 0;
	game->map = NULL;
	game->map_copy = NULL;
	game->line_count = 0;
	game->line_width = 0;
	game->p_x = 0;
	game->p_y = 0;
	game->coll_s = 0;
	game->coll_c = 0;
	game->exit_count = 0;
	game->player_count = 0;
}

bool	load_texture(mlx_t *mlx, const char *path, mlx_image_t **texture)
{
	mlx_texture_t	*temp_texture;

	temp_texture = mlx_load_png(path);
	if (!temp_texture)
		return (false);
	*texture = mlx_texture_to_image(mlx, temp_texture);
	if (!*texture)
		return (false);
	mlx_delete_texture(temp_texture);
	return (true);
}

void	init_textures(t_game *game)
{
	if (!load_texture(game->mlx, WALL, &game->wall)
		|| !load_texture(game->mlx, FLOOR, &game->floor)
		|| !load_texture(game->mlx, DOOR, &game->door)
		|| !load_texture(game->mlx, COLLECTABLE, &game->collc)
		|| !load_texture(game->mlx, PLAYER, &game->player))
		error_and_cleanup(game, TXT_ERR);
}

void	init_game(t_game *game)
{
	int	game_width;
	int	game_height;

	game_width = TILE * game->line_width;
	game_height = TILE * game->line_count;
	game->mlx = mlx_init(game_width, game_height, "Redbull Bull", false);
	if (!(game->mlx))
		error_and_cleanup(game, mlx_strerror(mlx_errno));
	init_textures(game);
}
