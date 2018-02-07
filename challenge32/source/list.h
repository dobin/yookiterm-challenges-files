#ifndef LIST_H
#define LIST_H

#define offsetof(type, member) ((size_t) & ((type *)0)->member)

#define container_of(ptr, type, member) ({      \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

struct list_head
{
    struct list_head *next;
    struct list_head *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    prev->next = new;
    new->prev = prev;
    new->next = next;
    next->prev = new;
}

static inline void __list_del(struct list_head *prev, struct list_head *next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_del_entry(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

static inline int list_empty(struct list_head *head)
{
	return head->next == head;
}

#define list_first_entry(ptr, type, member) \
	list_entry( (ptr)->next, type, member )

#define list_last_entry(ptr, type, member) \
	list_entry( (ptr)->prev, type, member )

#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

#define list_for_each(pos, head) \
    for ( pos = (head)->next; pos != (head); pos = pos->next )

#define list_for_each_reverse(pos, head) \
    for ( pos = (head)->prev; pos != (head); pos = pos->prev )

#define list_for_each_entry(pos, head, member) 						\
	for ( pos = list_first_entry(head, typeof(*pos), member); 		\
		  &pos->member != (head);									\
		  pos = list_next_entry(pos, member) )

#endif

