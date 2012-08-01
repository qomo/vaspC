
#include "glib.h"
#include "vaspC.h"
#include <stdbool.h>
#include <string.h>

void check_base36()
{
    g_assert_cmpint(base36("0"),==,0);
    g_assert_cmpint(base36("1"),==,1);
    g_assert_cmpint(base36("8"),==,8);
    g_assert_cmpint(base36("9"),==,9);

    g_assert_cmpint(base36("A"),==,10);
    g_assert_cmpint(base36("B"),==,11);
    g_assert_cmpint(base36("Y"),==,34);
    g_assert_cmpint(base36("Z"),==,35);
    g_assert_cmpint(base36("10"),==,36);
    g_assert_cmpint(base36("11"),==,37);
    g_assert_cmpint(base36("ZY"),==,1294);
    g_assert_cmpint(base36("ZZ"),==,1295);
}

void check_equal_str()
{
    g_assert(!equal_str("abcdefg","abc"));
    g_assert(equal_str("abcdefg","abcdefg"));
}

void check_fold()
{
    fold_set(3,100);
    g_assert_cmpint(fold("0"),==,0);
    g_assert_cmpint(fold("10"),==,36);
    fold_set(1,100);
    g_assert_cmpint(fold("111111"),==,6);
}

void check_hash_new_free()
{
    fold_set(3,100);
    HASH* hash= HASH_New(100,fold,equal_str);

    HASH_Free(hash);
}

void check_hash_lookup()
{
    fold_set(3,10);
    HASH* hash= HASH_New(10,fold,equal_str);

    KEY_VALUE* p1= HASH_Lookup(hash, "A");
    KEY_VALUE* p2= HASH_Lookup(hash, "A");
    g_assert(p1==p2);

    KEY_VALUE* p3= HASH_Lookup(hash, "B");
    g_assert(p2!=p3);

    KEY_VALUE* p4= HASH_Lookup(hash, "B");
    g_assert(p3==p4);

    HASH_Free(hash);
}

void check_hash_set_get()
{
    fold_set(3,100);
    HASH* hash= HASH_New(100,fold,equal_str);

    char* str1="ten";
    char* ret1= HASH_Set(hash, "10", POINTER_MALLOC(str1, char, strlen(str1)+1));
    g_assert_cmpstr(str1,==,ret1);

    KEY_VALUE* key_value= HASH_Lookup(hash, "10");
    g_assert_cmpstr(key_value->key,==,"10");
    g_assert_cmpstr(key_value->value,==,"ten");

    char* str2="tenten";
    char* ret2= HASH_Set(hash, "10", POINTER_MALLOC(str2, char, strlen(str2)+1));
    g_assert_cmpstr(str2,==,ret2);

    KEY_VALUE* key_value2= HASH_Lookup(hash, "10");
    g_assert_cmpstr(key_value2->key,==,"10");
    g_assert_cmpstr(key_value2->value,==,"tenten");

    char* ret3= HASH_Get(hash, "10");
    g_assert_cmpstr(ret3,==,"tenten");


    double d1= 10.;
    HASH_Set(hash, "10", POINTER_MALLOC(&d1, double,1));
    double* ret_d1= HASH_Get(hash, "10");
    g_assert_cmpfloat(d1,==,*ret_d1);


    int i1=12345;
    int* ret4= HASH_Set(hash, "12345", POINTER_MALLOC(&i1, int, 1));
    g_assert_cmpint(*ret4,==,i1);

    HASH_Free(hash);
}
