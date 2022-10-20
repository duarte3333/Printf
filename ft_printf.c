#include "libftprintf.h"

//Calcula o numero de algarismos num long unsigned int
int     ft_size_unsigned(long unsigned int nbr, int base_len)
{
    int         i;
    i = 0;
    if (nbr == 0)
        return (1);
    while (nbr > 0)
    {
        nbr /= base_len;
        i++;
    }
    return (i);
}

//Esta funcao transforma um int numa string do numero numa certa base
char	*ft_itoa_unsigned(long unsigned int nbr, int base_len, char *base)
{
    char            *str_nbr;
    int             size_str;

    size_str = ft_size_unsigned(nbr, base_len);
    str_nbr = (char *)malloc((size_str + 1) * sizeof(char));
    str_nbr[size_str] = 0;
    if (!str_nbr)
        return (NULL);
    if (nbr == 0)
        *str_nbr = '0';
    while (nbr > 0)
    {
        str_nbr[size_str - 1] = base[(nbr % base_len)];
        nbr /= base_len;
        size_str--;
    }
    return (str_nbr);
}
//Nao existe hexadecimais negativos

void	ft_char(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

//Se o input for um valor invalido, o printf dá print de null
void	ft_string(char *str, int *len)
{
	if (!str)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
        (*len)++;
	}
}

//Recebo o numero e passo para uma str hexadecimal
void	ft_pointer(long unsigned int number, int *len)
{
	char *p;
	if (number == 0)
	{
		write(1, "(nil)", 5);
		(*len)  += 5;
	}
	else 
	{
		write(1, "0x", 2);
		(*len) += 2;
		p = ft_itoa_unsigned(number, 16, "0123456789abcdef");
		ft_string(p, len);
		free(p);
	}
}

void    ft_integer(int nb, int *len)
{
	char *s;
	ft_putnbr_fd(nb, 1);
	s = ft_itoa(nb);
    (*len) += ft_strlen(s);
	free(s);

}

void    ft_unsigned_decimal(unsigned int nb, int *len)
{
    char *p;
	p = ft_itoa_unsigned(nb, 10, "0123456789");
	ft_string(p, len);
	free(p);
}

void    ft_hex_lower(unsigned int nb, int *len)
{
    char *p;
	p = ft_itoa_unsigned(nb, 16, "0123456789abcdef");
	ft_string(p, len);
	free(p);
}

void    ft_hex_upper(unsigned int nb, int *len)
{
    char *p;
	p = ft_itoa_unsigned(nb, 16,"0123456789ABCDEFG");
	ft_string(p, len);
	free(p);
}

void ft_percentage(int *len)
{
    write(1, "%%", 1);
    (*len)++;
}

void ft_printvariable(char variable, va_list args, int *size, int *i)
{
	if (variable == 'c')
		ft_char(va_arg(args, int), size);
	else if(variable == 's')
		ft_string(va_arg(args, char *), size);
	else if(variable == 'p')
		ft_pointer(va_arg(args, long unsigned int), size);
	else if(variable == 'd' || variable == 'i')
		ft_integer(va_arg(args, int), size);
	else if(variable == 'u')
	 	ft_unsigned_decimal(va_arg(args, long unsigned int), size);
	else if(variable == 'x')
		ft_hex_lower(va_arg(args, long unsigned int), size);
	else if(variable == 'X')
		ft_hex_upper(va_arg(args, long unsigned int), size);
	else if(variable == '%')
		ft_percentage(size);
    else
        (*i)--;
}

//Este funcao replica o comportamento do printf()
// va_list args; #Cria uma lista de argumentos
// #Declarar o proximo argumento em type, ex: va_arg(args, int); 
// #Cada vez que chamo o va_arg ele anda pa frente
int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			ft_printvariable(string[i], args, &len, &i);
			i++;
		}
		else
		{
			write(1, &string[i], 1);
			i++;
			len++;
		}
	}
	va_end(args);
	return (len);
}

// int main()
// {
// 	ft_printf("%d\n", 0);
//     printf("%d\n", 0);
// }