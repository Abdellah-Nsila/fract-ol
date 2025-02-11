/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:42:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/08 16:01:09 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"


//! Multi threading for fast rendering < Forbideen ): >
// #include <pthread.h>
// #define THREADS 8  // Number of threads to use
// typedef struct s_thread_data {
// 	t_fractol *fractol;
// 	int start_y;
// 	int end_y;
// } t_thread_data;

// void *ft_draw_fractol_thread(void *arg)
// {
// 	t_thread_data *data = (t_thread_data *)arg;
// 	t_fractol *fractol = data->fractol;
// 	int x, y;
// 	t_complex c;

// 	for (y = data->start_y; y < data->end_y; y++)
// 	{
// 		for (x = 0; x < fractol->width; x++)
// 		{
// 			c = ft_map_pixel_to_complex(x, y, fractol);
// 			if (fractol->set == Mandelbrot_sqrt)
// 				ft_mandelbrot_sq_set(fractol, c, x, y, fractol->precision);
// 			else if (fractol->set == Julia_sqrt)
// 				ft_julia_sq_set(fractol, c, x, y, fractol->precision);
// 			else if (fractol->set == Mandelbrot_cube)
// 				ft_mandelbrot_cub_set(fractol, c, x, y, fractol->precision);
// 			else if (fractol->set == Julia_cube)
// 				ft_julia_cub_set(fractol, c, x, y, fractol->precision);
// 		}
// 	}
// 	return NULL;
// }

// void ft_draw_fractol(t_fractol *fractol)
// {
// 	pthread_t threads[THREADS];
// 	t_thread_data thread_data[THREADS];
// 	int i;
// 	int step = fractol->height / THREADS;

// 	for (i = 0; i < THREADS; i++)
// 	{
// 		thread_data[i].fractol = fractol;
// 		thread_data[i].start_y = i * step;
// 		thread_data[i].end_y = (i == THREADS - 1) ? fractol->height : (i + 1) * step;
// 		pthread_create(&threads[i], NULL, ft_draw_fractol_thread, &thread_data[i]);
// 	}

// 	for (i = 0; i < THREADS; i++)
// 		pthread_join(threads[i], NULL);

// 	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);
// }



//! Original
void	ft_draw_fractol(t_fractol *fractol)
{
	for (int y = 0; y < fractol->height; y++)
	{
		for (int x = 0; x < fractol->width; x++)
		{
			t_complex c = ft_map_pixel_to_complex(x, y, fractol);
			if (fractol->set == Mandelbrot_sqrt)
				ft_mandelbrot_sq_set(fractol, c, x, y, fractol->precision);
			else if (fractol->set == Julia_sqrt)
				ft_julia_sq_set(fractol, c, x, y, fractol->precision);
			else if (fractol->set == Mandelbrot_cube)
				ft_mandelbrot_cub_set(fractol, c, x, y, fractol->precision);
			else if (fractol->set == Julia_cube)
				ft_julia_cub_set(fractol, c, x, y, fractol->precision);
		}
	}
}

void	ft_init_fractol(t_fractol *fractol)
{
	// Initiale mlx connection with (X/Server) && create window
	fractol->mlx = mlx_init();
	if (NULL == fractol->mlx)
		exit(EXIT_FAILURE);
	fractol->width = 1000;
	fractol->height = 800;
	fractol->win = mlx_new_window(fractol->mlx, fractol->width, fractol->height, "Minilbx");
	if (NULL == fractol->mlx)
	{
		free(fractol->mlx);
		exit(EXIT_FAILURE);
	}
	fractol->img.img_ptr = NULL;
	ft_init_image_buffer(fractol);
	fractol->zoom = 1.0;
	fractol->offset_x = 0.0;
	fractol->offset_y = 0.0;
	fractol->precision = 50;
	fractol->julia_c_real = -0.8;
	fractol->julia_c_imag = 0.1; 
	ft_generate_random_gradient_color(fractol);
	ft_init_complex_plane(fractol);
	fractol->frame = 0;
}

void	ft_check_parse(t_fractol *fractol, int ac, char **av)
{
	if (ac == 2)
	{	
		if (ft_strlcmp("Mandelbrot", av[1], ft_strlen(av[1])) == true)
			fractol->set = Mandelbrot_sqrt;
		else if (ft_strlcmp("Julia", av[1], ft_strlen(av[1])) == true)
			fractol->set = Julia_sqrt;
	}
	else if (ac == 3)
	{
		if ((ft_strlcmp("Mandelbrot", av[1], ft_strlen(av[1])) == true)
			&& (ft_strlcmp("cube", av[2], ft_strlen(av[2])) == true))
			fractol->set = Mandelbrot_cube;
		else if ((ft_strlcmp("Julia", av[1], ft_strlen(av[1])) == true)
			&& (ft_strlcmp("cube", av[2], ft_strlen(av[2])) == true))
			fractol->set = Julia_cube;
	}
	else
	{
		ft_printf("Usage: ./fratcol <set> type\n\
	[1] ./fratcol Mandelbrot\n\
	[2] ./fratcol Julia\n");
		exit(EXIT_FAILURE);
	}
}

int ft_update_frame(t_fractol *fractol)
{
	fractol->frame += 0.06;
	if (fractol->frame > 600.0)
	{
		fractol->frame = 0;{
		
		ft_draw_fractol(fractol); // Recalculate the fractal
		mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img_ptr, 0, 0);
	}
	// printf("frame: %f\n", fractol->frame);
	return (0);
}


int main(int ac, char **av)
{
	t_fractol	fractol;

	ft_check_parse(&fractol, ac, av);
	ft_init_fractol(&fractol);
	ft_draw_fractol(&fractol);
	
	mlx_put_image_to_window(fractol.mlx,  fractol.win, fractol.img.img_ptr, 0, 0);
	mlx_destroy_image(fractol.mlx, fractol.img.img_ptr);

	// Hook the update function to be called every frame
	mlx_loop_hook(fractol.mlx, ft_update_frame, &fractol);

	// Lisening for events
	mlx_mouse_hook(fractol.win, ft_mouse_event, &fractol);
	mlx_key_hook(fractol.win, ft_key_hook, &fractol);
	mlx_loop(fractol.mlx);

	// Clean Up
	mlx_destroy_window(fractol.mlx, fractol.win);
	mlx_destroy_display(fractol.mlx);
	free(fractol.mlx);
}

