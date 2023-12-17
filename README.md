# Team 010-40

## Members:
 - Jacob Lopez (lope0384)
 - Ryan Sauers (sauer319)
 - Evan Burkstrand (burks079)
 - Harrison Wallander (walla875)


## Project Overview:
This project is centered around upgrading a drone delivery simulation with specific design patterns, documentation, new entities, and whole new features. The main goal of this project is to teach how to plan out, implement, and engage with various design patterns, development processes, and general programming best practices. Specifically, it involved the implementing the following on top of already existing base code for a basic delivery drone simulation:
 - Design patterns: 
   - Composite factories for entity creation
   - Strategies for entity pathing
   - Decorators for package delivery celebrations
 - Implementing our own non-trivial features:
   - Battery decorator class and charging/draining of drone battery, along with charging station entity
   - Singleton data collection class and data analysis
 - Adding new helicopter, human, and car entities
 - Adding an "Stop Simulation" button
 - Doxygen documentation to all relevant source header class files
 - Google code styling for all relevant source files
 


## What the Simulation Does:
#### Initilization/UI and Simulation Basics:
The simulation simulates package scheduling, pickup, and delivery on the UMN-TC campus, with the method of delivery being flying drones. The simulation starts with initialization of the campus map, a helicopter, a drone with battery, and the recharge station as JSON Objects with set initial positions, sizes, and meshes. The UMN campus map is a static background that the whole simulation runs "on top" of, while the drone and helicopter are animated and move around on a 2D coordinate plane as the simulation progresses, and the recharge station is a static object on the map. The simulation also has a basic UI with wich the user can stop the simulation, go to the scheduling page, move the camera, lock the camera onto an entity, and change the simulation speed, along with a message box on the left for any notifications if needed. From the scheduling page, the user can add a human to the simulation or schedule a delivery by giving it a name, adding a pickup and destination location, and selecting the desired pathing strategy. The simulation works by repeatedly calling each entity's "update" function with the time interval since the last call to update as the sole parameter, which moves or changes the state of each entity based on what each entity is doing at the time of the update call.
#### Entities:
##### Drone:
 - The drone is spawned upon simulation start, and will remain stationary until it either runs out of battery or a delivery is scheduled. If it runs out of battery, it will go to the charging station and recharge, before continuing what it was doing when it ran out of battery, and if a delivery is scheduled, it will pick up the package, and use the specified pathing strategy to deliver the package to its destination. If the drone runs out of battery during a delivery it will immediately drop the package and go recharge, before picking up the package afterwards and continuing the delivery. The drone's battery runs out after 50 seconds of simulation time has passed, and takes 5 seconds to recharge. When the drone finishes a delivery, it celebrates, which is accomplished with the use of a celebration decorator class, which either makes the drone appear to jump or spin.
 - The drone's update function checks what the drone's state is (charging, moving to charger, moving to package, moving to destination, celebrating, or idle) and if it needs to change states due to battery level or changing simulation circumstances, then updates the state or moves using the correct strategy if needed.
##### Helicopter:
 - The helicopter is spawned upon simulation start, and repeatedly beelines to a random location before picking a new random location and repeating.
 - The helicopter's update function moves directly towards a location or randomly chooses a new one if needed.
##### Human:
 - A human is spawned upon simulation start, and more humans can be spawned by clicking the "Add Human" button on the scheduling page, and humans repeatedly move to a random location before picking a new random location and repeating.
 - The human's update function moves to a location using Astar pathing or randomly selects a new location if needed. 
##### Package:
 - A package is spawned at the pickup location when a delivery is scheduled, and remains stationary until a drone picks it up, at which point it will be "carried" by the drone until the drone either delivers it or runs out of battery. When the package is delivered, the package celebrates with the drone before being dropped off and remaining stationary until the simulation ends.
 - The package's update function checks if a drone is carrying it, and if it is, then it moves the package with the drone, otherwise the package remains stationary.
##### Charge Station:
 - The charge station is spawned upon simulation start, and does not move. It waits idly until a drone docks to it, at which point it charges the drone before undocking the drone and repeating.
 - The charge station's update function is empty, but the equivalent function is the dockDrone function, which takes in a drone ID and checks if a drone is already docked, and if it is the drone that called the function, then it undocks that drone, otherwise it returns false to indicate another drone is docked. If no drones are docked, it returns true and docks the drone.
