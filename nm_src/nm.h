/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 20:37:58 by bandre            #+#    #+#             */
/*   Updated: 2018/06/01 16:00:17 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "../libft/libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft_chained_list/libft_chained_list_src/libft_chained_list.h"

# include <ar.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <mach-o/ranlib.h>
# include <mach-o/fat.h>
# include <mach-o/arch.h>

typedef struct				s_mainstruct
{
	int						is_valid;
	char					*error;
	int						is_64;
	int						file_type;
	int						bit_order;
	int						file_length;
	char					*file;
	uint32_t				size_of_header;
	uint32_t				nb_command;
	char					*filename;
	char					*architecture;
}							t_mainstruct;

typedef struct				s_symbol
{
	char					*name;
	uint64_t				value;
	int						type;
	int						section;
}							t_symbol;

typedef struct				s_section
{
	char					*sect_name;
	char					*seg_name;
	int						num;
}							t_section;

typedef struct				s_search_section
{
	int						value;
	char					*type;
	t_libft_chained_list	**sections;
}							t_search_section;

typedef struct				s_search
{
	void					*searched;
	int						found;
}							t_search;

void						create_symbol_list(
	t_libft_chained_list **symbols,
	t_libft_chained_list **sections,
	t_mainstruct *file);
void						parse_arg(t_libft_chained_list **first,
	int argc, char **argv);
void						quit_clean(char *msg);
void						parse_header(t_mainstruct *file_struct);
uint32_t					r32(void *ptr, t_mainstruct *file);
uint64_t					reverse_64(void *ptr, t_mainstruct *file_struct);

void						show_symbols(t_libft_chained_list **symbols,
	t_libft_chained_list **sections, t_mainstruct *file_struct);
void						order_symbol(t_libft_chained_list **symbols);
void						get_type(t_mainstruct *file_struct);
void						fat(t_mainstruct *file_struct, char *file);

void						get_sections_32(
	t_libft_chained_list **sections,
	struct segment_command *lc,
	int *j,
	t_mainstruct *file_struct);
void						get_sections_64(
	t_libft_chained_list **sections,
	struct segment_command_64 *lc,
	int *j,
	t_mainstruct *file_struct);
t_mainstruct				*create_file(char *file);
uint64_t					reverse(void *ptr, t_mainstruct *file_struct);
void						archive(t_mainstruct *file_struct, char *file);
void						print_file(void *file_struct);
int							header_name(void *ptr, char **name);
void						initmainstruct(t_mainstruct *file);
void						order_files(t_libft_chained_list **files);
void						file_done(t_libft_chained_list *maillon,
	void *param);
void						find_symbol(
	t_libft_chained_list *maillon,
	void *params);
void						parse_file(t_mainstruct *file_struct, char *filename);
void						invalid_file(t_mainstruct *f);

#endif
