//
// Created by Mort Deanne on 2019-08-20.
//

#include "ft_ptintf.h"

void 	parsing_flags(char **format, t_prsng *tools)
{
	while (1)
	{
		if (**format == '-')
			tools->flags += M_MINUS;
		else if (**format == '+')
			tools->flags += M_PLUS;
		else if (**format == '#')
			tools->flags += M_SHARP;
		else if (**format == '0')
			tools->flags += M_ZERO;
		else
			break ;
		(*format)++;
	}
}

void	parsing_modifiers(char **format, t_prsng *tools)
{
	if (**format == 'h' && *(*format + 1) == 'h')
		tools->modifiers += M_HH;
	else if (**format == 'l' && *(*format + 1) == 'l')
		tools->modifiers += M_LL;
	else if (**format == 'h')
		tools->modifiers += M_H;
	else if (**format =='l')
		tools->modifiers += M_L;
	else if (**format == 'L')
		tools->modifiers += M_UPPER_L;

	if (*(*format + 1) == 'h' || *(*format + 1) == 'l')
		(*format) += 2;
	else
		(*format)++;
}

void 	parsing(char **format, t_prsng *tools)
{
	while (!is_typeflag(**format))
	{
		if (**format == '-' || **format == '+' || **format == '0' || **format == '#')
			parsing_flags(format, tools);
		else if (((**format >= '1' && **format <= '9') || **format == '*') && *(*format - 1) != '.')
		{
			if (**format == '*')
				tools->field = va_arg(tools->ap, int);
			else
				tools->field = ft_atoi(*format);
			while ((**format >= '1' && **format <= '9') || **format == '*')
				(*format)++;
		}
		else if (**format == '.')
		{
			(*format)++;
			if (**format == '*')
				tools->precision = va_arg(tools->ap, int);
			else
				tools->precision = ft_atoi(*format);
			while ((**format >= '1' && **format <= '9') || **format == '*')
				(*format)++;
		}
		else if (**format == 'l' || **format == 'h' || **format == 'L')
			parsing_modifiers(format, tools);
	}
	tools->type = **format;
	(*format)++;
}