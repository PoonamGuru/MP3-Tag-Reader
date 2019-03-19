/* header file */

#ifndef TYPE_H
#define TYPE_H

typedef enum return_t { 
    SUCCESS = 0, 
    FAILURE = -1
}RETURN_VAL;

typedef enum return_o { 
    OP_SUCCESS  = 0 , 
    OP_FAILURE = -1, 
    OP_HELP = 1 , 
    OP_READ = 2 , 
    OP_EDIT = 3
} OP_STATUS;

typedef struct flag
{
    unsigned int t : 1;
    unsigned int T : 1;
    unsigned int  S: 1;
    unsigned int  A: 1;
    unsigned int  G: 1;
    unsigned int  Y: 1;
    unsigned int  C: 1;
    unsigned int  P: 1;
}flag_t;

typedef unsigned int u_int ;
typedef struct tag
{
    char ti_tag_idnt[4];
    float ti_tag_ver;
    char ti_title[100];
    char ti_singer[100];
    char ti_album[100];
    char ti_year[10];
    char ti_track[10];
    char ti_genre[100];
    char ti_comment[100];
    char ti_pic[100];
}tag_info;

typedef struct modifier
{
    
    char modify_name[7] [50];
    int modifier[3];
}md;
//char * t_name[7] ;
//= {"TIT2", "TPE1","TALB", "TYER", "COMM", "TRCK", "TCON"};


#endif
