#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include "Routers.h"


using namespace std;


//constructor
Routers::Routers()
: numNodes(0), time(0), headPtr(0), downLink(0), routCont(0)
{
    for(int i = 0; i < capacity; i++)
        for(int j = 0; j < capacity; j++)
        {
            routers[i].rTable[j].cost = 999999; // initialize cost to infinity
            routers[i].rTable[j].splitHorizon = -1;//init sH to undefined index
            routers[i].rTable[j].dest = j;      // initialize dest to index
            routers[i].rTable[j].nh = -1;       // initialize nh to unknown
            routers[i].numNeighbors = 0;
        }
}

// populates array with the routers from external .txt file
void Routers::getTopology()
{
    cout << "Please enter the topology filename with extension: ";
    cin >> file;
    
    if(file == "topology1.txt")
    {
        dataPackSrc = 0;
        dataPackDest = 3;
        linkDownA = 0;
        linkDownB = 2;
        downTime = 10;
        maxTime = 15;
    }
    else if(file == "topology2.txt")
    {
        dataPackSrc = 0;
        dataPackDest = 7;
        linkDownA = 5;
        linkDownB = 7;
        downTime = 20;    
        maxTime = 30;
    }
    else if(file == "topology3.txt")
    {
        dataPackSrc = 0;
        dataPackDest = 23;
        linkDownA = 9;
        linkDownB = 17;
        downTime = 30;
        maxTime = 60;
    }
    else
    {
        downTime = 70;
        maxTime = 60;
    }
        
    
    ifstream fin;
    fin.open(file.c_str());
    
    int tempSrc,
        tempDest,
        tempCost;
    float tempDelay;
    
    while(fin)
    {
        fin >> tempSrc >> tempDest >> tempCost >> tempDelay;
        
        // read into source router
        routers[tempSrc].rTable[tempDest].dest = tempDest;
        routers[tempSrc].rTable[tempDest].nh = tempDest;
        routers[tempSrc].rTable[tempDest].cost = tempCost;
        routers[tempSrc].neighbors[(routers[tempSrc].numNeighbors)].nabe = tempDest;
        routers[tempSrc].neighbors[(routers[tempSrc].numNeighbors)].delay = tempDelay;
        routers[tempSrc].numNeighbors++;
        
        // read into destination router
        routers[tempDest].rTable[tempSrc].dest = tempSrc;
        routers[tempDest].rTable[tempSrc].nh = tempSrc;
        routers[tempDest].rTable[tempSrc].cost = tempCost;
        routers[tempDest].neighbors[(routers[tempDest].numNeighbors)].nabe = tempSrc;
        routers[tempDest].neighbors[(routers[tempDest].numNeighbors)].delay = tempDelay;
        routers[tempDest].numNeighbors++;
        
        (tempSrc > numNodes)? numNodes = tempSrc : numNodes;    // get highest #
        (tempDest > numNodes)? numNodes = tempDest : numNodes;  // get highest #
        
        if(!inQueue(headPtr, tempDest))
            enQueue(headPtr, tempDest); // queuing triggered updates
        if(!inQueue(headPtr, tempSrc))
            enQueue(headPtr, tempSrc);  // queuing triggered updates
        
    }         
}

void Routers::displayTopology()
{
    for(int i = 0; i <= numNodes; i++)
    {
        cout << endl << "Router " << i << ":" << endl << endl;
        for(int j = 0; j <= numNodes; j++)
            if(i != j)  // don't display cost to itself
            {
                cout << routers[i].rTable[j].dest << ","
                     << routers[i].rTable[j].cost << ",";
            if(routers[i].rTable[j].nh != -1)
                cout << routers[i].rTable[j].nh  << endl;
            else
                cout << "-" << endl;
            }
    }
}

