 # Zoom behavioure
 - The key is to set a logical plan; This plane can represent any range of values, so tronsforme a maps to a mathematical coordinate system (logical plane) and zoom in/out

## Zooming in the Logical Plane

	When you zoom in or out, you adjust the min_x, max_x, min_y, and max_y values to focus on a smaller or larger region of the logical plane. For example:

		Zooming in by a factor of 2 would halve the range of min_x, max_x, min_y, and max_y.

		Zooming out by a factor of 2 would double the range.

The ft_zoom_plane function adjusts these values based on the mouse position and zoom factor:
c
Copy

``` C
void ft_zoom_plane(t_fractol *fractol, double zoom_factor, int mouse_x, int mouse_y)
{
	// Convert mouse coordinates to logical space
	double mouse_x_logical = fractol->min_x + (mouse_x / (double)fractol->width) * (fractol->max_x - fractol->min_x);
	double mouse_y_logical = fractol->min_y + (mouse_y / (double)fractol->height) * (fractol->max_y - fractol->min_y);

	// Adjust the min/max coordinates
	fractol->min_x = mouse_x_logical + (fractol->min_x - mouse_x_logical) / zoom_factor;
	fractol->max_x = mouse_x_logical + (fractol->max_x - mouse_x_logical) / zoom_factor;
	fractol->min_y = mouse_y_logical + (fractol->min_y - mouse_y_logical) / zoom_factor;
	fractol->max_y = mouse_y_logical + (fractol->max_y - mouse_y_logical) / zoom_factor;
}
```

## Explanation of ft_zoom_plane

`The function ft_zoom_plane is responsible for zooming in and out on the fractal image by adjusting the logical coordinate system (min_x, max_x, min_y, max_y). This transformation ensures that the zoom effect is centered at the mouse position.`

### Understanding the Logical Plane
	In fractal rendering, the screen (pixel coordinates) maps to a mathematical coordinate system (logical plane). The logical plane is defined by:

		min_x, max_x: The horizontal range in the logical plane.
		min_y, max_y: The vertical range in the logical plane.
		(mouse_x, mouse_y): The pixel position of the mouse.

	When zooming in:

		The range of values decreases, meaning we are focusing on a smaller region.
		The zoom is centered at the mouse position.

	When zooming out:

		The range increases, meaning we see a larger portion of the fractal.

#### Step-by-step Breakdown of the Code
```C
void ft_zoom_plane(t_fractol *fractol, double zoom_factor, int mouse_x, int mouse_y)
{
	// Convert mouse coordinates to logical space
	double mouse_x_logical = fractol->min_x + (mouse_x / (double)fractol->width) * (fractol->max_x - fractol->min_x);
	double mouse_y_logical = fractol->min_y + (mouse_y / (double)fractol->height) * (fractol->max_y - fractol->min_y);
```

##### Step 1: Convert Pixel Coordinates to Logical Coordinates
	The mouse position (mouse_x, mouse_y) is converted into the corresponding coordinates in the logical plane. This helps center the zoom around the cursor.

	For example, suppose:

		min_x = -2.0, max_x = 2.0 (horizontal range)
		min_y = -2.0, max_y = 2.0 (vertical range)
		width = 800, height = 800 (window size)
		mouse_x = 400, mouse_y = 400 (mouse at center)

	Then:
	mouse_x_logical=−2.0+(400800×(2.0−(−2.0)))=−2.0+(0.5×4.0)=0.0
	mouse_x_logical=−2.0+(800400​×(2.0−(−2.0)))=−2.0+(0.5×4.0)=0.0
	mouse_y_logical=−2.0+(400800×(2.0−(−2.0)))=0.0
	mouse_y_logical=−2.0+(800400​×(2.0−(−2.0)))=0.0

	Thus, the mouse at (400, 400) maps to (0.0, 0.0) in the logical plane.


#### Step 2: Adjust the Logical Range

```C
	// Adjust the min/max coordinates
	fractol->min_x = mouse_x_logical + (fractol->min_x - mouse_x_logical) / zoom_factor;
	fractol->max_x = mouse_x_logical + (fractol->max_x - mouse_x_logical) / zoom_factor;
	fractol->min_y = mouse_y_logical + (fractol->min_y - mouse_y_logical) / zoom_factor;
	fractol->max_y = mouse_y_logical + (fractol->max_y - mouse_y_logical) / zoom_factor;
}
```
	zoom_factor > 1: Zooms in (reduces the range).
	zoom_factor < 1: Zooms out (expands the range).

Each coordinate (min_x, max_x, min_y, max_y) is moved closer to the mouse_x_logical and mouse_y_logical by dividing the distance from the center by the zoom factor.

##### Example (Zoom in by a factor of 2):

	Initial: min_x = -2.0, max_x = 2.0, mouse_x_logical = 0.0
	Zoom factor: 2.0
	New values:

	min_x=0.0+−2.0−0.02.0=0.0−1.0=−1.0
	min_x=0.0+2.0−2.0−0.0​=0.0−1.0=−1.0
	max_x=0.0+2.0−0.02.0=0.0+1.0=1.0
	max_x=0.0+2.02.0−0.0​=0.0+1.0=1.0

	So after zooming in, the new logical range becomes [-1.0, 1.0], effectively zooming in.

#### Summary

	The function converts the mouse position to logical coordinates.
	It scales the logical range centered around the mouse.
	Higher zoom factor = smaller range (zoom in).
	Lower zoom factor = larger range (zoom out).

	The pixel space (x, y) is mapped to the logical plane (logical_x, logical_y) using linear interpolation.

	The logical plane can represent any custom range of values, allowing for flexible visualization.

	Zooming adjusts the min_x, max_x, min_y, and max_y values to focus on a specific region of the logical plane.

