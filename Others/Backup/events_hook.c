/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:57:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/02 16:36:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_mouse_event(int button, int x, int y, void *param)
{
	t_fractol *fractol = param;

	ft_init_image_buffer(fractol);
	if (button == 4) // Mouse scroll up (zoom in)
	{
		fractol->zoom *= 1.1;
		ft_zoom_complex_plane(fractol, 1.1, x, y); // Zoom in at the mouse position
	}
	else if (button == 5) // Mouse scroll down (zoom out)
	{
		fractol->zoom /= 1.1;
		ft_zoom_complex_plane(fractol, 1 / 1.1, x, y); // Zoom out at the mouse position
	}
	else if (button == 1) // Left mouse button (generate random gradient color)
		ft_generate_random_gradient_color(fractol);

	// Re-render the fractal
	ft_draw_fractol(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);

	return (EXIT_SUCCESS);
}

int	ft_key_hook(int keycode, t_fractol *fractol)
{
	ft_init_image_buffer(fractol);
	// printf("key: %d\n", keycode);
	if (keycode == XK_Escape) // ESC
		ft_clean_mlx(fractol);
	if (keycode == XK_Left) // Left arrow key (pan left)
		ft_pan_complex_plane(fractol, -0.1 / fractol->zoom, 0);
	else if (keycode == XK_Right) // Right arrow key (pan right)
		ft_pan_complex_plane(fractol, 0.1 / fractol->zoom, 0);
	else if (keycode == XK_Up) // Up arrow key (pan up)
		ft_pan_complex_plane(fractol, 0, -0.1 / fractol->zoom);
	else if (keycode == XK_Down) // Down arrow key (pan down)
		ft_pan_complex_plane(fractol, 0, 0.1 / fractol->zoom);
	else if (keycode == XK_q) // Increase precision
		fractol->precision += 5;
	else if (keycode == XK_w) // Decrease precision
		fractol->precision -= 5;
	// For julia set
	else if (keycode == XK_a)
		fractol->julia_c_real += 0.01;
	else if (keycode == XK_s)
		fractol->julia_c_real -= 0.01;
	else if (keycode == XK_z)
		fractol->julia_c_imag += 0.01;
	else if (keycode == XK_x)
		fractol->julia_c_imag -= 0.01;
	// printf("julia_c_real: %f    julia_c_imag: %f\n", fractol->julia_c_real, fractol->julia_c_imag);

	// Re-render the fractal
	ft_draw_fractol(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);
	return (0);
}


