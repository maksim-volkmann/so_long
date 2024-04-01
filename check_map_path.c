/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:09:42 by goldman           #+#    #+#             */
/*   Updated: 2024/03/28 13:00:19 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	copy_map(t_game *game)
{
	int	i;

	game->map_copy = malloc(sizeof(char *) * (game->line_count + 1));
	if (!game->map_copy)
		error_and_cleanup(game, CPY_MAP_ERR);
	i = 0;
	while (i < game->line_count)
	{
		game->map_copy[i] = ft_strdup(game->map[i]);
		if (!game->map_copy[i])
			error_and_cleanup(game, CPY_MAP_ERR);
		i++;
	}
	game->map_copy[game->line_count] = NULL;
}

bool	is_fill_target(char tile)
{
	int	i;

	i = 0;
	while (TRG_CHR[i] != '\0')
	{
		if (tile == TRG_CHR[i])
			return (true);
		i++;
	}
	return (false);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->line_width
		|| y < 0 || y >= game->line_count
		|| !is_fill_target(game->map_copy[y][x]))
	{
		return ;
	}
	game->map_copy[y][x] = FILL_CHR;
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}

void	check_reachability(t_game *game)
{
	int		x;
	int		y;
	char	current_tile;

	y = 0;
	while (y < game->line_count)
	{
		x = 0;
		while (x < game->line_width)
		{
			current_tile = game->map_copy[y][x];
			if (current_tile == 'C' || current_tile == 'E')
				error_and_cleanup(game, FIL_ERR);
			x++;
		}
		y++;
	}
}
