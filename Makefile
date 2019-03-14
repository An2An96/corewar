############################		Variables		############################
include var.mk

############################		  Rules 		############################

all:
	@$(MAKE) -C $(ASM_DIR)
	@$(MAKE) -C $(VM_DIR)

clean:
	@$(MAKE) clean -C $(ASM_DIR)
	@$(MAKE) clean -C $(VM_DIR)

fclean:
	@$(MAKE) fclean -C $(ASM_DIR)
	@$(MAKE) fclean -C $(VM_DIR)

re: fclean all

.PHONY: all re clean fclean

#	by rschuppe