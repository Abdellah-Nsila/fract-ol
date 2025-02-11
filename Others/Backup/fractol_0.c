/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:42:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/01/31 18:31:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_calculate_mandelbrot_set(t_fractol *fractol)
{
	double			MinRe = -2.0;
	double			MaxRe = 1.0;
	double			MinIm = -1.2;
	double			MaxIm = MinIm+(MaxRe-MinRe) * fractol->height / fractol->width;
	double			Re_factor = (MaxRe-MinRe) / (fractol->width - 1);
	double			Im_factor = (MaxIm-MinIm) / (fractol->height - 1);

	int	n;

	for(int y = 0; y < fractol->height; ++y)
	{
		double c_im = MaxIm - (y * Im_factor);
		for(int x = 0; x < fractol->width; ++x)
		{
			double c_re = MinRe + (x * Re_factor);

			double Z_re = c_re, Z_im = c_im;
			t_bool isInside = true;
			for(n = 0; n < fractol->precision; ++n)
			{
				double Z_re2 = (Z_re * Z_re), Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4)
				{
					isInside = false;
					break;
				}
				Z_im = (2 * (Z_re * Z_im)) + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}
			if(isInside)
				ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
			else
			{
				int color = ft_get_color(fractol, n, fractol->precision);
				ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			}
		}
	}
}

void	ft_calculate_julia_set(t_fractol *fractol)
{
	double			MinRe = -2.0;
	double			MaxRe = 1.0;
	double			MinIm = -1.2;
	double			MaxIm = MinIm+(MaxRe-MinRe) * fractol->height / fractol->width;
	double			Re_factor = (MaxRe-MinRe) / (fractol->width - 1);
	double			Im_factor = (MaxIm-MinIm) / (fractol->height - 1);

	int	n;

	for(int y = 0; y < fractol->height; ++y)
	{
		double c_im = MaxIm - (y * Im_factor);
		for(int x = 0; x < fractol->width; ++x)
		{
			double c_re = MinRe + (x * Re_factor);

			double Z_re = c_re, Z_im = c_im;
			t_bool isInside = true;
			for(n = 0; n < fractol->precision; ++n)
			{
				double Z_re2 = (Z_re * Z_re), Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4)
				{
					isInside = false;
					break;
				}
				Z_im = (2 * (Z_re * Z_im)) + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}
			if(isInside)
				ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
			else
			{
				int color = ft_get_color(fractol, n, fractol->precision);
				ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			}
		}
	}
}

void	ft_init_image_buffer(t_fractol *fractol)
{
	if (fractol->img.img_ptr)
	{
		printf("Image destroyed\n");
		mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	}
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
	fractol->img.img_pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bits_per_pixel, &fractol->img.line_length,
								&fractol->img.endian);
}

int mouse_event(int button, int x, int y, void *param)
{
	t_fractol *fractol;

	fractol = param;
	printf("Mouse Button: %d   x: %d  y: %d  precision: %d\n", button, x, y, fractol->precision);
	
	// Increase precision
	if (button == 4)
		fractol->precision += 1;
	// Decrease precision
	else if (button == 5)
		fractol->precision -= 1;
	else if (button == 1)
		ft_generate_random_gradient_color(fractol);

	ft_init_image_buffer(fractol);

	// Recalculate the Mandelbrot set with the new precision
	ft_calculate_mandelbrot_set(fractol);

	// Redraw the image in the window
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);

	return (EXIT_SUCCESS);
}

int main()
{
	t_fractol	fractol;

	// Initiale mlx connection with (X/Server) && create window
	fractol.mlx = mlx_init();
	if (NULL == fractol.mlx)
		return (EXIT_FAILURE);
	fractol.width = 800;
	fractol.height = 600;
	fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height, "Minilbx");
	if (NULL == fractol.mlx)
	{
		free(fractol.mlx);
		return (EXIT_FAILURE);
	}
	fractol.img.img_ptr = NULL;

	// Init Img 
	ft_init_image_buffer(&fractol);
	// Set a initile num of iteration
	fractol.precision = 50;
	// Set a random gradient for out set
	ft_generate_random_gradient_color(&fractol);
	// Draw the mandelbrot_set
	ft_calculate_mandelbrot_set(&fractol);
	mlx_put_image_to_window(fractol.mlx,  fractol.win, fractol.img.img_ptr, 0, 0);

	// Lisening for mouse events
	mlx_mouse_hook(fractol.win, &mouse_event, &fractol);
	mlx_loop(fractol.mlx);

	// Clean Up
	mlx_destroy_window(fractol.mlx, fractol.win);
	mlx_destroy_display(fractol.mlx);
	free(fractol.mlx);
}
