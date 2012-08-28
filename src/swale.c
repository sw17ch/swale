#include <stdlib.h>

#include "swale.h"

void SwaleTaskInit(swale_task_t * task,
                   swale_entry_cb_t entry,
                   void * param) {
  task->next = NULL;
  task->entry = entry;
  task->param = param;
}
