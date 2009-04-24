#ifndef __SORTEDLIST_H__
#define __SORTEDLIST_H__

#define NULL 0


template <class T> 
class list_member {
    // Assuming T is a pointer to a type of something, somewhere.
    public:
        T member;              // The member, for "public" use. A list that uses
                              // these nodes is responsible to make them private
                              
        list_member<T>* next; // pointer to a next member - for public use
        list_member<T>(T internal) : member(internal), next(NULL) {};
        bool operator<(const list_member& other) const {
            return (*member < *other.member); 
        }
        bool operator>(const list_member& other) const {
            return (*member > *other.member); 
        }
};
    
template <class T>
class SortedList {
        list_member<T>* top;
        list_member<T>* current;
    public:
        bool at_end;

        SortedList() : top(NULL), current(NULL), at_end(true) {}

//////////////////////
// Name: add
//    
// Arguments:
//    
//    A "type T" member which we'll add to the list.
//    
// Return Value:
//    
//    bool - true if the member was added successfully, and false if 
//        the adding failed.
//    
// Description:
//    
//    This method adds a new member to it's sorted place in the list.
//    
//////////////////////
 
        bool add(T);
        

//////////////////////
// Name: empty
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    bool - true if the list is empty and false otherwise.
//    
// Description:
//    
//    This method checks whether a list is empty or not.
//    
//////////////////////
 
        bool empty() const;

//////////////////////
// Name: printAll
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    None
//    
// Description:
//    
//    This method prints to the standard output the contents of the list.
//    
//////////////////////
 
        void printAll() const;
        

//////////////////////
// Name: start
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    None
//    
// Description:
//    
//    This method sets 'current' to point to the first member of the list.
//    
//////////////////////
 
        void start();
        

//////////////////////
// Name: next
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    None
//    
// Description:
//    
//    This method sets 'current' to point to the next member of the list.
//    
//////////////////////
 
        void next();


//////////////////////
// Name: getCurrent
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    A reference to the 'current' member.
//    
// Description:
//    
//    This method fetches a reference to the 'current' member of the list.
//    
//////////////////////
 
        T* getCurrent() const;
        
//////////////////////
// Name: end
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    bool - true if 'current' is the last member of the list, 
//        and false otherwise.
//    
// Description:
//    
//    This method checks whether the 'current' is the last member of the list.
//    
//////////////////////

        bool end() const;
        

//////////////////////
// Name: removeCurrent
//    
// Arguments:
//    
//    None
//    
// Return Value:
//    
//    bool - true if the member removal was successful, and false
//        if it wasn't.
//    
// Description:
//    
//    Removes the 'current' member.
//    
//////////////////////
 
        bool removeCurrent();

        ~SortedList(){
            if (top == NULL) {
                return;
            }
            list_member<T>* tmp_one = top->next;
            list_member<T>* tmp_two;
            delete top;
            while (tmp_one != NULL) {
                tmp_two = tmp_one;
                tmp_one = tmp_one->next;
                delete tmp_two;
            }
        }
};


template <class T>
bool operator==(SortedList<T>& one, SortedList<T>& two){
    one.start();
    two.start();
    T *one_member, *two_member;
    while ((one.end() == false) && (two.end() == false)) {
        one_member = one.getCurrent();
        two_member = two.getCurrent();
        if (!(*(*one_member) == *(*two_member))) {
            return false;
        }
        one.next();
        two.next();
    } // At this point all members are equal up to the point where at least
      // one list ended.
    if (one.end() != two.end()) { // Check if BOTH lists are at their end
        return false;
    }
    return true; // Reaching here means all members are equal.
}


template <class T>
bool SortedList<T>::add(T new_member) {
    if (new_member == NULL) {
        return false;
    }
    list_member<T>* the_member = new list_member<T>(new_member);
    if (the_member == NULL) { // Check allocation
        return false;
    }
    current = top;    // By definition, adding a member resets current
    at_end = false;
    if (top == NULL) {    // First in list
        top = the_member;
        return true;
    }
    list_member<T>* tmp = top; 
    if (*the_member < *top) {    // Special case: lower, then first
        top = the_member;
        the_member->next = tmp;
        return true;
    } else if (*the_member > *top) {
        while (tmp->next != NULL) {
            if (*the_member > *tmp) {
                 if (*the_member < *tmp->next) { // Found it
                    the_member->next = tmp->next;
                    tmp->next = the_member;
                    return true;
                } else if (!(*the_member > *tmp->next)){ 
                    delete the_member;
                    return false;
                }
            }
            tmp = tmp->next; // Iteration
        }
        tmp->next = the_member; // Not added yet - put it at end.
        return true;
    }
    delete the_member;
    return false; // This is dirty
}

template <class T>
bool SortedList<T>::empty() const {
    return (top == NULL ? true : false);
}

template <class T>
void SortedList<T>::printAll() const {
    if (empty()) {
        return;
    }
    list_member<T>* tmp = top;
    while (tmp != NULL) { // Iterate without changing current
        tmp->member->print();
        tmp = tmp->next;
    }
}

template <class T>
void SortedList<T>::start() {
    current = top;
    if (top != NULL) {
        at_end = false;
    }
}

template <class T>
void SortedList<T>::next() {
    if (current == NULL) {
        return;
    }
    if (current->next != NULL) { // Protection
        current = current->next;
    } else {
        at_end = true;
    }
}

template <class T>
bool SortedList<T>::end() const {
    return at_end;
}

template <class T>
T* SortedList<T>::getCurrent() const {
    return &(current->member);
}

template <class T>
bool SortedList<T>::removeCurrent(){
    current->member = NULL;
    if (current == top) { // Remove first!
        top = top->next;
        delete current; // delete the list_member
        current = top;
        return true;
    }
    list_member<T>* tmp = top;
    while (tmp->next != NULL) { // Iterate so we can get to current's daddy
        if (tmp->next == current) {
            tmp->next = current->next; // Side effect - empty list's top is NULL
            delete current; // delete the list_member
            current = top; // Current = top after removing, by definition.
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

#endif /* __SORTEDLIST_H__ */

