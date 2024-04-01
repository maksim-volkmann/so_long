/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:30:22 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/28 13:51:03 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	tile_draw(t_game *game, mlx_image_t *image, int x, int y)
{
	if (mlx_image_to_window(game->mlx, image, x * TILE, y * TILE) == -1)
		error_and_cleanup(game, mlx_strerror(mlx_errno));
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			tile_draw(game, game->floor, x, y);
			if (game->map[y][x] == '1')
				tile_draw(game, game->wall, x, y);
			else if (game->map[y][x] == 'C')
				tile_draw(game, game->collc, x, y);
			else if (game->map[y][x] == 'E')
				tile_draw(game, game->door, x, y);
			x++;
		}
		y++;
	}
}

void	redraw_tile(t_game *game, int x, int y)
{
	char		curr_type;
	mlx_image_t	*texture;

	curr_type = game->map[y][x];
	texture = game->collc;
	if (curr_type == 'E')
		texture = game->door;
	else
		texture = game->floor;
	tile_draw(game, game->floor, x, y);
	tile_draw(game, texture, x, y);
}

void	draw_player(t_game *game)
{
	redraw_tile(game, game->p_x, game->p_y);
	tile_draw(game, game->player, game->p_x, game->p_y);
}

void	attempt_move(t_game *game, int move_x, int move_y)
{
	int	next_x_p;
	int	next_y_p;

	next_x_p = game->p_x + move_x;
	next_y_p = game->p_y + move_y;
	if (next_x_p < 0 || next_x_p >= game->line_width || next_y_p < 0
		|| next_y_p >= game->line_count || game->map[next_y_p][next_x_p] == '1')
		return ;
	if (game->map[next_y_p][next_x_p] == 'C')
	{
		game->coll_c++;
		game->map[next_y_p][next_x_p] = '0';
	}
	redraw_tile(game, game->p_x, game->p_y);
	game->p_x = next_x_p;
	game->p_y = next_y_p;
	draw_player(game);
	game->counter++;
	ft_printf("Move count: %d\n", game->counter);
	if (game->map[next_y_p][next_x_p] == 'E' && game->coll_s == game->coll_c)
	{
		mlx_terminate(game->mlx);
		ft_printf("YOU WON!!!\nTotal moves: %d\n", game->counter);
		exit(0);
	}
}
