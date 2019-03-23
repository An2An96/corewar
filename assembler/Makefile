############################		Variables		############################
include ../var.mk

NAME = ../$(ASM_NAME)

LIB_DIR = ../libs
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes

LIBS = libft libftprintf

SRCS =	main.c file_stuff.c ft_strsplit.c lines_stuff.c list_stuff.c op.c \
		string_stuff.c tokens_stuff.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:%.c=%.o))
_INCS = asm.h
INCS = $(addprefix $(INC_DIR)/,$(_INCS))

FLAGS += -I$(INC_DIR)
OBJ_FLAGS += -I../common
FLAGS += $(foreach lib,$(LIBS),-I$(LIBS_DIR)/$(lib)/includes)

OBJ_FLAGS += -I$(INC_DIR)
OBJ_FLAGS += -I../common
OBJ_FLAGS += $(foreach lib,$(LIBS),-I$(LIB_DIR)/$(lib)/includes)

ifeq ($(STRICT),true)
	OBJ_FLAGS += -Wall -Wextra -Werror
endif
ifeq ($(DEBUG),true)
	OBJ_FLAGS += -g
endif

FLAGS += $(foreach lib,$(LIBS),-L$(LIB_DIR)/$(lib) -l$(lib:lib%=%))

############################		  Rules 		############################

all: $(LIBS) $(NAME)

$(LIBS):
	@$(MAKE) -C $(LIB_DIR)/$@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@gcc $(OBJ_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@gcc $(FLAGS) -o $@ $^
	@echo "$(OK_COLOR)Build assembler complete$(NO_COLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(DANGER_COLOR)Object files cleared$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(DANGER_COLOR)Build cleared$(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean

#	by rschuppe