#include "fdf.h"

void	parse_map(t_window *win, char *filename)
{
	t_map	*head;
	int		fd;

	head = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error file\n", 2);
		return ;
	}
	win->view.max_x = map(fd, &head);
	if (win->view.max_x == -1 || win->view.max_x <= 1)
	{
		free_map(head);
		ft_putstr_fd(ERROR_MAP, 2);
		return ;
	}
	win->map = head;
}

int		add_line_to_map(char **tab, t_map **head, int y)
{
	int		i;
	int		error;
	t_point	*p;

	error = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_strisdigit(tab[i]) == 0)
		{
			error = -1;
			break ;
		}
		p = set_point(i, y, ft_atoi(tab[i]));
		*head = add_point(*head, p);
		i++;
	}
	i = 0;
	while (tab[i])
		free(tab[i++]);
	if (error == -1)
		return (-1);
	else
		return (i);
}

int		map(int fd, t_map **head)
{
	char		*line;
	char		**tab;
	int			i;
	int			y;
	int			min;

	y = 0;
	min = 99999999;
	while (get_next_line(fd, &line) == 1)
	{
		tab = ft_split(line, ' ');
		free(line);
		i = add_line_to_map(tab, head, y);
		free(tab);
		if (i == -1)
			return (-1);
		if (i < min)
			min = i;
		y++;
	}
	if (y <= 1)
		return (-1);
	return (min);
}

void	free_map(t_map *map)
{
	t_map *next;

	while (map != NULL)
	{
		free(map->point);
		next = map->next;
		free(map);
		map = next;
	}
}

void	project(t_window *win)
{
	t_map *current;

	current = win->map;
	if (win->view.projection == ISO)
	{
		while (current != NULL)
		{
			iso(current->point, win->view);
			current = current->next;
		}
	}
	if (win->view.projection == OBL)
	{
		while (current != NULL)
		{
			obl(current->point, win->view);
			current = current->next;
		}
	}
}