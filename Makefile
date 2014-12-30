OPT=-g -Wall

TOT=pendol_int lorenz_int rtbps_int apartat3 apartat6 mani_rtbp

tot : $(TOT)

# ==========
# Utilitats
# ==========

pendol_int : pendol_int.c pendol.o flux.o rk78.o
	gcc -o pendol_int $(OPT) pendol_int.c pendol.o flux.o rk78.o -lm

lorenz_int : lorenz_int.c lorenz.o flux.o rk78.o
	gcc -o lorenz_int $(OPT) lorenz_int.c lorenz.o flux.o rk78.o -lm

rtbps_int : rtbps_int.c rtbps.o flux.o rk78.o
	gcc -o rtbps_int $(OPT) rtbps_int.c rtbps.o flux.o rk78.o -lm

apartat3 : apartat3.c rtbps.o flux.o rk78.o
	gcc -o apartat3 $(OPT) apartat3.c rtbps.o flux.o rk78.o -lm

apartat6 : apartat6.c cmani.o pendol.o sislin.o flux.o rk78.o
	gcc -o apartat6 $(OPT) apartat6.c cmani.o pendol.o sislin.o flux.o rk78.o -lm

cmani_rtbp : cmani_rtbp.c cmani.o rtbps.o sislin.o flux.o rk78.o
	gcc -o cmani_rtbp $(OPT) cmani_rtbp.c cmani.o rtbps.o sislin.o flux.o rk78.o -lm

# ========
# Rutines
# ========

rk78.o : rk78.c
	gcc -c $(OPT) rk78.c

flux.o : flux.c
	gcc -c $(OPT) flux.c

sislin.o : sislin.c
	gcc -c $(OPT) sislin.c

cmani.o : cmani.c
	gcc -c $(OPT) cmani.c -lm

pendol.o : pendol.c
	gcc -c $(OPT) pendol.c -lm

lorenz.o : lorenz.c
	gcc -c $(OPT) lorenz.c

rtbps.o : rtbps.c
	gcc -c $(OPT) rtbps.c

#========
# Neteja
#========

clean : 
	rm -f *.o

realclean : clean
	rm -f $(TOT)
