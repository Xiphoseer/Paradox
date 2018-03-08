bin_PROGRAMS = paradox
paradox_SOURCES = main.cpp md5.c pack.cpp pipeline.cpp transform.cpp \
fdb_cli.cpp pack_cli.cpp pipe_cli.cpp net_cli.cpp

paradox_CXXFLAGS = $(MAGICKXX_CFLAGS) -std=c++14
paradox_LDADD    = $(MAGICKXX_LIBS) -lz -lassembly
paradox_LDFLAGS  = -g

