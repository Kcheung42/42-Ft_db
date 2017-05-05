#include "ft_db.h"

/* create table roster.db(fname|char*,lname|char*,age|int) */
int handle_create_table(int argc, char **argv)
{

	FILE *fptr;
	char **array;
	char *header1;
	int len;
	int i;
	
	fptr = NULL;
	i = 1;
	header1 = "*,key|int";
	array = lsh_split_line(argv[2], ",()");
	len = argc_len(array);
	if (argc == 3 && !ft_strcmp(argv[1], "table"))
	{
		printf("creating table...\n");
		fptr = fopen(array[0], "w+");
		if (fptr == NULL)
		{
			printf("why\n");
			fclose(fptr);
			return (-1);
		}

		fprintf(fptr, "%s", header1);
		while (array[i] != '\0')
		{
			fprintf(fptr, "%s", ",");
			fputs(array[i], fptr);
			i++;
		}
		fprintf(fptr,"%s", "\n");
		fprintf(fptr, "%s", "**,");
		fprintf(fptr, "%d", len);
		fprintf(fptr,"%s","\n");
	}
	fclose(fptr);
	printf("table created!\n");
	return (1);
}
