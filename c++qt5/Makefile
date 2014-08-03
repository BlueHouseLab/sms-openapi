all: sendsms result

sendsms: Makefile.sendsms sendsms.cpp conf.h
	make -f $<

Makefile.sendsms: sendsms.pro
	qmake -unix -o $@ $<

result: Makefile.result result.cpp conf.h
	make -f $<

Makefile.result: result.pro
	qmake -unix -o $@ $<

clean:
	make -f Makefile.sendsms distclean
	make -f Makefile.result distclean
