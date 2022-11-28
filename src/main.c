#include "../includes/FractalTree.h"

void *mlx_ptr;
void *mlx_win;
char *get_addr;
int sl;
int bpp;
int end;
void *img;
int len = 100;

void	pixel_put(int x, int y)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		*((int *)&get_addr[(y * sl) + (x * bpp / 8)]) = 16711680;
	}
}
void	render_line(double beginx , double beginy, double endx, double endy)
{
	int		dx;
	int		dy;
	double	ddx;
	double	ddy;
	double	x_inc;
	double	y_inc;
	int		step;

	dx = (endx - beginx);
	dy = (endy - beginy);
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	x_inc = ((double)dx / (double)step);
	y_inc = ((double)dy / (double)step);
	dx = round(beginx);
	dy = round(beginy);
	ddx = beginx;
	ddy = beginy;
	while (step != 0)
	{
		pixel_put(dx, dy);
		ddx += x_inc;
		ddy += y_inc;
		dx = round(ddx);
		dy = round(ddy);
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
	return 0;
}

double convert_rad(double degree)
{
	double rad = degree * (M_PI / 180);
	return rad;
}

void	ft_drawtree(double angle, double endx, double endy, int level)
{
	double tmpendx = endx;
	double tmpendy = endy;
	double tmpoldendx;
	double tmpoldendy;
	len -= 10;
	double newbeginx = endx;
	double newbeginy = endy;
	tmpoldendx = newbeginx - cos(angle) * len;
	tmpoldendy = newbeginy - sin(angle) * len;
	render_line(newbeginx, newbeginy, tmpoldendx, tmpoldendy);
	newbeginx = tmpendx;
	newbeginy = tmpendy;
	endx = newbeginx + cos(-angle) * len;
	endy = newbeginy + sin(-angle) * len;
	render_line(newbeginx, newbeginy, endx, endy);
	angle -= convert_rad(1.5);
	if (level == 0)
		return ;
	ft_drawtree(angle, tmpoldendx, tmpoldendy, level - 1);
	ft_drawtree(angle, endx, endy, level - 1);
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
	render_line(WIN_WIDTH / 2, WIN_HEIGHT, endx, endy);
	double angle = convert_rad(45);
	ft_drawtree(angle, endx, endy, 3);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img, 0, 0);
	mlx_hook(mlx_win, 17, 0, ft_close, NULL);
	mlx_hook(mlx_win, 2, (1L << 0), keypress, NULL);
	mlx_loop(mlx_ptr);
}