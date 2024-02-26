// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "so_long.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 24 | a);
}

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

char    *ft_strstr(const char *haystack, const char *needle)
{
    unsigned int    i;
    unsigned int    j;

    if (!needle[0])
        return ((char *)haystack);
    i = 0;
    while (haystack[i])
    {
        j = 0;
        while (needle[j] && haystack[i + j] == needle[j])
            j++;
        if (!needle[j])
            return ((char *)&haystack[i]);
        i++;
    }
    return (NULL);
}



bool validate_ber_extension(const char *filename) {
	// Directly look for the ".ber" substring in the filename
	const char *extension = ".ber";

	// Find the position of ".ber" in the filename, if it exists
	const char *found_extension = ft_strstr(filename, extension);

	if (found_extension != NULL) {
		// Check if ".ber" is at the end of the filename
		size_t extension_pos = found_extension - filename;
		size_t filename_len = ft_strlen(filename);

		if (extension_pos + ft_strlen(extension) == filename_len) {
			return true; // ".ber" is at the end
		}
	}

	return false; // ".ber" not found at the end
}


int32_t main(int32_t ac, char *av[])
{
	mlx_t* mlx;

	if(ac != 2)
	{
		if(ac < 2) {
			printf(ERROR_MESSAGE); // Indicate the error
		} else {
			printf("Too many arguments\n"); // Indicate the error
		}
		return(EXIT_FAILURE); // Exit before attempting MLX operations
	}
	printf("%s\n", av[1]);
	if (validate_ber_extension(av[1])) {
		printf("This is a .ber file.\n");
	} else {
		printf("This is not a .ber file.\n");
		return(EXIT_FAILURE);
	}


	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_key_hook(mlx, key_event_handler, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// cc main.c MLX42/build/libmlx42.a -Iinclude -lglfw && ./a.out maps/map1.ber
