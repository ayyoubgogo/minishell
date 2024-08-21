CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
INCLUDE		=	-I include/
NAME		=	minishell
MAKE		=	make
MAKE_FLAGS	=	-C
LIBS		=	libs/libft/libft.a	\
				libs/gcollector/gcollector.a
RM			=	rm -f
SOURCE		=	src/builtings/env.c						\
                src/builtings/env_to_list.c				\
                src/builtings/red_in.c					\
                src/builtings/export_help.c				\
                src/builtings/append_red.c				\
                src/builtings/unset.c					\
                src/builtings/exit.c					\
                src/builtings/pwd.c						\
                src/builtings/cd.c						\
                src/builtings/builtings.c				\
                src/builtings/here_doc.c				\
                src/builtings/check_path.c				\
                src/builtings/pipex.c					\
                src/builtings/export.c					\
                src/builtings/red_out.c					\
                src/builtings/echo.c					\
                src/builtings/help_function.c			\
                src/builtings/check_pipe.c				\
                src/builtings/other.c					\
				src/errors/custom_errors.c				\
                src/parser/quotes_checker.c				\
                src/parser/parser.c						\
                src/parser/parsing_utils.c				\
                src/expander/expander.c					\
                src/expander/utils_2.c					\
                src/expander/utils_1.c					\
                src/utils/signals.c						\
                src/utils/initializer.c					\
                src/utils/environment.c					\
                src/utils/cleaning.c					\
                src/utils/check.c						\
                src/utils/other.c						\
                src/tokenization/utils.c				\
                src/tokenization/tokens_handler.c		\
                src/tokenization/tokenize.c				\
				src/expander/filter/filter.c			\
				src/expander/filter/ftgc_tab_join.c		\
                src/main.c
OBJECTS		=	$(SOURCE:.c=.o)

all: mklibs $(NAME)

$(NAME): $(OBJECTS) $(LIBS)
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $@ -lreadline

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

mklibs:
	@$(MAKE) $(MAKE_FLAGS) libs/libft
	@$(MAKE) $(MAKE_FLAGS) libs/gcollector

clean:
	@$(RM) $(OBJECTS)
	@$(MAKE) $(MAKE_FLAGS) libs/libft clean
	@$(MAKE) $(MAKE_FLAGS) libs/gcollector clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(MAKE_FLAGS) libs/libft fclean
	@$(MAKE) $(MAKE_FLAGS) libs/gcollector fclean

re: fclean all
