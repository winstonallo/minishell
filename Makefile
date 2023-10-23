NAME = minishell

OBJ_DIR = obj

SRC_DIR = src

SRCS = 	${SRC_DIR}/minishell.c \
		${SRC_DIR}/loop.c \
		${SRC_DIR}/paths.c \
		${SRC_DIR}/parse_for_quotes.c \
		${SRC_DIR}/parsing_utils.c \
		${SRC_DIR}/store_quoted_sequences.c \
		${SRC_DIR}/testing_utils.c \
		${SRC_DIR}/memory_management.c \
		${SRC_DIR}/commands.c \
		${SRC_DIR}/expand.c \
		${SRC_DIR}/initialize.c \
		${SRC_DIR}/execute.c \
		${SRC_DIR}/parse_special_characters.c \

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

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

.PHONY: all clean fclean re