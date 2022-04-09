# include "dynarray.h"

int	main(int ac, char **argv, char **envp);
char	*ft_get_dir(char *path);
char	*ft_make_prompt(char *dir);
int	init_dyn_env(char **envp, t_dynarray *darr);
void	ft_dyn_env(t_dynarray *darr);
int	ft_getenv_index(char **envp, uint64_t len, char *str);
int	ft_export(t_dynarray *darr, char *str);
int	ft_envcmp(char *str, char *str2);
int	ft_unset(t_dynarray *darr, char *str);
bool	ft_has_eq(char *str);
int	ft_cd(char *str);
int	ft_readline(t_dynarray *darr);
int	ft_check_bin_path(char *bin, char *paths);
