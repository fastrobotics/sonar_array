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
| Status | Diagnostic Type | Message | Level | Description |
| --- | --- | --- | --- | --- |
| READY | COMMUNICATIONS | INITIALIZING | INFO | Set when Comms with Sonar Array are initializing. |
| READY | COMMUNICATIONS | INITIALIZING_ERROR | ERROR | Set when the Comms port to the Sonar Array can't be initialized. |
| READY | COMMUNICATIONS | DEVICE_NOT_AVAILABLE | ERROR | Set when Comm Port becomes unavailable. |
| READY | COMMUNICATIONS | NODATA | ERROR | Set when Comm Port never received data. |
| READY | COMMUNICATIONS | NOERROR | INFO | Set when no error is present. |
| READY | DATA_STORAGE | INITIALIZING | INFO | Set when Driver is initializing configuration. |
| READY | DATA_STORAGE | INITIALIZING_ERROR | ERROR | Set when Driver can't initialize configuration. |
| READY | DATA_STORAGE | NOERROR | INFO | Set when no error is found with Data Storage. |
| READY | SENSORS | INITIALIZING | INFO | Set when Sensors are Initializing. |
| READY | SENSORS | DROPPING_PACKETS | WARN | Set when Sensor Array is missing data. |
| READY | SENSORS | DEVICE_NOT_AVAILABLE | ERROR | Set when Sonar Array becomes unavailable. |
| READY | SENSORS | NODATA | ERROR | Set when no Sensor data has been received. |
| READY | SENSORS | NOERROR | INFO  | Set when no error is present with Sensors. |
| READY | SYSTEM_RESOURCE | INITIALIZING | INFO | Set when Driver is initializing System Resource monitoring. |
| READY | SYSTEM_RESOURCE | INITIALIZING_ERROR | ERROR | Set when Driver can't initialize System Resource monitoring. |
| READY | SYSTEM_RESOURCE | NOERROR | INFO | Set when no error is present with System Resource monitoring. |