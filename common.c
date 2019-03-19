#include"main.h"
#include"type.h"


/* Name : common_operation
 * Input : fp , file_name , 
 * Outptut : SUCCESS/ FAILURE
 * Discription : check the extension of the file is .mp3
 */
RETURN_VAL common_function(char * file_name , tag_info * tag, FILE ** fp, char ** argv)
{
    //save the file name in file_name
    printf("file_name :%s\n",file_name);

    /*check the extension ,it must be mp3*/
    if(check_extension(file_name) == FAILURE) return 	FAILURE;

    /*open the file in read mode*/
    if(argv[1][1] == 'v')
    if( (*fp = open_file(file_name, "r")) == NULL) return FAILURE;

    /*open the file in read mode*/
    if(argv[1][1] == 'e')
    if( (*fp = open_file(file_name, "r+")) == NULL) return FAILURE;

    /*check the file has ID3 or not */
    if(Check_Version(*fp, tag) == FAILURE) return FAILURE;

    return SUCCESS;
}


/* Name : Check_version
 * Input : fp , tag
 * Outptut : SUCCESS/ FAILURE
 * Discription : check the version of the ID
 */
RETURN_VAL Check_Version(FILE * fp , tag_info * tag)
{
    int ch ;
    fseek(fp, 0, SEEK_SET);   // set the fp to begining of the file

    /* -------tag identifier------------*/
    fread(tag->ti_tag_idnt, 1, 3, fp);   //first 3 byte identify the tag
    tag->ti_tag_idnt[3] = '\0'; // end of string


    if(strcmp(tag->ti_tag_idnt, "ID3") != 0)  //check the if file has ID3 tag or not
    {
	printf("ERROR : the file doesnt have ID3 tag\n");
	return FAILURE;
    }

    /*-------------- tag  version---------------------------*/
    ch = fgetc(fp); // 4th bit is the version
    if( ch == 3)
	tag->ti_tag_ver= 2.3;

    printf("the file identifer is %s\n",tag->ti_tag_idnt);  
    printf("the version of the ID3 is %f\n",tag->ti_tag_ver);


}


/* Name : get_tag_size
 * Input : fp , 
 * Outptut : tag_size
 * Discription : get the tag_size
 */

u_int get_tag_size(FILE * fp)
{
    u_int cur_pos =ftell(fp);
    u_int tag_size ;
    fseek(fp , 2 , SEEK_CUR);  //goto to 6th position
    cur_pos = ftell(fp);
    printf("%u\n", cur_pos);
    /*get the size of the tag*/
    fread(&tag_size , 1, sizeof(int), fp);
    //printf("tag size = %X\n", tag_size);
    // printf("tag_size = %x\n", tag_size);
    u_int temp = 0 , mask = 0x7f, i = 1;
    /*convert to the normal formate*/
    size_conversion(&tag_size);
    /*get the valid 28 bites from the synchronized safe interger to normal integer*/
    temp = temp | ( tag_size & 0x7f );
    // printf("%x\n",temp);
    while(i < 3)
    {
	mask <<= 8; 
	temp = temp | (( tag_size & mask) >> i);
	//      printf("%x\n",temp);
	i++;
    }

    return tag_size;
}
/* name size_conversiom
 * input : size
 * output : size
 * discription : when 4 byte of data read and sotred in integer it wasnt in order , this function align it correctly
 */
void size_conversion(u_int *size)
{

    *size =  ((*size & 0x00ff00ff ) << 8)  | ((*size & 0xff00ff00) >> 8);
//    printf("size = %x\n", *size);
    *size = ((*size & 0xffff) << 16 ) | (( *size & 0xffff0000) >> 16);

  //  printf("size = %x\n", *size);
}


/* Name : get_frame_identifier
 * Input : fp , ch
 * Outptut : file_identifier
 * Discription : get the file identifer
 */

char * get_frame_identifier(FILE * fp,char ch)
{
    static   char frame_idnt[4];

    frame_idnt[0] = ch;
    fread((frame_idnt+1) , 1 , 3, fp);
    frame_idnt[4] = '\0';
    return frame_idnt;
}

 /* name :  display_tag_details
  * input : tag
  * output : void
 * discription : display the tag details on to the screen
 */


 void display_tag_details(tag_info * tag, flag_t *NF_flag)
 {
     puts("--------------------------------------------tag detatils------------------------------------------------");
     //printf("tag adress inside the display : %p\n",tag);
     
     printf("tag         : %2s\n",tag->ti_tag_idnt);
     printf("tag version : %5.2f\n",tag->ti_tag_ver);
     if(NF_flag->t == 1)
     printf("title       : %10s\n",tag->ti_title);
     else printf("title not fount\n");


     if(NF_flag->A == 1)
     printf("album       : %10s\n",tag->ti_album);
     else printf("album not fount\n");

     if(NF_flag->T == 1)
     printf("track       : %3s\n",tag->ti_track);
     else printf("track not fount\n");

     if(NF_flag->S == 1)
     printf("singer      : %10s\n",tag->ti_singer);
     else printf("singer not fount\n");

     if(NF_flag->G == 1)
     printf("genre       : %10s\n",tag->ti_genre);
     else printf("genre not fount\n");
     if(NF_flag->Y == 1)
     printf("year        : %3s\n",tag->ti_year);
     else printf("year not fount\n");
     if(NF_flag->C == 1)
     printf("comment     : %3s\n",tag->ti_comment);
     else printf("comment not fount\n");
     if(NF_flag->P == 1)
     printf("pic_type    :%3s\n",tag->ti_pic);
     else printf("pic not fount\n");
     //printf("  : %s\n",tag->ti_);

 }

