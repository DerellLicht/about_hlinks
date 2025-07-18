USE_64BIT = NO
USE_UNICODE = NO
USE_CLANG = NO
# use -static for clang and cygwin/mingw
USE_STATIC = NO

#  clang++ vs tdm g++
#  clang gives *much* clearer compiler error messages...
#  However, programs built with clang++ will require libc++.dll.
#  in order to be used elsewhere.
#  That is why the executable files are smaller than TDM ...
ifeq ($(USE_64BIT),YES)
TOOLS=d:\tdm64\bin
else
ifeq ($(USE_CLANG),YES)
TOOLS=d:\clang\bin
else
TOOLS=d:\tdm32\bin
endif
endif

ifeq ($(USE_DEBUG),YES)
CFLAGS=-Wall -O -g
LFLAGS=
else
CFLAGS=-Wall -O3
LFLAGS=-s
endif
CFLAGS += -Wno-write-strings
CFLAGS += -Weffc++

# link application-specific sources
CSRC=about_hlinks.cpp about.cpp hyperlinks.cpp

OBJS = $(CSRC:.cpp=.o) rc.o

BIN=about_hlinks
BINX=$(BIN).exe

#************************************************************
%.o: %.cpp
	$(TOOLS)/g++ $(CFLAGS) -Weffc++ -c $< -o $@

all: $(BINX)

clean:
	rm -f *.exe *.zip *.bak $(OBJS)

dist:
	rm -f *.zip
	zip $(BIN).zip $(BIN).exe readme.md LICENSE

lint:
	cmd /C "c:\lint9\lint-nt +v -width(160,4) -ic:\lint9 -ider_libs mingw.lnt -os(_lint.tmp) lintdefs.cpp $(CSRC)"

depend:
	makedepend $(CFLAGS) $(CSRC)

#************************************************************

$(BIN).exe: $(OBJS)
	$(TOOLS)/g++ $(CFLAGS) -mwindows -s $(OBJS) -o $@

#	\\InnoSetup5\iscc /Q winagrams.iss

rc.o: about_hlinks.rc
	$(TOOLS)\windres $< -O coff -o $@

# DO NOT DELETE

about_hlinks.o: version.h resource.h
about.o: resource.h version.h hyperlinks.h
hyperlinks.o: iface_32_64.h hyperlinks.h
