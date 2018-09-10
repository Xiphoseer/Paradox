/* PKTOOL */

#include <assembly/cli.hpp>
#include <assembly/manifest.hpp>

#include <getopt.h>
#include <fnmatch.h>
#include <iostream>
#include <iomanip>
#include <cstdio>


int pktool_manifest(int argc, char** argv)
{
    int show_checksum = 0;
    int show_file_version = 0;
    int show_version = 0;
    int show_total = 1;

    const char* filter = 0;

    int c;

    while (true)
    {
        int option_index = 0;
        static struct option long_options[] =
        {
            {"show-checksum", no_argument, &show_checksum,  1 },
            {"hide-checksum", no_argument, &show_checksum,  0 },
            {"show-file-version", no_argument, &show_file_version,  1 },
            {"hide-file-version", no_argument, &show_file_version,  0 },
            {"show-version", no_argument, &show_version,  1 },
            {"hide-version", no_argument, &show_version,  0 },
            {"show-total", no_argument, &show_total,  1 },
            {"hide-total", no_argument, &show_total,  0 },

            {"filter", required_argument, 0, 'q' },
            {"search", required_argument, 0, 'q' },
            {"query", required_argument, 0, 'q' },

            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "cCfFvVtTq", long_options, &option_index);
        if (c == -1) break;

        switch (c)
        {
        case 0:
            printf("option %s", long_options[option_index].name);
            if (optarg)
                printf(" with arg %s", optarg);
            printf("\n");
            break;

        case 'c': show_checksum = 0; break;
        case 'C': show_checksum = 1; break;
        case 'f': show_file_version = 0; break;
        case 'F': show_file_version = 1; break;
        case 'v': show_version = 0; break;
        case 'V': show_version = 1; break;
        case 't': show_total = 0; break;
        case 'T': show_total = 1; break;

        case 'q': filter = optarg; break;

        case '?':
            break;

        default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind >= argc)
    {
        fprintf(stderr, "Usage: [options] <file> ... \n");
    }
    else
    {
        bool is_multiple = (argc > optind + 1);

        while (optind < argc)
        {
            assembly::manifest::manifest_file manifest;
            const char* filename = argv[optind++];

            if (is_multiple) std::cout << "====== " << filename << " ======" << std::endl;
            if (assembly::manifest::read_from_file(filename, manifest) == 0)
            {
                if (show_checksum)     std::cout << "check " << manifest.checksum     << std::endl;
                if (show_file_version) std::cout << "filev " << manifest.fileVersion  << std::endl;
                if (show_version)      std::cout << "mfver " << manifest.version      << std::endl;

                std::cout << std::left;

                const std::vector<assembly::manifest::manifest_entry>& list = manifest.query(filter);
                if (show_total) std::cout << "total " << list.size() << std::endl;

                for (const assembly::manifest::manifest_entry& entry: list)
                {
                    std::cout << std::setw(10) << entry.sizeA << std::setw(10) << entry.sizeB << entry.path << std::endl;
                }
            }
        }
    }

    return 0;
}

int pktool_help (int argc, char** argv);

cli::opt_t pktool_options[] =
{
    { "manifest", &pktool_manifest, "Read a manifest" },
    { "help",     &pktool_help,     "Show this help" },

    {0,0,0}
};

int pktool_help (int argc, char** argv)
{
    return cli::help("Pack Files", pktool_options, "LU PK File manipulation");
}

int main (int argc, char** argv)
{
    if (argc <= 1)
    {
        printf("Usage: <subcommand> ...\n");
        printf("       help\n");
        return 1;
    }

    return cli::call("pktool", pktool_options, argv[1], argc - 1, argv + 1);
}
