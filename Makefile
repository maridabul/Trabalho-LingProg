CPP=g++
CPPFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LD=g++
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)


all: programa

programa: perlWrapper.o
#programa: main.o perlWrapper.o menu.o interface.o
	$(LD) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CPP)  -o $@ -c $<  $(CPPFLAGS)

clean:
	rm -f programa *.o
