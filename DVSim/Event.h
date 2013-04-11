/* 
 * File:   Event.h
 * Author: Nick
 *
 * Created on October 30, 2012, 11:55 PM
 * 
 * Member Functions:
 * 
 * 
 * void enQueue(trig*& headPtr, int value)
 *      pre:    none
 *      post:   value has been added to the end of the queue
 * 
 * bool inQueue(trig*& headPtr, int value)
 *      pre:    none
 *      post:   function returns true if a value is found in the queue
 * 
 * int front(trig*& headPtr)
 *      pre:    there is at least 1 element in the queue
 *      post:   value in front of queue is returned
 * 
 * int frontPop(trig*& headPtr)
 *      pre:    there is at least 1 element in the queue
 *      post:   value in front of queue is returned and the element removed
 * 
 * void pop(trig*& headPtr)
 *      pre:    there is at least 1 element in the queue
 *      post:   the element in the front of the queue is removed
 * 
 * void displayQueue(trig*& headPtr)
 *      pre:    there is at least 1 element in the queue
 *      post:   the queue has been displayed
 * 
 * int queueSize(trig*& heaPtr)
 *      pre:    none
 *      post:   the number of elements in the queue is returned
 * 
 */

#ifndef EVENT_H
#define	EVENT_H

    typedef int dataType;
    struct trig                 // linked list of indexes for triggered updates
    {
        dataType index;         // router index for triggered update
        trig* link;
    };
    
    void enQueue(trig*& headPtr, int value);
    bool inQueue(trig*& headPtr, int value);
    int front(trig*& headPtr);
    int frontPop(trig*& headPtr);
    void pop(trig*& headPtr);
    void displayQueue(trig*& headPtr);
    int queueSize(trig*& heaPtr);
    
#endif	/* EVENT_H */

