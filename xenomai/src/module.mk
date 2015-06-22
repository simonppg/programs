CURRENT_C		= $(shell find -name "sistema.c")
CURRENT_O 		= $(patsubst ./$(SRCDIR)/%,./$(BUILDDIR)/%,$(CURRENT_C:.$(SRCEXT)=.$(OBJEXT)))
XENOMAI_FLAGS 	= -I/usr/xenomai/include
XENOMAI_LIBS 	= -L/usr/xenomai/lib -lxenomai -lnative
$(CURRENT_O): CFLAGS+= $(XENOMAI_FLAGS)
$(TARGET): LIB += $(XENOMAI_LIBS)