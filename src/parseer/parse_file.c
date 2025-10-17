#include "ft_minirt.h"
#include <fcntl.h>

static char	**get_all_lines(int fd)
{
	int		size;
	char	*line;
	char	**content;
	char	**tmp;

	content = NULL;
	line = get_next_line(fd);
	size = 0;
	while (line)
	{
		tmp = emalloc(sizeof(char *) * (size + 2));
		if (content && size)
			ft_memcpy(tmp, content, sizeof(char *) * size);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		tmp[size] = line;
		tmp[size + 1] = NULL;
		ft_free(content);
		content = tmp;
		size++;
		line = get_next_line(fd);
	}
	content[size] = NULL;
	return (content);
}

static char	**get_file_lines(const char *path)
{
	int		fd;
	char	**lines;

	if (!ends_with_rt(path))
		die("scene must end with .rt");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die("cannot open scene file");
	lines = get_all_lines(fd);
	close(fd);
	return (lines);
}

int	parse_file(const char *path, t_scene *sc)
{
	char	**lines;
	int		i;

	i = 0;
	lines = get_file_lines(path);
	while (lines[i])
	{
		if (!parse_file_line(lines[i], sc))
			die("invalid line in scene");
		ft_free(lines[i]);
		i++;
	}
	ft_free(lines);
	return (1);
}
