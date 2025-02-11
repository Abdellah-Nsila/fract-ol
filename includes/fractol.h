/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:37:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/10 16:34:15 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <math.h>
# include <time.h>
# include "structs.h"

// Parsing
t_bool		ft_check_set_arg(char *set, char *set_arg,
				char *power, char *power_arg);
void		ft_check_parse(t_fractol *fractol, int ac, char **av);

// Struct Utils
void		ft_init_fractol(t_fractol *fractol);
void		ft_init_image_buffer(t_fractol *fractol);
void		ft_clean_fractol(t_fractol *fractol);
int			ft_close(t_fractol *fractol);

// Events Hook
int			ft_mouse_hook(int button, int x, int y, t_fractol *fractol);
int			ft_key_hook(int keycode, t_fractol *fractol);
int			ft_mouse_move_hook(int x, int y, t_fractol *fractol);
void		ft_init_events(t_fractol *fractol);

// 2D logical plane Utils
void		ft_init_complex_plan(t_fractol *fractol);
t_complex	ft_map_to_complex(t_fractol *fractol, int x, int y);
void		ft_zoom_plan(t_fractol *fractol, double zoom_factor,
				int mouse_x, int mouse_y);
void		ft_move_plan(t_fractol *fractol, double offset_x, double offset_y);

// Draw functions
void		ft_draw_fractal(t_fractol *fractol);
void		ft_walk(t_fractol *fractol,
				int (*fractal_func)(t_fractol *, t_complex));

// Fractal Sets Equations
int			ft_mandelbrot_sq_set(t_fractol *fractol, t_complex c);
int			ft_mandelbrot_cub_set(t_fractol *fractol, t_complex c);
int			ft_julia_sq_set(t_fractol *fractol, t_complex c);
int			ft_julia_cub_set(t_fractol *fractol, t_complex c);
int			ft_burningship_sq_set(t_fractol *fractol, t_complex c);
int			ft_burningship_cub_set(t_fractol *fractol, t_complex c);

// Fractol Utils
int			ft_abs(int nbr);
int			ft_get_psychedelic_color(t_fractol *fractol, int iter);
void		ft_generate_random_gradient_color(t_fractol *fractol);
void		ft_draw_menu(t_fractol *fractol);

// Others
int			ft_loop_hook(t_fractol *fractol);

#endif
