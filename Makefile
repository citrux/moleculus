PROG=moleculus
CC=g++
LOGICS=logics
SOURCES=moleculus.cpp $(LOGICS)/special.cpp $(LOGICS)/system.cpp \
	$(LOGICS)/physics.cpp
CFLAGS=-Wall -O3
LDCONFIG=-std=c++11
ifeq ($(shell uname -s),Linux)
	CFLAGS+=-lGL -lGLU -lglut -lm
	EXT=
else
	CFLAGS+=-lopengl32 -lglu32 -lfreeglut -lm
	EXT=.exe
endif

OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(PROG): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	strip -s $(PROG)$(EXT)

%.o: %.cpp %.d
	$(CC) $(LDCONFIG) -c $< -o $@

%.d: %.cpp
	@set -e; $(CC) -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@
	
clean:
	$(RM) $(PROG)$(EXT) $(OBJS) $(DEPS)
	$(RM) *~
	$(RM) config.txt

-include $(DEPS)
