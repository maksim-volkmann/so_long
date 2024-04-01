/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/04/01 14:56:59 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			attempt_move(game, 0, -1);
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			attempt_move(game, 0, 1);
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			attempt_move(game, -1, 0);
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			attempt_move(game, 1, 0);
	}
}

bool	validate_map_file_name(const char *map_name)
{
	const char	*actual_file_name;
	size_t		len;

	actual_file_name = ft_strrchr(map_name, '/');
	if (actual_file_name == NULL)
		actual_file_name = map_name;
	else
		actual_file_name++;
	len = ft_strlen(actual_file_name);
	if (len < 5)
		return (false);
	if (actual_file_name[len - 4] == '.'
		&& actual_file_name[len - 3] == 'b'
		&& actual_file_name[len - 2] == 'e'
		&& actual_file_name[len - 1] == 'r')
		return (true);
	return (false);
}

int32_t	main(int ac, char *av[])
{
	t_game	game;

	init_variables(&game);
	if (ac != 2)
		error_and_cleanup(&game, NUM_ARGS);
	if (!validate_map_file_name(av[1]))
		error_and_cleanup(&game, INV_NAME);
	line_counter(&game, av[1]);
	array_of_pointer(&game);
	populate_map(&game, av[1]);
	check_map_line_lengths(&game);
	copy_map(&game);
	flood_fill(&game, game.p_x, game.p_y);
	check_reachability(&game);
	init_game(&game);
	draw_map(&game);
	draw_player(&game);
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_loop(game.mlx);
	error_and_cleanup(&game, NULL);
	return (EXIT_SUCCESS);
}
// Rename the main function to the_real_main and uncomment the following code
// to check for memory leaks. This is only for testing purposes. And comment
// a "error_and_cleanup(&game, NULL)" function to see actual leaks.

// int main(int argc, char *argv[])
// {
// 	int32_t result = the_real_main(argc, argv);
// 	system("leaks so_long");
// 	return result;
// }
