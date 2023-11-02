NAME = minishell

OBJ_DIR = obj

SRC_DIR = src/

MAIN_DIR = main/

PARSER_DIR = parser/

UTILS_DIR = utils/

EXEC_DIR = executer/

SRCS = 	${SRC_DIR}${MAIN_DIR}minishell.c \
		${SRC_DIR}${MAIN_DIR}loop.c \
		${SRC_DIR}${PARSER_DIR}paths.c \
		${SRC_DIR}${PARSER_DIR}parse_for_quotes.c \
		${SRC_DIR}${PARSER_DIR}parsing_utils.c \
		${SRC_DIR}${UTILS_DIR}list_utils.c \
		${SRC_DIR}${UTILS_DIR}testing_utils.c \
		${SRC_DIR}${UTILS_DIR}memory_management_utils.c \
		${SRC_DIR}${UTILS_DIR}memory.c \
		${SRC_DIR}${EXEC_DIR}commands.c \
		${SRC_DIR}${PARSER_DIR}expand_dquotes.c \
		${SRC_DIR}${PARSER_DIR}expand.c \
		${SRC_DIR}${UTILS_DIR}initialize.c \
		${SRC_DIR}${EXEC_DIR}execute.c \
		${SRC_DIR}${PARSER_DIR}parse_special_characters.c \
		${SRC_DIR}${PARSER_DIR}escape.c \
		${SRC_DIR}${PARSER_DIR}get_command_table.c \
		${SRC_DIR}${UTILS_DIR}store_cmd_tables.c \
		${SRC_DIR}${PARSER_DIR}expand_uquotes.c \
		${SRC_DIR}${EXEC_DIR}pipe_utils.c \
		${SRC_DIR}${UTILS_DIR}store_environment.c \
		${SRC_DIR}${EXEC_DIR}built_ins.c \

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

generate_test:
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --gen-suppressions=all --log-file=$(NAME).log ./$(NAME)

test: all
	clear; valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)

child_test: all
	clear; valgrind --trace-children=yes --leak-check=full --track-origins=yes --track-fds=yes --show-reachable=yes --show-leak-kinds=all --error-limit=no --suppressions=./$(NAME).supp ./$(NAME)
.PHONY: all clean fclean re