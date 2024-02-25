
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include "so_long.h"

#define WIDTH 700
#define HEIGHT 700
#define MOVE_SPEED 5
#define PLAYER_SIZE 50

mlx_image_t	*player;

// void	hook(void *param)
// {

// 	t_my_data	*data;
// 	mlx_t		*mlx;

// 	data = (t_my_data *)param;
// 	mlx = data->mlx;
// 	// static int	i = 0;


// 	//mlx = param;
// 	// data->i++;
// 	// printf("THIS IS HOOOOK %d\n", (data->i++));
// 	// printf("This is hook, but for b %d\n", data->c--);

// // player->instances[0].z = 0;
// if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if ((mlx_is_key_down(mlx, MLX_KEY_UP)) | (mlx_is_key_down(mlx, MLX_KEY_W))) {
// 		if(player->instances[0].y > 0)
// 		{
// 			player->instances[0].y -= MOVE_SPEED;
// 			printf("Position - X: %d, Y: %d\n", player->instances[0].x, player->instances[0].y);
// 		}

// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) | (mlx_is_key_down(mlx, MLX_KEY_S))) {
// 		if(player->instances[0].y < HEIGHT - PLAYER_SIZE)
// 		{
// 			player->instances[0].y += MOVE_SPEED;
// 			printf("Position - X: %d, Y: %d\n", player->instances[0].x, player->instances[0].y);
// 		}

// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) | (mlx_is_key_down(mlx, MLX_KEY_A))) {
// 		if(player->instances[0].x > 0)
// 		{
// 			player->instances[0].x -= MOVE_SPEED;
// 			printf("Position - X: %d, Y: %d\n", player->instances[0].x, player->instances[0].y);
// 		}

// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) | (mlx_is_key_down(mlx, MLX_KEY_D))) {
// 		if(player->instances[0].x < WIDTH - PLAYER_SIZE)
// 		{
// 			player->instances[0].x += MOVE_SPEED;
// 			printf("Position - X: %d, Y: %d\n", player->instances[0].x, player->instances[0].y);
// 		}

// 	}
// }

void key_event_handler(mlx_key_data_t keydata, void* param) {
	mlx_t* mlx = param;

	if (keydata.action == MLX_PRESS) {
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(mlx);

		// Handle other key presses
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			player->instances[0].y -= 50;
		if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			player->instances[0].y += 50;
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			player->instances[0].x -= 50;
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			player->instances[0].x += 50;
	}
}


static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(int argc, char **argv)
{
	mlx_t	*game_window;
	int		fd;
	int		c_count;
	ssize_t	read_bytes;
	char	buffer[BUFFER_SIZE + 1];

	// buffer[BUFFER_SIZE] = '\0';
	printf("argv: %s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		printf("Open failed\n");
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	buffer[read_bytes] = 0;
	// printf("Buffer:\n");
	// printf("%s\n", buffer);
	// printf("-----\n");
	// printf("%c\n", buffer[0]);
	// while(read_bytes > 0)
	// {
	// 	if(read_bytes == 0)
	// 		break ;
	// 	read_bytes = read(fd, buffer, BUFFER_SIZE);
	// 	printf("Buffer:\n");
	// 	printf("%s\n", buffer);

	// }
	game_window = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!game_window)
		exit(EXIT_FAILURE);
	player = mlx_new_image(game_window, PLAYER_SIZE, PLAYER_SIZE);
	memset(player->pixels, 255, player->width * player->height * sizeof(int));
	mlx_texture_t* wall_texture = mlx_load_png("wall50_v2.png");
	if (!wall_texture)
		error();
	mlx_texture_t* grass_texture = mlx_load_png("grass50.png");
	if (!grass_texture)
		error();

	// Convert texture to a displayable image
	mlx_image_t* wall = mlx_texture_to_image(game_window, wall_texture);
	if (!wall)
		error();
	mlx_image_t* grass = mlx_texture_to_image(game_window, grass_texture);
	if (!grass)
		error();

	int i = 0;
	int x = 0;
	int y = 0;
	// mlx_image_to_window(game_window, player, x, y);
	int wall_i = 0;
	// Loop through the buffer to draw walls on every block of the main game window
	while(buffer[i] != '\0')
	{
		if(buffer[i] == 'P')
		{
			//mlx_image_to_window(game_window, grass, x, y);
			//mlx_set_instance_depth(grass->instances, 0);
			// grass->instances[0].z = 0;
			// mlx_set_instance_depth(player->instances->z, 1);
					mlx_image_to_window(game_window, player, x, y);
					//player->instances->z = 1;
					//player->instances->z = 1;
				mlx_set_instance_depth(player->instances + i, 1);
			// mlx_set_instance_depth(player->instances[0].z = 10, 1);
			//mlx_image_to_window(game_window, player, x, y);

			x = x + 50;
			printf("Draw the player tile\n");
		}
		if(buffer[i] == '1')
		{
			mlx_image_to_window(game_window, wall, x, y);
			mlx_set_instance_depth(wall->instances + wall_i++, 0);
			//wall->instances[0].z = 0;
			x = x + 50;
			printf("Draw the wall tile\n");
		}
		if(buffer[i] == '0')
		{
			//mlx_image_to_window(game_window, grass, x, y);
			//mlx_set_instance_depth(grass->instances + i, 0);
			//grass->instances[0].z = 0;
			x = x + 50;
			printf("Draw the grass tile\n");
		}

		if(buffer[i] == '\n')
		{
			printf("Break\n");
			x = 0;
			y = y + 50;
		}
		i++;
	}
	// player->instances->enabled = true;
// mlx_image_to_window(game_window, player, x, y);




	// mlx_image_to_window(game_window, player, 0, 0);
	// if(buffer[200] == '\0')
	// 	printf("Trying to find buffer ending %d\n", buffer[200]);
	// if(buffer[0] == '1')
	// 	mlx_image_to_window(game_window, wall, 0, 0);
	// else
	// 	printf("something is wrong\n");

	// Display the image
	// if (mlx_image_to_window(mlx, img, 0, 0) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 0, 128) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 0, 256) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 0, 384) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 128, 0) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 128, 128) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 128, 256) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 128, 384) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 256, 0) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 256, 128) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 256, 256) < 0)
	// 	error();
	// if (mlx_image_to_window(mlx, img, 256, 384) < 0)
	// 	error();

	t_my_data	data;
	t_mynumber	anyVarNameIWant;

	anyVarNameIWant.b = 8;
	data.i = 0;
	data.mlx = game_window;
	data.c = anyVarNameIWant.b;

	// mlx_image_to_window(mlx, g_img, 20, 0);

	// mlx_image_to_window(mlx, g_img2, 50, 50);
	// mlx_image_to_window(mlx, g_img2, 50, 150);
	// mlx_loop_hook(game_window, &hook, &data);
	mlx_key_hook(game_window, key_event_handler, game_window);

	// mlx_loop_hook(mlx, &hook2, &data);
	// data.i = 0;
	mlx_loop(game_window);
	mlx_terminate(game_window);
	return (EXIT_SUCCESS);
}

