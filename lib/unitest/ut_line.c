/**
 * @breif unittest
 * @author Zhi-Quan Huang
 * @date 2012-04-16
 */

#include "glib.h"
#include "vaspC.h"

void check_readline()
{
    FILE* pf= NULL;
    char line[10];
    char* ret;

    if ((pf=fopen("data/readline_data","r"))==NULL)
    {
        g_assert(false);
    }

    g_assert(readline(line,10,NULL)==NULL);
    g_assert(readline(NULL,10,NULL)==NULL);
    g_assert(readline(NULL,10,pf)==NULL);

    ret= readline(line,10,pf); // 1st 12345
    g_assert_cmpstr(line,==,"12345");
    g_assert_cmpstr(ret,==,"12345");
    ret= readline(line,10,pf); // 2nd 12345
    g_assert_cmpstr(line,==," 0.12345");
    g_assert_cmpstr(ret,==," 0.12345");
    ret= readline(line,10,pf); // 3rd 123456789
    g_assert_cmpstr(line,==,"abcdefghi"); 
    g_assert_cmpstr(ret,==,"abcdefghi"); 
    ret= readline(line,10,pf); // 4th 1234567890
    g_assert_cmpstr(line,==,"ABCDEFGHI"); 
    g_assert_cmpstr(ret,==,"ABCDEFGHI"); 
    ret= readline(line,10,pf); // 5th 1234567890.....x216 + EOF
    g_assert_cmpstr(line,==,"KLMNOPQRS"); 
    g_assert_cmpstr(ret,==,"KLMNOPQRS"); 
    ret= readline(line,10,pf); // 6th EOF
    g_assert_cmpstr(line,==,"KLMNOPQRS"); 
    g_assert(ret==NULL);
    fclose(pf); 
}

void check_nitems()
{
    const char *DELIMITERS= "\t \n";
    char* test_str="\t H He     Li   Na   K       \t";
    g_assert(nitems(test_str,DELIMITERS)==5);
}

void check_rstrip()
{
    char str[10]="\t  4567  ";
    rstrip(str); 
    g_assert_cmpstr(str,==,"\t  4567");
}
