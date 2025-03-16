[Home](../../README.md)
# Literature Review

## ToDo List
| ToDo |
| --- |
| Define: `Interference` |
| Define: `Cross-Talk` |
| Terminology difference between ego-interference and agent-interference |
| Review Propeller 2 Edge Board Circuit Diagram |
| Document Propeller 2 Boot Process, including timing |
| Add story to support Propeller 2 Programming via Linux |
| Better understanding of semaphores in Spin |
| Lit Review: Octave/Matlab simulation |
| Lit Review: Occupancy Grid Algo's |
| Sensor Characterization includes dead-zone in front of sensor |
| CAD Model of Propleller 2/Edge Board |
| Set LED's on Edge for Diagnostic/Status |
| Install Octave on Dev Computers and run basic tutorials |
| Update architecture to support creation of map/occupancy grid in a separate node, and rename current "Sonar Array Node" to "Sonar Array Driver Node" |

## Questions to Answer
| Question | Answer |
| --- | --- |
| What is the Ping Sonar FOV | |
| Any way to detect sonar-sonar interference | |
| What is actual propogation speed of sonar? | |
| How to use 2 instances of a module (example: 2 uart's) | |
| Possible to plug in Program Port on Propeller 2 without resetting? | |
| How do interrupts work on Propeller 2? | |
| How does cognew process work ? | |
| Any utility to using the SPI Flash on the Propeller, such as storing previous run information. | |
| Should add a SD Card to Prop 2 Hardware ? | |
| Understand how to do temperature compensation for sonars.  Is this already done internally in the Ping's? | |
| How does Boot Mode selection work on Prop Edge?  What should I pick? | |
| What's the best-case optimiziation that can be done (related to timing) for parallel processing with Ping's?  How does this scale with number of Ping's?  i.e what's the difference between running every Ping in its own cog vs running all Ping's on one cog, using max wait times? | |