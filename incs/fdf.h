/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femaury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 15:49:58 by femaury           #+#    #+#             */
/*   Updated: 2018/06/28 18:17:55 by femaury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
**	----------------------------- SYSTEM LIBRARIES -----------------------------
*/

# include <math.h>

/*
**	------------------------------- MY LIBRARIES -------------------------------
*/

# include "../minilibx/mlx.h"
# include "../minilibx/mlx_keycodes.h"
# include "../libft/incs/libft.h"

/*
**	--------------------------------- DEFINES ----------------------------------
*/

# define WIN_W 1600
# define WIN_H 900
# define IMG_W WIN_W
# define IMG_H WIN_H

/*
**	-------------------------------- STRUCTURES --------------------------------
*/

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_img
{
	int				bpp;
	int				ln_size;
	int				endian;
	void			*ptr;
	unsigned int	*data;

}				t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*header;
	float	height;
	int		pad_x;
	int		pad_y;
	int		zoom;
	int		file_ln;
	int		file_sz;
	int		**file;
	int		color;
	t_img	img;
}				t_mlx;

/*
**	------------------------------- FDF FUNCTIONS ------------------------------
*/

int				parse_file(t_mlx *env, char *file);
int				key_hook(int keycode, t_mlx *env);
int				hook_keydown(int keycode, t_mlx *env);
int				hook_keyup(int keycode, t_mlx *env);
void			draw_grid(t_mlx *env);
void			put_line_to_image(t_mlx *env, t_point p1, t_point p2);
void			put_header_to_window(t_mlx *env);

#endif
