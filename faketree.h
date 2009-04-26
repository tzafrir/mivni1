#ifndef __FAKETREE_H__
#define __FAKETREE_H__

#include "sortedlist.h"
#include "library1.h"

// TODO: When does the tree release memory? When should I?1

template <class T>
class FakeTree {
	SortedList<T*> list;
		public:
	~FakeTree() {
		list.start();
		while(!list.end()){
			delete *list.getCurrent();
			list.next();
		}
	}
	StatusType insert(T* item) {
			list.start();
			while(!list.end()) {
				if (list.getCurrent() != NULL) {
					if (*item == **list.getCurrent()) {
						return FAILURE;
					}
					list.next();
				}
			}
			if (list.add(item)) { // returns true for successful entering
				return SUCCESS;
			} else {
				return FAILURE;
			}
	}
	StatusType remove(T* item) { // TODO What does the real tree want here? Example?
		list.start();
		while (!list.end()) {
			if ((**list.getCurrent()) == *item) {
				delete *list.getCurrent();
				list.removeCurrent();
				return SUCCESS;
			}
			list.next();
		}
		return FAILURE;
	}
	
	T* find(T* key) {
		list.start();
		while (!list.end()) {
			if ((**list.getCurrent()) == *key) {
				return *list.getCurrent();
			}
			list.next();
		}
		return NULL;
	}
	
	T* GetMin() {
		list.start();
		return *list.getCurrent();
	}
};

#endif /* __FAKETREE_H__ */

