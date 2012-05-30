/**
 * @breif unittest
 * @author Zhi-Quan Huang
 * @date 2012-04-16
 */

#include "glib.h"
#include "vaspC.h"

void check_element()
{
    g_assert(PERIOD_TABLE_num2name(0)==NULL);
    g_assert_cmpstr(PERIOD_TABLE_num2name(1),==,"H");
    g_assert_cmpstr(PERIOD_TABLE_num2name(88),==,"Ra");
    
    g_assert_cmpint(PERIOD_TABLE_name2num("ZZZ"),==,-1);
    g_assert_cmpint(PERIOD_TABLE_name2num("he"),==,2);
    g_assert_cmpint(PERIOD_TABLE_name2num("RA"),==,88);
}
