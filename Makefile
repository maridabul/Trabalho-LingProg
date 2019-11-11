CPP=g++
CPPFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
LD=g++
LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)

# -I $PWD

all: programa

#programa: menu.o perlWrapper.o interface.o
programa: main.o perlWrapper.o menu.o interface.o
	$(LD) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CPP)  -o $@ -c $<  $(CPPFLAGS)

clean:
	rm -f programa *.o
