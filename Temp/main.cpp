#include <iostream>
#include "FCFSOperatingSystem.h"
#include "SJFOperatingSystem.h"
#include "TimeSimulator.h"
using namespace std;

int main() {
    FCFSOperatingSystem sys_FCFS;
    SJFOperatingSystem sys_SJF;
    TimeSimulator sim = TimeSimulator(sys_SJF, 60, 86400, TimeSimulator::EVERY_TIME_INTERVAL);
    /*    
1      JA       02：40     20      
2      JB       02：50     30      
3      JC       02：55     10      
4      JD       03：00     24      
5      JE       03：05     6        
    */
    sim.registerJob(JCB(1, "JA", DateTime(2, 40), 20 * 60));
    sim.registerJob(JCB(2, "JB", DateTime(2, 50), 30 * 60));
    sim.registerJob(JCB(3, "JC", DateTime(2, 55), 10 * 60));
    sim.registerJob(JCB(4, "JD", DateTime(3, 0), 24 * 60));
    sim.registerJob(JCB(5, "JE", DateTime(3, 5), 6 * 60));
    
    sim.init(DateTime(2, 40));
    for (int i = 0; sim.getNow() < DateTime(5, 0); i++) {
         sim.update();
    }
}