// cc -W -W -W main.c MLX42/build/libmlx42.a -Iinclude -lglfw && ./a.out

// #include "MLX42/include/MLX42/MLX42.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <memory.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <stdbool.h>
// #include "so_long.h"

// #define WIDTH 384
// #define HEIGHT 384

// mlx_image_t	*g_img;

// typedef struct s_my_data
// {
// 	mlx_t	*mlx;
// 	int		i;
// } t_my_data;


// void	hook(void *param)
// {

// 	t_my_data	*data;

// 	data = (t_my_data *)param;
// 	mlx_t	*mlx;

// 	mlx = data->mlx;
// 	// static int	i = 0;


// 	data->i = 0;
// 	mlx = param;
// 	(data->i)++;
// 	printf("THIS IS HOOOOK %d\n", (data->i));


// if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if ((mlx_is_key_down(mlx, MLX_KEY_UP)) | (mlx_is_key_down(mlx, MLX_KEY_W))) {
// 		g_img->instances[0].y -= 5;
// 		printf("Position - X: %d, Y: %d\n", g_img->instances[0].x, g_img->instances[0].y);
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) | (mlx_is_key_down(mlx, MLX_KEY_S))) {
// 		g_img->instances[0].y += 5;
// 		printf("Position - X: %d, Y: %d\n", g_img->instances[0].x, g_img->instances[0].y);
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) | (mlx_is_key_down(mlx, MLX_KEY_A))) {
// 		g_img->instances[0].x -= 5;
// 		printf("Position - X: %d, Y: %d\n", g_img->instances[0].x, g_img->instances[0].y);
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) | (mlx_is_key_down(mlx, MLX_KEY_D))) {
// 		g_img->instances[0].x += 5;
// 		printf("Position - X: %d, Y: %d\n", g_img->instances[0].x, g_img->instances[0].y);
// 	}
// }

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// int32_t	main(int argc, char **argv)
// {
// 	mlx_t	*mlx;
// 	int		fd;
// 	int		c_count;
// 	ssize_t	read_bytes;
// 	char	buffer[BUFFER_SIZE + 1];

// 	// buffer[BUFFER_SIZE] = '\0';
// 	fd = open("map1.ber", O_RDONLY);
// 	read_bytes = read(fd, buffer, BUFFER_SIZE);
// 	printf("bytes: %zd\n", read_bytes);
// 	printf("Main Function\n");
// 	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
// 	if (!mlx)
// 		exit(EXIT_FAILURE);
// 	g_img = mlx_new_image(mlx, 50, 50);
// 	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));

// 	mlx_texture_t* texture = mlx_load_png("tile.png");
// 	if (!texture)
// 		error();

// 	// Convert texture to a displayable image
// 	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
// 	if (!img)
//         error();

// 	// Display the image
// 	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 0, 128) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 0, 256) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 0, 384) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 128, 0) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 128, 128) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 128, 256) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 128, 384) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 256, 0) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 256, 128) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 256, 256) < 0)
//         error();
// 	if (mlx_image_to_window(mlx, img, 256, 384) < 0)
//         error();

// 	//t_my_data	data;

// 	mlx_image_to_window(mlx, g_img, 0, 0);
// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

// // cc -W -W -W main.c MLX42/build/libmlx42.a -Iinclude -lglfw && ./a.out
// cc main.c MLX42/build/libmlx42.a -Iinclude -lglfw && ./a.out maps/map1.ber
