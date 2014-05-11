#!/bin/bash

command="convert -size 4097x514 xc:white"

# Draw block-ciphers.
command="${command} -fill \"#FFCCCC\" -stroke \"#FF2222\" -strokewidth 3"
for (( i=0 ; i<32 ; i++ )); do
	position_begin=$(($i * 16))
	position_end=$(($position_begin + 16))
	command="${command} -draw \"rectangle ${position_begin},0 ${position_end},512\""
done

# Draw sections.
command="${command} -fill \"#CCFFCC\" -stroke \"#448844\" -strokewidth 3"
for (( i=1 ; i<8 ; i++ )); do
	position_begin=$(($i * 512))
	position_end=$(($position_begin + 512))
	command="${command} -draw \"rectangle ${position_begin},0 ${position_end},512\""
done

# Draw block.
command="${command} -fill none -stroke \"#4444CC\" -strokewidth 13 -draw \"rectangle 0,0 4096,512\""

command="${command} sizes.gif"
# Okay, so, if I echo the command, copy + paste and run it then it works just
# fine, but if I try and run it from my script it spits out errors? What the
# actual fucking fuck, bash? Oh, and you too, ImageMagick, for wonky usage of
# command-line arguments and non-useful error messages. QQ.
#${command}
echo "${command}"
