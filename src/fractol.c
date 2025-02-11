/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:18:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/09 13:46:06 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_walk(t_fractol *fractol, int (*fractal_func)(t_fractol *, t_complex))
{
	int			x;
	int			y;
	t_complex	c;

	x = 0;
	while (x < fractol->width)
	{
		y = 0;
		while (y < fractol->height)
		{
			c = ft_map_to_complex(fractol, x, y);
			*(unsigned int *)(fractol->img.img_pixels_ptr
					+ ((y * fractol->img.line_length)
						+ (x * (fractol->img.bits_per_pixel / 8))))
				= fractal_func(fractol, c);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img_ptr, 0, 0);
}

void	ft_draw_fractal(t_fractol *fractol)
{
	if (fractol->set_type == Mandelbrot_square)
		ft_walk(fractol, &ft_mandelbrot_sq_set);
	else if (fractol->set_type == Mandelbrot_cube)
		ft_walk(fractol, &ft_mandelbrot_cub_set);
	else if (fractol->set_type == Julia_square)
		ft_walk(fractol, &ft_julia_sq_set);
	else if (fractol->set_type == Julia_cube)
		ft_walk(fractol, &ft_julia_cub_set);
	else if (fractol->set_type == Burningship_square)
		ft_walk(fractol, &ft_burningship_sq_set);
	else if (fractol->set_type == Burningship_cube)
		ft_walk(fractol, &ft_burningship_cub_set);
}

int	main(int ac, char **av)
{
	t_fractol	fractol;

	ft_check_parse(&fractol, ac, av);
	ft_init_fractol(&fractol);
	ft_init_complex_plan(&fractol);
	ft_init_image_buffer(&fractol);
	ft_init_events(&fractol);
	mlx_loop(fractol.mlx);
	ft_close(&fractol);
}
