#include "bsq.h"

static	t_list	*new_list(int len)
{
	t_list	*lst = (t_list *)malloc(sizeof(t_list));

	lst->str = (char *)malloc(len);
	lst->str_len = 0;
	lst->next = NULL;
	return lst;
}

static	void	free_lists(t_list *lst)
{
	while (lst != NULL)
	{
		t_list	*tmp = lst;

		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
}

static int		save_map(t_bsq *bsq, t_list *map)
{
	bsq->map = (char **)malloc(sizeof(char *) * bsq->lines_count);
	int j = 0;
	bsq->lines_malloced = 0;
	for (int i = 0; i < bsq->lines_count; i++)
	{
		bsq->map[i] = (char *)malloc(bsq->line_len);
		bsq->lines_malloced++;
		int n;
		for (n = 0; n < bsq->line_len; n++)
		{
			if (j == map->str_len)
			{
				if (map->next == NULL || map->str_len == 0)
					return -1;
				j = 0;
				map = map->next;
			}
			bsq->map[i][n] = map->str[j++];
			if (!((bsq->map[i][n] == '\n' && n == bsq->line_len - 1)
				|| bsq->map[i][n] == bsq->empty
				|| bsq->map[i][n] == bsq->obstacle))
				return -1;
		}
		if (bsq->map[i][n - 1] != '\n')
			return -1;
	}
	return (j != map->str_len ? -1 : 0);
}

static	int		find_line_len(t_list *lst)
{
	int len = 0;
	while (lst != NULL)
	{
		int i = 0;
		while (i < lst->str_len)
		{
			if (lst->str[i++] == '\n')
				return i + len;
		}
		len += i;
		lst = lst->next;
	}
	return -1;
}

int		read_map(t_bsq *bsq, int fd)
{
	int		buf_size = 128;
	t_list	*map = new_list(buf_size);
	t_list	*map_head = map;

	int		bytes_read;
	while ((bytes_read = read(fd, map->str, buf_size)) > 0)
	{
		map->str_len = bytes_read;
		if (bytes_read == buf_size)
			buf_size *= 2;
		map->next = new_list(buf_size);
		map = map->next;
	}
	if ((bsq->line_len = find_line_len(map_head)) <= 0
	|| save_map(bsq, map_head) == -1)
	{
		free_lists(map_head);
		return -1;
	}
	free_lists(map_head);
	bsq->line_len--;
	return 0;
}
