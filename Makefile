DESTDIR ?= /usr/local

all: tr2cyr

README: README.7
	mandoc -Tascii $< | col -b > $@

install: tr2cyr
	install -d ${DESTDIR}/bin ${DESTDIR}/share/man/man1
	install -m755 tr2cyr ${DESTDIR}/bin
	install -m644 tr2cyr.1 ${DESTDIR}/share/man/man1

uninstall:
	${RM} ${DESTDIR}/bin/tr2cyr ${DESTDIR}/share/man/man1/tr2cyr.1

clean:
	${RM} tr2cyr
