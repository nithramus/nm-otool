#include "nm.h"

void	print_symbol(void *ptr, int symoff, int stroff, int nsyms)
{
	void *stringable = ptr + stroff;
	struct nlist_64 *array = ptr + symoff;
	int i = 0;
	short unsigned int yolo;
	// char test = (char)ptr;

	// ft_printf("%x\n", array[6].n_value);
	while (i < nsyms)
	{
		yolo = *(&array[i].n_value);
		ft_printf("%08hx\n", yolo);
		// ft_printf("%p\n",array[i].n_type);
		// print_memory((char*)&array[i].n_value, 16);
		// ft_putendl("");
		if (ft_strlen(stringable + array[i].n_un.n_strx) > 0)
		{
			// ft_printf("%x\n", array[i].n_value);
			if (array[i].n_type & N_SECT && (array[i].n_type - N_SECT) ==  N_EXT)
				ft_putstr("T ");
			else if (array[i].n_type & N_SECT)
				ft_putstr("t ");
			else if (array[i].n_type & N_EXT && (array[i].n_type - 1) == N_UNDF)
				ft_putstr("U ");
			ft_printf("%s\n", stringable + array[i].n_un.n_strx);
		}
		i++;
	}
}

void handle64(void *ptr)
{
	struct mach_header_64 header64;
	unsigned int nbcommands;
	unsigned int i;
	struct load_command *lc;
	struct symtab_command *symtab;

	i = 0;
	header64 = *(struct mach_header_64*)ptr;
	nbcommands = header64.ncmds;
	lc = (void*)(struct load_command*)ptr + sizeof(struct mach_header_64);
	while (i < nbcommands)
	{
		// ft_printf("cmd %d cmdsize: %d \n", lc->cmd, lc->cmdsize);
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command*)lc;
			// ft_printf("smtab size %d\n", symtab->cmdsize);
			// ft_printf("nsyms size %d\n", symtab->nsyms);
			// ft_printf("stroff  %s\n", ptr + symtab->stroff);
			// ft_printf("str size %d\n", symtab->strsize);
			print_symbol(ptr, symtab->symoff, symtab->stroff, symtab->nsyms);
			
			


			
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
}

int ft_nm(void *ptr)
{
	int magic_number;

	magic_number = *((int*)ptr);
	// ft_printf("%d %d\n", (unsigned int)magic_number, MH_MAGIC_64);
	if ((unsigned int)magic_number == MH_MAGIC_64)
		handle64(ptr);
	return 1;
}

int main(int argc, char **argv)
{
	int fd;
	struct stat buff;
	void *file;

	if (argc != 2)
	{
		ft_putendl("Envoie un nom de fichier gros");
		return EXIT_FAILURE;
	}
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
	{
		perror("open: ");
		return EXIT_FAILURE;
	}
	if (fstat(fd, &buff) < -1)
	{
		perror("fstat");
		return EXIT_FAILURE;
	}
	// ft_printf("%d\n", fd);
	// ft_printf("%d\n", buff.st_size);
	if (!(file = (char*)malloc(buff.st_size + 1)))
	{
		perror("malloc");
		return EXIT_FAILURE;
	}
	if (read(fd, file, buff.st_size) < buff.st_size)
	{
		perror("read");
		return EXIT_FAILURE;
	}
	ft_nm(file);
	return 1;

	
}