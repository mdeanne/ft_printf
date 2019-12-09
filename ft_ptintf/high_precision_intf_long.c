//
// Created by Yeste Lila on 2019-11-22.
//

#include "high_precision.h"
#include "ft_ptintf.h"

t_highl		*hp_ldbl_initializ(void)
{
	t_highl	*new;

	if (!(new = (t_highl *)malloc(sizeof(t_highl))))
		return (NULL);
	ft_memcpy(new, &(t_highl){{0}, {0}, 32, 1}, sizeof(*new));
	return (new);
}

_Bool		hp_is_lzero(t_highl *hp, _Bool intg)
{
	size_t i;

	i = 0;
	if (intg)
	{
		while (i < ARRSIZE_INTG_LDBL)
			if (hp->data_intg[i++] != 0)
				return (0);
	}
	else
		while (i < ARRSIZE_FRCT_LDBL)
			if (hp->data_frct[i++] != 0)
				return (0);
	return (1);
}

static void	fill_lresult_fract(t_highl *hp, _Bool intg, t_prsng *tools,
							t_result *res)
{
	char	rem_overf;
	int		nxt_nu;
	int		prec;

	ft_memcpy(&prec, &tools->precision, sizeof(int));
	if (!*res->result && (tools->type == 'e' || tools->type == 'E'))
		fill_fucking_l_e(res, tools, hp, &prec);
	while (prec > 0 && !hp_is_lzero(hp, intg))
	{
		rem_overf = mul_ret_loverflow(hp, 10) + '0';
		ft_strncat(res->result, &rem_overf, 1);
		++res->len;
		--prec;
	}
	if (prec <= 0 && (nxt_nu = mul_ret_loverflow(hp, 10)) >= 5)
		float_round(res, nxt_nu);
	else
		while (prec-- > 0)
		{
			ft_strncat(res->result, "0", 1);
			++res->len;
		}
}

static void	fill_lresult_intg(t_highl *hp, _Bool intg, t_result *res, char type)
{
	char	rem_overf;

	rem_overf = div_ret_lremainder(hp, 10) + '0';
	ft_strncat(res->buff, &rem_overf, 1);
	++res->bf_len;
	while (!hp_is_lzero(hp, intg))
	{
		rem_overf = div_ret_lremainder(hp, 10) + '0';
		ft_strncat(res->buff, &rem_overf, 1);
		++res->bf_len;
	}
	ft_reverse(res->buff);
	if ((type == 'e' || type == 'E') && (res->bf_len > 1 || *res->buff == '0'))
		check_e_intg_res(res);
	else
	{
		ft_strncpy(res->result, res->buff, res->bf_len);
		res->len = res->bf_len;
		clear_res_buff(res);
	}
}

void		fill_lresult(t_highl *hp, _Bool intg, t_prsng *tools, t_result *res)
{
	if (intg)
	{
		res->len = 0;
		res->bf_len = 0;
		fill_lresult_intg(hp, intg, res, tools->type);
	}
	else
	{
		if (res->buff)
		{
			while (++res->buff && *res->buff && tools->precision-- && ++res->bf_len)
			{
				ft_strncat(res->result, res->buff, 1);
				++res->len;
			}
			if (*res->buff && *res->buff >= '5')
				float_round(res, *res->buff - '0');
			else if (!*res->buff)
				fill_lresult_fract(hp, intg, tools, res);
			res->buff -= res->bf_len + 1;
			clear_res_buff(res);
		}
		else
			fill_lresult_fract(hp, intg, tools, res);
	}
}
