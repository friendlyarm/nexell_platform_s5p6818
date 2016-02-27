ifndef	JOBS
JOBJS	:= 8
endif

DIR		:= 
######################################################################
# Build options

# Multi Media Libraries
DIR += libion
DIR += libnxmalloc
DIR += libnxv4l2
DIR += libnxvpu
DIR += libnxscaler

# I/O Wrapper
DIR += libcec

# Etc Libraries
DIR += libnxuevent

######################################################################
# Build
all:
	@for dir in $(DIR); do			\
	make -C $$dir || exit $?;		\
	make -C $$dir install; 			\
	done

clean:
	@for dir in $(DIR); do			\
	make -C $$dir clean || exit $?;	\
	done

distclean:
	@for dir in $(DIR); do			\
	make -C $$dir distclean || exit $?;	\
	done
