#include "fdf.h"

void	init_view(t_window *win, int init)
{
	if (init == RETURN)
	{
		win->view.origin_x = 400;
		win->view.origin_y = 300;
		win->view.altitude = 0.2;
	}
}

void	update_win(t_window *win, int help, int hover)
{
	mlx_destroy_image(win->mlx_ptr, win->img.img_ptr);
	win->img.img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	win->img.data = (int*)mlx_get_data_addr(win->img.img_ptr, \
	&win->img.bpp, &win->img.s_l, &win->img.endian);
	project(win);
	draw_map(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	draw_ui(win, help, hover);
}

void	switch_color(t_window *win)
{
	if (win->view.is_color == 0)
		win->view.is_color = 1;
	else
	{
		if (win->view.color == RED)
			win->view.color = YELLOW;
		else if (win->view.color == YELLOW)
			win->view.color = GREEN;
		else if (win->view.color == GREEN)
			win->view.color = BLUE;
		else if (win->view.color == BLUE)
			win->view.color = PURPLE;
		else if (win->view.color == PURPLE)
			win->view.color = RED;
	}
}

void	init_win(t_window *win, char *filename)
{
	parse_map(win, filename);
	if (win->map == NULL)
		return ;
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fdf");
	win->img.img_ptr = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	win->img.data = (int*)mlx_get_data_addr(win->img.img_ptr, &win->img.bpp, \
	&win->img.s_l, &win->img.endian);
	win->view.projection = ISO;
	init_view(win, RETURN);
	win->view.zoom = 20;
	win->view.color = RED;
	win->view.is_color = 0;
	win->filename = filename;
}


int		main(int argc, char **argv)
{
	t_window	win;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./fdf [file]\n", 2);
		return (1);
	}
	init_win(&win, argv[1]);
	if (win.map == NULL)
		return (1);
	project(&win);
	draw_map(&win);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img.img_ptr, 0, 0);
	draw_ui(&win, 0, 0);
	// hook_event(&win);
	mlx_hook(win.win_ptr, 2, (1L << 0), key_press, &win);
	mlx_hook(win.win_ptr, 17, (1L << 17), close_window, &win);
	mlx_loop(win.mlx_ptr);
	return (0);
}