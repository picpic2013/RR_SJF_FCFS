#include <iostream>
#include <iomanip>
#include "FCFSOperatingSystem.h"
#include "SJFOperatingSystem.h"
#include "HRRNOperatingSystem.h"
#include "RROperatingSystem.h"
#include "TimeSimulator.h"
using namespace std;

int main() {
    FCFSOperatingSystem sys_FCFS;
    SJFOperatingSystem sys_SJF;
    HRRNOperatingSystem sys_HRRN;
    RROperatingSystem sys_RR;
    TimeSimulator sim = TimeSimulator(sys_RR, 1, 1, TimeSimulator::EVERY_TIME_INTERVAL);
/*    
1      JA       02：40     20      
2      JB       02：50     30      
3      JC       02：55     10      
4      JD       03：00     24      
5      JE       03：05     6        
*/

    /*
    sim.registerJob(JCB(1, "JA", DateTime(2, 40), 20 * 60));
    sim.registerJob(JCB(2, "JB", DateTime(2, 50), 30 * 60));
    sim.registerJob(JCB(3, "JC", DateTime(2, 55), 10 * 60));
    sim.registerJob(JCB(4, "JD", DateTime(3, 0), 24 * 60));
    sim.registerJob(JCB(5, "JE", DateTime(3, 5), 6 * 60));
    sim.init(DateTime(2, 40));
    */
    
    
    
    
    sim.registerJob(JCB(1, "A", 0, 3));
    sim.registerJob(JCB(2, "B", 2, 6));
    sim.registerJob(JCB(3, "C", 4, 4));
    sim.registerJob(JCB(4, "D", 6, 5));
    sim.registerJob(JCB(5, "E", 8, 2));
    
    
    
    while (sim.update());

    cout << setw(3) << setfill(' ') << "ID" << setw(5) << setfill(' ') << "Name" 
        << "\t" << setw(16) << setfill(' ') << "Job_Submit_Time" 
        << "\t" << setw(16) << setfill(' ') << "Job_Required_Time"
        << "\t" << setw(16) << setfill(' ') << "Job_Begin_Time"
        << "\t" << setw(16) << setfill(' ') << "Job_End_Time"
        << "\t" << setw(16) << setfill(' ') << "Job_Wait_Time"
        << "\t" << setw(16) << setfill(' ') << "Turnaround_Time"
        << "\t" << "Turnaround_Time_R" << endl;
    
    int totalTurnaroudTime = 0;
    double totalRightTurnaroudTime = 0;
    for (auto i : sim.getEndList()) {
        cout << setw(3) << setfill(' ') << 
            i.getID() << setw(5) << setfill(' ') <<
            i.getName() << "\t" <<
            i.getSubmitTime() << "\t" <<
            i.getTimeRequired() << "\t" <<
            i.getBeginTime() << "\t" <<
            i.getEndTime() << "\t" <<
            i.getWaitTime() << "\t" <<
            i.getTotalTime() << "\t" <<
            i.getRightTotal() << endl;
        totalTurnaroudTime += i.getTotalTime();
        totalRightTurnaroudTime += i.getRightTotal();
    }
    cout << "Avg turnaroud time: " << static_cast<double>(totalTurnaroudTime) / sim.getEndList().size() << " Second(s)" << 
        endl << "Avg turnaroud time with right: " << totalRightTurnaroudTime / sim.getEndList().size() << endl;
}
