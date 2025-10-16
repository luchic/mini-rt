NAME		= miniRT

UNAME_S		:= $(shell uname -s)

# ---- MLX42 (auto-clone & build) -------------------------------------------
MLX42_DIR	:= MLX42
MLX42_REPO	:= https://github.com/codam-coding-college/MLX42.git
MLX_INC		:= -I$(MLX42_DIR)/include
MLX_LIB		:= $(MLX42_DIR)/build/libmlx42.a

ifeq ($(UNAME_S),Darwin)
	MLX_LDFLAGS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else
	MLX_LDFLAGS := -ldl -lglfw -lm -lpthread
endif

# ------ Libft ------------------------------------------------------
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a
FT = ft

# ------ Sources -----------------------------------------------------

SRC = src/

RENDER = $(SRC)render/
PARSE = $(SRC)parse/
MATH = $(SRC)math/
UTILS = $(SRC)utils/
ANIMATION = $(SRC)animation/


SRC_FILES = $(SRC)main.c

#Render
SRC_FILES += $(wildcard $(RENDER)*.c)

#Parse
SRC_FILES += $(wildcard $(PARSE)*.c)

#Math
SRC_FILES += $(wildcard $(MATH)*.c)

#Utils
SRC_FILES += $(wildcard $(UTILS)*.c)

#Animation
SRC_FILES += $(wildcard $(ANIMATION)*.c)

OBJS = $(SRC_FILES:.c=.o)


# ------ Includes -----------------------------------------------

INCLUDES = includes


CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDES) $(MLX_INC)
LIBS = -L$(LIBFT_PATH) -l$(FT) $(MLX_LIB) $(MLX_LDFLAGS)

DEBUG =	-g -fsanitize=address

all: $(NAME)


$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
	@echo ">> Linking final executable..."
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

bonus: CFLAGS += -DBONUS=1
bonus: $(OBJS) $(BONUS_OBJS) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(BONUS_OBJS) $(LIBS)

bonus-d: CFLAGS += -DBONUS=1 -g -fsanitize=address
bonus-d: $(OBJS) $(BONUS_OBJS) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(BONUS_OBJS) $(LIBS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(MLX42_DIR)/include/MLX42/MLX42.h:
	@printf ">> Preparing MLX42 headers...\n"
	@if [ ! -d "$(MLX42_DIR)/include/MLX42" ]; then \
		echo "   Cloning MLX42..."; \
		git clone --depth 1 --recursive "$(MLX42_REPO)" "$(MLX42_DIR)"; \
	else \
		echo "   Found MLX42; updating submodules..."; \
		git -C "$(MLX42_DIR)" submodule update --init --recursive; \
	fi


$(MLX_LIB): $(MLX42_DIR)/include/MLX42/MLX42.h
	@echo ">> Configuring MLX42 with CMake..."
	@cmake -S "$(MLX42_DIR)" -B "$(MLX42_DIR)/build" -DDEBUG=OFF
	@echo ">> Building MLX42..."
	@cmake --build "$(MLX42_DIR)/build" -j

%.o: %.c
	@echo ">> Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

mlx42clean:
	@rm -rf "$(MLX42_DIR)/build"

.PHONY: all clean fclean re bonus mlx42clean
