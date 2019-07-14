
<p align="center">
  <h1 align="center">ASUSAR Communication Stack</h1>
</p>

<p align="center">
  <b>Ain Shams University</b> Open Source Implementation of the AUTO<b>SAR</b> Standard.
</p>

<details>
 <summary>Contents</summary>

 - [What is AUTOSAR?](#what-is-autosar)
 - [AUTOSAR Communication Stack](autosar-communication-stack)
 - [Project Description](#project-description)
 - [Project Supervisors](#project-supervisors)
 - [License](#license)

</details>

# What is AUTOSAR?
AUTomotive Open System ARchitecture,
Middleware and system-level standard, jointly developed by
automobile manufacturers, electronics and software suppliers
and tool vendors.
More than 100 members
##### Motto: 
“cooperate on standards, compete on implementations”
##### Reality:
current struggle between OEM and Tier1 suppliers
##### Target: 
facilitate portability, composability, integration of SW components over the lifetime of the vehicle
<p align="center">
  <b>AUTOSAR Layered Software Architecture</b>
  <img src="https://www.embitel.com/wp-content/uploads/2015/04/1-AUTOSAR-Archtecture.jpg"/>
<p align="center">

# AUTOSAR Communication Stack
A software stack that provides communication services to the Basic Software Modules and Application Layer or Application Software<br>
Depending on the Bus Type of the in-vehicle network (such as CAN, LIN, Flex-Ray … etc.), implementation of the communication stack is executed .<br>
<p align="center">
  <img src="http://www.embitel.com/wp-content/uploads/2015/04/autosar-communication-stack.png"/>
<p align="center">
  
# Project Description
We have work through AUTOSAR Software layers , from the application layer to MCAL Layer .

##### Embedded C :
We implement a lot of Autosar interfaces in the following Modules :
  - Service Layer :
    - OS
    - COM Module
    - PDUR
    - CANTP
  - ECU Abstraction Layer
    - CANIF
  - Microcontroller Abstraction Layer
    - CAN Driver
##### AUTOSAR Tools  :
  - Developer Tools :
     - AUTOSAR Studio<br>
         - A tool for designing the architecture of software components (SWCs) for AUTOSAR ECUs, similar to <br><b>[DaVinci Developer](https://www.vector.com/int/en/products/products-a-z/software/davinci-developer/)</b>
   - Configuration Tools :
      - RTE Tool
      - OS Tool
      - CANTP Tool
      - CAN Driver Tool
      - Main Configuration Tool
##### Applications :
  - Seat Heater Application on more than one ECU (TM4C123 Board)
      - We are integrating all AUTOSAR Modules implementation and our configuration tools to make a working application
      
# Project Supervisors

  - **Dr.Sherif Hammad** 
    * Email: sherif.hammad@eng.asu.edu.eg
  - **Eng.Mohamed Abdelhay**
    * Email: mhmd.a.elhay@gmail.com

# License

Copyright © 2019, [Faculty of Engineering Ain Shams University](https://eng.asu.edu.eg/).
Released under the [apache license v2.0](LICENSE).
