#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include "Event.h"
#include "Routers.h"

using namespace std;

void enQueue(trig*& headPtr, int value)
{
   trig* newTrigPtr = new trig;
   newTrigPtr->index = value;
   newTrigPtr->link = 0;
   if (!headPtr)
      headPtr = newTrigPtr;
   else
   {
      trig* cursor = headPtr;

      while (cursor->link)
         cursor = cursor->link;
      cursor->link = newTrigPtr;
   }
}

bool inQueue(trig*& headPtr, int value)
{
    if(headPtr)
    {
        trig* cursor = headPtr;
    
        while(cursor->link)
        {
                cursor = cursor->link;
                if(cursor->index == value)
                        return true;
        }
    }
    return false;
}

void displayQueue(trig*& headPtr)
{
    if(headPtr)
    {
        cout << "Values in queue: ";
        trig* cursor = headPtr;
        while(cursor->link)
        {
                cursor = cursor->link;
                cout << cursor->index << " ";
        }
        cout << endl;
    }
    else
        cout << "Queue is empty" << endl;
}

int front(trig*& headPtr)
{
    if(headPtr->link)
        return headPtr->link->index;
    else
        return -1;
}

int frontPop(trig*& headPtr)
{
    if(headPtr->link)
    {
        int front = headPtr->link->index;
        trig* temp = headPtr->link;
        headPtr->link = temp->link;
        delete temp;
        return front;
    }
    else
        return -1;
}

int queueSize(trig*& headPtr)
{
    int size = 0;
    if(headPtr)
    {
        trig* cursor = headPtr;
    
        while(cursor->link)
        {
                cursor = cursor->link;
                size++;
        }
    }
    return size;
}

void pop(trig*& headPtr)
{
    if(headPtr->link)
    {
        trig* temp = headPtr;
        headPtr = headPtr->link;
        delete temp;
    }
}