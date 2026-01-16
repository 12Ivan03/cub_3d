CC = cc 
CFLAGS = -I. -Wall -Werror -Wextra -I$(INC_DIR) -I$(LIB_DIR) -I$(MLX_DIR)/include -g3 #-fsanitize=address
MLX_FLAGS = ./lib/MLX42/build/libmlx42.a -I./lib/MLX42/include -ldl -lglfw -pthread -lm 
# MLX_FLAGS = ./lib/MLX42/build/libmlx42.a \
#             -L/opt/homebrew/lib -lglfw -pthread -lm \
#             -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

SRC_FILES = src/main.c \
src/error_handler/error_handler.c \
src/parse_file/valid_file.c \
src/parse_file/eval_graph.c \
src/parse_file/process_map.c \
src/parse_file/parse_file_content.c \
src/parse_file/read_file_direction_f_c.c \
src/parse_file/eval_map.c \
src/free/ft_free.c \
src/hooks/key_hook.c \
src/hooks/key_hook_helper.c \
src/hooks/resize_hook.c \
src/utils/extract_color_walls_from_file.c \
src/utils/extract_map_line.c \
src/utils/parse_and_config_line.c \
src/utils/process_map_utils.c \
src/utils/close_gnl_fd.c \
src/init/init_game.c \
src/init/init_structs.c \
src/math/game_math.c \
src/game_loop/start_game.c \
src/graph/graph.c \
src/graph/graph_background.c \
src/mini_map/mini_map.c \
lib/get_next_line/get_next_line.c \
lib/get_next_line/get_next_line_utils.c \


OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = cub3D

INC_DIR = ./include
LIB_DIR = ./lib/libft
LIBFT = $(LIB_DIR)/libft.a
MLX_DIR = ./lib/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(MLX_LIB):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX_LIB) $(MLX_DIR)/src/* 
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: clean fclean all

PHONY: clean fclean all
