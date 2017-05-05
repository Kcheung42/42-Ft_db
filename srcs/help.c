#include "../includes/ft_db.h"

int handle_help(int argc, char **argv)
{
	int		fd;
	char 	*line;
	char	**array;

	if (argc == 1)
	{
		if(!strcmp(argv[0], "help"))
		{
			printf("\n");
			ft_printf(" \x1B[31m(              (                 \n )\\ )     (     )\\ )           )  \n(()/(   ( )\\   (()/(   (    ( /(  \n \x1B[33m/(_))  )((_)   /(_))  )\\   )\\()) \n(_))   ((_)_   (_))   ((_) (_))/  \n\x1B[37m/ __|   / _ \\  | |     (_) | |_   \n\\__ \\  | (_) | | |__   | | |  _|  \n|___/   \\__\\_\\ |____|  |_|  \\__| \n\n");
			printf("\x1B[37mUse any of the following commands for help:\nhelp (file_name) | help create |  help insert | help select | help update | help delete\n\n");
		}
	}
	else if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY, 444)))
		{
			get_next_line(fd, &line);
			array = lsh_split_line(line, ",");
			array += 2;
			printf("Column_namep\x1B[32m|\x1B[37mType):\n");
			while (*array)
			{
				printf("(*%s) ", *array);
				array++;
			}
			printf("\n");
			close(fd);
		}
		if (!strcmp(argv[1], "insert"))
		{
			printf("\n");
			printf("Inserting a record:\n");
			printf("insert into (filename) values(fname,lname,age,course_id)\n\n");
		}
		if (!strcmp(argv[1], "select"))
		{
			printf("\n");
			printf("Selecting a record to print:\n");
			printf("select * from (filename)\n");
			printf("select (col_name) (col_name) from (filename)\n");
			printf("select * from (filename) where (col_name)=(value)\n");
			printf("Allowed =,>,<,<=,>=,<>\n\n");
		}
		if (!strcmp(argv[1], "update"))
		{
			printf("\n");
			printf("Update a field in a record:\n");
			printf("update (filename) set (column)=[changed value] where (column)=[current value]\n");
			printf("Allowed =,>,<,<=,>=,<>\n\n");
		}
		if (!strcmp(argv[1], "delete"))
		{
			printf("\n");
			printf("\x1B[34m  .-')       .-')                      .-') _    \n ( OO ).   .(  OO)                    (  OO) )   \n(_)\x1B[37m---\x1B[34m\\_) (_)\x1B[37m---\x1B[34m\\_)  \x1B[37m,--.      \x1B[37m,-.-\x1B[34m') /     '._  \n\x1B[37m/    _ |  '  .-.  '  |  |\x1B[34m.-')  \x1B[37m|  |\x1B[34mOO)\x1B[37m|'--...__\x1B[34m) \x1B[37m\n\\  :` \x1B[34m`. \x1B[34m,\x1B[37m|  | |  |  |  |\x1B[34m OO ) \x1B[37m|  |  \x1B[34m\\\x1B[37m'--.  .--' \n '..`''.\x1B[34m|_\x1B[37m|  | |  |  |  |\x1B[34m`-' | \x1B[37m|  |\x1B[34m(_/   \x1B[37m|  |    \n\x1B[37m.-._)   \\ |  | |  | \x1B[34m(\x1B[37m|  \x1B[37m'---.\x1B[34m',\x1B[37m|  |\x1B[34m_.'   \x1B[37m|  |    \n\\       / '  '-'  '-.|      |\x1B[34m(_\x1B[37m|  |      |  |    \n `-----'   `-----'--'`------'  `--'      `--'   \n");
			printf("Deleting a record:\n");
			printf("delete from (filename) where (col_name)=(value)\n");
			printf("Allowed =,>,<,<=,>=,<>\n\n");
		}
		if (!strcmp(argv[1], "create"))
		{
			printf("Creating a table:\n");
			printf("create table [filename]([column name]|[type],[column name]|[type],etc...)\n\n");
		}
	}
	return (1);
}
