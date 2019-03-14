SUBDIRS = fdbcli
bin_PROGRAMS = paradox pktool

paradox_SOURCES = main.cpp md5.c pack.cpp pipeline.cpp transform.cpp \
fdb_cli.cpp pack_cli.cpp pipe_cli.cpp net_cli.cpp data_cli.cpp json.cpp

paradox_CXXFLAGS = $(MAGICKXX_CFLAGS) -std=c++14
paradox_LDADD    = $(MAGICKXX_LIBS) -lz -lassembly -ltinyxml2
paradox_LDFLAGS  = -g

pktool_SOURCES = pktool.cpp
pktool_CXXFLAGS = -std=c++17
pktool_LDADD = -lz -lassembly
pktool_LDFLAGS  = -g
