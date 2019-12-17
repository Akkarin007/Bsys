#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct node
{
	int key;
	struct node *next;
	pthread_mutex_t lock;
}node;

typedef struct list
{
	node *head;
	pthread_mutex_t lock;
}list;

void init(list *L)
{
	L->head = NULL;
	pthread_mutex_init(&L->lock, NULL);
}

void add(list *L, int key)
{
	node *new = malloc(sizeof(node));
	if (new == NULL) {
		perror("malloc");
		return;
	}
	new->key = key;

	pthread_mutex_lock(&L->lock);
	new->next = L->head;
	L->head = new;
	pthread_mutex_unlock(&L->lock);
}

int Lookup(list *L, int key) {
	int rv = -1;

	pthread_mutex_lock(&L->lock);
	node *curr = L->head;
	while(curr) {
		if (curr->key == key) {
			rv = 0;
			break;
		}
		curr = curr->next;
	}

	pthread_mutex_unlock(&L->lock);
	return rv;
}
#endif
