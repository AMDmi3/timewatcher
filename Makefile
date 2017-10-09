CC?=		gcc
CFLAGS?=	# none

PROG=		timewatcher

all: ${PROG}

${PROG}: ${PROG}.c
	${CC} ${CFLAGS} ${PROG}.c -o ${PROG}

clean:
	rm ${PROG}
