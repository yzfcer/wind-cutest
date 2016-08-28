/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: test_framework.h / test_framework.c
** 创   建   人: 周江村
** 最后修改日期: 2015/1/24 15:42:27
** 描        述: 
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2015/1/24 15:42:27
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: wind_os的系统的测试框架文件，在框架下继承了各种功能的单元测试
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************头文件定义***********************************************/
//#include "port/wind_config.h"
//#include "port/wind_types.h"
#include "test_framework.h"



/********************************************内部变量定义**********************************************/



/********************************************内部函数定义*********************************************/

static s32_t stringlenth(char *str)
{
	s32_t i;
	for(i = 0;i < 65535;i ++)
	{
		if(str[i] == 0)
			break;
	}
	return i;
} 

/********************************************全局变量定义**********************************************/
test_suite_global_s g_test_suite_info;
test_info_s g_test_info;
fail_info_s g_fail_obj[TEST_FAIL_LIST_CNT];
u32_t fail_list_index;

/********************************************全局函数定义**********************************************/
void test_info_init(test_info_s *ti)
{
	u32_t i;
	fail_info_s *fail;

	ti->case_err = 0;
	ti->suite_err = 0;
	
	ti->stat.failed_case = 0;
	ti->stat.passed_case = 0;
	ti->stat.failed_suite = 0;
	ti->stat.passed_suite = 0;
	
	ti->faillist = NULL;
	ti->lastfail = NULL;
	ti->failcnt = 0;
	fail_list_index = 0;
	for(i = 0;i < TEST_FAIL_LIST_CNT;i ++)
	{
		fail = &g_fail_obj[i];
		fail->line = 0;
		fail->next = NULL;
		fail->suite = NULL;
		fail->tcase = NULL;
	}
}
void test_framework_init(void)
{
	
	test_info_s *ti;
    test_suite_global_s *tsg = &g_test_suite_info;

	ti = &g_test_info;
    tsg->head = NULL;
    tsg->tail = NULL;
    tsg->cnt = 0;

	test_info_init(ti);

}

err_t test_suite_register(test_suite_s *test_suite)
{
    test_suite_global_s *tsg = &g_test_suite_info;
	test_info_s *ti;

    WIND_ASSERT_RETURN(test_suite == NULL,ERR_NULL_POINTER);
 	ti = &g_test_info;
   if(tsg->tail == NULL)
    {
        tsg->tail = test_suite;
        tsg->head = test_suite;
    }
    else
    {
        tsg->tail->next = test_suite;
		tsg->tail = test_suite;
    }
    test_suite->next = NULL;
    tsg->cnt ++;
    return ERR_OK;
}
void save_fail_info(u32_t line)
{
	test_info_s *ti;
	fail_info_s *fail;
	ti = &g_test_info;
	if(fail_list_index >= TEST_FAIL_LIST_CNT)
	{
		return;
	}
	fail = &g_fail_obj[fail_list_index ++];
	fail->suite = ti->suite;
	fail->tcase = ti->tcase;
	fail->line = line;
	if(ti->lastfail == NULL)
	{
		ti->faillist = fail;
		ti->lastfail = fail;
	}
	else
	{
		ti->lastfail->next = fail;
		ti->lastfail = fail;
	}
	fail->next = NULL;
	ti->failcnt ++;
}
void test_suite_err(u32_t line)
{
    test_suite_s *ts;
    test_case_s *tc;
	test_info_s *ti;

	ti = &g_test_info;
	ts = ti->suite;
	tc = ti->tcase;

	ti->suite_err ++;
	ti->case_err ++;
	save_fail_info(line);
}

void test_case_done(void)
{
	test_info_s *ti;

	ti = &g_test_info;
	if(ti->case_err > 0)
	{
		ti->stat.failed_case ++;
	}
	else
	{
		ti->stat.passed_case ++;
	}
	ti->case_err = 0;
}

