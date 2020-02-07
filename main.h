#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>

# define SUCCESS	0
# define FAILURE	-1
# define TRUE		1
# define FALSE		0

# define NB_STATE		4
# define NB_FLAG		6
# define NB_CONV		10
# define CHAR_FORMAT	'%'

# define F_HH			"hh"
# define F_LL			"ll"
# define F_H			"h"
# define F_L			"l"
# define F_HASH			"#"
# define F_ZERO			"0"

# define STR_CONV		"diouxXsc%f"

# define HH				0x000001
# define LL				0x000002
# define H				0x000004
# define L				0x000008
# define HASH			0x000010
# define ZERO			0x000020

# define D				0x000100
# define I				0x000200
# define O				0x000400
# define U				0x000800
# define X				0x001000
# define XMAJ			0x002000
# define S				0x004000
# define C				0x008000
# define PERCENT		0x010000
# define F				0x020000


enum	e_state
{
	LETTER,
	FLAG,
	CONV,
	ERROR
};

typedef struct s_state_machine
{
	enum e_state	state;	
	int				flag;
}				t_state_machine;

typedef	int	(*t_function)(char *, t_state_machine *);


#endif
