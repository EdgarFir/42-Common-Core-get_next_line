#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

char	*get_next_line(int fd);

void swap_nl_for_dots(char *line)
{
	int i;
	if (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\n')
				line[i] = '.';
			i++;
		}
	}
}

int test_gnl(int fd, char *expected, int test_nbr, char *testing)
{
	char *s;
	int errors;

	errors = 0;
	if (testing)
		printf("Testing: %s\n", testing);
	printf("Test %i. -> ", test_nbr);
	s = get_next_line(fd);
	if (s && expected)
	{
		swap_nl_for_dots(s);
		if (strcmp(s, expected) == 0)
			printf("\033[0;32mOK!\033[0m ");
		else
		{
			printf("\033[0;31mKO!\033[0m ");
			errors++;
		}
	}
	else
	{
		if (expected == NULL)
			printf("\033[0;32mOK!\033[0m ");
		else
		{
			printf("\033[0;31mKO!\033[0m ");
			errors++;
		}
	}
	printf("\n-> Expected: %s\n-> Output:   %s\n\n", expected, s);
	free(s);
	return (errors);
}

int main()
{
	int fd;
	int errors = 0;
	
	printf("============ BUFFER_SIZE=%i ============\n\n", BUFFER_SIZE);

	printf("============ empty.txt ============\n");
	fd = open("empty.txt", O_RDONLY);
	errors += test_gnl(fd, NULL, 1, "Empty file.");
	errors += test_gnl(fd, NULL, 2, 0);
	printf("\n");
	close(fd);

	printf("============ onechar.txt ============\n");
	fd = open("onechar.txt", O_RDONLY);
	errors += test_gnl(fd, "a", 1, "One char no line.");
	errors += test_gnl(fd, NULL, 2, "End of file.");
	close(fd);

	printf("============ onlyline.txt ============\n");
	fd = open("onlyline.txt", O_RDONLY);
	errors += test_gnl(fd, "aaaaaaaaaaaaaa", 1, "One line.");
	errors += test_gnl(fd, NULL, 2, "End of file.");
	close(fd);

	printf("============ bigline.txt ============\n");
	fd = open("bigline.txt", O_RDONLY);
	errors += test_gnl(fd, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 1, "One big line.");
	errors += test_gnl(fd, NULL, 2, "End of file.");
	close(fd);

	printf("============ onlyNL.txt ============\n");
	fd = open("onlyNL.txt", O_RDONLY);
	errors += test_gnl(fd, ".", 1, "One new line.");
	errors += test_gnl(fd, NULL, 2, "End of file.");
	close(fd);

	printf("============ multipleNL.txt ============\n");
	printf("============ \\n\\ = '.' ============\n");
	fd = open("multipleNL.txt", O_RDONLY);
	errors += test_gnl(fd, ".", 1, "New line.");
	errors += test_gnl(fd, ".", 2, "Other new line.");
	errors += test_gnl(fd, ".", 3, "Other new line.");
	errors += test_gnl(fd, ".", 4, "Other new line.");
	errors += test_gnl(fd, ".", 5, "Other new line.");
	errors += test_gnl(fd, ".", 6, "Other new line.");
	errors += test_gnl(fd, ".", 7, "Other new line.");
	errors += test_gnl(fd, NULL, 8, "End of file.");
	close(fd);

	printf("============ bigNL.txt ============\n");
	printf("============ \\n\\ = '.' ============\n");
	fd = open("bigNL.txt", O_RDONLY);
	errors += test_gnl(fd, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.", 1, "One big new line.");
	errors += test_gnl(fd, NULL, 2, "End of file.");
	close(fd);

	printf("============ randomNL.txt ============\n");
	printf("============ \\n\\ = '.' ============\n");
	fd = open("randomNL.txt", O_RDONLY);
	errors += test_gnl(fd, "0123456789.", 1, "First random new line.");
	errors += test_gnl(fd, "012345678.", 2, "Other random new line.");
	errors += test_gnl(fd, "01234567.", 3, "Other random new line.");
	errors += test_gnl(fd, "0123456.", 4, "Other random new line.");
	errors += test_gnl(fd, "012345.", 5, "Other random new line.");
	errors += test_gnl(fd, "01234.", 6, "Other random new line.");
	errors += test_gnl(fd, "0123.", 7, "Other random new line.");
	errors += test_gnl(fd, "012.", 8, "Other random new line.");
	errors += test_gnl(fd, "01.", 9, "Other random new line.");
	errors += test_gnl(fd, "0.", 10, "Other random new line.");
	errors += test_gnl(fd, NULL, 11, "End of file.");
	close(fd);

	printf("============ giantline.txt ============\n");
	// Read file to expected
	fd = open("giantline.txt", O_RDONLY);
	char expected[20000 + 1] = {0};
	read(fd, expected, 20000);
	expected[20000] = '\0';
	close(fd);

	fd = open("giantline.txt", O_RDONLY);
	errors += test_gnl(fd, expected, 10, "Giant line.");
	errors += test_gnl(fd, NULL, 11, "End of file.");
	errors += test_gnl(fd, NULL, 11, "End of file.");
	close(fd);

	if (errors)
		printf("\033[0;31mSomething is wrong! Check test!\033[0m\n");
	else
		printf("\033[0;32mAll correct! Congratulations!\033[0m\n\n");
}