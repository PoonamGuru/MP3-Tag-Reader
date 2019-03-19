#include"main.h"


RETURN_VAL View_Edit(FILE * fp, tag_info * tag , char ** argv, flag_t * NF_flag)
{
    u_int cur_pos =ftell(fp);
    u_int tag_size ;
    char * frame_idnt;
    char ch;

    /*get the tag_size */
    tag_size = get_tag_size(fp);  //get the size of tag
    //    printf("tag_size = %x\n", tag_size);


    cur_pos = ftell(fp);
    //printf("after tagsize %d\n",cur_pos);

    while(cur_pos <= tag_size)
    {

	ch = fgetc(fp); //read each character

	if( ch == 'T')
	{
	    frame_idnt = get_frame_identifier(fp , ch); //get the frame identifier
	    //puts(file_idnt);
	    if(read_write_frame(frame_idnt , fp ,tag ,  argv, NF_flag) != SUCCESS) return FAILURE; 
	}

	else if(ch == 'C')
	{

	    frame_idnt = get_frame_identifier(fp , ch); //get the frame identifier
	    //	    puts(frame_idnt); 
	    //	    fseek(fp,-3,SEEK_CUR);
	    if(read_write_frame(frame_idnt , fp ,tag ,  argv, NF_flag) != SUCCESS) return FAILURE; 
	}

	else if(ch == 'A')
	{
	    frame_idnt = get_frame_identifier(fp , ch); //get the frame identifier
	    fseek(fp,-3,SEEK_CUR);
//	    	    puts(frame_idnt); 
	    if(read_write_frame(frame_idnt , fp ,tag ,  argv, NF_flag) != SUCCESS) return FAILURE; 
	}

	cur_pos = ftell(fp); // get the current position after parsing
    }

return SUCCESS;

}//endif rwf

