# Cooking Robot
Creating a robot that will function as an appliance to cook in the home
requires a cheap, high performance robotic arm and manipulator. Current open
source options have performance limitations or do not take advantage of some
of the constraints available to a robot in the kitchen. This repository provides
a robot that does.

## Current Design
The current design will provide 6 degrees of freedom to the end effector.
The arm hangs upside down in a gantry which is built from generic [1530 Aluminum
extrusion](https://www.fazstore.ca/product/15qe1530/) providing an effective
workspace of approximately 6' x 2' x 2'. This choice of workspace is common to an 
apartment kitchen, but is easily modified as necessary by replacing the corresponding extrusion.
Currently 2 degrees of freedom have been implemented providing motion in the plane
of the table.

Each drive axis contains a [ODrive](https://github.com/odriverobotics/ODrive)
controller and [CUI AMT102-V](https://www.cuidevices.com/product/resource/amt10.pdf) encoder.
All of the components pertaining to the structure of each axis can be 3D printed. 
Besides this, there are an assortment of pulleys, 8mm shafts and bearings, and GT2 belts. 
Emphasis has been placed onsourcing parts that are readily available on Amazon and
quickly/easily replacable.
