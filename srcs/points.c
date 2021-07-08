#include "fdf.h"

t_map		*add_point(t_map *head, t_point *p)
{
	t_map	*current;

	if ((current = (t_map*)malloc(sizeof(t_map))) == NULL)
		return (NULL);
	current->point = p;
	current->next = head;
	return (current);
}

t_point		*set_point(int x, int y, int z)
{
	t_point *p;

	if ((p = (t_point*)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

int			swap_point(t_point *p1, t_point *p2)
{
	int swapped;

	swapped = 0;
	if (abs(p1->proj_x - p2->proj_x) < abs(p1->proj_y - p2->proj_y))
	{
		ft_swap(&p1->proj_x, &p1->proj_y);
		ft_swap(&p2->proj_x, &p2->proj_y);
		swapped = 1;
	}
	if (p1->proj_x > p2->proj_x)
	{
		ft_swap(&p1->proj_x, &p2->proj_x);
		ft_swap(&p1->proj_y, &p2->proj_y);
	}
	return (swapped);
}

void		iso(t_point *p, t_view view)
{
	p->proj_x = ((p->x - p->y) * cos(0.523599))
		* view.zoom + view.origin_x;
	p->proj_y = ((p->x + p->y) * sin(0.523599) - p->z
	* view.altitude) * view.zoom + view.origin_y;
}

void		obl(t_point *p, t_view view)
{
	p->proj_x = (p->x + 0.5 * (p->z * view.altitude)
		* cos(1.099557)) * view.zoom + view.origin_x;
	p->proj_y = (p->y + 0.5 * (p->z * view.altitude)
		* sin(1.099557)) * view.zoom + view.origin_y;
}
