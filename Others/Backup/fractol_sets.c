/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:56:00 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/05 10:09:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

//! Mandelbrot z^2 + c
void	ft_mandelbrot_sq_set(t_fractol *fractol, t_complex c, int x, int y)
{
	t_complex z = {0, 0};
	int iter = 0;
	double z_re_sq = 0;
	double z_img_sq = 0;

	while (iter < fractol->precision)
	{
		z_img_sq = z.img * z.img;
		z_re_sq = z.re * z.re;
		if (z_re_sq + z_img_sq > 4.0)
			return (ft_put_escape_pixel(fractol, iter, x, y));
		z.img = 2 * z.re * z.img + c.img;
		z.re = z_re_sq - z_img_sq + c.re;
		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Mandelbrot z^3 + c
void	ft_mandelbrot_cub_set(t_fractol *fractol, t_complex c, int x, int y)
{
	t_complex z = {0, 0};
	int iter = 0;

	while (iter < (int)fractol->precision)
	{
		double z_re_sq = z.re * z.re;
		double z_img_sq = z.img * z.img;

		if (z_re_sq + z_img_sq > 4.0)
			return (ft_put_escape_pixel(fractol, iter, x, y));
		z.re = (z_re_sq * z.re) - (3 * z.re * z_img_sq) + c.re;
		z.img = (3 * z_re_sq * z.img) - (z_img_sq * z.img) + c.img;
		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Julia  z^2 + c
void	ft_julia_sq_set(t_fractol *fractol, t_complex c, int x, int y)
{
	int iter = 0;

	while (iter < (int)fractol->precision)
	{
		double z_re = c.re;
		double z_img = c.img;

		// Escape condition: If |z| > 2, it escapes
		if ((z_re * z_re) + (z_img * z_img) > 4.0)
			return (ft_put_escape_pixel(fractol, iter, x, y));

		// Julia formula: z = z^2 + c (Fixed `c`)
		double temp = (z_re * z_re) - (z_img * z_img) + fractol->fixed_c_re;
		c.img = (2 * z_re * z_img) + fractol->fixed_c_img;
		c.re = temp;

		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Julia z^3 + c
void	ft_julia_cub_set(t_fractol *fractol, t_complex c, int x, int y)
{
	int iter = 0;

	while (iter < (int)fractol->precision)
	{
		double z_re = c.re;
		double z_img = c.img;

		// Escape condition: If |z| > 2, it escapes
		if ((z_re * z_re) + (z_img * z_img) > 4.0)
			return (ft_put_escape_pixel(fractol, iter, x, y));

		// Julia formula: z = z^3 + c (Fixed `c`)
		double temp = (z_re * z_re * z_re) - (3 * z_re * (z_img * z_img)) + fractol->fixed_c_re;
		c.img = (3 * (z_re * z_re) * z_img) - (z_img * z_img * z_img) + fractol->fixed_c_img;
		
		c.re = temp;

		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Burningship z^2 - c
void	ft_burningship_sq_set(t_fractol *fractol, t_complex c, int x, int y)
{
	t_complex z = {0, 0};
	int iter = 0;
	double z_re_sq = 0;
	double z_img_sq = 0;

	while (iter < fractol->precision)
	{
		z_img_sq = z.img * z.img;
		z_re_sq = z.re * z.re;
		if (z_re_sq + z_img_sq > 4.0)
			return (ft_put_escape_pixel(fractol, iter, x, y));

		z.img = fabs(2 * z.re * z.img) - c.img;
		z.re = fabs(z_re_sq - z_img_sq - c.re);
		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

//! Burningship z^3 - c
void	ft_burningship_cub_set(t_fractol *fractol, t_complex c, int x, int y)
{
	t_complex z = {0, 0};
	int iter = 0;
	double z_re_sq = 0;
	double z_img_sq = 0;

	while (iter < fractol->precision)
	{
		z_img_sq = z.img * z.img;
		z_re_sq = z.re * z.re;
		if (z_re_sq + z_img_sq > 4.0)
			return (ft_put_escape_pixel(fractol, iter, x, y));

		z.re = fabs((z_re_sq * z.re) - (3 * z.re * z_img_sq) - c.re);
		z.img = fabs(3 * z_re_sq * z.img) - fabs(z_img_sq * z.img) - c.img;
		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}
