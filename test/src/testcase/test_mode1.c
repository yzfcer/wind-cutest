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
#include "cut.h"


/********************************************内部变量定义**********************************************/



/********************************************内部函数定义*********************************************/



/********************************************全局变量定义**********************************************/



/********************************************全局函数定义**********************************************/
case_setup(Test1)
{
    test_printf("Test1 setup\r\n");
}

case_teardown(Test1)
{
    test_printf("Test1 teardown\r\n");
}
case_func(Test1)
{
    test_printf("Test1 test\r\n");
}


case_setup(Test2)
{
    test_printf("Test2 setup\r\n");
}

case_teardown(Test2)
{
    test_printf("Test2 teardown\r\n");
}
case_func(Test2)
{
    test_printf("Test2 test\r\n");
}


case_setup(Test3)
{
    test_printf("Test3 setup\r\n");
}

case_teardown(Test3)
{
    test_printf("Test3 teardown\r\n");
}
case_func(Test3)
{
    test_printf("Test3 test\r\n");
}


suite_setup(TestSuite2)
{
    test_printf("test suite setup\r\n");
}

suite_teardown(TestSuite2)
{
    test_printf("test suite teardown\r\n");
}


TEST_CASE_START
TEST_CASE(Test1)
TEST_CASE(Test2)
TEST_CASE(Test3)
TEST_CASE_END
TEST_SUITE(TestSuite2)


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
