/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:41:38 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/10 18:35:14 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define WIDTH 800
# define HEIGHT 600
# define CENTER_X -0.0
# define CENTER_Y 0.0
# define RANGE_X 4.0
# define DEFAULT_ZOOM 1
# define ZOOM_FACTOR 1.08
# define MAX_ZOOM 508689079416445.0
# define MIN_ZOOM 0.00457443136616103498
# define PRECISION_FACTOR 5
# define MAX_PRECISION 950
# define MIN_PRECISION 1
# define MOVE_FACTOR 0.2
# define INSIDE_COLOR 0x000000
# define DEFAULT_ITERATIONS 30
# define ESCAPE_LIMITE 4.0
# define PALETTE_SIZE 13

enum e_sets
{
	Mandelbrot_square,
	Mandelbrot_cube,
	Julia_square,
	Julia_cube,
	Burningship_square,
	Burningship_cube,
};

enum e_events_hooks
{
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 17,
};

enum e_events_inputs
{
	ZOOM_IN = 4,
	ZOOM_OUT = 5,
	INCREASE_BUTTON = 1,
	DECREASE_BUTTON = 3,
	LEFT_KEY = 65361,
	UP_KEY = 65362,
	RIGHT_KEY = 65363,
	DOWN_KEY = 65364,
	ESCAPE_KEY = 65307,
	SHIFT_KEY = 65505,
	SPACE_KEY = 32,
	h_KEY = 104,
};

#endif
