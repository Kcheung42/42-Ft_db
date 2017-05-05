/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:46:48 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/04 11:57:59 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* DELETE SQL Command*/

int		delete_record(int fd, char *key)
{
	int		ret;
	char	*line;
	char	**array;
	int		delete_bytes;
	off_t	pos;
	
	pos = lseek(fd, 0, SEEK_SET);								//resets the fd position
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		delete_bytes = ft_strlen(line);
		array = lsh_split_line(line, ",");
		if (ret == 0)
			return (ret);
		else if (!ft_strcmp(key, array[0]))
		{
			printf("deleting...\n");
			pos = lseek(fd, 0, SEEK_CUR);
			pos = lseek(fd, pos - delete_bytes - 1, SEEK_SET);
			printf("deleting [%d] bytes\n", delete_bytes);
			ft_bzero(line, delete_bytes);
			ret = write(fd, &line, delete_bytes);
			return (ret);
		}
		pos = lseek(fd, 0, SEEK_CUR);
	}
	printf("record not found\n");
	return (ret);
}

void	delete_records(int fd, int *row_list)
{
	char		*line;
	int			curr_row;
	off_t		pos;
	int			delete_bytes;

	curr_row = 0;
	while (*row_list)
	{
		lseek(fd, 0, SEEK_SET);
		curr_row = 0;
		while (curr_row != *row_list && (get_next_line(fd, &line)) != -1)
		{
			delete_bytes = ft_strlen(line);
			curr_row++;
		}
		if (curr_row == *row_list)
		{
			printf("deleting...\n");
			pos = lseek(fd, 0, SEEK_CUR);
			pos = lseek(fd, pos - delete_bytes - 1, SEEK_SET);
			printf("deleting [%d] bytes\n", delete_bytes);
			ft_bzero(line, delete_bytes);
			write(fd, &line, delete_bytes);
		}
		free(line);
		row_list++;
	}
}

int		handle_delete(int argc, char **argv)
{
	int		fd;
	char	*constraint;
	t_table	*table;
	int		*row_list;
	char	**col_list;
	/* t_table	*table; */

	col_list = NULL;
	constraint = get_constraint(argv);
	if (argc > 3 && !ft_strcmp(argv[1], "from"))
	{
		if((fd = open_record_delete(argv[2])) == -1)
			return (0);
		table = build_table(fd);
		row_list = select_record(col_list, table, constraint);
		delete_records(fd, row_list);
		close_record(fd);
		return (1);
	}
	return (0);
}
