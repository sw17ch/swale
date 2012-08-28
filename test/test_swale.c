#include "unity.h"
#include "swale.h"

#include "mock_cb_stubs.h"

void setUp(void) { }

void tearDown(void) { }

void test_SwaleInit_sets_head_and_tail_to_null(void) {
  swale_t swale;

  SwaleInit(&swale);

  TEST_ASSERT_EQUAL_PTR(NULL, swale.head);
  TEST_ASSERT_EQUAL_PTR(NULL, swale.tail);
  TEST_ASSERT_EQUAL_PTR(NULL, swale.next_task);

  TEST_ASSERT_EQUAL(24, sizeof(swale_t));
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
  swale_t swale;
  swale_task_t task;

  SwaleInit(&swale);
  SwaleTaskInit(&task, task_entry_0, NULL);
  task.next = &task; // initialize to invalid value

  SwaleRegisterTask(&swale, &task);

  TEST_ASSERT_EQUAL_PTR(&task, swale.head);
  TEST_ASSERT_EQUAL_PTR(&task, swale.tail);
  TEST_ASSERT_EQUAL_PTR(NULL,  task.next);
}

void test_SwaleRegisterTask_should_replace_tail_if_head_exists(void) {
  swale_t swale;
  swale_task_t task_0;
  swale_task_t task_1;

  SwaleInit(&swale);
  SwaleTaskInit(&task_0, task_entry_0, NULL);
  SwaleTaskInit(&task_1, task_entry_1, NULL);

  SwaleRegisterTask(&swale, &task_0);
  SwaleRegisterTask(&swale, &task_1);

  TEST_ASSERT_EQUAL_PTR(&task_0, swale.head);
  TEST_ASSERT_EQUAL_PTR(&task_1, swale.tail);
  TEST_ASSERT_EQUAL_PTR(&task_1, task_0.next);
  TEST_ASSERT_EQUAL_PTR(NULL,    task_1.next);
}

void test_SwaleProcess_does_nothing_if_head_is_null(void) {
  swale_t swale;

  SwaleInit(&swale);

  SwaleProcess(&swale);
}

void test_SwaleProcess_calls_head_first_if_next_task_is_null(void) {
  swale_t swale;
  swale_task_t task_0;
  int32_t param_0;

  SwaleInit(&swale);
  SwaleTaskInit(&task_0, task_entry_0, (void *)&param_0);

  SwaleRegisterTask(&swale, &task_0);

  task_entry_0_Expect((void*)&param_0);
  SwaleProcess(&swale);
}

void test_SwaleProcess_calls_one_task_per_call_in_order_of_list(void) {
  swale_t swale;
  swale_task_t task_0;
  swale_task_t task_1;
  swale_task_t task_2;
  int32_t param_0;
  int32_t param_1;
  int32_t param_2;

  SwaleInit(&swale);
  SwaleTaskInit(&task_0, task_entry_0, (void *)&param_0);
  SwaleTaskInit(&task_1, task_entry_1, (void *)&param_1);
  SwaleTaskInit(&task_2, task_entry_2, (void *)&param_2);

  SwaleRegisterTask(&swale, &task_0);
  SwaleRegisterTask(&swale, &task_1);
  SwaleRegisterTask(&swale, &task_2);

  task_entry_0_Expect((void*)&param_0);
  task_entry_1_Expect((void*)&param_1);
  task_entry_2_Expect((void*)&param_2);

  SwaleProcess(&swale);
  SwaleProcess(&swale);
  SwaleProcess(&swale);
}

