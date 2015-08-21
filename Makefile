# $Id: Makefile,v 1.12 2014-05-08 18:32:56-07 - - $
#g++ -g -O0 -Wall -Wextra -std=gnu++11 -c Pong.cpp Paddle.cpp Paddle.h Net.cpp Net.h Ball.cpp Ball.h Blackhole.cpp Blackhole.h AI.cpp AI.h
#g++ Pong.o Paddle.o Net.o Ball.o Blackhole.o AI.o -o sfml-app -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
#./sfml-app

MKFILE        = Makefile
DEPFILE       = ${MKFILE}.dep
NOINCL        = ci clean spotless
NEEDINCL      = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE         = ${MAKE} --no-print-directory
COMPILECPP    = g++ -g -O0 -Wall -Wextra -std=gnu++11
AFTERCPP	  = g++ Pong.o Paddle.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
MAKEDEPCPP    = g++ -MM -std=gnu++11

MODULES       = Paddle
CPPHEADER     = ${MODULES:=.h}
CPPSOURCE     = ${MODULES:=.cpp} main.cpp
OTHERS        = ${MKFILE}
ALLSOURCES    = ${CPPHEADER} ${CPPSOURCE} ${OTHERS}
EXECBIN       = gdraw
OBJECTS       = ${CPPSOURCE:.cpp=.o}
LINKLIBS      = -lGL -lGLU -lglut -lm

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<
	${AFTERCPP}

ci : ${ALLSOURCES}
	cid + ${ALLSOURCES}

lis : ${ALLSOURCES}
	mkpspdf ${LISTING} ${ALLSOURCES} ${DEPFILE}

clean :
	- rm ${OBJECTS} ${DEPFILE} core ${GENFILES}

spotless : clean
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf}
	- rm ${EXECBINWIN} ${LISTING} ${LISTING:.ps=.pdf}

dep : ${CPPSOURCE} ${CPPHEADER} ${GENFILES}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

${DEPFILE} :
	@ touch ${DEPFILE}
	${GMAKE} dep

again :
	${GMAKE} spotless dep ci all lis

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif

