[Communication](../Communication.md)
# Board to Sensor Comms
The Sonar Sensor currently selected (Parallax Ping Ultrasonic Sensor) follows a defined communication protocol that uses 1 pin on a microcontroller.  

## Overview
Typically the pin would be triggered in the following method (at a high level)

```mermaid
graph TD;
  Start[START];
  SetPinOutput[Set Pin to Output]
  PulsePin[Pulse Pin]
  SetPinInput[Set Pin to Input]
  ReadPinPulse[Read Pin Pulse Width]

  Start --> SetPinOutput
  SetPinOutput --> PulsePin
  PulsePin --> SetPinInput
  SetPinInput --> ReadPinPulse
  ReadPinPulse --> SetPinOutput
```

## Specification
The actual specification for this protocol is defined here:
![](ref/PingCommunicationProtocol.png)