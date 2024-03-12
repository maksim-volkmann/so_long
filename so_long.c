// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "so_long.h"

#define WIDTH 250
#define HEIGHT 250

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 24 | a);
}

// color randomizer of player block;
void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void key_event_handler(mlx_key_data_t keydata, void* param) {
	// t_game mlx = param;
	mlx_t* mlx = param;

	if (keydata.action == MLX_PRESS) {
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(mlx);

		// Handle other key presses
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			image->instances[0].y -= 50;
		if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			image->instances[0].y += 50;
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			image->instances[0].x -= 50;
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			image->instances[0].x += 50;
	}
}

// -----------------------------------------------------------------------------

int validate_ber_extension(const char *filename)
{
	const char *extension;
	size_t filename_len;
	size_t extension_len;

	filename_len = ft_strlen(filename);
	extension_len = 4;
	extension = ".ber";
	if (filename_len >= extension_len)
	{
		// Compare the end of the filename with the extension
		// Using ft_strcmp to compare the substring starting from the end of filename - extension_len
		if (ft_strcmp(filename + filename_len - extension_len, extension) == 0)
			return 1; // True, filename ends with ".ber"
	}
	return 0; // False, filename does not end with ".ber"
}

int	file_exists(const char *filename, mlx_t* mlx)
{
	int fd;
	ssize_t	read_bytes;
	char	buffer[BUFFER_SIZE + 1];
	int i;
	int x = 0;
	int y = 0;
	int wall_i = 0;

	i = 0;
	fd = open(filename, O_RDONLY);
	if(fd == -1)
		return (0);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	buffer[read_bytes] = 0;
	printf("Buffer:\n");
	printf("%s\n", buffer);
	close(fd);
	mlx_texture_t* wall_texture = mlx_load_png("wall50_v2.png");
	if (!wall_texture)
		return(EXIT_FAILURE);
	mlx_image_t* wall = mlx_texture_to_image(mlx, wall_texture);
	if (!wall)
		return(EXIT_FAILURE);

	while(buffer[i] != '\0')
	{
		if(buffer[i] == '1')
		{
			mlx_image_to_window(mlx, wall, x, y);
			mlx_set_instance_depth(wall->instances + wall_i++, 0);
			wall->instances[0].z = 0;
			x = x + 50;
			printf("Draw the wall tile\n");
		}
		i++;
	}

	return (1);
}


int32_t main(int32_t ac, char *av[])
{
	t_game game;

	if(ac < 2)
		return(EXIT_FAILURE, printf(NO_MAP_ERR));
	if(ac > 2)
		return(EXIT_FAILURE, printf(NO_ARGS_ERR));
	if (!validate_ber_extension(av[1]))
		return(EXIT_FAILURE, printf(WRONG_FILE_EXT));


	// Gotta error check this stuff
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game.mlx, 50, 50)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!file_exists(av[1], game.mlx))
		return(EXIT_FAILURE, printf(NO_FILE_EXIST, av[1]));


	//Creating a grass.
	mlx_texture_t* grass_texture = mlx_load_png("grass50.png");
	if (!grass_texture)
		return(EXIT_FAILURE);
	mlx_image_t* grass = mlx_texture_to_image(game.mlx, grass_texture);
	if (!grass)
		return(EXIT_FAILURE);
	mlx_image_to_window(game.mlx, grass, 200, 200);

	mlx_loop_hook(game.mlx, ft_randomize, game.mlx);
	mlx_key_hook(game.mlx, key_event_handler, game.mlx);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

// cc main.c MLX42/build/libmlx42.a -Iinclude -lglfw && ./a.out maps/map1.ber
