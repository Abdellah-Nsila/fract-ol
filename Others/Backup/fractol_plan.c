/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:13:26 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/08 15:40:20 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_init_complex_plan(t_fractol *fractol)
{
	double center_re = 0.0; // Center of the Mandelbrot set (natural center)
	double center_img = 0.0; // Center in the imaginary axis
	double range_re = 4.0;   // Initial range in the real axis

	// Adjust the imaginary range to maintain the aspect ratio
	double range_img = range_re * fractol->height / fractol->width;

	// Set the complex plane boundaries centered around (-0.5, 0.0)
	fractol->min_re = center_re - (range_re / 2.0);
	fractol->max_re = center_re + (range_re / 2.0);
	fractol->min_img = center_img - (range_img / 2.0);
	fractol->max_img = center_img + (range_img / 2.0);

	// Compute mapping factors
	fractol->re_factor = (fractol->max_re - fractol->min_re) / (fractol->width);
	fractol->img_factor = (fractol->max_img - fractol->min_img) / (fractol->height);
}

t_complex	ft_map_to_complex(t_fractol *fractol, int x, int y)
{
	t_complex	c;

	c.re = fractol->min_re + (x * fractol->re_factor);
	c.img = fractol->max_img - (y * fractol->img_factor);
	return (c);
}

void	ft_zoom_plan(t_fractol *fractol, double zoom_factor, int mouse_x, int mouse_y)
{
	t_complex	c;

	c = ft_map_to_complex(fractol, mouse_x, mouse_y);

	fractol->min_re = c.re + (fractol->min_re - c.re) / zoom_factor;
	fractol->max_re = c.re + (fractol->max_re - c.re) / zoom_factor;
	fractol->min_img = c.img + (fractol->min_img - c.img) / zoom_factor;
	fractol->max_img = c.img + (fractol->max_img - c.img) / zoom_factor;

	fractol->re_factor = (fractol->max_re - fractol->min_re) / (fractol->width);
	fractol->img_factor = (fractol->max_img - fractol->min_img) / (fractol->height);
}

void	ft_move_plan(t_fractol *fractol, double offset_x, double offset_y)
{
	fractol->min_re += offset_x;
	fractol->max_re += offset_x;
	fractol->min_img += offset_y;
	fractol->max_img += offset_y;

	fractol->re_factor = (fractol->max_re - fractol->min_re) / (fractol->width - 1);
	fractol->img_factor = (fractol->max_img - fractol->min_img) / (fractol->height - 1);
}
