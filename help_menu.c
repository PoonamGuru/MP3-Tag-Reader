#include"main.h"

void help_menu(void)
{
    puts("\n\n-----------------------------------------mp3 Tag Reader help menu---------------------------------\n");

    printf("\tModifier\t\t\tFunction\n\n");

    printf("\t-t\t\t\t\tModifies Title tag\n");
    printf("\t-T\t\t\t\tModifies Track tag\n");
    printf("\t-S\t\t\t\tModifies Singer tag\n");
    printf("\t-A\t\t\t\tModifies Album tag\n");
    printf("\t-Y\t\t\t\tModifies Year tag\n");
    printf("\t-C\t\t\t\tModifies Comment tag\n");
    printf("\t-G\t\t\t\tModifies Genre tag\n\n\n\n");
puts("-------------------------------------------------USAGE----------------------------------------\n");
    printf("./mp3_tag_reader -h --- help\n");
    printf("./mp3_tag_reader -v  <xxx.mp3> ---- to view the id3 tag details\n");
    printf("./mp3_tag_reader -e <.mp3 file> <modifier> <modifer_name> -------------to edit the tad detail\n\n");

}

