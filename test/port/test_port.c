#include "test_port.h"
#include "test_framework.h"
extern test_suite_s testsuite;
extern test_suite_s testsuite1;
extern test_suite_s testsuite2;
extern test_suite_s testsuite3;
void test_suite_register_all(void)
{
	test_suite_register(&testsuite);
	test_suite_register(&testsuite1);
	test_suite_register(&testsuite2);
	test_suite_register(&testsuite3);

}



