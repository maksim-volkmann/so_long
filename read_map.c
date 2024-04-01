/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:39:18 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/28 11:47:29 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	line_counter(t_game *game, char *file)
{
	int		fd;
	char	*current_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_and_cleanup(game, OPN_ERR);
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		game->line_count++;
		free(current_line);
		current_line = get_next_line(fd);
	}
	if (game->line_count > 25)
		error_and_cleanup(game, FIL_TO_BIG);
	close(fd);
}

void	array_of_pointer(t_game *game)
{
	if (game->line_count <= 0)
		error_and_cleanup(game, EMP_FILE);
	game->map = malloc(sizeof(char *) * (game->line_count + 1));
	if (!game->map)
		error_and_cleanup(game, MLC_ERR);
	game->map[game->line_count] = NULL;
}

void	populate_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;
	size_t	len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_and_cleanup(game, OPN_ERR);
	i = 0;
	line = get_next_line(fd);
	while ((line != NULL) && (i < game->line_count))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->line_width = ft_strlen(game->map[0]);
	if (game->line_width > 50)
		error_and_cleanup(game, FIL_TO_BIG);
	close(fd);
}
