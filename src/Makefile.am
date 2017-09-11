bin_PROGRAMS = paradox
paradox_SOURCES = catalog.cpp cdclient.cpp cli.cpp database.cpp fdb_cli.cpp filesystem.cpp main.cpp manifest.cpp md5.c pack.cpp pack_cli.cpp package.cpp pipeline.cpp transform.cpp trim.cpp

paradox_CXXFLAGS = -std=c++14 $(MAGICKXX_CFLAGS)
paradox_LDADD       = $(MAGICKXX_LIBS) -lz -lm -lstdc++

