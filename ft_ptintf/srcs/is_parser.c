/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:10:49 by mdeanne           #+#    #+#             */
/*   Updated: 2019/12/10 22:11:06 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

_Bool	is_signed(char c)
{
	if (c == 'd' || c == 'i' || c == 'f' || c == 'a' || c == 'A' ||
		c == 'e' || c == 'E' || c == 'F' || c == 'g' || c == 'G')
		return (1);
	return (0);
}

_Bool	is_typeflag(char c)
{
	if (is_csp(c) || is_ddioouuxx(c) || is_aaeeffgg(c))
		return (1);
	return (0);
}

_Bool	is_signflag(char c)
{
	if (c == '0' || c == '+' || c == '-' || c == '#' || c == ' ' || c == 'b')
		return (1);
	return (0);
}

_Bool	is_modifiers(char c)
{
	if (c == 'l' || c == 'h' || c == 'L')
		return (1);
	return (0);
}

_Bool	is_flag(char c)
{
	if (is_typeflag(c) || is_signflag(c) || ft_isdigit(c) ||
		c == '.' || is_modifiers(c))
		return (1);
	return (0);
}
