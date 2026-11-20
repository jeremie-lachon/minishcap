NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -g3
#CFLAGS = -g3
INC = -I. 

DIR_BUILT = builtin/

DIR_LIB = lib/

DIR_PARSE = parsing/

DIR_ARG = argument/

DIR_EXEC = exec/

SRC_BUILT = ms_cd.c ms_cd2.c ms_echo.c ms_env.c ms_export.c ms_pwd.c ms_unset.c ms_exit.c builtin.c

SRC_LIB = ms_atoi.c ms_split.c ms_strdup.c ms_strncmp.c ms_strtrim.c \
	ms_substr.c libft.c misc.c moded_libft.c ms_strcat.c ms_strcmp.c \
	ms_substr.c signal.c ms_write.c ms_isalphanum.c libft2.c misc2.c

SRC_PARSE = ms_free.c lexing_check.c tools_heredoc.c parse_redirs.c \
	ms_memory.c ms_free2.c init_structs.c \
	tools_parsing.c parsing_heredoc.c lexer.c init_redirs_er.c \
	parsing_exec.c sub_lexer.c quotes.c \
	init_redirs.c ms_parsing.c tools_node.c tokens.c \
	ms_memory2.c lexer_checks.c misc.c line_savers.c\

SRC_ARG = argument.c expansion.c filelist.c files.c  listfuncs.c listprinters.c \
	structs.c substitution.c terminalstage.c wildcard.c heredocarg.c dollar.c dollarhere.c \
	structsfree.c subquote.c

SRC_EXEC = cmd.c execfree.c ms_pathsplit.c heredoc.c path.c pipe.c redir.c subandor.c fds.c mainexec.c \
	execfreeer.c dollarhere.c execfreeer.c

SRC_MAIN = main.c printer.c

SRC_TEST = test.c

OBJ_BUILT = $(addprefix $(DIR_BUILT), $(SRC_BUILT:.c=.o))

OBJ_LIB = $(addprefix $(DIR_LIB), $(SRC_LIB:.c=.o))

OBJ_PARSE = $(addprefix $(DIR_PARSE), $(SRC_PARSE:.c=.o))

OBJ_ARG = $(addprefix $(DIR_ARG), $(SRC_ARG:.c=.o))

OBJ_EXEC = $(addprefix $(DIR_EXEC), $(SRC_EXEC:.c=.o))

OBJ_MAIN = $(SRC_MAIN:.c=.o)

OBJ_TEST = $(SRC_TEST:.c=.o)

OBJ_ALL = $(OBJ_BUILT) $(OBJ_ARG) $(OBJ_LIB) $(OBJ_PARSE) $(OBJ_EXEC) $(OBJ_MAIN)

OBJ_TESTER = $(OBJ_BUILT) $(OBJ_ARG) $(OBJ_LIB) $(OBJ_PARSE) $(OBJ_EXEC) $(OBJ_TEST)

.c.o:
	@$(CC) $(CFLAGS) $(INC) -c $^ -o $@

all: $(NAME)

$(NAME): $(OBJ_ALL)
	@$(CC) $(CFLAGS) $(INC) -o $@ $^ -lreadline

clean:
	@rm -rf $(OBJ_ALL) $(OBJ_TEST)

fclean: clean
	@rm -rf $(NAME) test

re: fclean all

valg: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.supp --track-fds=yes -q ./$(NAME)

env: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.supp -s --track-fds=yes env -i ./$(NAME)

test: $(OBJ_TESTER)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lreadline

.PHONY: all clean fclean re valg test
