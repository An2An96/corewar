#!/bin/sh
CHAMPION=$1
CYCLES=$2
if [ -n "$CYCLES" ]
then
	MY_COREWAR=/Users/rschuppe/projects/corewar/corewar
	ORIGINAL_COREWAR=/Users/rschuppe/Downloads/vm_champs/corewar
	mkdir -p tmp/
	#| tail -n64
	$MY_COREWAR -v 2 -dump $CYCLES $CHAMPION > tmp/my
	$ORIGINAL_COREWAR -v 2 -d $CYCLES $CHAMPION > tmp/original
	diff tmp/my tmp/original
fi
