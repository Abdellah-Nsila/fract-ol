/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:54:47 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/03 16:18:52 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_my_optimized_pixel_put(t_fractol *fractol, t_img *img, int x, int y, int color)
{
	int	offset;
	if (x >= 0 && x < fractol->width && y >= 0 && y < fractol->height)
	{
		offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		*(unsigned int *)(img->img_pixels_ptr + offset) = color;
	}
}

void	ft_init_image_buffer(t_fractol *fractol)
{
	// if (fractol->img.img_ptr)
	// 	mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
	fractol->img.img_pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr, &fractol->img.bits_per_pixel, &fractol->img.line_length,
								&fractol->img.endian);
}

void	ft_clear_image(t_fractol *fractol, int color)
{
	// Fill the image buffer with black (or any other color)
	int total_pixels = fractol->width * fractol->height;
	for (int i = 0; i < total_pixels; i++)
	{
		((int *)fractol->img.img_pixels_ptr)[i] = color; // Black color
	}
}

int	ft_get_color(t_fractol *fractol, int iteration, int max_iterations)
{
	if (iteration == max_iterations)
		return 0x000000; // Inside the Mandelbrot set (black)

	// Normalize the iteration count to a value between 0 and 1
	double t = (double)iteration / max_iterations;

	// Apply smoothing to t
	t = log(t + 1); // Optional: Use a square root or other function to adjust the gradient

	// Scale t to the range of the palette
	double scaled_t = t * (PALETTE_SIZE - 1);

	// Find the two nearest colors in the palette
	int index1 = (int)scaled_t;
	int index2 = (index1 + 1) % PALETTE_SIZE; // Wrap around to the first color if necessary

	// Get the fractional part of scaled_t
	double fractional = scaled_t - index1;

	// Interpolate between the two nearest colors
	int color1 = fractol->palette[index1];
	int color2 = fractol->palette[index2];

	int r = (int)(((color2 >> 16) & 0xFF) * fractional + ((color1 >> 16) & 0xFF) * (1 - fractional));
	int g = (int)(((color2 >> 8) & 0xFF) * fractional + ((color1 >> 8) & 0xFF) * (1 - fractional));
	int b = (int)((color2 & 0xFF) * fractional + (color1 & 0xFF) * (1 - fractional));

	// Combine the RGB components into a single color value
	return (r << 16) | (g << 8) | b;
}

void	ft_generate_random_gradient_color(t_fractol *fractol)
{
	for (int i = 0; i < PALETTE_SIZE; i++)
	{
		fractol->palette[i] = rand() % 0xFFFFFF; // Generate a random 24-bit color
	}
}

void	ft_clean_mlx(t_fractol *fractol)
{
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(EXIT_SUCCESS);
}
