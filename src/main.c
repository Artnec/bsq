#include "bsq.h"

static void		free_map(t_bsq *bsq)
{
	for (int i = 0; i < bsq->lines_malloced; i++)
		free(bsq->map[i]);
	free(bsq->map);
}

static int		read_initial_line(t_bsq *bsq, int fd)
{
	char	c;

	bsq->lines_count = 0;
	while (read(fd, &c, 1) == 1 && c >= '0' && c <= '9')
		bsq->lines_count = bsq->lines_count * 10 + c - '0';

	if (bsq->lines_count == 0 || (bsq->empty = c) == '\n'
	|| read(fd, &bsq->obstacle, 1) < 1 || bsq->obstacle == '\n'
	|| read(fd, &bsq->full, 1) < 1 || bsq->full == '\n'
	|| read(fd, &c, 1) < 1 || c != '\n')
		return -1;

	if (bsq->empty == bsq->obstacle || bsq->empty == bsq->full
	|| bsq->full == bsq->obstacle)
		return -1;
	return 0;
}

static int		read_data_and_solve(int fd)
{
	t_bsq	bsq;

	if (read_initial_line(&bsq, fd) == -1)
		return -1;
	if (read_map(&bsq, fd) == -1)
	{
		free_map(&bsq);
		return -1;
	}
	solve(&bsq);
	free_map(&bsq);
	return 0;
}

int		main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (read_data_and_solve(0) == -1)
			write(2, "error\n", 6);
	}
	else
	{
		int fd;
		int i = 1;
		while (i < argc)
		{
			if ((fd = open(argv[i++], O_RDONLY)) == -1 || read_data_and_solve(fd) == -1)
				write(2, "error\n", 6);
			if (i < argc)
				write(1, "\n", 1);
		}
	}
	return 0;
}
