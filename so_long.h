/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:21:37 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/11 03:01:47 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#define NO_MAP_ERR "ERROR: Map file is not provided!\n"
#define NO_ARGS_ERR "ERROR: Too many arguments!\n"
#define WRONG_FILE_EXT "ERROR: Wrong file extension!\n"
#define NO_FILE_EXIST "ERROR: File '%s' does not exist or cannot be accessed.\n"

#endif
