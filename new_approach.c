#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "INIParser.h"

int main(int argc, char **argv)
{
    INIFile config;

    if(inifile_create(&config, "test.ini"))
    {
        return EXIT_FAILURE;
    }

    printf("%s",inifile_get(&config,"sekcja21234567890987654321234","param27qwertyuioppoiuytrewqqw"));


    // const char *text = "djutuiiif.dghjn -ghrfhry.sdth";
    char *section1 = NULL;
    char *section2 = NULL;
    char *key1 = NULL;
    char *key2 = NULL;
    char operatorr;
    int begin = 0;
    int end = -2;
    int iter = 0;
    int i = 0;
    for (i; i < strlen(argv[3]); i++)
    {
        if (argv[3][i] == '.' ||argv[3][i] == '-' ||argv[3][i] == '+' ||argv[3][i] == '/' ||argv[3][i] == '*')
        {
            iter++;
            begin = end + 2;
            end = i - 1;
            if (iter == 1)
            {
                section1 = (char *)malloc(end - begin + 1);
                strncpy(section1, (argv[3]), i);
            }
            if (iter == 2)
            {
                operatorr = argv[3][i];
                key1 = (char *)malloc(i - begin + 1);
                strncpy(key1, (argv[3] + begin), i - begin);
            }
            if (iter == 3)
            {
                section2 = (char *)malloc(i - begin + 1);
                strncpy(section2, (argv[3] + begin), i - begin);
            }
            // printf("%c",operatorr);
        }
    }
    // printf("%d %d %d    ",begin,end,i);
    key2 = (char *)malloc(i - end - 1);
    strcpy(key2, argv[3] + end + 2);
    if (operatorr=='+'){
        printf("%s%s",inifile_get(&config,section1,key2),inifile_get(&config,section2,key2));
    }
    // printf("Section1: %s key1: %s section2: %s key2: %s", section1, key1, section2, key2);


    //if (argv[2] != NULL && !strcmp(argv[2], "expression"))
    // {
    //     for (i; i < strlen(argv[3]); i++)
    //     {
    //         if (argv[3][i] == '.' || argv[3][i] == '-' || argv[3][i] == '+' || argv[3][i] == '/' || argv[3][i] == '*')
    //         {
    //             iter++;
    //             begin = end + 2;
    //             end = i - 1;
    //             if (iter == 1)
    //             {
    //                 section1 = (char *)malloc(end - begin + 1);
    //                 strncpy(section1, (argv[3]), i);
    //             }
    //             if (iter == 2)
    //             {
    //                 key1 = (char *)malloc(i - begin + 1);
    //                 strncpy(key1, (argv[3] + begin), i - begin);
    //             }
    //             if (iter == 3)
    //             {
    //                 section2 = (char *)malloc(i - begin + 1);
    //                 strncpy(section2, (argv[3] + begin), i - begin);
    //             }
    //             // printf("%d %d %d    ",begin,end,i);
    //         }
    //     }
    //     // printf("%d %d %d    ",begin,end,i);
    //     key2 = (char *)malloc(i - end - 1);
    //     strcpy(key2, argv[3] + end + 2);
    //     printf("Section1: %s key1: %s section2: %s key2: %s", section1, key1, section2, key2);
    // // }
    free(section1);
    free(section2);
    free(key1);
    free(key2);

    inifile_destroy(&config);
    return 0;
}