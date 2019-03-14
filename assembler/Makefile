############################		Variables		############################
include ../var.mk

NAME = ../$(ASM_NAME)

LIB_DIR = ../libs
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes

LIBS = libft libftprintf

SRCS = main.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:%.c=%.o))
_INCS = asm.h
INCS = $(addprefix $(INC_DIR)/,$(_INCS))

FLAGS += -I$(INC_DIR)
FLAGS += $(foreach lib,$(LIBS),-I$(LIBS_DIR)/$(lib)/includes)

ifeq ($(STRICT),true)
	FLAGS += -Wall -Wextra -Werror
endif
ifeq ($(DEBUG),true)
	FLAGS += -g
endif

############################		  Rules 		############################

all: $(LIBS) $(NAME)

$(LIBS):
	@$(MAKE) -C $(LIB_DIR)/$@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@gcc -o $@ $^
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