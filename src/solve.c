#include "bsq.h"

#define MIN(a, b)	((a) < (b) ? (a) : (b))
#define MAX(a, b)	((a) > (b) ? (a) : (b))

static void		draw_bigest_square(t_bsq *bsq)
{
	for (int n = 0; n < bsq->max; n++)
	{
		for (int i = 0; i < bsq->max; i++)
			bsq->map[n + bsq->h][i + bsq->l] = bsq->full;
	}
}

static void		print_redrawn_map(t_bsq *bsq)
{
	for (int n = 0; n < bsq->lines_count; n++)
		write(1, bsq->map[n], bsq->line_len + 1);
}

static int		try_to_fit(t_bsq *bsq, int n, int i)
{
	int max = MIN(bsq->lines_count - n, bsq->line_len - i);
	for (int h = 0; h < max; h++)
	{
		for (int l = 0; l < max; l++)
		{
			if (bsq->map[n + h][i + l] == bsq->obstacle)
			{
				max = MAX(h, l);
				if (max <= bsq->max)
					return l;
			}
		}
	}
	if (max > bsq->max)
	{
		bsq->max = max;
		bsq->h = n;
		bsq->l = i;
	}
	return 0;
}

void	solve(t_bsq *bsq)
{
	bsq->h = 0;
	bsq->l = 0;
	bsq->max = 0;
	for (int n = 0; n < bsq->lines_count - bsq->max; n++)
	{
		for (int i = 0; i < bsq->line_len - bsq->max; i++)
		{
			if (bsq->map[n][i] == bsq->empty)
				i += try_to_fit(bsq, n, i);
		}
	}
	draw_bigest_square(bsq);
	print_redrawn_map(bsq);
}
