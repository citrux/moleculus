PROG=moleculus
CC=g++
LOGICS=logics
SOURCES=moleculus.cpp $(LOGICS)/special.cpp $(LOGICS)/system.cpp \
	$(LOGICS)/physics.cpp
LDCONFIG=-std=c++11
ifeq ($(shell uname -s),Linux)
	CFLAGS=-lGL -lGLU -lglut -lm
else
	CFLAGS+=-lopengl32 -lglu32 -lglut32 -lm
endif

OBJS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(PROG): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	strip -s $(PROG)

%.o: %.cpp %.d
	$(CC) $(LDCONFIG) -c $< -o $@

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
