#include "element.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define PERIOD_TABLE_MAX 88
char PERIOD_TABLE[PERIOD_TABLE_MAX+1][3]={
    ""  ,
    "H" ,  "He",  "Li",  "Be",  "B" ,
    "C" ,  "N" ,  "O" ,  "F" ,  "Ne",
    "Na",  "Mg",  "Al",  "Si",  "P" ,
    "S" ,  "Cl",  "Ar",  "K" ,  "Ca",
    "Sc",  "Ti",  "V" ,  "Cr",  "Mn",
    "Fe",  "Co",  "Ni",  "Cu",  "Zn",
    "Gg",  "Ge",  "As",  "Se",  "Br",
    "Kr",  "Rb",  "Sr",  "Y" ,  "Zr",
    "Nb",  "Mo",  "Tc",  "Ru",  "Rh",
    "Pd",  "Ag",  "Cd",  "In",  "Sn",
    "Sb",  "Te",  "I" ,  "Xe",  "Cs",
    "Ba",  "La",  "Ce",  "Pr",  "Nd",
    "Pm",  "Sm",  "Eu",  "Gd",  "Tb",
    "Dy",  "Ho",  "Er",  "Tm",  "Yb",
    "Lu",  "Hf",  "Ta",  "W" ,  "Re",
    "Os",  "Ir",  "Pt",  "Au",  "Hg",
    "Tl",  "Pb",  "Bi",  "Po",  "At",
    "Rn",  "Fr",  "Ra"
};

char* PERIOD_TABLE_num2name(int num)
{
    if (num<=0 || num > PERIOD_TABLE_MAX)
    {
        return NULL;
    }
    else
    {
        return PERIOD_TABLE[num];
    }
}

int PERIOD_TABLE_name2num(char* str)
{
    char* str_tmp=NULL;
    size_t str_len=strlen(str);
    if ((str_tmp= malloc((str_len+1)*sizeof(char)))==NULL)
        return -2;
    strncpy(str_tmp,str,str_len);
    str_tmp[str_len]='\0';
    int i;
    for (i=0; i<str_len; i++)
    {
        const char ch= str_tmp[i];
        str_tmp[i]= (i==0)?toupper(ch):tolower(ch);
    }

    for (i=1; i<=PERIOD_TABLE_MAX; i++)
    {
        if (strcmp(str_tmp, PERIOD_TABLE[i])==0)
        {
            return  i;
        }
    }
    return -1;
}
