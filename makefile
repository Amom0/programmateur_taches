gestionnaire_tache.exe : gestionnaire_tache.o 
	gcc -o gestionnaire_tache.exe gestionnaire_tache.o
	./gestionnaire_tache.exe

gestionnaire_tache.o : gestionnaire_tache.c 
	gcc -c gestionnaire_tache.c