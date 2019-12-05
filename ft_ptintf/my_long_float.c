//
// Created by da.filiptsev on 04.12.2019.
//

#include "myfloat.h"
#include "high_precision.h"
#include "ft_ptintf.h"

static char	*initialize_ldbl(t_result *res, t_dbl_comp *ldblcomp, long double number, t_prsng *tools)
{
	uint64_t	*ldbl;

	ldbl = (uint64_t *)&number;
	ldblcomp->sign = get_lsign(ldbl);
	if ((ldblcomp->exp_val = get_lexp(ldbl)) == 0x7FFF)
	{
		if (!get_lmantissa(ldbl))
			return (print_inf(res, ldblcomp->sign, tools->type));
		return (print_nan(res, tools->type));
	}
	if (!ldblcomp->exp_val)
	{
		if (!get_lmantissa(ldbl))
			return (print_zero(res, tools));
		ldblcomp->exp_val = 1 - OFFSET_LDBL;
		ldblcomp->mant_val = get_lmantissa(ldbl);
	}
	else
	{
		ldblcomp->exp_val -= OFFSET_LDBL;
		ldblcomp->mant_val = get_lmantissa(ldbl);
	}
	ldblcomp->mant_High_Bits = ldblcomp->mant_val >> 32;
	ldblcomp->mant_Low_Bits = ldblcomp->mant_val & 0xFFFFFFFF;
	return (NULL);
}

static void	process(t_result *res, t_highl *hp, const t_dbl_comp *ldblcomp, t_prsng *tools)
{
	insert_low_lbits(hp, ldblcomp->mant_High_Bits, ldblcomp->exp_val + 1, 1);
	insert_low_lbits(hp, ldblcomp->mant_Low_Bits, ldblcomp->exp_val - 32 + 1, 1);
	fill_lresult(hp, 1, tools, res);
	if (*res->result)
		add_point(res, tools);
	insert_top_lbits(hp, ldblcomp->mant_High_Bits, 63 - ldblcomp->exp_val - 32, 0);
	insert_top_lbits(hp, ldblcomp->mant_Low_Bits, 63 - ldblcomp->exp_val, 0);
	res->bf_len = 0;
	fill_lresult(hp, 0, tools, res);
	if (tools->type == 'e' || tools->type == 'E')
		fill_exp_chars(res, tools->type);
}

char		*print_long_double(t_prsng *tools, t_mkfld *fld, long double number)
{
	t_dbl_comp	ldblcomp;
	t_highl		*hp;
	t_result	res;
	int 		precision;

	precision = tools->precision;
	res.len = -1;
	if ((res.result = initialize_ldbl(&res, &ldblcomp, number, tools)))
		return (res.result);
	if (!res.len)
		return (NULL);
	res.lg_10 = ft_floor(ft_log10(number));
	if (!(hp = hp_ldbl_initializ()))
		return (NULL);
	res = create_str(res.lg_10, tools, fld);
	if (!res.result)
		return (NULL);
	process(&res, hp, &ldblcomp, tools);
	check_result(&res, tools, precision);
	if (!res.len)
		return (NULL);
	free_l_hp(hp);
	return (res.result);
}
