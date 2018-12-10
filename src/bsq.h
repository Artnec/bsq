#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_bsq
{
	int				h;
	int				l;
	int				max;
	int				lines_malloced;
	int				lines_count;
	int				line_len;
	char			empty;
	char			obstacle;
	char			full;
	char			**map;
}					t_bsq;

typedef struct		s_list
{
	char			*str;
	int				str_len;
	struct s_list	*next;
}					t_list;


int			read_map(t_bsq *bsq, int fd);
void		solve(t_bsq *bsq);

#endif
