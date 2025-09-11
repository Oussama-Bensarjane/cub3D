NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Werror -Ilib/libft -Ilib/mlx -Iincludes
LDFLAGS := -L./lib/libft/ -lft -L./lib/mlx/ -lmlx -lXext -lX11 -lm -lz

# ================================ Libraries ================================

# MLX
MLX_DIR :=	lib/mlx
MLX :=		$(MLX_DIR)/libmlx.a

# LIBFT
LIBFT_DIR :=	lib/libft
LIBFT :=	$(LIBFT_DIR)/libft.a
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
LIBFT_SRCS	:= $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))

# ================================ Cub3D ================================

INCLUDES :=	includes/cub3d.h \
			includes/config.h

# Directories
SRCDIR :=		src
GPLAY_DIR :=	$(SRCDIR)/gameplay
UTILS_DIR :=	$(SRCDIR)/utils

# main.c
SRC :=	$(SRCDIR)/main.c

# gameplay
SRC :=	$(SRC) \
		$(GPLAY_DIR)/utils.c \
		$(GPLAY_DIR)/player.c \
		$(GPLAY_DIR)/gameplay.c

# utils
SRC :=	$(SRC) \
		$(UTILS_DIR)/exit.c

OBJDIR := obj
OBJ := $(SRC:src/%.c=$(OBJDIR)/%.o)

COLOR_RESET := \033[0m
COLOR_GREEN := \033[1;32m
COLOR_BLUE  := \033[1;34m
COLOR_RED   := \033[1;31m

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "$(COLOR_BLUE)🔨 Linking $(NAME)...$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(COLOR_GREEN)✅ Successfully built $(NAME)!$(COLOR_RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	@echo "$(COLOR_BLUE)📦 Compiling $<...$(COLOR_RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(MLX):
	@echo "$(COLOR_BLUE)📚 Building MLX...$(COLOR_RESET)"
	@make -C $(MLX_DIR)
	@echo "$(COLOR_GREEN)✅ Successfully built $(MLX)!$(COLOR_RESET)"

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_DIR)/libft.h
	@echo "$(COLOR_BLUE)📚 Building libft...$(COLOR_RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(COLOR_GREEN)✅ Successfully built $(LIBFT)!$(COLOR_RESET)"

all: $(NAME)

clean:
	@echo "$(COLOR_RED)🧹 Cleaning object files...$(COLOR_RESET)"
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJDIR)
	@echo "$(COLOR_GREEN)✅ Clean done.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_RED)🧨 Full clean...$(COLOR_RESET)"
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(COLOR_GREEN)✅ Full clean complete.$(COLOR_RESET)"

re: fclean all

.PHONY: clean
