
#ifndef LIBCORK_DS_SLSTACK_H
#define LIBCORK_DS_SLSTACK_H

#include <libcork/core/api.h>
#include <libcork/core/types.h>

struct cork_slstack_item {
    /* A pointer to the next element in the list. */
    struct cork_slstack_item  *next;
};


struct cork_slstack {
    /* The sentinel element for this list. */
    struct cork_slstack_item  *head;
#ifdef STACK_HAS_SIZE
    size_t size;
#endif
};

#ifdef STACK_HAS_SIZE
#define cork_slstack_init(stk)  \
    do { \
      (stk)->head = NULL; \
      (stk)->size = 0; \
    }while(0)
#else
#define cork_slstack_init(stk)  \
    do { \
      (stk)->head = NULL; \
    }while(0)
#endif

#define cork_slstack_is_empty(stk) ((stk)->head==NULL)

static inline void cork_slstack_push(struct cork_slstack *stk, struct cork_slstack_item *item)
{
  item->next = stk->head;
  stk->head = item;
#ifdef STACK_HAS_SIZE
  stk->size++;
#endif
}
static inline struct cork_slstack_item * cork_slstack_pop(struct cork_slstack *stk)
{
  struct cork_slstack_item *item = stk->head;
  if (item) {
    stk->head = item->next;
#ifdef STACK_HAS_SIZE
    stk->size--;
#endif
  }
  return item;
}
#define cork_slstack_peek(struct cork_slstack *stk) ((stk)->head)

#define cork_slstack_foreach(stk, cur) for(cur=stk->head; cur; cur=cur->next)

// stk : struct cork_dlstack *
// obj : container pointer
// member : item name in container struct
// tmp : a tmp var with type of struct cork_slstack_item *
#define cork_slstack_foreach_entry(stk, obj, member, tmp) \
  for(tmp=stk->head; tmp && (obj=cork_container_of(tmp, typeof(obj), member)); tmp=tmp->next)


#endif
