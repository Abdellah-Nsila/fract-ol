/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:55:43 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/02 14:54:27 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_init_complex_plane(t_fractol *fractol)
{
	fractol->MinRe = -2.0;
	fractol->MaxRe = 1.0;
	fractol->MinIm = -1.2;
	fractol->MaxIm = fractol->MinIm + (fractol->MaxRe - fractol->MinRe) * fractol->height / fractol->width;

	fractol->Re_factor = (fractol->MaxRe - fractol->MinRe) / (fractol->width - 1);
	fractol->Im_factor = (fractol->MaxIm - fractol->MinIm) / (fractol->height - 1);
}

t_complex	ft_map_pixel_to_complex(int x, int y, t_fractol *fractol)
{
	t_complex c;
	c.real = fractol->MinRe + x * fractol->Re_factor;
	c.imag = fractol->MaxIm - y * fractol->Im_factor;
	return c;
}

void	ft_zoom_complex_plane(t_fractol *fractol, double zoom_factor, int mouse_x, int mouse_y)
{
	// Calculate the complex number at the mouse position
	t_complex mouse_c = ft_map_pixel_to_complex(mouse_x, mouse_y, fractol);

	// Adjust the complex plane range
	fractol->MinRe = mouse_c.real + (fractol->MinRe - mouse_c.real) / zoom_factor;
	fractol->MaxRe = mouse_c.real + (fractol->MaxRe - mouse_c.real) / zoom_factor;
	fractol->MinIm = mouse_c.imag + (fractol->MinIm - mouse_c.imag) / zoom_factor;
	fractol->MaxIm = mouse_c.imag + (fractol->MaxIm - mouse_c.imag) / zoom_factor;

	// Recalculate the scaling factors
	fractol->Re_factor = (fractol->MaxRe - fractol->MinRe) / (fractol->width - 1);
	fractol->Im_factor = (fractol->MaxIm - fractol->MinIm) / (fractol->height - 1);
}

void	ft_pan_complex_plane(t_fractol *fractol, double offset_x, double offset_y)
{
	fractol->MinRe += offset_x;
	fractol->MaxRe += offset_x;
	fractol->MinIm += offset_y;
	fractol->MaxIm += offset_y;

	// Recalculate the scaling factors
	fractol->Re_factor = (fractol->MaxRe - fractol->MinRe) / (fractol->width - 1);
	fractol->Im_factor = (fractol->MaxIm - fractol->MinIm) / (fractol->height - 1);
}
