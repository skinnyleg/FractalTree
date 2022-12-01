#include "../includes/FractalTree.h"

void *mlx_ptr;
void *mlx_win;
char *get_addr;
int sl;
int bpp;
int end;
void *img;
int len = 50;

void	pixel_put(int x, int y)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		*((int *)&get_addr[(y * sl) + (x * bpp / 8)]) = 16711680;
	}
}
void	render_line(double beginx , double beginy, double endx, double endy)
{
	double	dx;
	double	dy;
	double	x_inc;
	double	y_inc;
	int		step;

	dx = (endx - beginx);
	dy = (endy - beginy);
	if (abs((int)dx) > abs((int)dy))
		step = abs((int)dx);
	else
		step = abs((int)dy);
	x_inc = (dx / (double)step);
	y_inc = (dy / (double)step);
	dx = round(beginx);
	dy = round(beginy);
	while (step != 0)
	{
		pixel_put(round(dx), round(dy));
		dx += x_inc;
		dy += y_inc;
		step--;
	}
}

int	ft_close()
{
	exit(0);
	return (0);
}

int	keypress(int keycode)
{
	if (keycode == 53)
		ft_close();
	if (keycode == 65307)
		ft_close();
	return 0;
}

double convert_rad(double degree)
{
	double rad = degree * (M_PI / 180);
	return rad;
}

void	ft_drawtree(double angle, double endx, double endy, int level)
{
	double	leftendx;
	double	leftendy;
	double	rightendx;
	double	rightendy;
	double	newbeginx;
	double	newbeginy;

	if (len < 0 || level == 0)
		return;
	newbeginx = endx;
	newbeginy = endy;
	leftendx = newbeginx - cos(angle) * len;
	leftendy = newbeginy - sin(angle) * len;
	render_line(newbeginx, newbeginy, leftendx, leftendy);
	rightendx = newbeginx + cos(-angle) * len;
	rightendy = newbeginy + sin(-angle) * len;
	render_line(newbeginx, newbeginy, rightendx, rightendy);
	// ft_drawtree(angle, leftendx, leftendy, level - 1);
	ft_drawtree(angle, rightendx, rightendy, level - 1);
}

int main()
{
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FractalTree");
	img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	get_addr = mlx_get_data_addr(img, &bpp, &sl, &end);
	if (get_addr == NULL)
		exit(1);
	double endx = (double)WIN_WIDTH / 2;
	double endy = (double)WIN_HEIGHT - (double)len;
	render_line((double)WIN_WIDTH / 2, WIN_HEIGHT, endx, endy);
	double angle = convert_rad(45);
	ft_drawtree(angle, endx, endy, 20);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img, 0, 0);
	mlx_hook(mlx_win, 17, 0, ft_close, NULL);
	mlx_hook(mlx_win, 2, (1L << 0), keypress, NULL);
	mlx_loop(mlx_ptr);
}
