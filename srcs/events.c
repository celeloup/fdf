#include "fdf.h"

int		key_press(int keycode, t_window *win)
{
	if (keycode == K_ESC)
		close_window(win);
	else if (keycode == K_NP_PLU)
		win->view.zoom += 1;
	else if (keycode == K_NP_MIN && win->view.zoom >= 1)
		win->view.zoom -= 1;
	else if (keycode == K_AR_R)
		win->view.origin_x += 5;
	else if (keycode == K_AR_L)
		win->view.origin_x -= 5;
	else if (keycode == K_AR_U)
		win->view.origin_y -= 5;
	else if (keycode == K_AR_D)
		win->view.origin_y += 5;
	else if (keycode == K_Q)
		win->view.altitude += 0.1;
	else if (keycode == K_A)
		win->view.altitude -= 0.1;
	else if (keycode == K_SP)
		win->view.projection = (win->view.projection == ISO) ? OBL : ISO;
	else if (keycode == K_C)
		switch_color(win);
	init_view(win, keycode);
	update_win(win, 0, 0);
	return (0);
}

int		close_window(t_window *win)
{
	free_map(win->map);
	mlx_destroy_image(win->mlx_ptr, win->img.img_ptr);
	exit(0);
	return (0);
}

int		mouse_press(int button, int x, int y, t_window *win)
{
	static int help;

	if (button == 1 && x <= 1172 && x >= 1147 && y >= 1150 && y <= 1175)
	{
		if (!help)
		{
			update_win(win, 1, 0);
			help = 1;
		}
		else
		{
			update_win(win, -1, 0);
			help = 0;
		}
	}
	if (button == 1 && x <= 1186 && x >= 1086 && y <= 75 && y >= 20)
	{
		if (win->view.is_color == 0)
			win->view.is_color = 1;
		else
			win->view.is_color = 0;
		update_win(win, 0, 0);
	}
	return (0);
}

int		mouse_move(int x, int y, t_window *win)
{
	static int hover;

	if (x <= 1172 && x >= 1147 && y >= 1150 && y <= 1175)
	{
		update_win(win, 0, 1);
		hover = 1;
	}
	else if (hover == 1)
	{
		update_win(win, 0, 0);
		hover = 0;
	}
	return (0);
}

void	hook_event(t_window *win)
{
	mlx_hook(win->win_ptr, 2, 0, key_press, win);
	mlx_hook(win->win_ptr, 17, (1L << 17), close_window, win);
	mlx_hook(win->win_ptr, 6, 0, mouse_move, win);
	mlx_hook(win->win_ptr, 4, 0, mouse_press, win);
}
