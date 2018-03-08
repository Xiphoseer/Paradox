#include "pipe_cli.hpp"

#include <getopt.h>

#include <sstream>
#include <iomanip>

#include "zlib_stream.hpp"
#include "sd0_stream.hpp"

#include "transform.hpp"


int verbose_flag;

int main_pipe(int argc, char** argv) {

	int c;
	int part = 0; // 0: in, 1: out

	InputStage* ipipe = new InitialInputStage();
	OutputStage* opipe = new InitialOutputStage();
	TransformStage* tpipe = nullptr;
	ManageStage* mpipe = nullptr;

	std::stringstream pipe;
	while (true) {
		static struct option long_options[] =
        {
			{"verbose",	 no_argument,	&verbose_flag, 'v'},
			{"brief",    no_argument,	&verbose_flag, 0},
			{"inflate",  no_argument,				0, 'i'},
			{"sd0",      no_argument, 				0, 's'},
			{"sd0c",     no_argument, 				0, 'S'},
			{"file",     required_argument,			0, 'f'},
			{"config", 	 no_argument,				0, 'c'},
			{"pki",      no_argument,				0, 'p'},
			{"manifest", optional_argument,			0, 'm'},
			{"md5",      no_argument,				0, '5'},
			{"checksd0", no_argument,				0, '0'},
			{"client",   required_argument,			0, 'l'},
			{0, 0, 0, 0}
		};

		int option_index = 0;
		c = getopt_long (argc, argv, "isf:cpm::v50lS", long_options, &option_index);

		if (c == -1) break;

		switch (c){
	        case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0)
	            	break;
	           	pipe << "option " << long_options[option_index].name;
				if (optarg)
					pipe << " with arg " << optarg;
				break;

	        case 'i':
				if (part == 0) {
					pipe << "Inflate >> ";
					ipipe = new GenericInputStage(ipipe, &create_inflate_stream<1024>);
				} else {
					std::cerr << "Cannot add inflate stage to output!" << std::endl;
					exit(2);
				}
				break;

	        case 's':
	        	if (part == 0) {
					pipe << "SD0 >> ";
					ipipe = new GenericInputStage(ipipe, &create_sd0_stream<1024>);
				} else {
					std::cerr << "Cannot add SD0 stage to output!" << std::endl;
					exit(2);
				}
				break;

			case 'S':
	        	part = 1;
				pipe << "Compress SD0 >> ";
				opipe = new GenericOutputStage(opipe, &create_sd0_ostream<1024>);
				break;

	        case 'f':
				if (part == 0) {
					pipe << "File(" << optarg << ") >>";
					ipipe = new DumpInputStage(ipipe, std::string(optarg));
				} else {
					std::cerr << "Output to file is not implemented yet!" << std::endl;
				}

				break;

	        case 'c':
	        	if (part == 0) {
					pipe << "Config >> ";
					tpipe = new ConfigTransformStage();
					part = 1;
				} else {
					std::cerr << "Cannot add Config transform to output!" << std::endl;
					exit(2);
				}
				break;

			case '0':
	        	if (part == 0) {
					pipe << "Check SD0 >> ";
					tpipe = new SD0TransformStage();
					part = 1;
				} else {
					std::cerr << "Cannot add SD0 Check transform to output!" << std::endl;
					exit(2);
				}
				break;

			case 'm':
	        	if (part == 0) {
					pipe << "Manifest >> ";
					tpipe = new ManifestTransformStage(optarg ? std::string(optarg) : "");
					part = 1;
				} else {
					std::cerr << "Cannot add Manifest transform to output!" << std::endl;
					exit(2);
				}
				break;

			case 'l':
	        	if (part == 0) {
					pipe << "ClientExtract >> ";
					tpipe = new ClientExtractorStage(optarg ? std::string(optarg) : "");
					part = 1;
				} else {
					std::cerr << "Cannot add ClientExtract transform to output!" << std::endl;
					exit(2);
				}
				break;

			case 'p':
	        	if (part == 0) {
					pipe << "PackIndex >> ";
					tpipe = new PackIndexTransformStage();
					part = 1;
				} else {
					std::cerr << "Cannot add pack index transform to output!" << std::endl;
					exit(2);
				}
				break;

			case '5':
				if (part == 0) {
					pipe << "MD5 >> ";
					tpipe = new MD5TransformStage();
					part = 1;
				} else {
					std::cerr << "Cannot add MD5 transform to output!" << std::endl;
					exit(2);
				}
				break;

	        case '?':
				/* getopt_long already printed an error message. */
				break;

			case 'v':
				verbose_flag = 1;
				break;

	        default:
				abort ();
	    }
	}

	pipe << "Standard Out";

	if (verbose_flag) std::cout << std::setw(10) << "Pipeline" << ": " << pipe.str() << std::endl;

	/* Print any remaining command line arguments (not options). */
  	std::vector<std::string> files;
	while (optind < argc) {
		std::string file(argv[optind++]);
		if (verbose_flag) std::cout << std::setw(10) << "File" << ": " << file << std::endl;
		files.push_back(file);
	}
	if (verbose_flag) std::cout << std::string(70, '-') << std::endl;

	if (tpipe == nullptr) {
		tpipe = new NoTransformStage();
	}

	if (tpipe != nullptr) {
		mpipe = new TransformManageStage(tpipe);
	}

	if (mpipe != nullptr) {
		mpipe->run(ipipe, opipe, files);
	}

	if (verbose_flag) std::cout << std::string(70, '-') << std::endl;
	return 0;
}
