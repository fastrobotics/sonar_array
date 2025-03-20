# Lexicon

## Term: Board
_Summary_: Typically used in this project when referring to separate content running on a Propeller.  This differentiates content that's running natively in a ROS system (such as on an x86 Computer, Raspberry Pi,etc).

_Related Terms_:

_Example_: [Sonar Array Board](boards/SonarArrayBoard/)

| References |
| --- |
| | 

## Term: Cog
_Summary_: `Each cog sits dormant until called into action—referred to as "launching a cog"—at which point the cog executes
its given code independently from, and in parallel alongside, other active cogs.`

_Related Terms_: 

_Example_:

| References |
| --- |
| [Propeller 2 Hardware Manual](doc/LiteratureReview/ref/Propeller2/Hardware/Propeller-2-Hardware-Manual-20221101.pdf) | 



## Term: Cross-Talk
_Summary_: `Crosstalk is a phenomenon by which a signal transmitted on one circuit or channel of a transmission system creates an undesired effect in another circuit or channel.`

_Related Terms_: [Interference](#term-interference)

_Example_: Sonar B can receive sonar waves from Sonar A and report a distance that is incorrect.

| References |
| --- |
| [Wikipedia](https://en.wikipedia.org/wiki/Crosstalk) | 

## Term: Driver
_Summary_: Software that is tied to specific hardware.

_Related Terms_: 

_Example_:

| References |
| --- |
|  | 

## Term: Local-Interference
_Summary_:Interference caused by a Sensor on an ego machine that is received by another sensor on the ego machine.  As more information is likely known about the ego machine, it may be possible to remove this interference via post-processing.

_Related Terms_: [Cross-Talk](#term-cross-talk),[Nonlocal Interference](#term-nonlocal-interference)

_Example_: Sonar B can receive sonar waves from Sonar A and report a distance that is incorrect.  However since there may be other information known about Sonar A (timing, state, etc) this interference may be able to be removed.

| References |
| --- |
| | 

## Term: Multi-Path
_Summary_:`Multipath interference is a phenomenon in the physics of waves whereby a wave from a source travels to a detector via two or more paths and the two (or more) components of the wave interfere constructively or destructively.`

_Related Terms_:

_Example_:

| References |
| --- |
| [Wikipedia](https://en.wikipedia.org/wiki/Multipath_propagation#:~:text=Multipath%20interference%20is%20a%20phenomenon,wave%20interfere%20constructively%20or%20destructively.) | 

## Term: Node
_Summary_:Typically used in this project when referring to a ROS Node.

_Related Terms_:

_Example_: [Sonar Array Node](nodes/SonarArrayDriverNode/)

| References |
| --- |
| | 

## Term: Nonlocal-Interference
_Summary_:Interference caused by a Sensor on a non-ego machine that is received by a sensor on the ego machine.  As less information known about this non-ego machine, it may be more difficult to remove this interference via post-processing.

_Related Terms_: [Cross-Talk](#term-cross-talk), [Local Interference](#term-local-interference)

_Example_:

| References |
| --- |
| | 



## Term: Sonar
_Summary_:`Sonar (sound navigation and ranging or sonic navigation and ranging) is a technique that uses sound propagation (usually underwater, as in submarine navigation) to navigate, measure distances (ranging), communicate with or detect objects on or under the surface of the water, such as other vessels.`

_Related Terms_:

_Example_:

| References |
| --- |
| [Wikipedia](https://en.wikipedia.org/wiki/Sonar) | 