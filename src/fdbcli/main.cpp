#include <assembly/fdb_io.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

#include <readline/readline.h>

#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace assembly::database::io;

const int TT_EOF = -2;
const int TT_ERROR = -1;

const int TT_SQL_SELECT = 0;
const int TT_SQL_FROM = 1;
const int TT_SQL_WHERE = 2;
const int TT_SQL_GROUP = 3;
const int TT_SQL_BY = 4;
const int TT_SQL_HAVING = 5;
const int TT_SQL_ORDER = 6;
const int TT_SQL_ASC = 7;
const int TT_SQL_DESC = 8;

const int TT_SQL_L = 10; // <
const int TT_SQL_LT = 11; // <=
const int TT_SQL_EQ = 12; // =
const int TT_SQL_GT = 13; // >=
const int TT_SQL_G = 14; // >
const int TT_SQL_NE = 15; // <>

const int TT_SQL_TIMES = 20; // *
const int TT_SQL_PLUS = 21; // +
const int TT_SQL_MINUS = 22; // -
const int TT_SQL_SLASH = 23; // /
const int TT_SQL_COMMA = 24; // ,

const int TT_SQL_DOT = 25; // .
const int TT_SQL_STRING = 26; // [a-zA-Z_]+
const int TT_SQL_TEXT = 27; // "[a-zA-Z_]+"
const int TT_SQL_FIELD = 28; // '[a-zA-Z_]+'

// tokenizer states
const int TS_SQL_ERR = -2;
const int TS_SQL_DONE = -1;
const int TS_SQL_INIT = 0;
const int TS_SQL_S = 1;
const int TS_SQL_F = 2;
const int TS_SQL_W = 3;
const int TS_SQL_G = 4;
const int TS_SQL_B = 5;
const int TS_SQL_H = 6;
const int TS_SQL_O = 7;
const int TS_SQL_A = 8;
const int TS_SQL_D = 9;

const int TS_SQL_STR = 30;

#define is_letter(C) 'A' <= C && C <= 'Z' || 'a' <= C && C <= 'z'

#define t_accept(c,s,t,v,r) case c: s=t; v++; r++; \
    /*printf("Accept: %c\n", c);*/ break
#define t_skip t_accept
#define t_return(CHAR,TOKEN,CURSOR) case CHAR: CURSOR++; return TOKEN

#define t_complete_if(LEN, INP, VAL, ST, TK, FS) \
{ \
    INP += LEN; VAL += LEN; \
    bool b = is_letter(*INP); \
    /*printf("Complete! [%c] %d \n", *INP, b); */\
    if (b) { ST=FS; } else { /*printf("Else %d\n", TK);*/ return TK; } \
}

#define t_complete(TS,STR,INP,VAL,ST,TK,FS) \
    case TS: \
        if (strcmp(INP, STR) >= 0) \
            t_complete_if(sizeof(STR) - 1, INP, VAL, ST, TK, FS) \
            else { ST=FS; } break;

