## Cooking Robot
Creating a robot that will function as an appliance to cook in the home
requires a cheap, high performance robotic arm and manipulator. Current open
source options have performance limitations or do not take advantage of some
of the constraints available to a robot in the kitchen. This repository provides
a robot that does.

## Current Design
The current design will provide 6 degrees of freedom to the end effector. Two of these
have already been implemented, providing motion in the plane of the table.
Each drive axis is controlled in closed loop using [ODrive](https://github.com/odriverobotics/ODrive)
controllers and [CUI AMT102-V](https://www.cuidevices.com/product/resource/amt10.pdf) encoders.
The arm hangs upside down in a gantry which is built from generic [1530 Aluminum
extrusion](https://www.fazstore.ca/product/15qe1530/). All of the components pertaining
to the structure of the arm can be 3D printed. Besides this, there are an assortment
of pulleys, 8mm shafts and bearings, and GT2 belts. Emphasis has been placed on
sourcing parts that are readily available on Amazon and quickly/easily replacable.
