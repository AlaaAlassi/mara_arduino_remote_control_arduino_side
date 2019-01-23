# mara_arduino_remote_control_arduino_side
The arduino side source code to control Mara robotic arm remotely 

Author: Jack cox
(Jack.cox@nobleo.nl)

# The aim of this demo
An investigation of the capabilities of the current release of ROS2 is carried out. Focus is maintained on the networking capabilities of the DDS middleware system and possible participants in the shared DDS data space. In particular, a ROS2 package known as [micro-XRCE-DDS](https://github.com/eProsima/Micro-XRCE-DDS) is used to  allow eXtremely Resource Constrained Environment devices to communicate with other devices through the DDS publisher/subscriber model. This is demonstrated with an Arduino implementation. A simple demo of the networking capabilities of ROS2 is shown.

# The architecture

An Arduino MEGA 2560 was programmed to obtain data from an ultrasonic sensor and send this data, via the DDS middleware to a ROS2 system. This range data was then used to control the trajectory of a MARA M-Cobot simulation. To achieve this, a few different packages are used. The first is [micro-XRCE-DDS](https://github.com/eProsima/Micro-XRCE-DDS), this package provides a client-server system to allow the Arduino to participate in the DDS data space. [micro-XRCE-DDS](https://github.com/eProsima/Micro-XRCE-DDS) provides an agent which performs operations such as participant, subscriber and publisher creation. In turn, the Arduino communicates with the agent, informing it which entities to create in the DDS data space. For the Arduino code, an existing library called [ros2arduino](https://github.com/ROBOTIS-GIT/ros2arduino) is used. 


The diagram below shows the system architecture. The Arduino instructs the micro-XRCE-DDS agent to create and publish to the topic “/arduino_ranger”. The data from an ultrasonic sensor plugged into the Arduino is sent as a ROS2 message type “sensor_msgs/Range”. The ROS2 Subscriber/Publisher takes the range data and converts it to an angle for the simulated robot joint to achieve. This is then published to its own topic which is picked up by the gazebo simulation on both computers simultaneously. The simulated robot [MARA](https://acutronicrobotics.com/products/mara/) is designed to operate in the ROS2 environment. 
![architecture](https://github.com/AlaaAlassi/mara_arduino_remote_control_arduino_side/blob/master/assets/Setup_Diagram.jpg?raw=true)
      
# The implementation 

RangePubTest.ino is the arduino code. Range.hpp is a header file required by ros2arduino since it doesn’t include the Range message type by default. If the code does not compile for the Arduino you are using, then the default size of the data packet can be reduced from 512 bytes to a lower value by altering the relevant header file. The lowest spec board that I was able to get it working on was an Arduino MEGA 2560 which has 256kb flash, 8kb ram and a 16Mhz 8-bit processor.

# Project setup 
Because this is a networking demo, you will need two host devices wit ROS2 installed in both. in the first device (labtop 1) you need to  
  - install [micro-XRCE-DDS](https://github.com/eProsima/Micro-XRCE-DDS) 
  - connect your Arduino to it and flash RangePubTest.ino
  
On the other host device (labtop 2) you will instll ros2 packages related to MARA robot simulation, The steps to do so are in this reposetory :
  - [mara_arduino_remote_control](https://github.com/AlaaAlassi/mara_arduino_remote_control).

 






