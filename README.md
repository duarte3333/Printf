# Printf

## The goal of the project
I had to create my own version of the printf function in C. This project helped me understand how the printf function works and how to handle different format specifiers like %d for integers, %s for strings, and %f for floating-point numbers. I learned about variadic functions, string manipulation, and formatting rules. 

## Variadic functions (Funções variádicas)

A variadic function is a function that can accept a variable number of arguments.

**Procedure to use variadic functions in C:**

1. Include the **`<stdarg.h>`** header file, which provides the necessary macros and types for working with variadic functions.
2. Define your variadic function by specifying the variable argument list using an ellipsis (**`...`**) as the last parameter.
3. Inside the function, declare a **`va_list`** variable to hold the variable arguments.
4. Use the **`va_start`** macro to initialize the **`va_list`** variable, passing it the last named parameter of the function (before the ellipsis).
5. Access the variable arguments using the **`va_arg`** macro, specifying the **`va_list`** variable and the type of the argument you expect.
6. Process the variable arguments as needed.
7. Use the **`va_end`** macro to clean up the **`va_list`** variable before returning from the function.

**Example:**

```c
#include <stdio.h>
#include <stdarg.h>

void print_numbers(int fixed_int, double fixed_double, int count, ...)
{
		printf("Fixed int: %d\n", fixed_int);
	  printf("Fixed double: %lf\n", fixed_double);    
		
		va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        int num = va_arg(args, int);
        printf("%d ", num);
    }
    va_end(args);
    printf("\n");
}

int main()
{
    print_numbers(3, 10, 20, 30);  // Output: 10 20 30

    return 0;
}
```

### va_list()

Is a type defined in **`<stdarg.h>`**. It is a special type that **holds the information needed** to access the variable arguments in a variadic function. You declare variables of type **`va_list`** to work with the variable argument list.

### va_start()

Is a macro that **initializes a `va_list`** variable for accessing the variable arguments. It takes two arguments: the **`va_list`** variable and the last named parameter of the function (before the ellipsis). This macro must be called before accessing any variable arguments.

### va_arg()

Is a macro used to **retrieve the next argument from the variable argument list**. It takes two arguments: the **`va_list`** variable and the type of the argument you expect to retrieve. The macro returns the value of the argument and advances the **`va_list`** variable to the next argument.

### va_end()

Is a macro that performs the necessary **cleanup after using the variable arguments**. It takes one argument: the **`va_list`** variable. It must be called before the function returns to release any resources associated with the variable arguments.

### Specifiers in printf (just a few):

1. **`%d`** or **`%i`**: Prints an integer in signed decimal format.
2. **`%u`**: Prints an integer in unsigned decimal format.
3. **`%o`**: Prints an integer in octal format.
4. **`%x`** or **`%X`**: Prints an integer in hexadecimal format (lowercase or uppercase).
5. **`%f`** or **`%F`**: Prints a floating-point number in decimal notation.
6. **`%e`** or **`%E`**: Prints a floating-point number in scientific notation.
7. **`%g`** or **`%G`**: Prints a floating-point number in either decimal or scientific notation, depending on the value and precision.
8. **`%c`**: Prints a single character.
9. **`%s`**: Prints a null-terminated string of characters.
10. **`%%`**: Prints a literal '%' character.
11. **`%p`**: Prints a pointer address in hexadecimal format.
12. **`%n`**: Writes the number of characters printed so far into an integer variable passed as an argument.

### Printf (for exam):

```c
#include <stdarg.h> // For va_lis, va_start, va_arg, va_copy, va_end
#include <unistd.h> // For malloc, free, write

void	put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	put_digit(long long int nbr, int base, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		put_digit((nbr / base), base, len);
	*len += write(1, &hexa[nbr % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	agrs;

	len = 0;
	va_start(agrs, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == "s")
				put_str(va_arg(agrs, char *), &len);
			else if (*format == "d")
				put_digit(va_arg(agrs, int), 10, &len);
			else if (*format == "x")
				put_digit(va_arg(agrs, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (va_end(agrs), len);
}
```
