#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "INIParser.h"

int check(const char *key)
{
    int flag = 1;
    for (int i = 0; i <= strlen(key) - 1; i++)
    {
        if (!(48 <= (int)key[i] && (int)key[i] <= 57))
        {
            flag = 0;
        }
    }
    return flag;
}
int main(int argc, char **argv)
{
    INIFile config;

    if (inifile_create(&config, "test.ini"))
    {
        return EXIT_FAILURE;
    }
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
        if (argv[3][i] == '.' || argv[3][i] == '-' || argv[3][i] == '+' || argv[3][i] == '/' || argv[3][i] == '*')
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
        }
    }

    key2 = (char *)malloc(i - end - 1);
    strcpy(key2, argv[3] + end + 2);
    char *value1 = inifile_get(&config, section1, key1);
    char *value2 = inifile_get(&config, section2, key2);
    if (operatorr == '+')
    {

        if (!check(value1) || !check(value2))
        {
            printf("\n%s%s", value1, value2);
        }
        else if (check(value1) && check(value2))
        {
            printf("\n%llu", atoll(value1) + atoll(value2));
        }
    }
    else if (operatorr == '-')
    {
        if (check(value1) && check(value2))
        {
            printf("\n%llu", atoll(value1) - atoll(value2));
        }
        else
        {
            printf("This operation on given key types is forbidden! You cannot subtract [string] elements");
            return EXIT_FAILURE;
        }
    }
    else if (operatorr == '*')
    {
        if (check(value1) && check(value2))
        {
            printf("\n%llu", atoll(value1) * atoll(value2));
        }
        else
        {
            printf("This operation on given key types is forbidden! You cannot multiply strings!");
            return EXIT_FAILURE;
        }
    }
    else if (operatorr = '/')
    {
        if (check(value1) && check(value2))
        {
            printf("\n%llu", atoll(value1) / atoll(value2));
        }
        else
        {
            printf("This operation on given key types is forbidden! You cannot divide strings!");
            return EXIT_FAILURE;
        }
    }
    free(section1);
    free(section2);
    free(key1);
    free(key2);
    inifile_destroy(&config);
    return 0;
}