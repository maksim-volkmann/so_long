/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:21:37 by mvolkman          #+#    #+#             */
/*   Updated: 2024/01/27 13:05:16 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "MLX42/include/MLX42/MLX42.h"

// typedef struct increasing_number
// {
// 	int	i;
// }	t_whythisishere;

typedef struct s_my_data
{
	mlx_t	*mlx;
	int		i;
	int		c;
}t_my_data;

typedef struct s_increasing_number
{
	int	i;
}t_increase_number;

typedef struct s_myNumber
{
	int	b;
}t_mynumber;



void		hook(void *param);
static void	error(void);
int32_t		main(int argc, char **argv);

#endif
