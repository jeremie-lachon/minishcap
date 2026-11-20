#include "minishell.h"
#include <unistd.h>

int	ms_pwd(t_execs *execs)
{
	static const char	err[] = "pwd: error retrieving current directory: "
		"getcwd: cannot access parent directories: "
		"No such file or directory\n";
	char				*pwd;

	arrayfree(&((t_execcmd *)execs->cmd)->args);
	((t_execcmd *)execs->cmd)->args = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (write(STDERR_FILENO, err, sizeof(err) - 1), 333);
	if (ms_write(1, "", 0))
		return (execfree(execs), 1);
	printf("%s\n", pwd);
	fflush(stdout);
	free(pwd);
	return (0);
}

// int main()
// {
//     char **cmd;
//     cmd = (char **)malloc(sizeof(char *) * 3);
//     cmd[0] = strdup("DUMDUM");
//     cmd[1] = strdup("PATH");
//     cmd[2] = NULL;
//     ms_pwd(cmd);
//     return (0);
// }