/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:13:26 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/09 13:56:11 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_init_complex_plan(t_fractol *fractol)
{
	double	range_img;

	range_img = RANGE_X * fractol->height / fractol->width;
	fractol->min_re = CENTER_X - (RANGE_X / 2.0);
	fractol->max_re = CENTER_X + (RANGE_X / 2.0);
	fractol->min_img = CENTER_Y - (range_img / 2.0);
	fractol->max_img = CENTER_Y + (range_img / 2.0);
	fractol->re_factor = (fractol->max_re - fractol->min_re)
		/ fractol->width;
	fractol->img_factor = (fractol->max_img - fractol->min_img)
		/ fractol->height;
}

t_complex	ft_map_to_complex(t_fractol *fractol, int x, int y)
{
	t_complex	c;

	c.re = fractol->min_re + (x * fractol->re_factor);
	c.img = fractol->max_img - (y * fractol->img_factor);
	return (c);
}

void	ft_zoom_plan(t_fractol *fractol, double zoom_factor, int m_x, int m_y)
{
	t_complex	c;

	c = ft_map_to_complex(fractol, m_x, m_y);
	fractol->min_re = c.re + (fractol->min_re - c.re) / zoom_factor;
	fractol->max_re = c.re + (fractol->max_re - c.re) / zoom_factor;
	fractol->min_img = c.img + (fractol->min_img - c.img) / zoom_factor;
	fractol->max_img = c.img + (fractol->max_img - c.img) / zoom_factor;
	fractol->re_factor = (fractol->max_re - fractol->min_re) / (fractol->width);
	fractol->img_factor = (fractol->max_img - fractol->min_img)
		/ (fractol->height);
}

void	ft_move_plan(t_fractol *fractol, double offset_x, double offset_y)
{
	fractol->min_re += offset_x;
	fractol->max_re += offset_x;
	fractol->min_img += offset_y;
	fractol->max_img += offset_y;
	fractol->re_factor = (fractol->max_re - fractol->min_re)
		/ (fractol->width - 1);
	fractol->img_factor = (fractol->max_img - fractol->min_img)
		/ (fractol->height - 1);
}
