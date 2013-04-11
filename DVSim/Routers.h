/* 
 * File:   Routers.h
 * Author: Nick
 *
 * Created on October 22, 2012, 7:16 AM
 * 
 * Member Functions:
 * 
 * void getTopology()
 *      pre:    none
 *      post:   a topology file has been read into the Routers and initial
 *              routing tables have been created
 * 
 * void displayTopology()
 *      pre:    none
 *      post:   all routing tables of each router have been displayed 
 * 
 * bool converge()
 *      pre:    initial routing tables have been read into routers
 *      post:   all routers have shared their routing tables with their
 *              neighbors one time, and true has been returned if the
 *              network has converged
 * 
 * bool splitCheck()
 *      pre:    converge() has been called at least once
 *      post:   true has been returned if splitHorizon value matches 
 *              neighbor index value
 * 
 * float getTime()
 *      pre:    converge() has been called at least once
 *      post:   current time of network is returned
 * 
 * void downedLink(int routerA, int routerB)
 *      pre:    network has converged
 *      post:   link between routerA and routerB has been set to 999999
 * 
 * void periodicUpdate()
 *      pre:    network has converged
 *      post:   program remains in this function until max time is met
 * 
 * void showConvergeTime()
 *      pre:    converge() has been called
 *      post:   time of convergence and last node to converge has been printed
 * 
 * void dataPacket(int src, int dest)
 *      pre:    network has converged
 *      post:   data packet has been sent and traced with cout statement
 * 
 * float neighborDelay(int src, int dest)
 *      pre:    topology has been read into routers
 *      post:   delay value of neighbor has been returned
 * 
 */

#ifndef ROUTERS_H
#define	ROUTERS_H
#include "Event.h"

using namespace std;

class Routers
{
public:
    trig* headPtr;
    
    static const int capacity = 100;
    Routers();
    void getTopology();
    void displayTopology();
    void converge();
    bool splitCheck(int, int, int);
    int neighborIndex(int, int);
    float getTime();
    void showTime();
    void downedLink(int routerA, int routerB);
    void periodicUpdate();
    void showConvergeTime();
    void dataPacket(int src, int dest);
    float neighborDelay(int src, int dest);
    
private:
    struct node
    {
        struct routingTable
        {
                int dest;
                int nh;
                int cost;
                int splitHorizon;               // neighbor table came from
        };
        
        // structure to hold list of neighbors with delay to each
        struct neighb
        {
            int nabe;                           // index of neighbor
            float delay;                        // delay to neighbor
        };
        
        int numNeighbors;                       // number of neighbors
        neighb neighbors[capacity];             // list of neighbors
        routingTable rTable[capacity];          // list of routing tables
    };
    
    node routers[capacity];
    int numNodes;               // keep track of number of nodes
    float time;                 // maintains running time
    int downLink;               // determine if a link has already gone down
    int lastNode;               // last node to converge
    string file;                // topology file
    int dataPackSrc;            // node sending data packet
    int dataPackDest;           // node receiving data packet
    int linkDownA;              // node that drops a link
    int linkDownB;              // other node that drops link
    int downTime;               // time to down link
    int maxTime;                // time to run program
    int routCont;               // count routing control msgs
  
};

#endif	/* ROUTERS_H */
