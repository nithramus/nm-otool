#ifndef NM
#define NM

#include "../libft/libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"
#include "../libft_chained_list/libft_chained_list_src/libft_chained_list.h"

#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct	s_mainstruct
{
	int			is_valid;
	char		*error;
	int			is_64;
	int			file_type;
	int			bit_order;
	int			file_length;
	char		*file;
	uint32_t	size_of_header;
	uint32_t	nb_command;
}				t_mainstruct;

typedef struct	s_symbol
{
	char		*name;
	uint64_t	value;
	int			type;
	int			segment;
}				t_symbol;

void			create_symbol_list(t_libft_chained_list **symbols, t_mainstruct *file);

#endif