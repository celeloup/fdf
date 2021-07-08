#include "fdf.h"

void	help_button(int hover, t_window *win)
{
	t_point	*p;

	if (hover)
	{
		p = set_point(1147, 1150, 0);
		rectangle(p, 25, WHITE, win);
		free(p);
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1155, 1151, BLACK, "?");
	}
	else
	{
		p = set_point(1147, 1150, 0);
		rectangle(p, 25, BLACK, win);
		free(p);
		p = set_point(1147, 1150, 0);
		empty_rect(p, 25, 25, win);
		free(p);
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1155, 1151, WHITE, "?");
	}
}

void	help(int help_display, t_window *win)
{
	static int	help;
	t_point		*p;
	void		*mlx;
	void		*win_p;

	help += help_display;
	if (help)
	{
		mlx = win->mlx_ptr;
		win_p = win->win_ptr;
		p = set_point(30, 1110, 0);
		empty_rect(p, 1155, 75, win);
		free(p);
		mlx_string_put(mlx, win_p, 45, 1120, WHITE, "[^] UP   [<] LEFT");
		mlx_string_put(mlx, win_p, 305, 1120, WHITE,
			"[Q] + ALTITUDE   [+] ZOOM IN");
		mlx_string_put(mlx, win_p, 675, 1120, WHITE,
			"[SPACE] CHANGE PROJECTION");
		mlx_string_put(mlx, win_p, 1005, 1120, WHITE, "[C] COLOR");
		mlx_string_put(mlx, win_p, 45, 1150, WHITE, "[v] DOWN [>] RIGHT");
		mlx_string_put(mlx, win_p, 305, 1150, WHITE,
			"[A] - ALTITUDE   [-] ZOOM OUT");
		mlx_string_put(mlx, win_p, 675, 1150, WHITE, "[RETURN] RESET");
		mlx_string_put(mlx, win_p, 1005, 1150, WHITE, "[ESC] QUIT");
	}
}

void	draw_ui(t_window *win, int help_display, int hover)
{
	char *x;
	char *y;
	char *z;

	y = ft_itoa(win->view.origin_y - 500);
	x = ft_itoa(win->view.origin_x - 500);
	z = ft_itoa((int)(win->view.altitude * 10));
	mlx_string_put(win->mlx_ptr, win->win_ptr, 20, 20, WHITE, "FDF");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 70, 20, WHITE, win->filename);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 500, 20, WHITE, "x:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 525, 20, WHITE, x);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 585, 20, WHITE, "y:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 610, 20, WHITE, y);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 670, 20, WHITE, "z:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 695, 20, WHITE, z);
	mlx_string_put(win->mlx_ptr, win->win_ptr, 520, 45, WHITE, "projection:");
	mlx_string_put(win->mlx_ptr, win->win_ptr, 640, 45, WHITE,
		win->view.projection);
	free(x);
	free(y);
	free(z);
	help_button(hover, win);
	help(help_display, win);
	color_button(win->view.is_color, win);
}

void	color_button(int is_color, t_window *win)
{
	t_point *p;

	p = set_point(1080, 20, 0);
	empty_rect(p, 100, 35, win);
	free(p);
	if (is_color)
	{
		p = set_point(1087, 26, 0);
		rectangle(p, 23, WHITE, win);
		free(p);
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1119, 26, RED, "C");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1129, 26, YELLOW, "O");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1139, 26, GREEN, "L");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1149, 26, BLUE, "O");
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1159, 26, PURPLE, "R");
	}
	else
	{
		p = set_point(1150, 26, 0);
		rectangle(p, 23, WHITE, win);
		free(p);
		mlx_string_put(win->mlx_ptr, win->win_ptr, 1102, 26, WHITE, "B&W");
	}
}
