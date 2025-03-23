[Boards](../Boards.md)
# Connect Board
The Connect Board provides the GPIO connections necessary to connect multiple Sonar's to the Parallax Propeller.

## ToDo List
| ToDo |
| --- |
| Check Shunt Size/Footprint |
| Resistor Footprint |
| Board Mounting Holes |
| Prop Pin Connection Names |

## Requirements
| Requirement | Description |
| --- | --- |
| Connect up to 24 Sonars | GPIO connection for up to 24 Sonars |
| Propeller Pin Protection | 4.7k Ohm Resistor on every Sonar Signal Pin. |
| Connect groups of 4 Sonars | 3 Banks of 8 Sonars |
| Signal protection disable resistor | Able to disable signal protection resistor per 8-bank |
| Secure connection | Secure connection to Propeller 2 |
| 3.3V/5V Select | Jumper selector for each 8-bank |
| Comm Port | Has 4-pin comm port connection to Raspeberry Pi |