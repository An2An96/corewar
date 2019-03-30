#!/bin/sh
CHAMPION=$1
MY_ASM=/Users/rtroll/Desktop/corewar_norme/asm
ORIGINAL_ASM=/Users/rtroll/Desktop/resourses/vm_champs/asm
CHAMPION_COR=${CHAMPION%\.s}.cor
mkdir -p tmp/
$MY_ASM $CHAMPION
hexdump -C ${CHAMPION%\.s}.cor > tmp/my
$ORIGINAL_ASM $CHAMPION
hexdump -C ${CHAMPION%\.s}.cor > tmp/original
diff tmp/my tmp/original
