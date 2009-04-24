#ifndef __FAKETREE_H__
#define __FAKETREE_H__

#include "sortedlist.h"
#include "library1.h"

template <class T>
class FakeTree {
	SortedList<T> list;
		public:
	StatusType insert(T item) {
			list.start();
			while(!list.end()) {
				if (list.getCurrent() != NULL) {
					if (*item == **list.getCurrent()) {
						delete item;
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
	StatusType remove(T item) { // TODO What does the real tree want here? Example?
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

};

#endif /* __FAKETREE_H__ */

