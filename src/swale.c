#include <stdlib.h>

#include "swale.h"

void SwaleInit(swale_t * swale) {
  swale->head = NULL;
  swale->tail = NULL;
  swale->next_task = NULL;
}

void SwaleTaskInit(swale_task_t * task,
                   swale_entry_cb_t entry,
                   void * param) {
  task->next  = NULL;
  task->entry = entry;
  task->param = param;
}

void SwaleRegisterTask(swale_t * swale, swale_task_t * task) {
  if (NULL == swale->head) {
    swale->head = task;
    swale->tail = task;
  } else {
    swale->tail->next = task;
    swale->tail = task;
  }
  task->next = NULL;
}

void SwaleProcess(swale_t * swale) {
  if (NULL != swale->head) {
    swale_task_t * task;

    if (NULL == swale->next_task) {
      swale->next_task = swale->head;
    }

    task = swale->next_task;
    task->entry(task->param);
    swale->next_task = task->next;
  }
}
