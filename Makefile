tres: obj/tres_raya.o obj/funciones.o
	gcc -o tres_raya obj/tres_raya.o obj/funciones.o

obj/tres_raya.o: src/tres_raya.c src/tres_raya.h
	gcc -c src/tres_raya.c -o obj/tres_raya.o

obj/funciones.o: src/funciones.c src/tres_raya.h
	gcc -c src/funciones.c -o obj/funciones.o

clean:
	del obj/tres_raya.o
