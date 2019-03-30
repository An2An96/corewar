#!/bin/sh
CYCLES=$1
if [ -n "$CYCLES" ]
then
	CHAMP1=champions/examples/bee_gees.cor
	#champions/examples/helltrain.cor
	CHAMP2=champions/examples/helltrain.cor
	#champions/examples/bee_gees.cor
	CHAMP3=champions/examples/turtle.cor
	#champions/examples/turtle.cor
	#champions/examples/bee_gees.cor
	CHAMP4=champions/examples/helltrain.cor
	#champions/examples/helltrain.cor

	MY_COREWAR=/Users/rschuppe/projects/corewar/corewar
	ORIGINAL_COREWAR=/Users/rschuppe/Downloads/vm_champs/corewar
	mkdir -p tmp/
	# | tail -n 64
	$MY_COREWAR -dump $CYCLES -v 16 -a $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4 > tmp/my
	$ORIGINAL_COREWAR -d $CYCLES -v 16 -a $CHAMP1 $CHAMP2 $CHAMP3 $CHAMP4 > tmp/original
	diff tmp/my tmp/original
fi