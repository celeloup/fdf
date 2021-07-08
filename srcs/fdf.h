#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/src/libft.h"
# include "key_linux.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# define WHITE 0xFFFFFF
# define RED 0xD62727
# define YELLOW 0xEAD725
# define GREEN 0x03BF23
# define BLUE 0x3A7ECC
# define PURPLE 0x925CC3
# define BLACK 0x000000

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200

# define ISO "ISO"
# define OBL "OBL"

# define PLUS 69
# define MINUS 78
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define Q 12
# define A 0
# define SPACE 49
# define ESC 53
# define RETURN 36
# define C 8

# define ERROR_MAP "Error : Bad map. Size min 2x2, only digits, no newline.\n"

typedef struct			s_img
{
	void				*img_ptr;
	int					*data;
	int					s_l;
	int					bpp;
	int					endian;
}						t_img;

typedef struct			s_view
{
	int					zoom;
	int					origin_x;
	int					origin_y;
	float				altitude;
	char				*projection;
	int					color;
	int					is_color;
	int					max_x;
}						t_view;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					proj_x;
	int					proj_y;
}						t_point;

typedef struct			s_map
{
	t_point				*point;
	struct s_map		*next;
}						t_map;

typedef struct			s_window
{
	char				*filename;
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_view				view;
	t_map				*map;
}						t_window;

void					init_win(t_window *win, char *filename);
void					init_view(t_window *win, int init);
void					update_win(t_window *win, int help, int hover);
void					switch_color(t_window *win);

int						map(int fd, t_map **head);
int						add_line_to_map(char **tab, t_map **head, int y);
void					free_map(t_map *map);
void					project(t_window *win);
void					parse_map(t_window *win, char *filename);

t_map					*add_point(t_map *head, t_point *p);
t_point					*set_point(int x, int y, int z);
int						swap_point(t_point *p1, t_point *p2);
void					iso(t_point *p, t_view view);
void					obl(t_point *p, t_view view);

void					put_pixel(int *str_img, int x, int y, int color);
void					draw_line(t_point p1, t_point p2, int color,
	t_window *win);
void					draw_map(t_window *win);
void					empty_rect(t_point *p, int lo, int la, t_window *win);
void					rectangle(t_point *p, int lo, int la, t_window *win);

void					draw_ui(t_window *win, int help_display, int hover);
void					help_button(int hover, t_window *win);
void					help(int help_display, t_window *win);
void					color_button(int is_color, t_window *win);

void					hook_event(t_window *win);
int						mouse_move(int x, int y, t_window *win);
int						mouse_press(int button, int x, int y, t_window *win);
int						key_press(int keycode, t_window *win);
int						close_window(t_window *win);

void	ft_putstr_fd(char const *s, int fd);
int		ft_strisdigit(char *str);

#endif