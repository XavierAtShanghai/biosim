#include "network_arts_conjuncs.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;
using namespace alger;

void print_usage (FILE* stream, int exit_code) {
	fprintf (stream, "Usage: bloodflow -i inputFolder -o dataFolder [-s string] [-q] [-v]\n");
	fprintf (stream,
			"-h --help	Display this usage information.\n"
			"-i --input	folderName Parameter files to initalize the computing.\n"
			"-o --output	folderName Write output to this folder.\n"
			"-s --suffix	string Suffix to the names of output files.\n"
			"-q --sequential sequential computing, otherwise using openMP.\n"
			"-v --verbose	Print verbose messages.\n");
	exit (exit_code);
}

int main(int argc, char* argv[])
{
    int next_option;
	/* A string listing valid short options letters. */
	const char* const short_options = "hi:o:s:vq";
	/* An array describing valid long options. */
	const struct option long_options[] = {
	{ "help", 0, NULL, 'h' },
	{ "output", 1, NULL, 'o' },
	{ "suffix", 1, NULL, 's' },
	{ "verbose", 0, NULL, 'v' },
	{ "sequential", 0, NULL, 'p' },
	{ NULL, 0, NULL, 0 }
	};  	/* Required at end of array. */

	/* The name of the file to receive program output */
    const char* input_folderName = NULL;
	const char* output_folderName = NULL;
    const char* suff_string = NULL;
    /* Whether to display verbose messages. */
    bool verbose = false;
    bool sequential = false;


	do {
	next_option = getopt_long (argc, argv, short_options, long_options, NULL);
	switch (next_option) {
		case 'h':   /* -h or --help */
		             /* User has requested usage information. Print it to standard
                    output, and exit with exit code zero (normal termination). */
		print_usage (stdout, 0);
        case 'i':
		input_folderName = optarg;
        break;

		case 'o':
		output_folderName = optarg;
		break;

        case 's':
		suff_string = optarg;
		break;

		case 'v':	 /* -v or --verbose */
		verbose = true;
		break;

       	case 'q':	 /* -v or --verbose */
		sequential = true;
        break;

		case '?':
		/* The user specified an invalid option. */
		/* Print usage information to standard error, and exit with exit
		code one (indicating abnormal termination). */
		print_usage (stderr, 1);
		case -1:
		break;
		/* Done with options.
		*/
		default:
		/* Something else: unexpected.*/
		abort ();
		}
	} while (next_option != -1);

    if (input_folderName == NULL || output_folderName == NULL)
        print_usage(stderr,1);
    printf("input folder: %s \n", input_folderName);
    printf("output folder: %s \n", output_folderName);
    printf("suffix string: %s \n", suff_string);
    printf("verbosel: %s \n",verbose? "Yes": "No");
    printf("sequential computing: %s \n", sequential? "Yes":"No");


    struct stat sb;
    if(stat(input_folderName, &sb) != 0 ) {
        printf("Error: no \"%s\" \n",input_folderName);
        exit(1);
        }
    else{
        if (!S_ISDIR(sb.st_mode)){
            printf("Error: \"%s\" exists, but not a foldoer\n",input_folderName);
            exit(1);
        }
      }

      if(stat(output_folderName, &sb) != 0 ) {
        printf("Error: no \"%s\"\n",output_folderName);
        exit(1);
        }
       else{
        if (!S_ISDIR(sb.st_mode)){
            printf("Error: \"%s\" exists, but not a foldoer\n",output_folderName);
            exit(1);
        }
      }


    network_arts_conjuncs net1(input_folderName);
    net1.set_dataFolder(output_folderName);
    if (suff_string != NULL) {
    net1.set_Adatafile("histA_"+string(suff_string)+".csv" );
    net1.set_Qdatafile("histQ_"+string(suff_string)+".csv" );
    net1.set_Pdatafile("histP_"+string(suff_string)+".csv" );
    }
    else {
    net1.set_Adatafile("histA.csv" );
    net1.set_Qdatafile("histQ.csv" );
    net1.set_Pdatafile("histP.csv" );
    }

    if (verbose) {
        net1.print();
        cout<<"press enter to continue or 0 to quit "<<endl;
        int flag = getchar();
        if(flag == '0')
        exit(0);
    }


    if(sequential )
        net1.run();
    else {
        net1.run_openMP();
        }
    return 0;
}

