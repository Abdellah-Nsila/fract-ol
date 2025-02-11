#include "../includes/fractol.h"

// TODO Good recources video : https://github.com/Gontjarow/MiniLibX/blob/master/docs/index.md



void    ft_draw_line(t_fractol *frat_fractol, t_line *line)
{
	double deltaX = line->endX - line->beginX;
	double deltaY = line->endY - line->beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = line->beginX;
	double pixelY = line->beginY;
	while (pixels)
	{
		mlx_pixel_put(frat_fractol->mlx, frat_fractol->win, pixelX, pixelY, line->color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

int main()
{
	t_fractol	frat_fractol;
	t_line		line;;

	frat_fractol.mlx = mlx_init();
	if (NULL == frat_fractol.mlx)
		return (EXIT_FAILURE);
	frat_fractol.width = 800;
	frat_fractol.height = 600;
	frat_fractol.win = mlx_new_window(frat_fractol.mlx, frat_fractol.width, frat_fractol.height, "Minilbx");
	if (NULL == frat_fractol.mlx)
	{
		free(frat_fractol.mlx);
		return (EXIT_FAILURE);
	}

	line.beginX = 0;
	line.beginY = 0;
	line.endX = frat_fractol.width;
	line.endY = frat_fractol.height;
	line.color = 0xFFFFFF;
	ft_draw_line(&frat_fractol, &line);
	mlx_loop(frat_fractol.mlx);
}