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
#ifndef __TEST_FRAMEWORK_H__
#define __TEST_FRAMEWORK_H__
#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/*********************************************头文件定义***********************************************/
//#include "port/wind_config.h"
//#include "port/wind_types.h"



/***********************************************宏定义*************************************************/
#define TEST_CASE_NAME_LEN 24
#define TEST_SUITE_NAME_LEN 24
#define TEST_FAIL_LIST_CNT 100
extern void test_suite_err(unsigned line);

#define FAIL_EXPECT_OUT(x,y,than) printf("failed expection:FILE:%s,LINE:%d:which expected "#x" %s "#y"\r\n",__FILE__,__LINE__,than)

//断言x == y
#define EXPECT_EQ(x,y) \
	do{if((x) != (y)) \
	{FAIL_EXPECT_OUT(x,y,"==");test_suite_err(__LINE__);}\
	}while(0)

//断言x != y
#define EXPECT_NE(x,y) \
	do{if((x) == (y)) \
	{FAIL_EXPECT_OUT(x,y,"!=");test_suite_err(__LINE__);}\
	}while(0)

//断言x > y
#define EXPECT_GREATER(x,y) \
	do{if((x) <= (y)) \
	{FAIL_EXPECT_OUT(x,y,">");test_suite_err(__LINE__);}\
	}while(0)

//断言x < y
#define EXPECT_SMALLER(x,y) \
	do{if((x) <= (y)) \
	{FAIL_EXPECT_OUT(x,y,"<");test_suite_err(__LINE__);}\
	}while(0)

//断言x <= y
#define EXPECT_NOT_GREATER(x,y) \
	do{if((x) <= (y)) \
	{FAIL_EXPECT_OUT(x,y,"<=");test_suite_err(__LINE__);}\
	}while(0)

//断言x >= y
#define EXPECT_NOT_SMALLER(x,y) \
	do{if((x) <= (y)) \
	{FAIL_EXPECT_OUT(x,y,">=");test_suite_err(__LINE__);}\
	}while(0)

//#define EXPECT_EQ(x,y) printf("FILE:%s,LINE:%d,expected %s,in fact %s\r\n",__FILE__,__LINE__,#x,#y)
/**********************************************枚举定义************************************************/
#include <stdio.h>
typedef unsigned int u32_t;
typedef int s32_t;
#ifndef NULL
#define NULL (void*)0
#endif
#define err_t u32_t
#define ERR_OK 0
#define ERR_COMMAN 1
#define WIND_ASSERT_RETURN(x,y)
#define TEST_STDOUT printf

/*********************************************结构体定义***********************************************/
//测试用例结构
typedef struct 
{
    char name[TEST_CASE_NAME_LEN];
    void (*setup)(void);
    void (*teardown)(void);
    void (*test)(void);
}test_case_s;

//测试套结构
typedef struct __test_suite_s
{
    char name[TEST_SUITE_NAME_LEN];
    u32_t case_cnt;//测试用例的数量
    test_case_s *tcase;
    //void (*init)(void);
    void (*setup)(void);
    void (*teardown)(void);
    struct __test_suite_s *next;
}test_suite_s;

//全局的test suite列表
typedef struct __test_suite_global
{
    test_suite_s *head;
    test_suite_s *tail;
    u32_t cnt;
}test_suite_global_s;

//用例执行结果统计信息
typedef struct __test_stati_s
{
	u32_t tot_suite;
	u32_t tot_case;
	u32_t passed_suite;
	u32_t failed_suite;
	u32_t passed_case;
	u32_t failed_case;
}test_stati_s;

//执行失败的信息
typedef struct __fail_info_s
{
	test_suite_s *suite;
	test_case_s *tcase;
	u32_t line;
	struct __fail_info_s *next;
}fail_info_s;



typedef struct __test_info_s
{
	test_stati_s stat;
	fail_info_s *faillist;
	fail_info_s *lastfail;
	u32_t failcnt;

	test_suite_s *suite;
	test_case_s *tcase;
	u32_t case_err;
	u32_t suite_err;

}test_info_s;

/********************************************全局变量申明**********************************************/
extern test_suite_s testsuite;
extern test_suite_s testsuite1;
extern test_suite_s testsuite2;
extern test_suite_s testsuite3;



/********************************************全局函数申明**********************************************/
err_t test_suite_register(test_suite_s *test_suite);
//void test_framework_init(void);
//void test_start(void);
void test_framework_entry(void);


#ifdef __cplusplus
}
#endif // #ifdef __cplusplus
#endif // #ifndef __TEST_FRAMEWORK_H__
