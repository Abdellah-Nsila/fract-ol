/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:57:35 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/10 14:24:20 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_loop_hook(t_fractol *fractol)
{
	if (!fractol)
		return (1);
	ft_draw_fractal(fractol);
	mlx_string_put(fractol->mlx, fractol->win, 15, 15, 0xFFFFFF,
		"Settings Menu: h Key");
	if (fractol->toggle_menu)
		ft_draw_menu(fractol);
	return (0);
}

int	ft_mouse_move_hook(int x, int y, t_fractol *fractol)
{
	if (fractol->trick_mouse)
	{
		fractol->fixed_c_re = (double)x / fractol->width * 2.5 - 1.0;
		fractol->fixed_c_img = (double)y / fractol->height * 2.5 - 1.0;
	}
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (button == ZOOM_IN && (fractol->zoom < MAX_ZOOM))
	{
		fractol->zoom *= ZOOM_FACTOR;
		ft_zoom_plan(fractol, ZOOM_FACTOR, x, y);
	}
	else if (button == ZOOM_OUT && (fractol->zoom > MIN_ZOOM))
	{
		fractol->zoom /= ZOOM_FACTOR;
		ft_zoom_plan(fractol, 1 / ZOOM_FACTOR, x, y);
	}
	else if (button == INCREASE_BUTTON && fractol->precision < MAX_PRECISION)
		fractol->precision += PRECISION_FACTOR;
	else if (button == DECREASE_BUTTON && fractol->precision > MIN_PRECISION)
		fractol->precision -= PRECISION_FACTOR;
	return (EXIT_SUCCESS);
}

int	ft_key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == ESCAPE_KEY)
		ft_close(fractol);
	else if (keycode == LEFT_KEY)
		ft_move_plan(fractol, -MOVE_FACTOR / fractol->zoom, 0);
	else if (keycode == RIGHT_KEY)
		ft_move_plan(fractol, MOVE_FACTOR / fractol->zoom, 0);
	else if (keycode == UP_KEY)
		ft_move_plan(fractol, 0, MOVE_FACTOR / fractol->zoom);
	else if (keycode == DOWN_KEY)
		ft_move_plan(fractol, 0, -MOVE_FACTOR / fractol->zoom);
	else if (keycode == SHIFT_KEY)
		ft_generate_random_gradient_color(fractol);
	else if (keycode == SPACE_KEY)
		fractol->trick_mouse = !fractol->trick_mouse;
	else if (keycode == h_KEY)
		fractol->toggle_menu = !fractol->toggle_menu;
	return (EXIT_SUCCESS);
}

void	ft_init_events(t_fractol *fractol)
{
	mlx_mouse_hook(fractol->win, ft_mouse_hook, fractol);
	mlx_key_hook(fractol->win, ft_key_hook, fractol);
	mlx_hook(fractol->win, ON_MOUSEMOVE, 1L << 6, ft_mouse_move_hook, fractol);
	mlx_hook(fractol->win, ON_DESTROY, 0L, ft_close, fractol);
	mlx_loop_hook(fractol->mlx, ft_loop_hook, fractol);
}
