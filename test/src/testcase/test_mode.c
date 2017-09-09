/****************************************Copyright (c)**************************************************
**                                       清  风  海  岸
** 文   件   名: test_mode.h / test_mode.c
** 创   建   人: 周江村
** 最后修改日期: 2015/1/24 16:29:55
** 描        述: 
**  
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 周江村
** 版  本: v1.0
** 日　期: 2015/1/24 16:29:55
** 描　述: 原始版本
**
**--------------当前版本修订----------------------------------------------------------------------------
** 修改人: 
** 日　期: 
** 描　述: 单元测试用例的测试模板
** 本文件由C语言源文件模板软件生成。------------清风海岸出品，必属精品！------------
**------------------------------------------------------------------------------------------------------
*******************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus


/*********************************************头文件定义***********************************************/
#include "test_framework.h"


/********************************************内部变量定义**********************************************/



/********************************************内部函数定义*********************************************/



/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/
static void test_case_setup(void)
{
    test_printf("test case setup\r\n");
}

static void test_case_teardown(void)
{
    test_printf("test case teardown\r\n");
}

static void test_suite_setup(void)
{
    test_printf("test suite setup\r\n");
}

static void test_suite_teardown(void)
{
    test_printf("test suite teardown\r\n");
}



static void test1(void)
{
    test_printf("test1 test\r\n");
	EXPECT_EQ(0,1);
}

static void test2(void)
{
	int res = 1;
    test_printf("test2 test\r\n");
	EXPECT_EQ(0,res);
	EXPECT_NE(1,res);
}


static test_case_s testcase[] = 
{
    {"Test1",test_case_setup,test_case_teardown,test1},
    {"Test2",test_case_setup,test_case_teardown,test2},
};


test_suite_s testsuite = 
{
    "TestSuite1",
    sizeof(testcase)/sizeof(test_case_s),
    testcase,
    test_suite_setup,
    test_suite_teardown,
    NULL
};

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
