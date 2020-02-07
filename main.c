#include "main.h"

int		ft_strnequ(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}


void	print_bin(int nb)
{
	int	i;

	i = 0;
	printf("flag : [");
	while (i < 32)
	{
		if (i != 0 && i % 8 == 0)
			printf(".");
		if (nb & (1 << (31 - i)))
			printf("1");
		else
			printf("0");
		i++;
	}
	printf("]\n");
}



////////////////////////////////////////////////////

int	error(char *format, t_state_machine *machine)
{
	printf("[%c] -> ERROR\n", *format);
	machine->state = LETTER;
	machine->flag = 0;
	print_bin(machine->flag);
	return (1);
}

int	conv(char *format, t_state_machine *machine)
{
	static char	str_conv[NB_CONV] = STR_CONV;
	int			i;

	i = 0;
	while (i < NB_CONV)
	{
		if (*format == str_conv[i])
		{
			machine->flag |= (1 << i) << 8;
			printf("[%c] -> CONV\n", str_conv[i]);
			machine->state = LETTER;
			print_bin(machine->flag);
			machine->flag = 0;
			return (1);
		}
		i++;
	}
	machine->state = ERROR;
	return (0);
}


int	flag(char *format, t_state_machine *machine)
{
	static char	*str_flag[NB_FLAG] = {F_HH, F_LL, F_H, F_L, F_HASH, F_ZERO};
	int			len;
	int			i;

	i = 0;
	while (i < NB_FLAG)
	{
		len = (i < 2) ? 2 : 1;
		if (ft_strnequ(format, str_flag[i], len) == TRUE)
		{
			printf("[%s] -> FLAG\n", str_flag[i]);
			machine->flag |= (1 << i);
			return (len);
		}
		i++;
	}
	machine->state = CONV;
	return (0);
}

int	letter(char *format, t_state_machine *machine)
{
	if (*format == CHAR_FORMAT)
		machine->state = FLAG;
	else
		printf("[%c] -> LETTER\n", *format);
	return (1);
}

int	parser(char *format)
{
	t_state_machine		machine;
	static t_function	func[NB_STATE] = {letter, flag, conv, error};
	int					ret;

	machine.state = LETTER;	
	machine.flag = 0;
	while (*format != '\0')
	{
		ret = func[machine.state](format, &machine);
		if (ret == FAILURE)
			return (FAILURE);
		format += ret;
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac != 2 || parser(av[1]) == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
