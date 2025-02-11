#include "../includes/fractol.h"

int mouse_event(int button, int x, int y, void *param)
{
	printf("%s: %d  |  x: %d   |  y: %d\n",(char *)param, button, x, y);
	return (EXIT_SUCCESS);
}

int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Registering Mouse Events");

	mlx_mouse_hook(win, &mouse_event, "Mouse Button");

	mlx_loop(mlx);
}