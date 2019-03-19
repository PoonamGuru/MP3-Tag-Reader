#include"main.h"


/* Name : Operation_type
 * Input : argv, argc
 * Outptut : OP_SUCCESS/ OP_FAILURE
 * Discription : check the type of operation to be performed
 */

OP_STATUS  operation_type( int argc , char ** argv)
{
    /*no arguement was passed*/
    if(argc == 1)
    {
	printf("ERROR : Insufficient arguements \n");
	printf("USAGE : ./mp3_tag_reader -h --- help\n");
	printf("USAGE: ./mp3_tag_reader -v  <xxx.mp3> ---- to view the id3 tag details\n");
	printf("USAGE: ./mp3_tag_reader -e <.mp3 file> <modifier>  <modifername>-------------to edit the tad detail\n");

	return OP_FAILURE ;
    }


    /*help menu*/
    if( strcmp(argv[1], "-h") == 0 )
    {
	return OP_HELP;
    }

    /* alway 2nd arguement should be start with '-'*/
    if ( argv[1][0] != '-')
    {
	printf("ERROR : Insufficient arguements \n");
	printf("ERROR : no option given\n");
	printf("USAGE : please enter -h for help\n");

	return OP_FAILURE;
    }

    /* if .mp3 file is not given */
    if(argv[2] == NULL)
    {
	printf("ERROR : Insufficient arguements \n");
	printf("ERROR : mp3 file is not  given\n");
	printf("USAGE : please enter -h for help\n");
	return OP_FAILURE;
    }

    /*edit operation*/
    if(strcmp(argv[1],"-e") == 0)
    {
	if ( argv[3] == NULL)
	{
	    printf("ERROR : Insufficient arguements \n");
	    printf("ERROR : Number of option need to be Modify is not given \n");
	    printf("USAGE : please enter -h for help\n");
	    return OP_FAILURE;
	}

	else  if ( argv[4] == NULL)
	{
	    printf("ERROR : Insufficient arguements \n");
	    printf("ERROR : Number of option need to be Modify is not given \n");
	    printf("USAGE : please enter -h for help\n");
	    return OP_FAILURE;
	}

	return OP_EDIT;
    }


    /*view operation */
    if ( strcmp(argv[1] , "-v" ) == 0 )
    {
	return OP_READ;
    }

    else
    {
	puts("ERROR : Unsupported");
	puts("ERROR : Enter the proper option");
	puts("INFO : please enter -h for help");
	return OP_FAILURE;
    }

}

/* Name : check_extension
 * Input : file_name
 * Outptut : SUCCESS/ FAILURE
 * Discription : check the extension of the file is .mp3
 */
int check_extension(const char * file_name)
{
    int i = 0;
    /*checking the file extension*/
    while((file_name[i] != '.') && (file_name[i] != '\0'))
	i++;
    if(strcmp((file_name+i),".mp3") != 0)
    {
	printf("ERROR : enter the file name with extension .mp3\n");
	return FAILURE;
    }
    else
    {
	printf("INFO : correct FILE EXTENSION\n");
	return SUCCESS;
    }

}

/* Name : open_file
 * Input : file_name, mode
 * Outptut : SUCCESS/ FAILURE
 * Discription : open the file in the specified mode
 */

FILE * open_file(const char * file_name,const char * mode)
{
    FILE * fptr1 = fopen(file_name, mode);

    if(fptr1 == NULL)
    {
	perror("fopen");
	printf("ERROR : %s is not openned successfully\n",file_name);
	return NULL;
    }

    else
    {
	printf("INFO : %s is opened successfully\n", file_name);
	return fptr1;
    }

}
/* Name : check_extension
 * Input : file_name
 * Outptut : SUCCESS/ FAILURE
 * Discription : check the extension of the file is .mp3
 */


