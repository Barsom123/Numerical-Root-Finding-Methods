// functions.c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <float.h>
#include "tinyexpr.h"
#include "functions.h"
#include <math.h>

void get_number(char *str, double *var)
{
    // Prompt the user for input until a valid number is entered
    int inputCheck = 0;
    // Loop until a valid number is entered
    // Use a do-while loop to ensure the prompt is displayed at least once
    do
    {
        // Print the prompt message
        printf("%s", str);
        // Read the input from the user
        // The inputCheck variable stores the return value of scanf
        // If scanf returns 1, it means a valid number was entered
        inputCheck = scanf("%lf", var);
        // Check if the input is valid
        // If inputCheck is not 1, it means the input was invalid
        if (inputCheck != 1)
        {
            // Clear the input buffer to remove any invalid characters
            // Use getchar() to read characters until a newline is encountered
            // This ensures that the input buffer is cleared before the next prompt
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter valid numbers.\n");
            // Set inputCheck to 0 to continue the loop
            // continue equal inputCheck = 0;
            continue;
        }
        break;
    } while (1);
}

void bisection_and_false_position(int BFSN, double error)
{
    // variables to store the function values at a and b
    double a, b, xm, fa, fb, fxm, max_iter, xmold;
    char equation[100];
    // Get the equation from the user
    get_equation(equation);
    // Get the initial guesses and number of iterations from the user
    get_a_b_maxiter(&a, &b, &max_iter);
    // calculate the minimum number of iterations required for the method to converge
    if (BFSN == 1)
        calclate_mim_iter(a, b, error);
    fa = eval_expression(equation, a);
    fb = eval_expression(equation, b);
    // Check if the function values at a and b are valid
    if (fa == 1 || fb == 1)
    {
        printf("Error compiling expression.\n");
        return;
    }
    // Check if the function values at a and b have the same sign
    // If they do, the method cannot be applied
    if (fa * fb > 0)
    {
        printf("f(a) = %.4f\t\tf(b) = %.4f\n", fa, fb);
        printf("f(a) and f(b) have the same sign\n");
        return;
    }
    // iterate for the maximum number of iterations
    for (int i = 0; i < (int)max_iter; i++)
    {
        if (BFSN == 2)
            xm = b - ((fb * (b - a)) / (fb - fa));
        else
            xm = (a + b) / 2;

        fxm = eval_expression(equation, xm);

        printf("\niteration (%d):\n", i + 1);
        printf("a = %.4f\t\tb = %.4f\t\txm = %.4f\n", a, b, xm);
        printf("f(%lf) = %.4f\t\tf(%lf) = %.4f\t\tf(%lf) = %.4f\n", a, fa, b, fb, xm, fxm);
        printf("------------------------------------------------------------------------------------------------------\n");
        if (fxm == 0.0)
        {
            printf("f(xm) = zero\n");
            break;
        }
        if (calculate_error(xmold, xm, error, i))
            return;
        // check sign of f(xm) and f(a)
        // if they have the same sign, set a = xm and f(a) = f(xm)
        if (fa * fxm > 0)
        {
            a = xm;
            fa = fxm;
        } // if they have different signs, set b = xm and f(b) = f(xm)
        else
        {
            b = xm;
            fb = fxm;
        }
        xmold = xm;
    }
}

void get_equation(char *equation)
{
    do
    {
        printf("Enter equation (use x): ");
        scanf("%s", equation);

        // Check if the equation contains any invalid characters
    } while (!expression_uses_var(equation, 'x') || expression_uses_var(equation, 'y') || expression_uses_var(equation, 'z'));
}

// check if expression uses variable x ,y or z
int expression_uses_var(const char *expr, char var)
{
    // Check if the expression contains the variable 'var'
    char pattern[2] = {var, '\0'};
    // strstr is used to find the first occurrence of the pattern in the expression
    // If found, it returns a pointer to the first occurrence, otherwise NULL
    return strstr(expr, pattern) != NULL;
}

void get_a_b_maxiter(double *a, double *b, double *iterations)
{
    /*
    this function gets the interval a and b from user input
    and the maximum number of iterations from user input
    it uses the get_number function to get the input from the user
    */
    get_number("Enter a: ", a);
    get_number("Enter b: ", b);
    get_number("Enter number of iterations: ", iterations);
}
void continue_prompt()
{
    printf("Press any key to continue...\n");
    // Wait for user input before continuing
    // use getchar() for Linux and MacOS operating systems
    // use getch() for Windows operating system
    char c = getch();
}

