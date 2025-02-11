/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:47:06 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/03 10:16:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_zoom_square_plane(t_fractol *fractol, double zoom_factor, int mouse_x, int mouse_y)
{
	// Convert mouse coordinates to logical space
	double mouse_x_logical = fractol->min_x + (mouse_x / (double)fractol->width) * (fractol->max_x - fractol->min_x);
	double mouse_y_logical = fractol->min_y + (mouse_y / (double)fractol->height) * (fractol->max_y - fractol->min_y);

	// Adjust the min/max coordinates
	fractol->min_x = mouse_x_logical + (fractol->min_x - mouse_x_logical) / zoom_factor;
	fractol->max_x = mouse_x_logical + (fractol->max_x - mouse_x_logical) / zoom_factor;
	fractol->min_y = mouse_y_logical + (fractol->min_y - mouse_y_logical) / zoom_factor;
	fractol->max_y = mouse_y_logical + (fractol->max_y - mouse_y_logical) / zoom_factor;
}

void	ft_draw_square(t_fractol *fractol)
{
	int		x, y;
	double	logical_x, logical_y;
	ft_init_image_buffer(fractol);

	for (x = 0; x < fractol->width; x++)
	{
		for (y = 0; y < fractol->height; y++)
		{
			// Map pixel to logical space
			logical_x = fractol->min_x + x * (fractol->max_x - fractol->min_x) / fractol->width;
			logical_y = fractol->min_y + y * (fractol->max_y - fractol->min_y) / fractol->height;

			// Draw only inside the square
			if (logical_x >= -150 && logical_x <= 150 && logical_y >= -150 && logical_y <= 150)
				ft_my_optimized_pixel_put(fractol, &fractol->img, x, y, 0xFF0000);
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);
}


int	ft_mouse(int button, int x, int y, void *param)
{
	t_fractol *fractol = param;
	double zoom_factor = 1.0;

	if (button == 4) // Mouse scroll up (zoom in)
		zoom_factor = 1.1;
	else if (button == 5) // Mouse scroll down (zoom out)
		zoom_factor = 0.9;
	if (zoom_factor != 1.0)
	{
		ft_zoom_square_plane(fractol, zoom_factor, x, y);
		ft_draw_square(fractol);
	}

	return (EXIT_SUCCESS);
}

int	ft_key(int keycode, t_fractol *fractol)
{
	if (keycode == XK_Escape)
	{
		if (fractol->img.img_ptr)
			mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
		ft_clean_mlx(fractol);
	}
	return (EXIT_SUCCESS);
}

void	ft_init_square_plane(t_fractol *fractol)
{
	fractol->min_x = (fractol->width / 2) * -1; // Centered at (0,0)
	fractol->max_x = fractol->width / 2;
	fractol->min_y = (fractol->height / 2) * -1;
	fractol->max_y = fractol->height / 2;
}

int	main()
{
	t_fractol fractol;

	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		return (EXIT_FAILURE);
	fractol.width = 1000;
	fractol.height = 800;
	fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height, "MiniLibX");
	if (!fractol.win)
		return (EXIT_FAILURE);

	// Initialize zooming system
	fractol.zoom = 1.0;
	fractol.offset_x = 0;
	fractol.offset_y = 0;
	ft_init_square_plane(&fractol);

	// Draw the initial square
	ft_draw_square(&fractol);

	// Hook events
	mlx_mouse_hook(fractol.win, ft_mouse, &fractol);
	mlx_key_hook(fractol.win, ft_key, &fractol);
	mlx_loop(fractol.mlx);

	return (EXIT_SUCCESS);
}

