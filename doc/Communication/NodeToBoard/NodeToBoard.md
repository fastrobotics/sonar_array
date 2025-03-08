[Communication](../Communication.md)

# Node to Board Comms
## Overview
A protocol and an interface is required to interface a ROS Node to the Board that is connected to the Sonar Sensors.

## Methodology
There are a variety of protocols/interfaces that can be defined for this purpose. 

## Interface Selection

The interface is typically restricted to what's available on the hardware.  At present the following interfaces are believed to be supported.  Note that in order to be on this list, the Board (running on a Propeller 2) and a Node (running on either an x86 computer or a Raspberry Pi) must both be supported.

| Interface | Comments |
| --- | --- |
| Serial/UART | Max Data Rate is believed to be at least 115200 bps, if not much higher. Some documentation suggests that baudrate up to 921600 bps should work.  Board and Node should natively support. |
| Ethernet | Not sure at present Board will support this without siginficant wiring/external connections. |

## Protocol Design
In general the Protocol (i.e. the data encoding on the interface) should be agnostic to the interface.  In practice, there are restrictions.  For example, a typical I2C interface would use a specialized protocol.  However a protocol designed for an UART interface would typically be supported on an Ethernet interface.

### Serial Protocol Design
A POC Serial Protocol is designed in [Serial Protocol Design](SerialProtocolDesign.ods).  There are at least 2 POC's present there.  Further testing is required to understand the actual capabilities of the Board and the Node, which may limit the design of the protocol.

Note that in the current state, main design consideration is given to optimizing the streaming message that is sent from the Board to the Node for the main sensor data.  Further enhancements will include:
- Configuration
- Time Sync
- Enable/Disable