int next_token(char** cursor, char** text)
{
    *text = 0;
    char* start = (*cursor);
    int len = 0;

    int state = TS_SQL_INIT;
    do
    {
        switch (state)
        {
            case TS_SQL_INIT:
            switch (**cursor)
            {
                t_accept('S', state, TS_SQL_S, len, (*cursor));
                t_accept('F', state, TS_SQL_F, len, (*cursor));
                t_accept('W', state, TS_SQL_W, len, (*cursor));
                t_accept('G', state, TS_SQL_G, len, (*cursor));
                t_accept('B', state, TS_SQL_B, len, (*cursor));
                t_accept('H', state, TS_SQL_H, len, (*cursor));
                t_accept('O', state, TS_SQL_O, len, (*cursor));
                t_accept('A', state, TS_SQL_A, len, (*cursor));
                t_accept('D', state, TS_SQL_D, len, (*cursor));
                t_return('=', TT_SQL_EQ,    (*cursor));
                t_return('*', TT_SQL_TIMES, (*cursor));
                t_return('+', TT_SQL_PLUS,  (*cursor));
                t_return('-', TT_SQL_MINUS, (*cursor));
                t_return('/', TT_SQL_SLASH, (*cursor));
                t_return(',', TT_SQL_COMMA, (*cursor));
                t_skip(' ', state, TS_SQL_INIT, start, (*cursor));
                case 0: return TT_EOF;
                default:
                if (is_letter(**cursor))
                {
                    len++; (*cursor)++;
                    state = TS_SQL_STR;
                }
                else return TT_ERROR;
            }
            break;
            t_complete(TS_SQL_S, "ELECT", (*cursor), len, state, TT_SQL_SELECT, TS_SQL_STR);
            t_complete(TS_SQL_F, "ROM", (*cursor), len, state, TT_SQL_FROM, TS_SQL_STR);
            t_complete(TS_SQL_W, "HERE", (*cursor), len, state, TT_SQL_WHERE, TS_SQL_STR);
            t_complete(TS_SQL_G, "ROUP", (*cursor), len, state, TT_SQL_GROUP, TS_SQL_STR);
            t_complete(TS_SQL_B, "Y", (*cursor), len, state, TT_SQL_BY, TS_SQL_STR);
            t_complete(TS_SQL_H, "AVING", (*cursor), len, state, TT_SQL_HAVING, TS_SQL_STR);
            t_complete(TS_SQL_O, "RDER", (*cursor), len, state, TT_SQL_ORDER, TS_SQL_STR);
            t_complete(TS_SQL_A, "SC", (*cursor), len, state, TT_SQL_ASC, TS_SQL_STR);
            t_complete(TS_SQL_D, "ESC", (*cursor), len, state, TT_SQL_DESC, TS_SQL_STR);
            case TS_SQL_STR:
            if (is_letter(**cursor))
            {
                len++; (*cursor)++;
            }
            else
            {
                char* data = (char*) malloc(len);
                strncpy(data, start, len); data[len] = 0;
                *text = data;
                return TT_SQL_STRING;
            }
            break;
        }
    }
    while (state >= TS_SQL_INIT);
    return 0;
}

int main(int argc, char** argv)
{
    off_t fsize;

    if (argc < 1)
    {
        printf("Usage: paradox-fdbcli <file>\n");
        return 1;
    }

    printf("Loading file: %s\n", argv[1]);
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        printf("Failed to load file!\n");
        return 1;
    }

    fsize = lseek(fd, 0, SEEK_END);
    printf("File size: %d\n", fsize);

    void* mapped = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (mapped == MAP_FAILED)
    {
        printf("Map failed!\n");
        return 1;
    }

    char* data = (char*) mapped;

    schema_header* header = (schema_header*) data;
    printf("Schema [%d]\n", header->table_count);

    table_header_entry* table_headers = (table_header_entry*) (data + header->table_header_addr);
    for (int i = 0; i < header->table_count; i++)
    {
        column_header* c_header = (column_header*) (data + table_headers[i].column_header_addr);
        row_top_header* rt_header = (row_top_header*) (data + table_headers[i].row_top_header_addr);

        char* t_name = data + c_header->table_name_addr;

        //printf("Table: %s [%d]\n", t_name, c_header->column_count);
    }

    char* line = readline("SQL> ");
    char* txt = line;
    char* str = 0;

    int token = 0;
    do
    {
        token = next_token(&txt, &str);
        switch (token)
        {
            case TT_SQL_SELECT: printf("> SELECT\n"); break;
            case TT_SQL_WHERE: printf("> WHERE\n"); break;
            case TT_SQL_FROM: printf("> FROM\n"); break;
            case TT_SQL_TIMES: printf("> *\n"); break;
            case TT_SQL_COMMA: printf("> ,\n"); break;
            case TT_SQL_EQ: printf("> =\n"); break;
            case TT_SQL_STRING: printf("> %s\n", str); break;
            case TT_EOF: printf("EOF\n"); break;
            default: printf("> %d\n", token); break;
        }
        if (str != 0) free(str);
    }
    while (token >= 0);

    free(line);

    munmap(mapped, fsize);

    return 0;
}
