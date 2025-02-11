
#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../Libft/includes/libft.h"
# include <math.h>
# include <X11/keysym.h>
# include <stdio.h>

#define PALETTE_SIZE 13

typedef struct s_img {
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_line
{
	int beginX;
	int beginY;
	int endX;
	int endY;
	int	color;
}	t_line;

enum e_sets
{
	Mandelbrot_sqrt,
	Mandelbrot_cube,
	Julia_sqrt,
	Julia_cube,
};

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
	int		set;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		precision;
	double	min_x; // Min X coordinate
	double	max_x; // Max X coordinate
	double	min_y; // Min Y coordinate
	double	max_y; // Max Y coordinate
	int		palette[PALETTE_SIZE];
	double	MinRe;
	double	MaxRe;
	double	MinIm;
	double	MaxIm;
	double	Re_factor;
	double	Im_factor;
	double	julia_c_real;
	double	julia_c_imag;
	double	frame;
}				t_fractol;


typedef struct s_complex
{
	double real;
	double imag;
} t_complex;

// Complex Plan functions
void		ft_init_complex_plane(t_fractol *fractol);
t_complex	ft_map_pixel_to_complex(int x, int y, t_fractol *fractol);
void		ft_zoom_complex_plane(t_fractol *fractol, double zoom_factor, int mouse_x, int mouse_y);
void		ft_pan_complex_plane(t_fractol *fractol, double offset_x, double offset_y);

// Events hook functions
int			ft_mouse_event(int button, int x, int y, void *param);
int			ft_key_hook(int keycode, t_fractol *fractol);

// Fractol utils functions
void		ft_init_image_buffer(t_fractol *fractol);
void		ft_my_optimized_pixel_put(t_fractol *fractol, t_img *img, int x, int y, int color);
void		ft_clear_image(t_fractol *fractol, int color);
void		ft_generate_random_gradient_color(t_fractol *fractol);
int			ft_get_color(t_fractol *fractol, int iteration, int max_iterations);

// Draw fractol functions
void		ft_mandelbrot_sq_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter);
void		ft_mandelbrot_cub_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter);
void		ft_julia_sq_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter);
void		ft_julia_cub_set(t_fractol *fractol, t_complex c, int x, int y, int max_iter);

void		ft_draw_fractol(t_fractol *fractol);

// Clean Up
void		ft_clean_mlx(t_fractol *fractol);

#endif
