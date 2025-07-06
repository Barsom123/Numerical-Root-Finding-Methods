// functions.h

// get a number from user input
// if input is invalid, prompt user to enter again
// if input is valid, return the number
void get_number(char *str, double *var);

// bisection and false position method
void bisection_and_false_position(int BFSN, double error);

// take equation as input from user
// if the equation is invalid, return an error message
void get_equation(char *equation);

// get interval a and b from user input
// get the maximum number of iterations from user input
void get_a_b_maxiter(double *a, double *b, double *iterations);

void continue_prompt();

// check if expression uses variable x ,y or z
// if it does return 1 else return 0
int expression_uses_var(const char *expr, char var);

// evaluate expression using tinyexpr library
// if it fails return error code
double eval_expression(const char *expr, double x);

// get the derivative of the expression using finite difference method
double derivative(const char *expr, float x);



// newton raphson method
// takes in a pointer to the initial guess, number of iterations and the equation
// returns the root of the equation
// if the derivative is zero, return an error message
void Newton_Raphson_Method(double error);

// secant method
// take in two initial guesses, number of iterations and the equation
void Secant_Method(double error);

// check if the error is within the tolerance
// if it is, return 1 else return 0
int calculate_error(double xmold, double xm, double error, int i);

void calclate_mim_iter(double a, double b, double error);