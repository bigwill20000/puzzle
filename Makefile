compile: main.c puzzle.c pgm.c
	#kompiliere mit den Parametern zum Debuggen, Anzeigen aller Warnings so 
	# dass die Aufrufe beim Target testausgabe funktionieren und mit dem Standard c99. 
	gcc -g --std=c99 -Wall -o puzzle main.c puzzle.c pgm.c

clean: # TODO: loesche die ausfuehrbare Datei und alle Testausgabedateien
	rm -f puzzle
	rm -f test_berge_out.pgm test_hhu_out.pgm test_muenzen_out.pgm
	rm -f *.log

diff: compile
	@sh diff.sh

valgrind: compile valgrind.sh
	@sh valgrind.sh