void test_suite_done(void)
{
	test_info_s *ti;

	ti = &g_test_info;
	if(ti->suite_err > 0)
	{
		ti->stat.failed_suite ++;
	}
	else
	{
		ti->stat.passed_suite ++;
	}
	ti->suite_err = 0;

}
void print_boarder(u32_t space_cnt)
{
	char space[20];
	u32_t i,len;
	len = space_cnt > 20?20:space_cnt;
	for(i = 0;i < len;i ++)
		space[i] = ' ';
	for(;i < 20;i ++)
		space[i] = 0;

	TEST_STDOUT("------------");
	TEST_STDOUT("%s",space);
	TEST_STDOUT("------------");
	TEST_STDOUT("%s",space);
	TEST_STDOUT("------\r\n");
}

void print_header(u32_t space_cnt)
{
	char space[20];
	u32_t i,len;
	len = space_cnt > 20?20:space_cnt;
	for(i = 0;i < len;i ++)
		space[i] = ' ';
	for(;i < 20;i ++)
		space[i] = 0;

	TEST_STDOUT("%-12s","SUITE");
	TEST_STDOUT("%s",space);
	TEST_STDOUT("%-12s","CASE");
	TEST_STDOUT("%s",space);
	TEST_STDOUT("%-6s\r\n","LINE");
}

void print_fail_info(fail_info_s *fail,u32_t space_cnt)
{
	char space[20];
	u32_t i,len;
	len = space_cnt > 20?20:space_cnt;
	for(i = 0;i < len;i ++)
		space[i] = ' ';
	for(;i < 20;i ++)
		space[i] = 0;

	TEST_STDOUT("%-12s",fail->suite->name);
	TEST_STDOUT("%s",space);
	TEST_STDOUT("%-12s",fail->tcase->name);
	TEST_STDOUT("%s",space);
	TEST_STDOUT("%-6d\r\n",fail->line);
}

void test_framework_summit(void)
{
	test_info_s *ti;
	u32_t i;
	fail_info_s *fail;
	u32_t space_cnt = 4;
	ti = &g_test_info;
	TEST_STDOUT("\r\n\r\n[-----------ALL TEST SUMMARY-----------]\r\n");
	TEST_STDOUT("total  suites:%d\r\n",ti->stat.tot_suite);
	TEST_STDOUT("passed suites:%d\r\n",ti->stat.passed_suite);
	TEST_STDOUT("failed suites:%d\r\n",ti->stat.failed_suite);

	TEST_STDOUT("\r\ntotal  cases:%d\r\n",ti->stat.tot_case);
	TEST_STDOUT("passed cases:%d\r\n",ti->stat.passed_case);
	TEST_STDOUT("failed cases:%d\r\n",ti->stat.failed_case);

	if(ti->faillist != NULL)
	{
		TEST_STDOUT("\r\nfailture list as following:\r\n\r\n",ti->stat.tot_case);
		fail = ti->faillist;
		//TEST_STDOUT("------------    ------------    ------\r\n");
		print_boarder(space_cnt);
		//TEST_STDOUT("%-12s    %-12s    %-6s\r\n","SUITE","CASE","LINE");
		print_header(space_cnt);
		print_boarder(space_cnt);
		//TEST_STDOUT("------------    ------------    ------\r\n");
		for(i = 0;i < ti->failcnt;i ++)
		{
			//TEST_STDOUT("%-12s    %-12s    %-6d\r\n",fail->suite->name,fail->tcase->name,fail->line);
			print_fail_info(fail,space_cnt);
			fail = fail->next;
			if(fail == NULL)
				break;
		}
		print_boarder(space_cnt);
		//TEST_STDOUT("------------    ------------    ------\r\n");

	}
}
s32_t do_match(char *str,char *filter,s32_t idx,s32_t len)
{
	s32_t i;
	for(i = 0;i < len;i ++)
	{
		if(str[i + idx] != filter[i])
			break;
	}
	return i;
}

