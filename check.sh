#!/bin/sh
CYCLES=400
MY_COREWAR=/Users/rschuppe/projects/corewar/corewar
ORIGINAL_COREWAR=/Users/rschuppe/Downloads/vm_champs/corewar
CHAMPION=/Users/rschuppe/projects/corewar/champions/Gagnant.cor
mkdir -p tmp/
$MY_COREWAR -dump $CYCLES $CHAMPION | tail -n64 > tmp/my
$ORIGINAL_COREWAR -d $CYCLES $CHAMPION | tail -n 64 > tmp/original
diff tmp/my tmp/original
