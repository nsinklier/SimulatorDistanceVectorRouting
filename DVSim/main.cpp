/* 
 * File:   main.cpp
 * Author: Nick
 *
 * Created on October 22, 2012, 6:38 AM
 */
#include <iostream>
#include <cstdlib>
#include "Routers.h"
#include "Event.h"

using namespace std;


int main(int argc, char** argv)
{
    Routers test1;

    test1.getTopology();
    cout << "--------------------------------------------------------" 
         << "\nThis is the initial topology of the network:"
         << "\n--------------------------------------------------------";    
    test1.displayTopology();
    test1.converge();
    test1.periodicUpdate();
    
    cout << "\nRun Complete at " << test1.getTime() << " seconds"
         << "\n--------------------------------------------------------\n"; 
    return 0;
}
