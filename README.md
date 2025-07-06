# Root Finding Program

This project implements various **root-finding algorithms** for solving equations numerically.
 It supports methods like:

- Bisection Method
- False Position Method
- Secant Method
- Newton-Raphson Method

The program is written in **C language** and uses the **TinyExpr** library to evaluate mathematical expressions.

------

## Features

- Evaluate mathematical expressions with a variable `x`
- Calculate derivatives numerically (finite difference method)
- Find roots using four different methods
- Input validation for equations and numbers
- Error tolerance checking
- Minimum number of iterations calculator (for Bisection Method)
- Clear and user-friendly console interface



## Project Structure

- `main.c` — Main program loop (menu + method selection)
- `functions.h` — Function declarations
- `functions.c` — Function definitions (root-finding methods, input handling, etc.)
- `tinyexpr.c/h` — TinyExpr library for expression evaluation

## Notes

- Only equations using the variable `x` are supported.
- If you use variables like `y` or `z`, the program will reject the input.
- Error handling is included for invalid input, division by zero, and zero derivatives.
- TinyExpr library must be included in the project folder (`tinyexpr.c`, `tinyexpr.h`).

## How to Run

Make sure you have GCC installed. Then compile and run the project using:

```cmd
gcc main.c tinyexpr.c functions.c -o main.exe
./main.exe
```

Or just run the **main.exe** if you have it.

