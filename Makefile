NAME		= miniRT

UNAME_S		:= $(shell uname -s)

# ---- MLX42 (auto-clone & build) -------------------------------------------
MLX42_DIR	:= MLX42
MLX42_REPO	:= https://github.com/codam-coding-college/MLX42.git
MLX_INC		:= -I$(MLX42_DIR)/include/MLX42
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
PARSER = $(SRC)parser/
MATH = $(SRC)math/
UTILS = $(SRC)utils/
ANIMATION = $(SRC)animation/
INIT = $(SRC)init/


SRC_FILES = $(SRC)main.c

#Render
SRC_FILES += $(RENDER)accum_light_once.c \
			$(RENDER)accum_lights.c \
			$(RENDER)bump_bonus.c \
			$(RENDER)camera.c \
			$(RENDER)checker_bonus.c \
			$(RENDER)hit_cone_utils.c \
			$(RENDER)hit_cone_bonus.c \
			$(RENDER)hit_cylinder_utils.c \
			$(RENDER)hit_cylinder.c \
			$(RENDER)hit_plane.c \
			$(RENDER)hit_sphere.c \
			$(RENDER)image.c \
			$(RENDER)render_context.c \
			$(RENDER)render.c \
			$(RENDER)rgb.c \
			$(RENDER)shade.c \
			$(RENDER)shadow.c \
			$(RENDER)specular_bonus.c \
			$(RENDER)texture.c \
			$(RENDER)trace.c

# $(wildcard $(RENDER)*.c)

#Parse
SRC_FILES += $(PARSER)create_new_obj.c \
			$(PARSER)parse_ambient_light.c \
			$(PARSER)parse_camera.c \
			$(PARSER)parse_color.c \
			$(PARSER)parse_cone.c \
			$(PARSER)parse_cylinder.c \
			$(PARSER)parse_file_line.c \
			$(PARSER)parse_file.c \
			$(PARSER)parse_light.c \
			$(PARSER)parse_plane.c \
			$(PARSER)parse_sphere.c \
			$(PARSER)parse_spotlight.c \
			$(PARSER)parse_utils.c \
			$(PARSER)parse_vectors.c

# $(wildcard $(PARSER)*.c)

#Math
SRC_FILES += $(MATH)polynomial.c \
			$(MATH)projection.c \
			$(MATH)vec_ops.c \
			$(MATH)vec_ops1.c \
			$(MATH)vec.c

# $(wildcard $(MATH)*.c)

#Utils
SRC_FILES += $(UTILS)atof.c \
			$(UTILS)atoi.c \
			$(UTILS)emalloc.c \
			$(UTILS)error_handle.c \
			$(UTILS)ft_atoi_checker.c \
			$(UTILS)ft_free.c

# $(wildcard $(UTILS)*.c)

#Animation
SRC_FILES += $(ANIMATION)animation.c \
			$(ANIMATION)camera_mouse.c \
			$(ANIMATION)lamp_move.c \
			$(ANIMATION)rand.c \
			$(ANIMATION)shfx_core.c \
			$(ANIMATION)shfx_find.c \
			$(ANIMATION)shfx_math.c \
			$(ANIMATION)shfx_physics.c \
			$(ANIMATION)shfx_spwan.c \
			$(ANIMATION)shfx_update.c
			
# $(wildcard $(ANIMATION)*.c)

#MLX Windowing
SRC_FILES += $(INIT)init_camera.c \
			$(INIT)init_hooks.c \
			$(INIT)init_window.c \
			$(INIT)resize_hook.c \

# $(wildcard $(INIT)*.c)

OBJS = $(SRC_FILES:.c=.o)


# ------ Includes -----------------------------------------------

INCLUDES = includes


CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDES) $(MLX_INC)
LIBS = -L$(LIBFT_PATH) -l$(FT) $(MLX_LIB) $(MLX_LDFLAGS)

DEBUG =	-g -fsanitize=address

all: $(NAME)


$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	@echo ">> Linking final executable..."
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

debug: CFLAGS += $(DEBUG)
debug: $(NAME)

bonus: CFLAGS += -DBONUS=1
bonus: $(OBJS) $(BONUS_OBJS) $(MLX_LIB) $(LIBFT)
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
	rm -fr $(MLX42_DIR)
	rm -f $(NAME)

re: fclean all

mlxclean:
	@rm -rf "$(MLX42_DIR)/build"

.PHONY: all clean fclean re bonus mlxclean debug
