#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "parser.h"
# include "textures.h"
# include "../libft/libft.h"


void	cleanup(t_config *cfg);
void	free_2d_array(char **arr);
char	**ft_split_set(char const *s, char *seps);




#endif
