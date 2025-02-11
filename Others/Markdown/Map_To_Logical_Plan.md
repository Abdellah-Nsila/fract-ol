# How window (pixel space) is mapped to a 2D logical plane (custom dimension)

`To understand how the window (pixel space) is mapped to a 2D logical plane (custom dimension), let’s break it down step by step. This explanation will also include how each pixel (x, y) in the window corresponds to a point (logical_x, logical_y) in the 2D logical plane.`

## Window (Pixel Space)

	The window is a grid of pixels with dimensions width x height. Each pixel has coordinates (x, y), where:

	x ranges from 0 to width - 1 (left to right).
	y ranges from 0 to height - 1 (top to bottom).


	For example, if the window is `800x600`:

	The top-left corner is (0, 0).
	The bottom-right corner is (799, 599).

### 2D Logical Plane (Custom Dimension)

	The 2D logical plane is a custom coordinate system defined by (min_x, max_x, min_y, max_y). This plane can represent any range of values, such as:

	min_x = -2.0, max_x = 2.0
	min_y = -1.5, max_y = 1.5
	
	This allows you to map the pixel space to a custom range of values, `which is useful for rendering fractals, graphs, or other mathematical visualizations`.

### Mapping Pixel Space to Logical Space

	To map a pixel (x, y) to a point (logical_x, logical_y) in the 2D logical plane, we use the following formulas:

	logical_x = min_x + (x / width) × (max_x − min_x)
	logical_y = min_y + (y / height) × (max_y − min_y)

#### Explanation:

	* `x / width` gives the normalized position of the pixel along the x-axis (ranging from 0 to 1).

	* Multiplying by `(max_x - min_x)` scales this normalized value to the range of the logical plane.

	* Adding min_x shifts the value to the correct position in the logical plane.

	* The same logic applies for logical_y.

### Example Mapping
	Let’s say:

	Window dimensions: width = 800, height = 600
	Logical plane: min_x = -2.0, max_x = 2.0, min_y = -1.5, max_y = 1.5

 #### Mapping the Top-Left Corner (0, 0):
	logical_x = −2.0+(0800)×(2.0−(−2.0)) = −2.0
	logical_y = −1.5+(0600)×(1.5−(−1.5)) = −1.5

	So, (0, 0) in pixel space maps to (-2.0, -1.5)dimensi to you plan in the logical plane.

 #### Mapping the Bottom-Right Corner (799, 599):
	logical_x = −2.0+(799800)×(2.0−(−2.0)) ≈ 2.0
	logical_y = −1.5+(599600)×(1.5−(−1.5)) ≈ 1.5

	So, (799, 599) in pixel space maps to (2.0,  1.5) in the logical plane.

 #### Mapping the Center (400, 300):
	logical_x = −2.0+(400800)×(2.0−(−2.0)) = 0.0
	logical_y = −1.5+(300600)×(1.5−(−1.5)) = 0.0

	So, (400, 300) in pixel space maps to (0.0, 0.0) in the logical plane.

 ### Here’s a simple ASCII representation of how the pixel space maps to the logical plane:
``` plainText
Pixel Space (800x600)          Logical Plane (min_x=-2.0, max_x=2.0, min_y=-1.5, max_y=1.5)
+-------------------------+    +-------------------------+
| (0,0)                   |    | (-2.0, 1.5)             |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
| (400,300)               |    | (0.0, 0.0)              |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
|                         |    |                         |
| (799,599)               |    | (2.0, -1.5)             |
+-------------------------+    +-------------------------+
```

`This approach is commonly used in fractal rendering, graphing, and other applications where you need to map pixel coordinates to a custom coordinate system.`

### Optimization

#### First version

	✅ Pros:

		Directly calculates the mapped complex coordinates.
		No extra variables are stored in t_fractol.

	❌ Cons:

		Repeated calculations: Every pixel recalculates the same (max - min) / width and (max - min) / height, which is inefficient.
		Less optimized for performance.

#### Second version

	✅ Pros:

		Precomputes scaling factors (x_factor and y_factor) only once instead of recalculating them for each pixel.
		Faster calculations inside ft_map_to_complex() because it only does multiplication & addition instead of division.

	❌ Cons:

		Requires additional variables (x_factor and y_factor) in t_fractol.
		Slightly more memory usage (but negligible).

##### Difference Between Both Implementations

	1️⃣ First Implementation (Dynamic Calculation per Pixel)

		logical_x = min_x + (x / width) × (max_x − min_x)
		logical_y = min_y + (y / height) × (max_y − min_y)

	✅ Pros:

		Directly calculates the mapped complex coordinates.
		No extra variables are stored in t_fractol.

	❌ Cons:

		Repeated calculations: Every pixel recalculates the same (max - min) / width and (max - min) / height, which is inefficient.
		Less optimized for performance.

	2️⃣ Second Implementation (Precomputed Factors)

	x_factor = (max_x - min_x) / (width - 1);
	y_factor = (max_y - min_y) / (height - 1);

	logical_x = min_x + x * x_factor
	logical_y = min_y + y * y_factor

	✅ Pros:

		Precomputes scaling factors (x_factor and y_factor) only once instead of recalculating them for each pixel.
		Faster calculations inside ft_map_to_complex() because it only does multiplication & addition instead of division.

	❌ Cons:

		Requires additional variables (x_factor and y_factor) in t_fractol.
		Slightly more memory usage (but negligible).
