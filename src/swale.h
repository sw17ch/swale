#ifndef swale_H
#define swale_H

#include <stdint.h>
#include <stdbool.h>

/*
 */
typedef struct swale_state_h {
  uint32_t tick;
} swale_state_t;

/*
 */
typedef void(*swale_entry_cb_t)(void * param);

/*
 */
typedef struct swale_task_h {
  struct swale_task_h * next;
  swale_entry_cb_t entry;
  void * param;
} swale_task_t;

/*
 */
typedef struct swale_h {
  swale_task_t * head;
  swale_task_t * tail;
} swale_t;


/*
 */
void SwaleProcess(swale_t * swale);

/*
 */
void SwaleTaskInit(swale_task_t * task,
                   swale_entry_cb_t entry,
                   void * param);

/*
 */
void SwaleRegisterTask(swale_t * swale, swale_task_t * task);

#endif // swale_H
