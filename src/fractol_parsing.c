/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:19:13 by abnsila           #+#    #+#             */
/*   Updated: 2025/02/09 16:26:05 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_bool	ft_get_julia_cord(t_fractol *fractol, char **av, int i)
{
	char	*endptr;
	t_bool	is_valid_cord;

	is_valid_cord = true;
	fractol->fixed_c_re = ft_strtod(av[i], &endptr);
	if (*endptr != '\0')
	{
		is_valid_cord = false;
		ft_putstr_fd("Error: Invalid Julia <fixed_x>\n", STDERR_FILENO);
	}
	fractol->fixed_c_img = ft_strtod(av[i + 1], &endptr);
	if (*endptr != '\0')
	{
		is_valid_cord = false;
		ft_putstr_fd("Error: Invalid Julia <fixed_y>\n", STDERR_FILENO);
	}
	return (is_valid_cord);
}

t_bool	ft_is_julia(t_fractol *fractol, int ac, char **av)
{
	int		i;

	i = 0;
	if (ac == 4 && ft_strlcmp("Julia", av[1]))
	{
		i = 2;
		fractol->set_type = Julia_square;
	}
	else if (ac == 5 && ft_check_set_arg("Julia", av[1], "square", av[2]))
	{
		i = 3;
		fractol->set_type = Julia_square;
	}
	else if (ac == 5 && ft_check_set_arg("Julia", av[1], "cube", av[2]))
	{
		i = 3;
		fractol->set_type = Julia_cube;
	}
	if (i)
		return (ft_get_julia_cord(fractol, av, i));
	return (false);
}

t_bool	ft_check_set_arg(char *set, char *set_arg, char *power, char *power_arg)
{
	return (ft_strlcmp(set, set_arg) && ft_strlcmp(power, power_arg));
}

void	ft_exit_on_error(void)
{
	ft_putstr_fd("Usage: ./fractol <set> <type>\n\
	[1] ./fractol Mandelbrot\n\
	[3] ./fractol Mandelbrot <square, cube>\n\
	[2] ./fractol Julia <fixed_x> <fixed_y>\n\
	[4] ./fractol Julia <square, cube> <fixed_x> <fixed_y>\n\
	[2] ./fractol Burningship\n\
	[4] ./fractol Burningship <square, cube>\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_check_parse(t_fractol *fractol, int ac, char **av)
{
	if (ac >= 2 && ac <= 5)
	{
		if (ac == 2 && ft_strlcmp("Julia", av[1]))
			ft_exit_on_error();
		else if ((ac == 2 && ft_strlcmp("Mandelbrot", av[1]))
			|| (ac == 3 && ft_check_set_arg("Mandelbrot", av[1],
					"square", av[2])))
			fractol->set_type = Mandelbrot_square;
		else if (ac == 3 && ft_check_set_arg("Mandelbrot", av[1],
				"cube", av[2]))
			fractol->set_type = Mandelbrot_cube;
		else if (ft_is_julia(fractol, ac, av))
			return ;
		else if ((ac == 2 && ft_strlcmp("Burningship", av[1]))
			|| (ac == 3 && ft_check_set_arg("Burningship", av[1],
					"square", av[2])))
			fractol->set_type = Burningship_square;
		else if (ac == 3 && ft_check_set_arg("Burningship", av[1],
				"cube", av[2]))
			fractol->set_type = Burningship_cube;
		else
			ft_exit_on_error();
	}
	else
		ft_exit_on_error();
}
