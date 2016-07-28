# OpenCVGraph
## Goal
Provide a user-friendly interface to build computer vision algorithms.
By moving and linking "nodes" representing the different OpenCV functions, the user will build his algorithm without writing lines of code.
I want it to be extensible, so the nodes are packaged into DLLs and loaded dynamically at runtime (adds up a little salt to the development)
## What's working
Features currently working :
* Loading nodes from DLLs
* Adding new nodes to a graph and moving them around
* Connecting nodes together by their "pins" (which represent nodes inputs/outputs)
* Running a live simulation (which updates automatically at each action on the graph)
* Displaying inputs and outputs for each node
* Deleting nodes and connections
* Scrolling in the graph canvas to have more space (no zoom in/out for instance)