void Routers::converge()
{
    int dupRouter = 0; // test that current router index can't be enqueued multiple times
    routCont = 0;
    float curDelay = 0,
          bigDelay = 0;
    
    // while there are triggered updates in the queue
    while(queueSize(headPtr)) 
    {    
        // j == router receiving table, must be accessed with:
        // neighborIndex(i,j) which == routers[i].neighbors[j].nabe
        for(int j = 0; j < routers[front(headPtr)].numNeighbors; j++) 
        {
      
            // table == index of rTable being shared
            for(int table = 0; table < capacity; table++)
            {
                // check that current info was not originally 
                // received from router receiving table and that table being
                // shared is not the same as index of router receiving data
                if(!splitCheck(front(headPtr),table,j) && neighborIndex(front(headPtr),j) != table)
                {    
                    //if(current cost < cost to node + cost in table)
                    if((routers[neighborIndex(front(headPtr),j)].rTable[table].cost) > 
                      (routers[front(headPtr)].rTable[table].cost + 
                       routers[front(headPtr)].rTable[neighborIndex(front(headPtr),j)].cost))
                    {                       
                        routers[neighborIndex(front(headPtr),j)].rTable[table].cost =
                        routers[front(headPtr)].rTable[table].cost +                         // neighbor's cost to node
                        routers[front(headPtr)].rTable[neighborIndex(front(headPtr),j)].cost;             // cost to neighbor
                        
                        // share destination
                        routers[neighborIndex(front(headPtr),j)].rTable[table].dest = table;
                        
                        // NH is set to index of node sending the table
                        routers[neighborIndex(front(headPtr),j)].rTable[table].nh = front(headPtr);
                        
                        // initialize split horizon by setting splitHorizon 
                        // variable of node receiving table to index of node
                        // sending table
                        routers[neighborIndex(front(headPtr),j)].rTable[table].splitHorizon  
                        = front(headPtr);
                        
                        if(!dupRouter)          // if not a duplicate router
                                enQueue(headPtr, front(headPtr));
                        dupRouter++;
                        routCont++;
                                                
                    }
                }
             }     
         curDelay = routers[front(headPtr)].neighbors[j].delay;    
        (curDelay > bigDelay)? bigDelay = curDelay : curDelay;// get biggest delay    
        }
    
        time += bigDelay;       // increment time by largest neighbor delay
        
        // set last node to converge to the last node with a triggered update
        lastNode = frontPop(headPtr);   
        dupRouter = 0;
        if(time >= downTime && downLink == 0)
        {
                downedLink(0, 2);
                downLink++;
        }
    }
    showConvergeTime();
}

void Routers::periodicUpdate()
{
    bool dataPacketSent = false;        // determine if a data packet has been sent
    
    float curDelay = 0, // delay of current link
          bigDelay = 0; // largest delay of link from current router
    
    while(time < maxTime)
    {
        for(int i = 0; i < numNodes; i++)                       // i == router index
        {               
            for(int j = 0; j < routers[i].numNeighbors; j++)    // j == neighbor index
            {
                for(int table = 0; table < capacity; table++)   // table == routing table index
                {
                    // check that current info was not originally 
                    // received from router receiving table and that table being
                    // shared is not the same as index of router receiving data
                    if(!splitCheck(i, table, j) && neighborIndex(i, j) != table)
                        
                        //if(current cost < cost to node + cost in table)
                        if((routers[neighborIndex(i, j)].rTable[table].cost) > 
                          (routers[i].rTable[table].cost + 
                          routers[i].rTable[neighborIndex(i, j)].cost))
                        {
                            enQueue(headPtr, i);
//                            converge();
                        }
                }
                curDelay = routers[i].neighbors[j].delay;    
                (curDelay > bigDelay)? bigDelay = curDelay : curDelay;// get biggest delay
            }
            time += bigDelay;
            if(time >= downTime && downLink == 0)
            {
               downedLink(linkDownA, linkDownB);
               downLink++;
            }
        }
        if(queueSize(headPtr))
            converge();
        // send data packet if it is time and network is converged
        if(time >= downTime && !dataPacketSent)
        {
            dataPacket(dataPackSrc, dataPackDest);
            dataPacketSent = true;
        }
    }
}

bool Routers::splitCheck(int i, int table, int j)
{
    return (routers[i].rTable[table].splitHorizon == neighborIndex(i, j));
}

int Routers::neighborIndex(int i, int j)
{
    return routers[i].neighbors[j].nabe;
}

float Routers::getTime() { return time; }

void Routers::showTime() { cout << "Time = " <<  time << " seconds\n"; }

void Routers::showConvergeTime()
{
    cout << "\nNetwork has converged at " << getTime() << " seconds\n"
         << "The last node to converge was " << lastNode
         << "\nNumber of routing control messages: " << routCont << endl;
    displayTopology();
}

void Routers::downedLink(int routerA, int routerB)
{
    cout << "\nLink between " << routerA << " and " << routerB 
         << " has gone down at " << getTime() << " seconds\n";
    routers[routerA].rTable[routerB].cost = 999999;
    routers[routerB].rTable[routerA].cost = 999999;
}

void Routers::dataPacket(int src, int dest)
{
    cout << "\n--------------------------------------------------------";
         
    while(src != dest)
    {
        cout << "\nData packet being sent from " << src << " to " << dest
             << " at " << getTime()
             << "\nData Packet received by " << routers[src].rTable[dest].nh
             << " at " 
             << (getTime() + neighborDelay(src, routers[src].rTable[dest].nh));
        time = (getTime() + neighborDelay(src, routers[src].rTable[dest].nh));
        src = routers[src].rTable[dest].nh;
    }
    
    cout << "\n--------------------------------------------------------\n";
    
}

float Routers::neighborDelay(int src, int dest)
{
    int i = 0;
    while(routers[src].neighbors[i].nabe != dest)
        i++;
    return routers[src].neighbors[i].delay;
}
