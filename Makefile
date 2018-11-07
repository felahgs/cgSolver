    CC     = gcc -std=c11 -g
    CFLAGS = 
    LFLAGS =

      PROG = cgSolver
      OBJS = utils.o \
             geraMat.o \
             validateEntry.o \
             $(PROG).o

.PHONY: limpa faxina clean distclean purge all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)
	
all: $(PROG) doc
	
doc: Doxyfile
	doxygen $<

Doxyfile:
	doxygen -g
	sed -e "s;OPTIMIZE_OUTPUT_FOR_C *= *.*;OPTIMIZE_OUTPUT_FOR_C = YES;g" $@ >$@.new
	sed -e "s;EXTRACT_ALL *= *.*;EXTRACT_ALL = YES;g" $@.new >$@
	sed -e "s;EXTRACT_PRIVATE *= *.*;EXTRACT_PRIVATE = YES;g" $@ >$@.new
	sed -e "s;EXTRACT_STATIC *= *.*;EXTRACT_STATIC = YES;g" $@.new >$@
	sed -e "s;EXTRACT_LOCAL_METHODS *= *.*;EXTRACT_LOCAL_METHODS = YES;g" $@ >$@.new
	sed -e "s;GENERATE_LATEX *= *.*;GENERATE_LATEX = NO;g" $@.new >$@
	sed -e "s;SOURCE_BROWSE *= *.*;SOURCE_BROWSE = YES;g" $@ >$@.new
	sed -e "s;VERBATIM_HEADER *= *.*;VERBATIM_HEADER = YES;g" $@.new >$@
	rm -f $@.new
	
clean:
	rm -rf *~ *.bak

purge: clean
	rm -rf Doxyfile html latex
	rm -f *.o $(PROG)
