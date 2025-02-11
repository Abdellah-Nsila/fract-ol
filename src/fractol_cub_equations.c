/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_cub_equations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:54:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/09 16:20:29 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_mandelbrot_cub_set(t_fractol *fractol, t_complex c)
{
	t_complex	z;
	double		z_re_sq;
	double		z_img_sq;
	int			iter;

	iter = 0;
	z.re = 0;
	z.img = 0;
	while (iter < fractol->precision)
	{
		z_re_sq = z.re * z.re;
		z_img_sq = z.img * z.img;
		if ((z_re_sq + z_img_sq) > ESCAPE_LIMITE)
			return (ft_get_psychedelic_color(fractol, iter));
		z.re = (z_re_sq * z.re) - (3 * z.re * z_img_sq) + c.re;
		z.img = (3 * z_re_sq * z.img) - (z_img_sq * z.img) + c.img;
		iter++;
	}
	return (INSIDE_COLOR);
}

int	ft_julia_cub_set(t_fractol *fractol, t_complex c)
{
	t_complex	z;
	double		z_re_sq;
	double		z_img_sq;
	double		temp;
	int			iter;

	iter = 0;
	z.re = c.re;
	z.img = c.img;
	while (iter < fractol->precision)
	{
		z_re_sq = z.re * z.re;
		z_img_sq = z.img * z.img;
		if ((z_re_sq + z_img_sq) > ESCAPE_LIMITE)
			return (ft_get_psychedelic_color(fractol, iter));
		temp = (z_re_sq * z.re) - (3 * z.re * z_img_sq) + fractol->fixed_c_re;
		z.img = (3 * z_re_sq * z.img) - (z_img_sq * z.img)
			+ fractol->fixed_c_img;
		z.re = temp;
		iter++;
	}
	return (INSIDE_COLOR);
}

int	ft_burningship_cub_set(t_fractol *fractol, t_complex c)
{
	t_complex	z;
	double		z_re_sq;
	double		z_img_sq;
	int			iter;

	iter = 0;
	z.re = c.re;
	z.img = c.img;
	while (iter < fractol->precision)
	{
		z.re = fabs(z.re);
		z.img = fabs(z.img);
		z_re_sq = z.re * z.re;
		z_img_sq = z.img * z.img;
		if ((z_re_sq + z_img_sq) > ESCAPE_LIMITE)
			return (ft_get_psychedelic_color(fractol, iter));
		z.re = (z_re_sq * z.re) - (3 * z.re * z_img_sq) + c.re;
		z.img = (3 * z_re_sq * z.img) - (z_img_sq * z.img) + c.img;
		iter++;
	}
	return (INSIDE_COLOR);
}
