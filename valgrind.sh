#!/bin/sh

echo "###\n### Teil 1: korrekte Aufrufe \n###"
echo "Prüfe Beispiel Berge"
2>&1 valgrind --log-file=berge.log ./puzzle berge_puzzleteil3.pgm berge_puzzleteil1.pgm berge_puzzleteil2.pgm v.pgm
grep -qE "([^0]|[0-9]0) bytes in" berge.log &&  echo "\t... Speicherleck bei ./puzzle berge_puzzleteil3.pgm berge_puzzleteil1.pgm berge_puzzleteil2.pgm v.pgm gefunden. Details in Datei berge.log." || echo "\t ...OK\n"

echo "Prüfe Beispiel Muenzen"
2>&1 valgrind --log-file=muenzen.log ./puzzle muenzen_puzzleteil3.pgm muenzen_puzzleteil1.pgm muenzen_puzzleteil2.pgm muenzen_puzzleteil5.pgm muenzen_puzzleteil4.pgm v.pgm
grep -qE "([^0]|[0-9]0) bytes in" muenzen.log &&  echo "\t... Speicherleck bei ./puzzle muenzen_puzzleteil3.pgm muenzen_puzzleteil1.pgm muenzen_puzzleteil2.pgm muenzen_puzzleteil5.pgm muenzen_puzzleteil4.pgm v.pgm gefunden. Details in Datei muenzen.log." || echo "\t ...OK\n"


echo "###\n### Teil 2: falsche Aufrufe \n###"

echo "Prüfe Inputdatei nicht vorhanden"
2>&1 valgrind --log-file=noinput.log ./puzzle NOTTHERE v.pgm > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" noinput.log &&  echo "\t... Speicherleck wenn Input nicht vorhanden! Details in Datei noinput.log." || echo "\t...Speicher: OK"
./puzzle NOTTHERE v.pgm >/dev/null
if [ $? -eq 2 ]
	then echo "\t...Rückgabe: OK\n"
	else echo "\t...Rückgabewert stimmt nicht.\n"
fi

echo "Prüfe Ausgabedatei darf nicht geschrieben werden"
touch v_bad.pgm
chmod 444 v_bad.pgm
2>&1 valgrind --log-file=badoutput.log ./puzzle input1.pgm v_bad.pgm > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" badoutput.log &&  echo "\t... Speicherleck wenn Outputdatei nicht geschrieben werden kann! Details in Datei badoutput.log." || echo "\t...Speicher: OK"
./puzzle input1.pgm v_bad.pgm >/dev/null
if [ $? -eq 2 ]
	then echo "\t...Rückgabe: OK\n"
	else echo "\t...Rückgabewert stimmt nicht.\n"
fi


echo "Prüfe zu wenig Parameter"
2>&1 valgrind --log-file=missingparams.log ./puzzle berge_puzzleteil1.pgm > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" missingparams.log &&  echo "\t... Speicherleck wenn zu wenige Parameter übergeben werden! Details in Datei missingparams.log." || echo "\t...Speicher: OK"
./puzzle berge_puzzleteil1.pgm  >/dev/null
if [ $? -eq 1 ]
	then echo "\t...Rückgabe: OK\n"
	else echo "\t...Rückgabewert stimmt nicht.\n"
fi

rm v.pgm
rm -f v_bad.pgm