##### Robot:
 - A robot is spawned at the destination location when a delivery is scheduled, and remains stationary as a marker of the destination for the package being delivered.
##### Battery:
 - The battery is spawned with the drone as a decorator onto the drone entity, and drains over 50 seconds of simulation time, and takes 5 seconds to recharge.
 - The battery update function checks if the drone is currently charging or not, and if it is, then it charges the drone such that it takes 5 seconds to fully refill the battery, otherwise it drains the battery such that it takes 50 seconds to drain fully.
#### Data Collection:
Additionally, there is a singleton data collection class that runs in the background collecting data about drone battery, turns, and pathing, along with general simulation data like time running. This class outputs a number of CSV files full of data points for analysis.

## How to Run:
#### With Source Code (Using SSH via VScode):
 - Navigate to the team-010-40-hw4 directory
 - Run "make -j"
 - In the bottom left of the window, slightly to the right of the SSH address tab, navigate to the port forwarding tab
 - Click "Forward a port"
 - Type whichever port number you are planning on using (Default is 8081), and press enter
 - Run "./build/bin/transit_service <port_number> apps/transit_service/web/"
 - Then, in a browser, go to "http://127.0.0.1:<port_number>" to view the simulation, and "http://127.0.0.1:<port_number>/schedule.html" to schedule deliveries
#### With Dockerfile (Link Below):
 - Assuming that Docker is already installed and working, the first step is to open a terminal and run "docker login"
 - Then, run "docker run --rm -it -p 8081:8081 (TODO: Input name of our docker file)"
 - Then, in a browser, go to "http://127.0.0.1:8081" to view the simulation, and "http://127.0.0.1:8081/schedule.html" to schedule deliveries


## New Features:
#### Battery Decorator Class/Charging Station:
The battery feature consists of two parts, a battery decorator and a charging station. It implements functionality such that drones have a limited amount of time that they can spend flying before needing to recharge at the station. The decorator is added onto the drone and slowly drains over time, and upon reaching 0%, the drone paths to the charging station and recharges before continuing with what it was doing before. The charging station is just a stationary entity that can accomodate one drone and charges it over time. This feature is worth adding since it adds a bit more realism to the simulation since a real drone would need to recharge quite often, and because it provides some challenges when it comes to programming. These challenges include figuring out how to add an entire new state and path strategy variable to the drone class used to seek out a charging station when needed without breaking existing functionality and trying to find a way to charge and drain a battery, and usee charge state of the battery to influence what the drone does within the simulation, along with figuring out how to dock only one drone at a time and how to tell if a drone has reached the charging station. This lead to some fairly complicated logic and some interesting workarounds like replacing the charging station's default update function (inherited from IEntity) with a separate dockDrone function that works to dock or undock a drone that calls it with its ID while ensuring only one drone can dock at any given time. The design pattern used was the decorator design pattern since it was a very convenient way to attach a battery to an already existing drone entity and to allow the drone to drain and charge a battery without affecting the drone's already existing functionality. The user cannot directly influence the battery functionality, but the user will see the drone go the charge station once every 50 seconds and stop to charge for 5 seconds (at the default simulation speed).
#### Singleton Data Collection Class:
The data collection feature runs in the background of the simulation and gathers data from primarily update functions. It gathers data about drone battery, turns, and pathing as the simulation progresses. It also gathers the run time of the simulation as a whole. When the simulation is stopped, it saves this data to 3 CSV files, which are then used for analysis of drone efficiency, efficiency of various pathing algorithms, and other parameters. This feature is interesting since it allows us to not just watch the simulation, but to also gather data from it and see the total outcome of the simulation, along with finding out interesting information about which algorithms are better for certain trip distances. The design pattern used is a singleton since it was the obvious choice for a class that exists as the same instance for all parts of the simulation to add their data to. This feature is not interactable while the simulation is running, but when it stops, the user is able to view the CSV files to see the data itself. Additionally, the analysis of our data can be found within this repository, so the user can see our conclusions and observations about the data we gathered from our runs of the simulation.


