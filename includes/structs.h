/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:41:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/09 16:42:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../Libft/includes/libft.h"
# include "settings.h"

typedef struct s_rgb
{
	double	percent;
	double	scaled_percent;
	double	fractional;
	int		r;
	int		g;
	int		b;
	int		index1;
	int		index2;
	int		color1;
	int		color2;
}				t_rgb;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_complex
{
	double	re;
	double	img;
}				t_complex;

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	t_img	img;
	double	min_re;
	double	max_re;
	double	min_img;
	double	max_img;
	double	re_factor;
	double	img_factor;
	double	zoom;
	double	fixed_c_re;
	double	fixed_c_img;
	int		width;
	int		height;
	int		set_type;
	int		precision;
	int		palette[PALETTE_SIZE];
	t_bool	trick_mouse;
	t_bool	toggle_menu;
}				t_fractol;

#endif
