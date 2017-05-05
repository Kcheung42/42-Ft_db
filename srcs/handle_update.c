/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:44:01 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/04 14:13:56 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* UPDATE SQL Command*/

char	*get_constraint(char **argv)
{
	int i;
	char	*constraint;
	
	i = 0;
	constraint = NULL;
	while (argv[i] && ft_strcmp(argv[i], "where"))
		i++;
	if (!argv[i])
		return (constraint);
	i++;
	if (argv[i])
		constraint = argv[i];
	return (constraint);
}

char	*get_set(char **argv)
{
	int i;
	char	*constraint;
	
	i = 0;
	constraint = NULL;
	while (argv[i] && ft_strcmp(argv[i], "set"))
		i++;
	i++;
	if (argv[i])
		constraint = argv[i];
	return (constraint);
}

void	update_fields(t_fields *rec, char **set_array, char **line, t_table table)
{
	t_fields	*iter_f;
	t_col		*iter_c;
	int			i;

	iter_c = table.header;
	iter_f = rec;
	i = 0;
	while (iter_f)
	{
		if (!strcmp(set_array[0], iter_f->header_name))
			iter_f->value = set_array[1];
		else
			iter_f->value = strdup(line[i]);
		if (!ft_strcmp(iter_c->type, "int") && (!atoi(iter_f->value) && ft_strcmp(iter_f->value, "0")))
		{
			printf("Invalid type for (%s). Need (%s)\n", iter_c->name, iter_c->type);
			exit(-1);
		}
		i++;
		iter_c = iter_c->next;
		iter_f = iter_f->next;
	}
	(void)table;
}

int		update_insert_record(int fd, t_fields *record)
{
	int			ret;
	t_fields	*iter_f;

	iter_f = record;
	ret = 0;
	printf("inserting...\n");
	while (iter_f)
	{
		ret += write(fd, iter_f->value, ft_strlen(iter_f->value));
		if (iter_f->next != NULL)
			ret += write(fd, ",", 1);
		iter_f = iter_f->next;
	}
	ret += write(fd, "\n", 1); 
	free(record);
	return (ret);
}

void	set_print_record(int fd, int fd_a, int *row_list, t_table table, char *set_constraint)
{
	char 	*line;
	int		curr_row;
	int		i;
	char	**array;
	char 	**set_array;
	int		*colist_index;
	t_fields	*rec_t;
	off_t		pos;
	int			delete_bytes;

	rec_t = NULL;
	colist_index = NULL;
	curr_row = 0;
	i = 0;
	set_array = lsh_split_line(set_constraint, "=");
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
			printf("Updating record\n");
			array = lsh_split_line(line, ",");
			rec_t = build_record(table);
			update_fields(rec_t, set_array, array, table);
			pos = lseek(fd, 0, SEEK_CUR);
			pos = lseek(fd, pos - delete_bytes - 1, SEEK_SET);
			ft_bzero(line, delete_bytes);
			write(fd, &line, delete_bytes);
			update_insert_record(fd_a, rec_t);
		}
		free(line);
		row_list++;
	}
}

/* update roster.db set fname=potato where fname=kim */
int		handle_set(int argc, char **argv)
{
	int			fd;
	int 		fd_a;
	t_table		*table;
	char		*file;
	char		**col_list;
	char		*constraint;
	char 		*set_constraint;
	int			*row_list;

	file = scan_for_file("update", argv);
	col_list = (char **)malloc(sizeof(char *) * 2);
	col_list[0] = "*";
	col_list[1] = NULL;
	constraint = get_constraint(argv);
	set_constraint = argv[3];
	if (argc >= 6 && file)
	{
		if((fd = open_record_delete(file)) == -1)
			return (0);
		if((fd_a = open_record(file)) == -1)
			return (0);
		table = build_table(fd);
		row_list = select_record(col_list, table, constraint);
		constraint = get_constraint(argv);
		set_print_record(fd, fd_a, row_list, *table, set_constraint);
		close_record(fd);
	}
	return (1);
}
