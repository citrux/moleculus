PROG=bin/moleculus
CC=g++
ENGINE=$(PWD)/bin/libwrench-`uname -m`.so
CFLAGS=-lGL -lGLU -lm $(ENGINE)
LOGICS=logics
SOURCES=moleculus.cpp $(LOGICS)/main.cpp $(LOGICS)/configure.cpp \
	$(LOGICS)/physics.cpp $(LOGICS)/special.cpp

OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(PROG): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	strip -s $(PROG)

%.o: %.cpp %.d
	$(CC) -c $< -o $@

%.d: %.cpp
	@set -e; $(CC) -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@
	
clean:
	$(RM) $(PROG) $(OBJS) $(DEPS)
	$(RM) *~
	$(RM) config.txt

-include $(DEPS)
