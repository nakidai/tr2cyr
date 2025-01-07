DESTDIR ?= /usr/local

all: tr2cyr

README: README.7
	mandoc -Tascii $< | col -b > $@

install: tr2cyr
	install -d ${DESTDIR}/bin
	install -m755 tr2cyr ${DESTDIR}/bin

uninstall:
	${RM} ${DESTDIR}/bin/tr2cyr

clean:
	${RM} tr2cyr
