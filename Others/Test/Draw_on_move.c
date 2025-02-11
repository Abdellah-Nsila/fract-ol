#include "../includes/fractol.h"

int mouse_event(int button, int x, int y, void *param)
{
	t_fractol *fractol;

	fractol = param;
	printf("Mouse Button: %d\n", button);
	mlx_pixel_put(fractol->mlx, fractol->win, x, y, rand() * 1000000);
	return (EXIT_SUCCESS);
}

int main()
{
	t_fractol	fractol;

	fractol.mlx = mlx_init();
	if (NULL == fractol.mlx)
		return (EXIT_FAILURE);
	fractol.width = 800;
	fractol.height = 600;
	fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height, "Minilbx");
	if (NULL == fractol.mlx)
	{
		free(fractol.mlx);
		return (EXIT_FAILURE);
	}

	mlx_mouse_hook(fractol.win, &mouse_event, &fractol);
	mlx_loop(fractol.mlx);
}