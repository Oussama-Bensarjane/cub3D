NAME := cub3D
NAME_BONUS := cub3D_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -Ilib/libft
LDFLAGS := -L./lib/libft/ -lft

OSFLAG := $(shell uname -s)
ifeq ($(OSFLAG),Linux)
CFLAGS += -Ilib/mlx_linux
endif
ifeq ($(OSFLAG),Darwin)
CFLAGS += -Ilib/mlx_mac
endif

ifeq ($(OSFLAG),Linux)
LDFLAGS += -L./lib/mlx_linux/ -lmlx -lXext -lX11 -lm -lz
endif
ifeq ($(OSFLAG),Darwin)
LDFLAGS += -L./lib/mlx_mac/ -lmlx -framework OpenGL -framework AppKit
endif

# ================================ Libraries ================================

# MLX
ifeq ($(OSFLAG),Linux)
MLX_DIR :=	lib/mlx_linux
endif
ifeq ($(OSFLAG),Darwin)
MLX_DIR :=	lib/mlx_mac
endif
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

INCLUDES_DIR :=	includes
INCLUDES :=	$(INCLUDES_DIR)/cub3d.h \
			$(INCLUDES_DIR)/config.h \
			$(INCLUDES_DIR)/parser.h \
			$(INCLUDES_DIR)/textures.h \

# Directories
SRCDIR :=		src
PAR_DIR :=		$(SRCDIR)/parser
GPLAY_DIR :=	$(SRCDIR)/gameplay
TEXTR_DIR :=	$(SRCDIR)/textures
UTILS_DIR :=	$(SRCDIR)/utils

# main.c
SRC :=	$(SRCDIR)/main.c

# parser
SRC +=	$(PAR_DIR)/parse_config.c \
		$(PAR_DIR)/parse_file.c \
		$(PAR_DIR)/parse_map.c \
		$(PAR_DIR)/parse_utils.c \
		$(PAR_DIR)/validate_map.c

# gameplay
SRC +=	$(GPLAY_DIR)/utils.c \
		$(GPLAY_DIR)/player.c \
		$(GPLAY_DIR)/player_move.c \
		$(GPLAY_DIR)/init_dda.c \
		$(GPLAY_DIR)/raycaster.c \
		$(GPLAY_DIR)/gameplay.c

# textures
SRC +=	$(TEXTR_DIR)/texture_loader.c \
		$(TEXTR_DIR)/texture_utils.c \
		$(TEXTR_DIR)/texture.c

# utils
SRC +=	$(UTILS_DIR)/exit.c \
		$(UTILS_DIR)/exit_free.c \
		$(UTILS_DIR)/ft_split_set.c

OBJDIR :=	obj
OBJ :=		$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ================================ Cub3D_BONUS ================================

INCLUDES_DIR_BONUS :=	bonus/includes
INCLUDES_BONUS :=		$(INCLUDES_DIR_BONUS)/cub3d_bonus.h \
						$(INCLUDES_DIR_BONUS)/config_bonus.h \
						$(INCLUDES_DIR_BONUS)/parser_bonus.h \
						$(INCLUDES_DIR_BONUS)/textures_bonus.h \

# Directories
SRCDIR_BONUS :=		bonus/src
PAR_DIR_BONUS :=	$(SRCDIR_BONUS)/parser
GPLAY_DIR_BONUS :=	$(SRCDIR_BONUS)/gameplay
TEXTR_DIR_BONUS :=	$(SRCDIR_BONUS)/textures
UTILS_DIR_BONUS :=	$(SRCDIR_BONUS)/utils

# main_bonus.c
SRC_BONUS :=	$(SRCDIR_BONUS)/main_bonus.c

# parser
SRC_BONUS +=	$(PAR_DIR_BONUS)/parse_config_bonus.c \
				$(PAR_DIR_BONUS)/parse_file_bonus.c \
				$(PAR_DIR_BONUS)/parse_map_bonus.c \
				$(PAR_DIR_BONUS)/parse_utils_bonus.c \
				$(PAR_DIR_BONUS)/validate_map_bonus.c

# gameplay
SRC_BONUS +=	$(GPLAY_DIR_BONUS)/utils_bonus.c \
				$(GPLAY_DIR_BONUS)/player_bonus.c \
				$(GPLAY_DIR_BONUS)/player_move_bonus.c \
				$(GPLAY_DIR_BONUS)/init_dda_bonus.c \
				$(GPLAY_DIR_BONUS)/raycaster_bonus.c \
				$(GPLAY_DIR_BONUS)/minimap_player_bonus.c \
				$(GPLAY_DIR_BONUS)/minimap_bonus.c \
				$(GPLAY_DIR_BONUS)/gameplay_bonus.c

# textures
SRC_BONUS +=	$(TEXTR_DIR_BONUS)/texture_loader_bonus.c \
				$(TEXTR_DIR_BONUS)/texture_utils_bonus.c \
				$(TEXTR_DIR_BONUS)/texture_bonus.c

# utils
SRC_BONUS +=	$(UTILS_DIR_BONUS)/exit_bonus.c \
				$(UTILS_DIR_BONUS)/exit_free_bonus.c \
				$(UTILS_DIR_BONUS)/ft_split_set_bonus.c

OBJDIR_BONUS :=	obj_bonus
OBJ_BONUS :=	$(SRC_BONUS:$(SRCDIR_BONUS)/%.c=$(OBJDIR_BONUS)/%.o)

COLOR_RESET := \033[0m
COLOR_GREEN := \033[1;32m
COLOR_BLUE  := \033[1;34m
COLOR_RED   := \033[1;31m

$(NAME): CFLAGS += -I$(INCLUDES_DIR)
$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "$(COLOR_BLUE)🔨 Linking $(NAME)...$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(COLOR_GREEN)✅ Successfully built $(NAME)!$(COLOR_RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	@echo "$(COLOR_BLUE)📦 Compiling $<...$(COLOR_RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS): CFLAGS += -I$(INCLUDES_DIR_BONUS)
$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJ_BONUS)
	@echo "$(COLOR_BLUE)🔨 Linking $(NAME_BONUS)...$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LDFLAGS) -o $(NAME_BONUS)
	@echo "$(COLOR_GREEN)✅ Successfully built $(NAME_BONUS)!$(COLOR_RESET)"

$(OBJDIR_BONUS)/%.o: $(SRCDIR_BONUS)/%.c $(INCLUDES_BONUS)
	@echo "$(COLOR_BLUE)📦 Compiling $<...$(COLOR_RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	@echo "$(COLOR_BLUE)📚 Building MLX...$(COLOR_RESET)"
	@make -C $(MLX_DIR)
	@echo "$(COLOR_GREEN)✅ Successfully built $(MLX)!$(COLOR_RESET)"

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_DIR)/libft.h
	@echo "$(COLOR_BLUE)📚 Building libft...$(COLOR_RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(COLOR_GREEN)✅ Successfully built $(LIBFT)!$(COLOR_RESET)"

all:	$(NAME)

bonus:	$(NAME_BONUS)

clean:
	@echo "$(COLOR_RED)🧹 Cleaning object files...$(COLOR_RESET)"
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJDIR_BONUS)
	@echo "$(COLOR_GREEN)✅ Clean done.$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_RED)🧨 Full clean...$(COLOR_RESET)"
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "$(COLOR_GREEN)✅ Full clean complete.$(COLOR_RESET)"

re: fclean all

.PHONY: clean
