CC = cc 
CFLAGS = -Wall -Werror -Wextra -I. -I$(INC_DIR) -I$(LIB_DIR) -I$(MLX_DIR)/include -g3 -fsanitize=address
MLX_FLAGS = ./lib/MLX42/build/libmlx42.a -I./lib/MLX42/include -ldl -lglfw -pthread -lm 
# MLX_FLAGS = ./lib/MLX42/build/libmlx42.a \
#             -L/opt/homebrew/lib -lglfw -pthread -lm \
#             -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

SRC_FILES = src/error_handler/error_handler.c \
src/main.c \
src/parse_file/valid_file.c \
src/parse_file/eval_graph.c \
src/parse_file/handle_map.c \
src/free/ft_free.c \
src/utils/check_settings_line.c \
src/utils/check_map_line.c \
src/init/init_game.c \
src/math/game_math.c \
src/game_loop/start_game.c \
src/graph/graph.c \
lib/get_next_line/get_next_line.c \
lib/get_next_line/get_next_line_utils.c \


OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = cub3d

INC_DIR = ./include
LIB_DIR = ./lib/libft
LIBFT = $(LIB_DIR)/libft.a
MLX_DIR = ./lib/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

all: MLX_CREATE $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

MLX_CREATE:
	cd ./lib/MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(OBJ_FILES) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: clean fclean all

PHONY: clean fclean alls







# CC = cc
# CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR) -I$(MLX_DIR)/include
# CLIB = -c

# LIBFT_DIR = ./lib/libft
# LIBFT_A = $(LIBFT_DIR)/libft.a

# MLX_DIR = ./lib/MLX42
# MLX_LIB = $(MLX_DIR)/build/libmlx42.a

# MLX_FLAGS =  $(MLX_DIR)/include -ldl -lglfw -pthread -lm
# # $(MLX_DIR)/build/libmlx42.a -I 

# SRC_FILES = ./src/main.c

# OBJ_FILES = $(SRC_FILES:.c=.o)

# NAME = cub3D


# all: MLX_CREATE $(LIBFT_A) $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(CLIB) -c $^ -o $@

# $(LIBFT_A):
# 	$(MAKE) -C $(LIBFT_DIR)

# MLX_CREATE:
# 	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

# $(NAME): $(OBJ_FILES) $(LIBFT_A) $(MLX_LIB)
# 	$(CC) $(CFLAGS) $(OBJ_FILES) $(MLX_FLAGS) -o $(NAME)


# clean:
# 	rm -f $(OBJ_FILES)
# 	$(MAKE) -C $(LIBFT_DIR) clean

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) -C $(LIBFT_DIR) fclean

# re: clean fclean all

# .PHONY: clean fclean all