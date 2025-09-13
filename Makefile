# ============================================================================ #
#                               Cub3D MAKEFILE                             #
# ============================================================================ #

# ******************************* VARIABLES ********************************** #
NAME		:= cub3D
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -Iincludes #-fsanitize=address
LDFLAGS		:= -Llibft -lft
LIBFT		:= libft/libft.a
LIBFT_FILES	:= \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
		ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memcmp.c ft_memset.c \
		ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_putnbr_fd.c ft_putendl_fd.c \
		ft_striteri.c ft_memchr.c ft_split.c ft_itoa.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		get_next_line.c get_next_line_utils.c

# Header files
INCLUDES	:=	includes/cub3d.h \
				includes/parser.h \
				includes/textures.h

# Source directories
LIBFT_SRCS	:= $(addprefix libft/, $(LIBFT_FILES))
SRC_DIR		:= src
PAR_DIR		:= $(SRC_DIR)/parser
UTL_DIR		:= $(SRC_DIR)/utils

# Source files
SRCS		:=	$(SRC_DIR)/main.c \
				$(PAR_DIR)/parse_file.c \
				$(UTL_DIR)/exit_free.c \
				$(UTL_DIR)/ft_split_set.c \


# Object files
OBJS		:= $(SRCS:.c=.o)

# ******************************** RULES ************************************* #

COLOR_RESET := \033[0m
COLOR_GREEN := \033[1;32m
COLOR_BLUE  := \033[1;34m
COLOR_RED   := \033[1;31m

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(COLOR_BLUE)🔨 Linking $(NAME)...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(COLOR_GREEN)✅ Successfully built $(NAME)!$(COLOR_RESET)"

$(OBJS): %.o: %.c $(INCLUDES)
	@echo "$(COLOR_BLUE)📦 Compiling $<...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRCS) libft/libft.h
	@echo "$(COLOR_BLUE)📚 Building libft...$(COLOR_RESET)"
	@make -C libft

all:
	@echo "$(COLOR_BLUE)🚀 Building mandatory project...$(COLOR_RESET)"
	@$(MAKE) $(NAME)

clean:
	@echo "$(COLOR_RED)🧹 Cleaning object files...$(COLOR_RESET)"
	@make -C libft clean
	@rm -f $(OBJS)
	@echo "$(COLOR_GREEN)✅ Clean done.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_RED)🧨 Full clean (executables)...$(COLOR_RESET)"
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "$(COLOR_GREEN)✅ Full clean complete.$(COLOR_RESET)"

re: fclean all

.PHONY:  clean