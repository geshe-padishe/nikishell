# include "dynarray.h"

typedef struct s_token
{
	int		id_token;
	int		is_redirection_input;
	int		is_redirection_output;
	int		is_here_doc;
	int		is_append_output;
	int		is_pipe;
	int		is_env_variable;
	int		is_cmd;
	int		is_arg;
	int		is_single_quoted;
	int		is_double_quoted;
	int		is_wrong;
	char	*elem;
}	t_token;

typedef struct s_split
{
	char	**split;
	int		i;
	int		j;
	char	quote;
	int		single_quote;
	int		double_quote;
	int		nb_split;
}	t_split;

typedef struct s_indexer
{
	int	*begin_word;
	int	*end_word;
	int	nb_word;
}	t_index;

/*
 *	ft_token.c
 */

t_token	*ft_token(t_split *split);

/*
 *	string_utils.c
 */

void	count_quotes(char *str, t_split *split);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		skip_space(char *str);

/*
 *	ft_quote.c
 */

void	to_quote_or_not_to_quote(char *str, int i, t_split *split);
int		is_quoted_good(char *str);

/*
 *	parser.c
 */

void	parse(char *line_buffer);

/*
 *	ft_memset.c
 */

void	ft_memset(void *s, int c, int n);

/*
 *	redo_split.c
 */

void	tab_init(int *tab, int len);
int		redo_split(char *str, t_split *split);

/*
 *	indexer.c
 */

t_index	*indexing(char *str, t_split *split);

/*
 *	ft_is.c
 */

void	which_is(t_token *token, int i);

/*
 *	unload.c
 */

void	unload(t_split *split, t_token *token);

/*
 *	convert_env_var.c
 */

void	convert_env_var(t_token *token, int i);

/*NIKI PROTOS*/

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
char	*ft_getenvval(char *str, char **envp, uint64_t len);
