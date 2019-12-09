//
// Created by Yeste Lila on 2019-12-05.
//

#include "high_precision.h"

void		add_point(t_result *res, t_prsng *tools)
{
	if (tools->precision || tools->flags & M_PRECISION_NOT_ADDED ||
	tools->flags & M_SHARP)
	{
		ft_strncat(res->result, ".", 1);
		++res->len;
	}
}

char		*calculate_g_a_result(t_prsng *tools, t_mkfld *fld, int lg_10)
{
	char		*res;
	int			prec;

	if (ft_tolower(tools->type) == 'g')
	{
		if (!tools->precision && tools->flags & M_PRECISION_NOT_ADDED)
			tools->precision = 6;
		prec = (tools->precision) ? tools->precision : 1;
		if (!(res = get_g_result(tools, fld, lg_10)))
			return (NULL);
		if (tools->precision || tools->flags & M_PRECISION_NOT_ADDED ||
		tools->flags & M_SHARP)
			if (!(res = delete_lst_zeroes(res, fld, tools->type)))
				return (NULL);
		if (!(res = prepare_to_round(res, prec, fld, tools)))
			return (NULL);
	}
	return (res);
}
