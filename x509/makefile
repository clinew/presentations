TARGET=presentation

default: pdf

dvi: ${TARGET}.tex 
#	run latex twice to get references correct
	latex ${TARGET}.tex
#	you can also have a bibtex line here
#	bibtex $(TARGET).tex
	latex $(TARGET).tex

ps: dvi
	dvips -R -Poutline ${TARGET}.dvi -o ${TARGET}.ps
#	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

pdf: ps
	ps2pdf ${TARGET}.ps
