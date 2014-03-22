# -*- cmake -*-

# Find libconfig++

find_path(LIBCONFIG++_INCLUDE_DIR libconfig.h++)
find_library(LIBCONFIG++_LIBRARY config++)
if (LIBCONFIG++_INCLUDE_DIR AND LIBCONFIG++_LIBRARY)
	set(LIBCONFIG++_FOUND TRUE)
endif (LIBCONFIG++_INCLUDE_DIR AND LIBCONFIG++_LIBRARY)
