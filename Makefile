DESTDIR ?= /usr/local

CFLAGS.tr2cyr += -DEXEC

OBJS += tr2cyr.o
OBJS.tr2cyr += tr2cyr_exec.o


all: tr2cyr tr2cyr.a tr2cyr.so

tr2cyr tr2cyr.a tr2cyr.so: ${OBJS}
tr2cyr: ${OBJS.tr2cyr}

tr2cyr.c tr2cyr_exec.c: tr2cyr.h

.SUFFIXES: .o .a
.o.a:
	${AR} rcs $@ $^

.SUFFIXES: .o .so
.o.so:
	${LD} -shared -o $@ ${LDFLAGS} ${LDLIBS} $^

README: README.7
	mandoc -Tascii $< | col -b > $@

clean:
	${RM} tr2cyr tr2cyr.a tr2cyr.so ${OBJS} ${OBJS.tr2cyr}


.PHONY: install
install: install_bin install_lib install_man1 install_man3

.PHONY: install_bin
install_bin: tr2cyr
	install -d ${DESTDIR}/bin
	install -m755 tr2cyr ${DESTDIR}/bin

.PHONY: install_lib
install_lib: tr2cyr.a tr2cyr.so
	install -d ${DESTDIR}/lib ${DESTDIR}/include
	install -m644 tr2cyr.a ${DESTDIR}/lib
	install -m755 tr2cyr.so ${DESTDIR}/lib
	install -m644 tr2cyr.h ${DESTDIR}/include

.PHONY: install_man1
install_man1:
	install -d ${DESTDIR}/share/man/man1
	install -m644 tr2cyr.1 ${DESTDIR}/share/man/man1

.PHONY: install_man3
install_man3:
	install -d ${DESTDIR}/share/man/man3
	install -m644 tr2cyr.3 ${DESTDIR}/share/man/man3


.PHONY: uninstall
uninstall: uninstall_bin uninstall_lib uninstall_man1 uninstall_man3

.PHONY: uninstall_bin
uninstall_bin:
	${RM} ${DESTDIR}/bin/tr2cyr

.PHONY: uninstall_lib
uninstall_lib:
	${RM} ${DESTDIR}/lib/tr2cyr.a ${DESTDIR}/lib/tr2cyr.so ${DESTDIR}/include/tr2cyr.h

.PHONY: uninstall_man1
uninstall_man1:
	${RM} ${DESTDIR}/share/man/man1/tr2cyr.1

.PHONY: uninstall_man3
uninstall_man3:
	${RM} ${DESTDIR}/share/man/man1/tr2cyr.3
