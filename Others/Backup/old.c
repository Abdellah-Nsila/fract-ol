#include "../includes/fractol.h"

void	ft_init_complex_plan(t_fractol *fractol)
{
	fractol->min_re = -2.0;
	fractol->max_re = 2.0;
	fractol->min_img = -1.5;
	fractol->max_img = fractol->min_img + (fractol->max_re - fractol->min_re) * fractol->height / fractol->width;
	// fractol->min_re = -2.0;
	// fractol->max_re = 2.0;
	// fractol->min_img = -1.5;
	// fractol->max_img = 1.5;

	fractol->re_factor = (fractol->max_re - fractol->min_re) / (fractol->width - 1);
	fractol->img_factor = (fractol->max_img - fractol->min_img) / (fractol->height - 1);
}

//! Orininal
void	ft_mandelbrot_sq_set(t_fractol *fractol, t_complex c, int x, int y)
{
	t_complex	z = {0, 0};	
	int			iter = 0;
	double		z_re_sq = 0;
	double		z_img_sq = 0;
	
	while (iter < (int)fractol->precision)
	{
		z_re_sq = z.re * z.re;
		z_img_sq = z.img * z.img;
		
		if (z_re_sq + z_img_sq > 4.0)
		{
			// int color = iter * 255 / fractol->precision;
			// color = (color << 16) | (color << 8) | color;
			
			//* [1] Use the gradient color function
			int color = create_gradient_color(iter, fractol->precision);

			//* [2] Use the psychedelic color function
			int color = create_psychedelic_color(iter);

			//* [3] Use the combined color function
			int color = create_combined_color(iter, fractol->precision);
			
			ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			return ;	
		}
		z.img = (2 * z.re * z.img) + c.img;
		z.re = z_re_sq - z_img_sq + c.re;
		iter++;
	}
	ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0x000000);
}

void	ft_draw_square(t_fractol *fractol)
{
	int			x;
	int			y;
	t_complex	c;
	
	ft_init_image_buffer(fractol);
	x = 0;
	while (x < fractol->width)
	{
		y = 0;
		while (y < fractol->height)
		{
			c = ft_map_to_complex(fractol, x, y);
			if (c.re  >= -1.0 && c.re <= 1.0 && c.img >= -0.5 && c.img <= 0.5)
			{
				ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0xFF0000);
			}
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);
}

void	ft_my_optimized_pixel_put(t_fractol *fractol, t_img *img, int x, int y, int color)
{
	int	offset;
	if (x >= 0 && x < fractol->width && y >= 0 && y < fractol->height)
	{
		offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		*(unsigned int *)(img->img_pixels_ptr + offset) = color;
	}
}

