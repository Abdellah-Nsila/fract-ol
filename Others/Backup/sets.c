/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:16:57 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/03 18:59:02 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

//! Mandelbrot z^2 + c
void	ft_mandelbrot_sq_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter)
{
	t_complex z = {0, 0};
	int iter = 0;
	double z_real_sq = 0;
	double z_imag_sq = 0;

	while (iter < max_iter)
	{
		z_imag_sq = z.imag * z.imag;
		z_real_sq = z.real * z.real;

		if (z_real_sq + z_imag_sq > 4.0) // Escape condition
		{
			int color = ft_get_color(fractol, iter, fractol->precision);
			ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			return;
		}

		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = z_real_sq - z_imag_sq + c.real;
		iter++;
	}
	// If we never escaped, mark as inside the set (black)
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Mandelbrot z^3 + c
void	ft_mandelbrot_cub_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter)
{
	t_complex z = {0, 0};
	int iter = 0;

	while (iter < max_iter)
	{
		double z_real_sq = z.real * z.real;
		double z_imag_sq = z.imag * z.imag;

		if (z_real_sq + z_imag_sq > 4.0) // Escape condition
		{
			int color = ft_get_color(fractol, iter, fractol->precision);
			ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			return;
		}
		z.real = (z_real_sq * z.real) - (3 * z.real * z_imag_sq) + c.real;
		z.imag = (3 * z_real_sq * z.imag) - (z_imag_sq * z.imag) + c.imag;
		iter++;
	}
	// If we never escaped, mark as inside the set (black)
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Julia  z^2 + c
void	ft_julia_sq_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter)
{
	int iter = 0;

	while (iter < max_iter)
	{
		double z_real = c.real;
		double z_imag = c.imag;

		// Escape condition: If |z| > 2, it escapes
		if ((z_real * z_real) + (z_imag * z_imag) > 4.0)
		{
			int color = ft_get_color(fractol, iter, fractol->precision);
			ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			return;
		}

		// Julia formula: z = z^2 + c (Fixed `c`)
		double temp = (z_real * z_real) - (z_imag * z_imag) + fractol->julia_c_real;
		c.imag = (2 * z_real * z_imag) + fractol->julia_c_imag;
		c.real = temp;

		iter++;
	}
	// If we never escaped, mark as inside the set (black)
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Julia z^3 + c
void	ft_julia_cub_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter)
{
	int iter = 0;

	while (iter < max_iter)
	{
		double z_real = c.real;
		double z_imag = c.imag;

		// Escape condition: If |z| > 2, it escapes
		if ((z_real * z_real) + (z_imag * z_imag) > 4.0)
		{
			int color = ft_get_color(fractol, iter, fractol->precision);
			ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			return;
		}

		// Julia formula: z = z^3 + c (Fixed `c`)
		double temp = (z_real * z_real * z_real) - (3 * z_real * (z_imag * z_imag)) + fractol->julia_c_real;
		c.imag = (3 * (z_real * z_real) * z_imag) - (z_imag * z_imag * z_imag) + fractol->julia_c_imag;
		
		c.real = temp;

		iter++;
	}
	// If we never escaped, mark as inside the set (black)
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}