s32_t is_contain(char *str,char *filter,s32_t len1,s32_t len2)
{
	s32_t i,j;
	s32_t stringlen;
	s32_t idx;
	if(len2 > len1)
		return 0;
	for(i = 0;i < len1;i++)
	{
		if(len1 - i < len2)
			return 0;
		idx = do_match(str,filter,i,len2);
		if(idx >= len2)
			return 1;
	}
	return 0;

}
s32_t do_match_end(char *str,char *filter,s32_t len1,s32_t len2)
{
	s32_t i;
	if(len2 > len1)
		return 0;
	for(i = 0;i < len2;i ++)
	{
		if(str[len1 - len2 + i] != filter[i])
			return 0;
	}
	return 1;
}

s32_t do_match_head(char *str,char *filter,s32_t len1,s32_t len2)
{
	s32_t i;
	if(len2 > len1)
		return 0;
	for(i = 0;i < len2;i ++)
	{
		if(str[i] != filter[i])
			return 0;
	}
	return 1;
}

s32_t do_match_all(char *str,char *filter,s32_t len1,s32_t len2)
{
	s32_t i;
	s32_t stringlen;
	if(len2 > len1)
		return 0;
	for(i = 0;i < len2;i ++)
	{
		if(str[len1 - len2 + i] != filter[i])
			return 0;
	}
	return 1;
}
s32_t is_match_str(char *str,char *filter)
{
	s32_t len1,len2;
	len1 = stringlenth(str);
	len2 = stringlenth(filter);

	if((filter[0] == '*') && (filter[len2 - 1] == '*'))
	{
		return is_contain(str,&filter[1],len1,len2 - 2);
	}
	else if(filter[0] == '*')
	{
		return do_match_end(str,&filter[1],len1,len2 - 1);
	}
	else if(filter[len2 - 1] == '*')
	{
		return do_match_head(str,&filter[0],len1,len2 - 1);
	}
	else
	{
		return do_match_head(str,filter,len1,len2);
	}
}
void show_test_suites(char *filter)
{
	s32_t i,j = 0;
	test_suite_s *ts;
	TEST_STDOUT("\r\nTest Suites List with filter \"%s\" As Following:\r\n",filter);
	ts = g_test_suite_info.head;
	for(i = 0;i < g_test_suite_info.cnt;i ++)
	{
		if(!is_match_str(ts->name,filter))
		{
			ts = ts->next;
			continue;
		}
		TEST_STDOUT("%d--%s\r\n", 1+j ++,ts->name);
		ts = ts->next;
	}
}

void test_suite_init(void)
{
	test_suite_register(&testsuite);
	test_suite_register(&testsuite1);
	test_suite_register(&testsuite2);
	test_suite_register(&testsuite3);
}

void test_filtered_suites(char *filter)
{
    u32_t i,j;
    test_suite_s *ts;
    test_case_s *tc;
	test_info_s *ti;
	ti = &g_test_info;
    ts = g_test_suite_info.head;
	test_info_init(ti);
    TEST_STDOUT("-------Test framework start-------\r\n");
    //for(i = 0;i < g_test_suite_info.cnt;i ++)
	while(ts)
    {
		if(!is_match_str(ts->name,filter))
		{
			ts = ts->next;
			continue;
		}
		ti->stat.tot_suite ++;
		ti->stat.tot_case += ts->case_cnt;

		TEST_STDOUT("\r\n[**************  Test Suite:%s  **************] \r\n",ts->name);
		ti->suite = ts;

        ts->setup();
        for(j = 0;j < ts->case_cnt;j ++)
        {
            tc = &ts->tcase[j];
			ti->tcase = tc;
			TEST_STDOUT("\r\n[######  Test Case:%s  ######]\r\n",tc->name);
            tc->setup();
            tc->test();
            tc->teardown();
			test_case_done();
			TEST_STDOUT("\r\n");
        }
        ts->teardown();
		test_suite_done();
		TEST_STDOUT("++++-----------------++++\r\n\r\n");
        ts = ts->next;
    }
	TEST_STDOUT("-------Test framework end-------\r\n");
	test_framework_summit();
}


void test_framework_entry(int argc,char **argv)
{
	char *filter = "*est*";
	test_framework_init();
	test_suite_init();
	show_test_suites(filter);
	test_filtered_suites(filter);
}
#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
