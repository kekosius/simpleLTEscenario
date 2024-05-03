# LTE simulation

This file describes simple LTE scenario for ns-3 simulator. This scenario consists of:
- One eNB and two UEs
- Full Buffer traffic between them
- PF-FF LTE MAC sceduler
- Rlc & MAC level KPIs output

To run simulation place this file into ns-3 workspace folder, for example ```./ns-3.41/scratch``` and run build
``` ./ns3 build ```. After that run simulation with ```./ns3 run scratch/LTEscenatio.cc```. Output files should appear in the workspace folder

The script also supports passing the simulation time as an argument. To do this run program as below:

``` ./ns3 run "scratch/LTEscenatio.cc --simTime=1" ```, simTime - simulation time in seconds
