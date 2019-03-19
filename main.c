
#include"main.h"

int main(int argc , char ** argv)
{
    char file_name[20];   // to store the file name
    FILE * fp;            
    tag_info tag;        // tag is structure to hold the text info
    int i;
    md edt_mdf ;   //modifier

    flag_t NF_flag;

    OP_STATUS opt_type = operation_type(argc,argv);

    switch(opt_type)
    {
	case OP_HELP :
	    help_menu();
	    break;
	case OP_READ :
	    puts("------------------------------------------ID3 Tag information ------------------------");
	    if ( common_function(argv[2] , &tag, &fp, argv) != SUCCESS) return 1;
	    if( View_Edit(fp, &tag ,argv,&NF_flag) != SUCCESS) return 1;

	    display_tag_details(&tag, &NF_flag);



	    break;
	case OP_EDIT : 
	    puts("-------------------------------------------Edit the ID3------------------------------");
	    if ( common_function(argv[2] , &tag, &fp, argv) != SUCCESS) return 1;

	    //	  if(View_Edit(fp,&tag,argv) != SUCCESS ) return 1; 
	    if( View_Edit(fp, &tag ,argv,&NF_flag) != SUCCESS) return 1;

	    display_tag_details(&tag, &NF_flag);

	    break;

	case OP_FAILURE :
	    break;
    }












    return 0;
}



