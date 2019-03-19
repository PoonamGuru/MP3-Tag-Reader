/* header file */

#ifndef MAIN_H
#define MAIN_H

#include"type.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>


/*function prototypes*/
OP_STATUS  operation_type( int argc , char ** argv);
void help_menu(void);
RETURN_VAL common_function(char * file_name , tag_info * tag, FILE ** fp, char ** argv);
int check_extension(const char * file_name);
FILE * open_file(const char * file_name,const char * mode);
RETURN_VAL Check_Version(FILE * fp, tag_info * tag);
RETURN_VAL View_Edit(FILE * fp, tag_info * tag , char ** argvi,flag_t * NF_flag);
void  size_conversion(u_int *size);
u_int get_tag_size(FILE * fp);
char * get_frame_identifier(FILE * fp, char ch);
RETURN_VAL read_write_frame(char * frame_idnt , FILE * fp ,tag_info * tag ,  char **  argv, flag_t * NF_flag);
void get_frame_size(FILE * fp, u_int *frame_size);
void write_frame(FILE * fp , u_int frame_size , char ** argv);
char * read_data(tag_info * tag , FILE * fp ,  u_int frame_size);
RETURN_VAL W_Frame(FILE * fp , u_int frame_size , char ** argv , char idnt);
void display_tag_details(tag_info * tag, flag_t * NF_flag);
#endif










#if 0
//int check_version(FILE * fp);
void read_write_frame(tag_info * tag , char *frame_idnt, FILE * fp, md * edt_mdf , char * argv);
u_int size_conversion(u_int size);
void mem_set(tag_info * tag);
RETURN_VAL  error_handling(char ** argv,int argc); 
void display_tag_details(tag_info * tag);
int edit_tag(md * edt_mdf , char * s_data);
void  write_to_frame(int frame_size ,char * argv ,char * mod,  md * edt_mdf, FILE * fp);
char * read_data(tag_info * tag, FILE * fp ,  u_int frame_size);
#endif

