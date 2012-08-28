#include "unity.h"
#include "swale.h"

#include "mock_cb_stubs.h"

void setUp(void) { }

void tearDown(void) { }

void test_SwaleProcess(void) {
	TEST_IGNORE_MESSAGE("Implement me!");
}

void test_SwaleTaskInit_fills_in_a_task(void) {
  swale_task_t task;
  uint32_t a_param = 99;

  SwaleTaskInit(&task, task_entry_0, (void*)&a_param);

  TEST_ASSERT_EQUAL_PTR(NULL, task.next);
  TEST_ASSERT_EQUAL_PTR(task_entry_0, task.entry);
  TEST_ASSERT_EQUAL_PTR((void*)&a_param, task.param);

  /* Ensure we catch when the size of swale_task_t changes. */
  TEST_ASSERT_EQUAL(24, sizeof(swale_task_t));
}

void test_SwaleRegisterTask_should_set_head_and_tail_if_no_head(void) {
	TEST_IGNORE_MESSAGE("Implement me!");
}

void test_SwaleRegisterTask_should_replace_tail_if_head_exists(void) {
	TEST_IGNORE_MESSAGE("Implement me!");
}