// evaluate expression using tinyexpr library
double eval_expression(const char *expr, double x)
{
    int error = 0;
    // Check if the expression contains the variable 'x'
    te_variable vars[] = {{"x", &x}};
    // compile the expression using tinyexpr
    // te_compile returns a pointer to the compiled expression
    // if it fails, it returns NULL
    // error is set to 1 if there is an error in the expression
    // if it fails, it returns NULL
    te_expr *n = te_compile(expr, vars, 1, &error);
    if (!error)
    {
        // evaluate the expression using tinyexpr
        double result = te_eval(n);
        // free the compiled expression using tinyexpr
        // te_free is used to free the memory allocated for the compiled expression
        te_free(n);
        return result;
    }
    else
    {
        printf("Error evaluating expression: %s at x = %0.4f\n", expr, x);
        return error;
    }
}

// get the derivative of the expression using finite difference method
// using the formula limit h-> 0  f'(x) = (f(x + h) - f(x)) / h
double derivative(const char *expr, float x)
{
    // Use a small value for h to approximate the derivative
    double h = DBL_EPSILON * 1000;
    return (eval_expression(expr, x + h) - eval_expression(expr, x)) / h;
}

void Newton_Raphson_Method(double error)
{
    double Xo, max_iter;
    char *equation;
    // Get the equation from the user
    get_equation(equation);
    get_number("Enter initial guess: ", &Xo);
    get_number("Enter number of iterations: ", &max_iter);

    for (int i = 0; i < max_iter; i++)
    {
        double derivativeValue = derivative(equation, Xo);
        double fx = eval_expression(equation, Xo);
        printf("Iteration %d: Xo = %.4f\n", i + 1, Xo);
        printf("f(%0.4lf)  = %.4f\n", Xo, fx);
        printf("f'(%0.4lf) = %.4f\n", Xo, derivativeValue);
        if (derivativeValue == 0)
        {
            printf("Derivative is zero. No solution found.\n");
            return;
        }
        if (calculate_error(Xo, (Xo - (fx / derivativeValue)), error, i))
            return;
        Xo = Xo - (fx / derivativeValue);
    }
    printf("Final root: x = %.4f\n", Xo);
}

void Secant_Method(double error)
{
    double a, b, max_iter;
    char *equation;
    get_equation(equation);
    get_a_b_maxiter(&a, &b, &max_iter);
    for (int i = 0; i < max_iter; i++)
    {
        double fx0 = eval_expression(equation, a);
        double fx1 = eval_expression(equation, b);
        if (fx1 - fx0 == 0)
        {
            printf("Division by zero. No solution found.\n");
            return;
        }
        double x2 = b - (fx1 * (b - a)) / (fx1 - fx0);
        printf("Iteration %d\n", i + 1);
        printf("x0 = %.4f\t\tx1 = %.4f\t\tx2 = %.4f\n", a, b, x2);
        printf("f(x0) = %.4f\t\tf(x1) = %.4f\t\tf(x2) = %.4f\n", fx0, fx1, eval_expression(equation, x2));
        printf("------------------------------------------------------------------------------------------------------\n");
        if (calculate_error(b, x2, error, i))
            return;
        if (eval_expression(equation, x2) == 0.0)
        {
            printf("Root found: x = %.4f\n", x2);
            return;
        }
        a = b;
        b = x2;
    }
}

int calculate_error(double xmold, double xm, double error, int i)
{
    if (error != -1.0 && i >= 1)
    {
        // Calculate the percentage error between previous and current function values
        double error2 = fabs((xm - xmold) / xm) * 100;
        printf("xmold = %.4f\t xm = %.4f\n", xmold, xm);
        printf("Error after iteration %d: %.4f%%\n", i + 1, error2);

        // If the error is smaller than the user-specified tolerance, break the loop
        if (error2 < error)
        {
            printf("Converged to desired error tolerance after %d iterations.\n", i + 1);
            return 1; // Set errorCheck to 1 to indicate convergence
        }
    }
    return 0; // Set errorCheck to 0 to indicate no convergence
}
void calclate_mim_iter(double a, double b, double error)
{
    double inputCheck = 0.0;
    get_number("if you want to calculate the minimum number of iterations, please enter 1 else enter any number: ", &inputCheck);
    if (inputCheck != 1.0)
        return;
    if (error == -1.0)
    {
        printf("Error tolerance not specified. Cannot calculate minimum iterations.\n");
        get_number("Please specify the error tolerance to calculate minimum iterations: ", &error);
        if (error == -1.0)
        {
            printf("Error tolerance not specified. Cannot calculate minimum iterations.\n");
            return;
        }
    }
    // Calculate the minimum number of iterations required for the method to converge
    double min_iter = log(b - a) - log(error);
    min_iter = ceil(min_iter / log(2)); // Round up to the nearest integer
    printf("Minimum number of iterations required: %.0f\n", min_iter);
}



