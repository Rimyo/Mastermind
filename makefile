
Mastermind: controller.o jeu.o vue.o mastermind.o combinaison.o stat-essai.o
	gcc combinaison.o stat-essai.o controller.o jeu.o vue.o mastermind.o -o Mastermind `pkg-config gtk+-3.0 --libs`

jeu.o: jeu.c controller.h 
	gcc -Wall -c jeu.c -o jeu.o `pkg-config gtk+-3.0 --cflags`

controller.o: controller.c controller.h vue.h 
	gcc -Wall -c controller.c -o controller.o `pkg-config gtk+-3.0 --cflags`

mastermind.o: mastermind.c mastermind.h combinaison.h stat-essai.h
	gcc -Wall -c mastermind.c -o mastermind.o `pkg-config gtk+-3.0 --cflags`
	
combinaison.o: combinaison.c combinaison.h
	gcc -Wall -c combinaison.c -o combinaison.o `pkg-config gtk+-3.0 --cflags`

stat-essai.o: stat-essai.c stat-essai.h
	gcc -Wall -c stat-essai.c -o stat-essai.o `pkg-config gtk+-3.0 --cflags`

vue.o: vue.c vue.h mastermind.h
	gcc -Wall -c vue.c -o vue.o `pkg-config gtk+-3.0 --cflags`

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf *.exe
