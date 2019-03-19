#include"main.h"

RETURN_VAL read_write_frame(char * frame_idnt , FILE * fp ,tag_info * tag ,  char **  argv, flag_t * NF_flag)
{

    u_int frame_size = 0;
    int backword;

    if(strcmp(frame_idnt , "TIT2") == 0)
    {
	get_frame_size(fp , &frame_size);  //get the frame_size

	if( W_Frame(fp , frame_size, argv, 't') == FAILURE) return FAILURE;
	//	printf("after write in rwfpos = %d\n",ftell(fp));
	strcpy(tag->ti_title , read_data(tag, fp ,  frame_size - 1));
	//	printf("title : ");
	//	puts(tag->ti_title);
	NF_flag->t =  1; 

    }
    /*signer info */
    else if( strcmp(frame_idnt, "TPE1") == 0)
    {
	get_frame_size(fp , &frame_size);  //get the frame_size
	//	W_Frame(fp , frame_size, argv, 'S');
	if( W_Frame(fp , frame_size, argv, 'S') == FAILURE) return FAILURE;
	strcpy(tag->ti_singer , read_data(tag, fp ,  frame_size - 1));
	//	printf("singer : ");
	//	puts(tag->ti_singer);
	NF_flag->S = 1;


    }
    /*year of release */   
    else if( strcmp(frame_idnt, "TYER") == 0)
    {
//	puts(frame_idnt);	
	get_frame_size(fp , &frame_size);  //get the frame_size
	//W_Frame(fp , frame_size, argv, 'Y');
	if( W_Frame(fp , frame_size, argv, 'Y') == FAILURE) return FAILURE;
	strcpy(tag->ti_year , read_data(tag, fp ,  frame_size - 1));
//	printf("year :");
//	puts(tag->ti_year);

	NF_flag->Y = 1;
    }
    /*track no in the album */
    else if( strcmp(frame_idnt, "TRCK") == 0)
    {

	get_frame_size(fp , &frame_size);  //get the frame_size
	//W_Frame(fp , frame_size, argv, 'T');
	if( W_Frame(fp , frame_size, argv, 'T') == FAILURE) return FAILURE;
	strcpy(tag->ti_track , read_data(tag, fp ,  frame_size - 1));
	//	printf("track : ");
	//	puts(tag->ti_track);
	NF_flag->T = 1;
    }
    /*album name*/
    else if( strcmp(frame_idnt, "TALB") == 0)
    {

	get_frame_size(fp , &frame_size);  //get the frame_size
	//	printf("alb fs = %d\n", frame_size);

	//W_Frame(fp , frame_size, argv, 'A');
	if( W_Frame(fp , frame_size, argv, 'A') == FAILURE) return FAILURE;
	strcpy(tag->ti_album , read_data(tag, fp ,  frame_size - 1));
	//	printf("album : ");
	//	puts(tag->ti_album);
	NF_flag->A = 1;
    }

    /*genre of the song*/
    else if( strcmp(frame_idnt, "TCON") == 0)
    {
	get_frame_size(fp , &frame_size);  //get the frame_size
	//	W_Frame(fp , frame_size, argv, 'G');
	if( W_Frame(fp , frame_size, argv, 'G') == FAILURE) return FAILURE;
	strcpy(tag->ti_genre , read_data(tag, fp ,  frame_size - 1));
//	printf("genre : ");
//	puts(tag->ti_genre);

	NF_flag->G  = 1;
    }
    /*comment on song*/
    else if( strcmp(frame_idnt, "COMM") == 0)
    {
//	puts(frame_idnt);
	get_frame_size(fp , &frame_size);  //get the frame_size
	fseek(fp,7,SEEK_CUR);
	strcpy(tag->ti_comment , read_data(tag , fp , frame_size - 5));
//	printf("comment :");
//	puts(tag->ti_comment);

	NF_flag->C = 1;
    }

    else if ( strcmp(frame_idnt , "APIC") == 0 )
    {
//	puts(frame_idnt);
	//	get_frame_size(fp , &frame_size);
	fseek(fp , 7, SEEK_CUR);
	strcpy(tag->ti_pic , read_data(tag, fp , 13));
	//	printf("pic type : ");
	//	puts(tag->ti_pic);

	NF_flag->P = 1;
    }

    return SUCCESS;
}
/* name : r_w_frame
 * input : fp 
 * output : void 
 * discription : read or write into the frame
 */
RETURN_VAL  W_Frame(FILE * fp , u_int frame_size , char ** argv , char idnt)
{
    int backword;
    backword = 1- frame_size ;
    fseek(fp,3,SEEK_CUR);  //skip 3 byte 2 flag + 1 encode
    if(argv[1][1] == 'e')
    {
	if(argv[3][1] == idnt)
	{	if(argv[1][1] == 'e' && strlen(argv[4]) >= frame_size)
	    {
		printf("title modifier name is larger than the frame size\n");
		return FAILURE;

	    }
	    else
	    {

		write_frame(fp , frame_size , argv);
		fseek(fp , backword , SEEK_CUR);
	    }
	}
    }

    return SUCCESS;
}

/* name : get_frame_size
 * input : frame_size
 * output : void
 * discription : get the frame size
 */

void get_frame_size(FILE * fp, u_int *frame_size)
{
    fread(frame_size,1,4,fp);
    //    printf(" before frame size = %x\n",*frame_size);
    size_conversion(frame_size);
    //  printf("after frame size = %x\n",*frame_size);
    //  printf("frame size = %d\n",frame_size);
}
/* name : write_frame
 * input : fp , frame_size, argv
 * output : void
 * discription : write into a frame
 */

void write_frame(FILE * fp , u_int frame_size , char ** argv)
{
    short int i;
    u_int len = strlen(argv[4]);
    u_int remain_part = (frame_size -1) - len;
    //    printf("len of string %d\n", len);
    //  printf("remain_part = %u\n",remain_part);
    //puts(argv[4]);

    // printf("before write pos = %d\n", ftell(fp));
    int ret = fwrite(argv[4], sizeof(char), len , fp);

    // printf("ret = %d\n",ret);
    // printf("iin write pos = %d\n", ftell(fp));
    while(remain_part)
    {
	fputc('\0',fp);
	remain_part--;
	//	printf("%d ", remain_part);
    }

    //printf("in write pos = %d\n", ftell(fp));

}


/* name : read_data
 * input : tag , fp , frame_size
 * output : buf address
 * discription : read the tag data info 
 */
char * read_data(tag_info * tag , FILE * fp ,  u_int frame_size)
{

    char ch;
    char  * buf = malloc(100 * sizeof(char));
    if(buf == NULL)
	return NULL;

    int i = 0;
    int j = 0;
    while(j < frame_size)
    {

	ch = fgetc(fp);
	if(ch != '\0')
	{
	    if( isprint(ch))
	    {   
		buf[i] = ch;
		//		putc(buf[i] , stdout);
		i++;
	    }
	}
	j++;
    }
    buf[j] = '\0';
    return buf;
}

