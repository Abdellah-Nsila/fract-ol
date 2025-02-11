#include "../includes/fractol.h"

// To compile :
// gcc main.c libmlx_Linux.a  -L/usr/lib -Imlx_linux -lXext -lX11 -lm
// PI = 3.141593

typedef struct s_line_data
{
	int	x;
	int	y;
	int	x_offset;
	int	y_offset;
	int	lg;
	int	color;
}				t_line_data;

void	my_optimized_pixel_put(t_fractol *fractol, t_img *img, int x, int y, int color)
{
	int	offset;
	if (x >= 0 && x < fractol->width && y >= 0 && y < fractol->height)
	{
		offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
		*(unsigned int *)(img->img_pixels_ptr + offset) = color;
	}
}

void	ft_draw_line(t_fractol *fractol, t_line_data line)
{
	int	i;

	i = 0;
	while (i < line.lg)
	{
		mlx_pixel_put(fractol->mlx, fractol->win, line.x, line.y, line.color);
		line.x += line.x_offset;
		line.y += line.y_offset;
		i++;
	}
}

void	ft_draw_square(t_fractol *fractol, int x, int y, int lg, int color)
{

	int i;
	int j;

	i = 0;
	x -= (lg / 2);
	y -= (lg / 2);
	while (i < lg)
	{
		j = 0;
		while (j < lg)
		{
			mlx_pixel_put( fractol->mlx,  fractol->win, x + i, y + j, rand() % 0x1000000);
			j++;
		}
		i++;
	}
}

void	ft_draw_square_border(t_fractol *fractol, int x, int y, int lg, int color)
{
	int i;
	int j;
	int xw;
	int yh;

	i = 0;
	xw = x - (lg / 2);
	yh = y - (lg / 2);
	while (i < lg)
	{
		j = 0;
		while (j < lg)
		{
			if (i == 0 || j == 0 || i == (lg - 1) || j == (lg - 1))
			{
				// mlx_pixel_put(fractol->mlx,  fractol->win, xw + i, yh + j, color);
				my_optimized_pixel_put(fractol, &fractol->img, xw + i, yh + j, color);
			}
			j++;
		}
		i++;
	}
	if (lg > 1)
	{
		ft_draw_square_border(fractol, x + (lg / 2), y, lg / 2, 0xff0000);
		ft_draw_square_border(fractol, x - (lg / 2), y, lg / 2, 0xff0000);
		ft_draw_square_border(fractol, x , y + (lg / 2), lg / 2, 0xff0000);
		ft_draw_square_border(fractol, x , y - (lg / 2), lg / 2, 0xff0000);
	}
}

void	ft_color_window(t_fractol *fractol, int color)
{

	int y;
	int x;

	y = 0;
	while (y < fractol->height)
	{
		x = 0;
		while (x < fractol->width)
		{
			my_optimized_pixel_put(fractol, &fractol->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	ft_handle_input(int keysym, t_fractol *fractol)
{
	printf("The %d key has beem pressed\n", keysym);
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	ft_change_bg(int keysym, t_fractol *fractol)
{
	if (keysym == XK_r)
		ft_color_window(fractol, 0xff0000);
	else if (keysym == XK_g)
		ft_color_window(fractol, 0x00ff00);
	else if (keysym == XK_b)
		ft_color_window(fractol, 0x0000ff);
	else
		ft_color_window(fractol, rand() * 1000000);
	mlx_put_image_to_window(fractol->mlx,  fractol->win, fractol->img.img_ptr, 0, 0);
}

int	main(void)
{
	t_fractol	fractol;
	void	*mlx;
	void	*win;

	// Init connection &&& window 
	fractol.mlx = mlx_init();
	if (NULL == fractol.mlx)
		return (EXIT_FAILURE);
	fractol.width = 2000;
	fractol.height = 1500;
    fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height, "Minilbx");
	if (NULL == fractol.mlx)
	{
		free(fractol.mlx);
		return (EXIT_FAILURE);
	}

	// ft_draw_square(&fractol, 450, 350, 450, 0xff0000);
	// mlx_string_put(fractol.mlx, fractol.win, 650, 600, 0xffffff, "Minilbx");

	// Init Img 
	fractol.img.img_ptr = mlx_new_image(fractol.mlx, fractol.width, fractol.height);
	fractol.img.img_pixels_ptr = mlx_get_data_addr(fractol.img.img_ptr, &fractol.img.bits_per_pixel, &fractol.img.line_length,
								&fractol.img.endian);
	
	// Draw some cheaps
	ft_draw_square_border(&fractol, fractol.width / 2, fractol.height / 2, 500, 0xff0000);
	mlx_put_image_to_window(fractol.mlx,  fractol.win, fractol.img.img_ptr, 0, 0);

	// Event Hook
	// mlx_key_hook(fractol.win, ft_change_bg, &fractol);

	// Window Loop
    mlx_loop(fractol.mlx);

	// Clean Up
	mlx_destroy_window(fractol.mlx, fractol.win);
	mlx_destroy_display(fractol.mlx);
	free(fractol.mlx);
}