## Sprint Retrospectives:
#### Sprint 1:
This sprint went quite well at the beginning, but about halfway through, the work slowed down a lot. This slow down has lead to the group being behind on tasks, and the group is now in a crunch to finish the project shortly before it is due, which is abviously not good. This issue can be attributed mainly to a lack of communication and code compatibility. Early on in the sprint, the group was often communicating what was being done, how it was being done, and what concerns were found with the codebase. This allowed for collaboration and for people to help with code that others were struggling to implement, and allowed for easy code integration. This lead to steady progress through the first half of the sprint, with tasks being finished quickly and effectively and on time. Around halfway through the sprint, though, the communication stopped, and the work slowed. This is because people were attempting their tasks, but realizing that other tasks needed to be finished first, so they waited for others to finish their tasks or change their code to work with the implementation others were using. This lead to essentially a deadlock within the group, since no one was making progress besides some small code upgrades and tinkering with upcoming tasks. This major issue occured because the group assumed that the way every member was planning on implementing their tasks was compatible with each other's code from other tasks. This was a false assumption since there are an infinite number of ways to implement the features and tasks that were allocated amongst the group, and there was no realistic way they would all line up without communication beforehand. The obvious solution to this problem was to communicate more, and to collaborate more. This solution can be enacted through synchronous meetings to work on code, which are going to happen during sprint 2, but which did not happen during sprint 1. This solution will allow for questions to be directly asked to group members, and for future implementation conflicts to be worked out quickly without causing larger issues, or slowing down progress significantly. Other than this issue, the sprint went generally well, and the quality of code was high, with relatively few bugs and setbacks, although some of the tasks for sprint 1 were not completed by the end of the sprint, and were pushed on to the backlog of sprint 2.
#### Sprint 2:
This sprint started off as more of the same from sprint one, as the issues with communication and integration were still being worked out, but once the sprint 1 issues were fixed, sprint 2 went smoothly. Work was done very effectively in person, and the project was finished, albeit with sigficantly more effort than sprint 1 due to time constraints requiring a lot of work towards the end. The only notable issue the group had was with the code implementation itself, since implementing the singleton class proved quite difficult, and some parts of the other code had to be changed to accommodate it. This issue was addressed during the sprint by asking the group for help, and the singleton class's implementation was figured out quickly. Other than that small issue, the work was steady and everything went well, and all goals were met.


## Dockerfile Link: 
(TODO: Paste link to Dockerfile on Dockerhub here)


## YouTube Presentation Overview Link: 
(TODO: Paste link to YouTube presentation here)


## UML Diagrams:
### Battery Decorator
![BatteryDecorator (1)](https://media.github.umn.edu/user/22463/files/13d4b7d6-9fa9-4583-902a-25e2f31479ff)

### Singleton Data Collection

## Data Analysis
All data was gathered from performing the same delivery route with the different pathing algorithms.

![Screenshot 2023-12-17 110736](https://media.github.umn.edu/user/22463/files/a00a03bd-8872-4edc-9bff-ed10e65a44ed)

### Battery Usage
![Battery](https://media.github.umn.edu/user/22463/files/80b9bb7f-4bc7-4f7e-b944-a153c5d05dbe)

Astar's less use of battery in general is a good indicator that it spends more time idle or travelling to the package than carrying it, which allows it to save on battery usage. Its also worth noting that Dijkstra was able to complete its route in one less charge. Finally, the DFS algorithm tended to bring it farther away from the charging station, which is why you see it spend more time at zero, and less time in delivery.

### Time Efficiency
![Delivery Time](https://media.github.umn.edu/user/22463/files/ce9cdeda-8d01-436b-bedd-8c5c13c1a334)

While the efficiency for Dijkstra was driven by its close proximity to the charging station in this test, each of these algorithms likely have a strength for specific situations. DFS could be much better at finding longer routes, and Astar may be better at handling more routes due to its efficient battery usage.

### Left Vs Right Turns
![turns](https://media.github.umn.edu/user/22463/files/f10f1157-6ce7-450f-93e0-b04f72726227)

While all are relatively similar, the most battery efficient algorithm in this case was the one that used the most right turns.
