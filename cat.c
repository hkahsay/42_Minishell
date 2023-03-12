
#include <libft.h>

static void	read_file(const char *path)
{
	t_file	*f;
	int		c;

	if ((f = ft_fopen(path, "r")))
	{
		while ((c = ft_fgetc(f)) != FT_EOF)
			ft_putchar(c);
		if (ft_ferror(f))
			ft_putendl_fd("error: Could not read file!", 2);
		ft_fclose(f);
	}
	else
		ft_putendl_fd("error: Could not open file!", 2);
}

int			main(int ac, char **av)
{
	int i;

	i = 0;
	while (++i < ac)
		read_file(av[i]);
	return (0);
}
