[Nodes](../Nodes.md)
# Sonar Array Node
## How It Works

## Setup Instructions


## Usage Instructions
### Sonar Array Node

#### Configuration


### Test Driver
A Test Executable for the Sonar Array Node Driver can be ran by running:
```bash
/install/bin/exec_servohat_driver
```

A Test Executable for the GPS Hat Driver can be ran by running:
```bash
/install/bin/exec_servohat_driver
```
This will give output similiar to:
```bash
Tester for Sonar Array Node Driver
-h This Menu.
-d Device.  Default: /dev/ttyUSB0
-s Sonar Count. Default: 20
-l Logger Threshold. [DEBUG,INFO,NOTICE,WARN,ERROR]

```

Examples:
```
./install/bin/exec_sonararray_node_driver -d /dev/ttyUSB0 -s 20 -l DEBUG
```



## Software Design
### Class Diagrams
![](../../output/Legend.png)
![](../../../nodes/SonarArrayDriverNode/driver/doc/output/SonarArrayNodeDriverClassDiagram.png)
![](../../../nodes/SonarArrayDriverNode/doc/output/SonarArrayDriverNodeClassDiagram.png)

### Sequence Diagrams
![](../../../nodes/SonarArrayDriverNode/driver/doc/output/SonarArrayNodeDriverSequenceDiagram.png)
![](../../../nodes/SonarArrayDriverNode/doc/output/SonarArrayDriverNodeSequenceDiagram.png)

## Diagnostics Strategy
| Diagnostic Type | Message | Level | Description |
| --- | --- | --- | --- |
| COMMUNICATIONS | INITIALIZING | INFO | Set when Comms with Sonar Array are initializing. |
| COMMUNICATIONS | INITIALIZING_ERROR | ERROR | Set when the Comms port to the Sonar Array can't be initialized. |
| COMMUNICATIONS | DROPPING_PACKETS | WARN | Set when Comms Port is missing data. |
| COMMUNICATIONS | DEVICE_NOT_AVAILABLE | ERROR | Set when Comm Port becomes unavailable. |
| COMMUNICATIONS | NODATA | ERROR | Set when Comm Port never received data. |
| COMMUNICATIONS | NOERROR | INFO | Set when no error is present. |
| DATA_STORAGE | INITIALIZING | INFO | Set when Driver is initializing configuration. |
| DATA_STORAGE | INITIALIZING_ERROR | ERROR | Set when Driver can't initialize configuration. |
| DATA_STORAGE | NOERROR | INFO | Set when no error is found with Data Storage. |
| SENSORS | INITIALIZING | INFO | Set when Sensors are Initializing. |
| SENSORS | DROPPING_PACKETS | WARN | Set when Sensor Array is missing data. |
| SENSORS | DEVICE_NOT_AVAILABLE | ERROR | Set when Sonar Array becomes unavailable. |
| SENSORS | MISSING_HEARTBEATS | WARN | Set when Sonar Array is missing heartbeat messages. |
| SENSORS | NODATA | ERROR | Set when no Sensor data has been received. |
| SENSORS | NOERROR | INFO  | Set when no error is present with Sensors. |
| SYSTEM_RESOURCE | INITIALIZING | INFO | Set when Driver is initializing System Resource monitoring. |
| SYSTEM_RESOURCE | INITIALIZING_ERROR | ERROR | Set when Driver can't initialize System Resource monitoring. |
| SYSTEM_RESOURCE | NOERROR | INFO | Set when no error is present with System Resource monitoring. |
| TIMING | INITIALIZING | INFO | Set when Timing system is initializing. |
| TIMING | INITIALIZING_ERROR | ERROR | Set when Timing system has an initializing error. |
| TIMING | DROPPING_PACKETS | WARN | Set when there is missing data related to Timing. |
| TIMING | NOERROR | INFO | Set when no error is present with Timing. |
