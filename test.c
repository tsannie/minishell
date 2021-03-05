#include <unistd.h>
#include <fcntl.h>

void	create_file(char *namefile)
{
	int fd;

	if (namefile)
	{
		if ((fd = open(namefile, O_CREAT | O_WRONLY | O_APPEND, 00700)) == -1) // do directory
			return ;
		write(fd, printf("oh pire mange moi lpoireau"), 9);
		close(fd);
	}
}

int main()
{
	create_file("caca");
	return (23);
}
