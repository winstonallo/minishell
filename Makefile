NAME = minishell

OBJ_DIR = obj

SRC_DIR = src/

MAIN_DIR = main/

PARSER_DIR = parser/

UTILS_DIR = utils/

EXEC_DIR = executer/

BUILT_INS = built_ins/

INIT_DIR = initialize/

LEXER_DIR = lexer/

SRCS = 	${SRC_DIR}${MAIN_DIR}minishell.c \
		${SRC_DIR}${MAIN_DIR}loop.c \
		${SRC_DIR}${MAIN_DIR}signals.c \
\
		${SRC_DIR}${PARSER_DIR}parse_quotes.c \
		${SRC_DIR}${PARSER_DIR}parse_special_characters.c \
		${SRC_DIR}${PARSER_DIR}expand2.c \
		${SRC_DIR}${PARSER_DIR}expand.c \
		${SRC_DIR}${PARSER_DIR}get_command_table.c \
		${SRC_DIR}${PARSER_DIR}prep_args.c \
\
		${SRC_DIR}${UTILS_DIR}list_utils_quote_parsing.c \
		${SRC_DIR}${UTILS_DIR}list_utils_special_char.c \
		${SRC_DIR}${UTILS_DIR}list_utils_environment.c \
		${SRC_DIR}${UTILS_DIR}list_utils_cmd_table.c \
		${SRC_DIR}${UTILS_DIR}list_utils_paths.c \
		${SRC_DIR}${UTILS_DIR}memory_management_arrays.c \
		${SRC_DIR}${UTILS_DIR}memory_management_cleanup.c \
		${SRC_DIR}${UTILS_DIR}parsing_utils.c \
		${SRC_DIR}${UTILS_DIR}testing_utils.c \
\
		${SRC_DIR}${EXEC_DIR}commands.c \
		${SRC_DIR}${EXEC_DIR}execute.c \
		${SRC_DIR}${EXEC_DIR}pipe_utils.c \
		${SRC_DIR}${EXEC_DIR}pipe.c \
		${SRC_DIR}${EXEC_DIR}exec_utils.c \
\
		${SRC_DIR}${BUILT_INS}export_utils.c \
		${SRC_DIR}${BUILT_INS}export_error.c \
		${SRC_DIR}${BUILT_INS}export.c \
		${SRC_DIR}${BUILT_INS}echo.c \
		${SRC_DIR}${BUILT_INS}pwd.c \
		${SRC_DIR}${BUILT_INS}cd.c \
		${SRC_DIR}${BUILT_INS}env.c \
		${SRC_DIR}${BUILT_INS}exit.c \
\
		${SRC_DIR}${INIT_DIR}initialize_paths.c \
		${SRC_DIR}${INIT_DIR}initialize_lists.c \
		${SRC_DIR}${INIT_DIR}environment.c \
\
		${SRC_DIR}${LEXER_DIR}errors.c \

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

LDFLAGS = -L ./libft -lm -lft -lreadline

RM = rm -rf

.SILENT:

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	printf "Compiling libft..."
	$(MAKE) -C ./libft --no-print-directory
	printf "\r\rCompiling minishell.."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME) $(LDFLAGS)
	printf "\rCompiling completed.\n"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: libft/src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ./libft --no-print-directory fclean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	clear; ./$(NAME)

generate_test:
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=$(NAME).log ./$(NAME)

test: all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)

child_test: all
	clear; valgrind --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)

.PHONY: all clean fclean re