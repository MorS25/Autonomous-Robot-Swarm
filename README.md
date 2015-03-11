# ROBOT-SWARM
Author: Avi Varshney
Created: March 08, 2015
Time: 3:03 AM

Overview:
	The end goal of this project is to have a a set of autonomous robots that act as one group (swarm).  Each robot will be able to communicate with one another, via RF Modules.  Each robot (node), will be equipped with a variety of sensors that allow it to collect environmental data.  
  
Features( Per Node ):														
  -Arduino 328p Microcontroller													
  -Flora Wearable GPS														
  -RF 433 MHZ Transmitter / Receiver Modules											
  -Four Omni-Wheel Drive													
  -Two encoders, across diagonal wheels												
  -NiMh Batterpack 7.2v														
  -Arduino Motor Expansion Shield												
  
Steps:																
	1. GPS Co-ordinates transmitted from PC via 433 mhz RF Transmitter Module.						
	2. Node reads data & node swarm confirmation										
	3. Current Location -> Destination											
	4. Confirmation within Nodes												
	5. Data Collection													
	6. Node swarm confirmation												
	7. Current Location -> Original Location										
	8. Data sent back to PC via 433 mhz RF Transmitter Module.								
	
Movement:																Each node has FIVE axis on which it may move.										
	-Forward / Backward													
	-Left Strafe / Right Strafe												
	-Left Rotation / Right Rotation												
	-Left Upward / Right Backward Diagonal											
	-Right Upward / Left Backward Diagonal											
