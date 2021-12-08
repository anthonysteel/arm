# Cooking Robot
Creating a robot that will function as an appliance to cook in the home
requires a cheap, high performance robotic arm and manipulator. Current open
source options have performance limitations or do not take advantage of some
of the constraints available to a robot in the kitchen. This repository provides
a robot that does.

## Design
### Cobot Arm
The arm is a generic 6-DOF cobot design similar to a UR5 or iiwa. It is actuated
using Ben Katz's wonderful [MIT Cheetah Motor and Motor Controller design](https://dspace.mit.edu/handle/1721.1/118671)
which can be built yourself or purchased from a Chinese knock-off distributor, such as
[T-Motor's AK60-6](https://store.tmotor.com/goods.php?id=1138), [My Actuator's
RMD-X6](https://www.robotshop.com/en/my-actuator-rmd-x6-brushless-dc-gear-motor-bldcrs485reduction-ratio-16.html) or equivalent. 
