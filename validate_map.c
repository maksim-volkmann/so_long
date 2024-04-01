/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:52:44 by goldman           #+#    #+#             */
/*   Updated: 2024/03/27 13:29:53 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_line_lengths(t_game *game)
{
	int		i;
	size_t	line_length;

	if (game->map == NULL || game->map[0] == NULL)
		error_and_cleanup(game, EMP_FILE);
	i = 0;
	line_length = ft_strlen(game->map[0]);
	while (game->map[i] != NULL)
	{
		if (ft_strlen(game->map[i]) != line_length)
			error_and_cleanup(game, NOT_RECT);
		i++;
	}
	check_map_for_valid_characters(game);
}

void	check_map_for_valid_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && game->map[i][j] != 'P' &&
				game->map[i][j] != 'E' && game->map[i][j] != 'C' &&
				game->map[i][j] != '0')
			{
				error_and_cleanup(game, INV_CHAR);
			}
			j++;
		}
		i++;
	}
	check_map_walls(game);
}

void	check_map_walls(t_game *game)
{
	int	j;

	j = 0;
	while (game->map[0][j])
	{
		if (game->map[0][j] != '1')
			error_and_cleanup(game, FRS_ROW);
		j++;
	}
	j = 0;
	while (game->map[game->line_count - 1][j])
	{
		if (game->map[game->line_count - 1][j] != '1')
			error_and_cleanup(game, LST_ROW);
		j++;
	}
	j = 0;
	while (game->map[j] != NULL)
	{
		if (game->map[j][0] != '1'
		|| game->map[j][ft_strlen(game->map[j]) - 1] != '1')
			error_and_cleanup(game, VRT_WALL);
		j++;
	}
	count_map_characters(game);
}

void	count_map_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E')
				game->exit_count++;
			else if (game->map[i][j] == 'C')
				game->coll_s++;
			else if (game->map[i][j] == 'P')
			{
				game->p_x = j;
				game->p_y = i;
				game->player_count++;
			}
			j++;
		}
		i++;
	}
	check_map_character_count(game);
}

void	check_map_character_count(t_game *game)
{
	if (game->exit_count != 1)
		error_and_cleanup(game, EXT_ERR);
	if (game->coll_s < 1)
		error_and_cleanup(game, COL_ERR);
	if (game->player_count != 1)
		error_and_cleanup(game, PLR_ERR);
}
