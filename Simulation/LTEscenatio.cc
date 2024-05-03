#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>
#include "ns3/config-store.h"

using namespace ns3;

int main (int argc, char *argv[])
{
	Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
	
	Time simTime = Seconds(1);
	
	//Enabling passing of simulation time as an argument
	CommandLine cmd(__FILE__);
    	cmd.AddValue("simTime", "Total duration of the simulation", simTime);
    	cmd.Parse(argc, argv);
	
	//configuring LTE MAC Scheduler (pf-ff)
	lteHelper->SetSchedulerType("ns3::PfFfMacScheduler");
	
	//creating one eNB node and two UE nodes
	NodeContainer eNBnodes;    
	eNBnodes.Create(1);
	NodeContainer UEnodes;	  
	UEnodes.Create(2);
	
	//implementing the movement model to eNB and UE nodes
	//this model will place all nodes at constant position (0,0,0)
	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(eNBnodes);
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(UEnodes);

	//implementing the LTE protocol stack to eNB and UE nodes
	NetDeviceContainer eNBdevs;
	eNBdevs = lteHelper->InstallEnbDevice(eNBnodes);
	NetDeviceContainer UEdevs;
	UEdevs = lteHelper->InstallUeDevice(UEnodes);
	
	//connecting UEs with eNB via RRC
	lteHelper->Attach(UEdevs, eNBdevs.Get(0));

	//Radio bearer activation
	enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
	EpsBearer bearer(q);
	lteHelper->ActivateDataRadioBearer(UEdevs, bearer);
	
	//enabling MAC and Rlc level key performance indicators 
	lteHelper->EnableMacTraces();
	lteHelper->EnableRlcTraces();

	//LTE scenario simulation
	Simulator::Stop(simTime);
	Simulator::Run();
	Simulator::Destroy();
	
	return 0;
}



