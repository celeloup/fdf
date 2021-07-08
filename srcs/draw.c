#include "fdf.h"

void	put_pixel(int *str_img, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		str_img[y * WIN_WIDTH + x] = color;
}

void	draw_line(t_point p1, t_point p2, int color, t_window *win)
{
	int		swapped;
	int		dy;
	float	error;
	int		y;
	int		x;

	swapped = swap_point(&p1, &p2);
	dy = abs(p2.proj_y - p1.proj_y);
	error = 0;
	y = p1.proj_y;
	x = p1.proj_x;
	while (x <= p2.proj_x)
	{
		if (swapped)
			put_pixel(win->img.data, y, x, color);
		else
			put_pixel(win->img.data, x, y, color);
		error += dy * 2;
		if (error > (p2.proj_x - p1.proj_x))
		{
			y += ((p2.proj_y > p1.proj_y) ? 1 : -1);
			error -= (p2.proj_x - p1.proj_x) * 2;
		}
		x++;
	}
}

void	draw_map(t_window *win)
{
	t_map	*current;
	t_map	*nl_current;
	int		color;

	current = win->map;
	nl_current = current;
	color = (win->view.is_color) ? win->view.color : WHITE;
	while (nl_current->point->y == current->point->y)
		nl_current = nl_current->next;
	while (current->next != NULL)
	{
		if (current->point->y == current->next->point->y
			&& current->point->x < win->view.max_x)
			draw_line(*current->point, *current->next->point, color, win);
		if (nl_current != NULL)
		{
			if (nl_current->point->x < win->view.max_x
				&& current->point->x < win->view.max_x)
				draw_line(*current->point, *nl_current->point, color, win);
			nl_current = nl_current->next;
		}
		current = current->next;
	}
}

void	empty_rect(t_point *p, int lo, int la, t_window *win)
{
	int lon;
	int lar;
	int xi;
	int yi;

	lon = p->x + lo;
	lar = p->y + la;
	xi = p->x;
	yi = p->y;
	while (yi <= lar)
	{
		xi = p->x;
		while (xi <= lon)
		{
			if (yi == p->y || xi == p->x || xi == lon || yi == lar)
				mlx_pixel_put(win->mlx_ptr, win->win_ptr, xi, yi, WHITE);
			xi++;
		}
		yi++;
	}
}

void	rectangle(t_point *p, int size, int color, t_window *win)
{
	int lon;
	int lar;
	int xi;

	lon = p->x + size;
	lar = p->y + size;
	while (p->y <= lar)
	{
		xi = p->x;
		while (xi <= lon)
		{
			mlx_pixel_put(win->mlx_ptr, win->win_ptr, xi, p->y, color);
			xi++;
		}
		p->y++;
	}
}
