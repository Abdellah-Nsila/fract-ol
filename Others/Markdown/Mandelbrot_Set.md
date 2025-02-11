 # Mandelbrot set

 - The `Mandelbrot set` is a two-dimensional set with a relatively simple definition that exhibits great complexity, especially as it is magnified. It is popular for its aesthetic appeal and fractal structures. The set is defined in the complex plane as the complex numbers `c`,
 - for which the function `f(z) = z^2 + c` does not diverge to infinity when iterated starting at `z = 0` , i.e., for which the sequence `f(0)`, `f(f(0))`, etc., remains bounded in absolute value.
 - We see that the representation of the `Mandelbrot set` is a recursive function => `f(z) = z^2 + c`, that call hitself starting at `z = 0`, and his utput is the input of the next call for example:
 - We have `z = 0`, and `c = 0`, let's apply this function recursively `f(z) = z^2 + c`:
 - `f(0) = 0^2 + 1` => `f(0) = 1` | `f(1) = 1^2 + 1` => `f(1) = 2` | `f(2) = 2^2 + 1` => `f(2) = 5` | `f(5) = 5^2 + 1` => `f(5) = 26` | `f(26) = 26^2 + 1` => `f(26) = 677` you can see the function diverge to infinity
 - Now We have `z = 0`, and `c = -1`, let's apply this function recursively `f(z) = z^2 + c`:
 - `f(0) = 0^2 - 1` => `f(0) = -1` | `f(-1) = -1^2 - 1` => `f(-1) = 0` | `f(0) = 0^2 - 1` => `f(0) = -1` | `f(-1) = -1^2 - 1` => `f(-1) = 0` you can see here the function does not diverge it stay in a loop
 - So know we have two senarios when given parametres to the `f(z) = z^2 + c`, if the function does not diverge is part of `Mandelbrot set`, if not, it'is not Xd 

# Instruction from math

 - `f(z) = z^2 + c` with `z0 = 0`, `c = a + bi` (`c` is a complex number)
 - `f(z1) = c`
 - `f(z2) = z1^2 + c`
 - `f(z2) = c^2 + c`
 - `f(z2) = c^2 + c`
 - let's take `c^2` first, we know that `c = a + bi`
 - `c^2` = `(a+bi) * (a+bi)`
 - `c^2` = `a^2 + abi + abi + (b^2 * i^2)` we know that `i^2 = -1`
 - `c^2` = `a^2 + abi + abi + (b^2 * -1)`
 - `c^2` = `a^2 + abi + abi + (-b^2)`
 - `c^2` = `a^2 + abi + abi - b^2`
 - `c^2` = `a^2 + 2abi - b^2`
 - `c^2` = `a^2 - b^2 + 2abi`
 - `c^2` = `(a^2 - b^2) + 2abi` now our expression containe two part real part and imaginary part
 - let's take `c` andto expression
 - `f(z2) = (a^2 - b^2) + 2abi + a + bi`
 - `f(z2) = (a^2 - b^2 + a) + 2abi + bi`
 - real part:     `(a^2 - b^2 + a)`
 - imaginary part: `2abi + bi`
 
 ## Color Condition (psychedelic effects)
 - Finally we need just to calculate the real part and imaginary part, and add them, and check if the result diverge to inifity, because we dont have time to wait to infinity we just take a value like `4` to check if its greater or smaller than,if it is smaller we color on black, otherwise we color using diffrent (gradient color/using a generated pallette for example) color to show the depth of each fractal.
