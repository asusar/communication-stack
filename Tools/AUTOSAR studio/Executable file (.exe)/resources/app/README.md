AUTOSAR Studio Desktop Application
====================
## Table of Contents
- [Intro](#intro)
- [Setup](#setup)
- [Knowledge](#knowledge)
- [Software Component ARXML Elements](#software-component-arxml-elements)
- [ToDo](#todo)


## Intro

<h4 align="center">An educational tool for AUTOSAR to help junior embedded enigneers with learning AUTOSAR </h4>
AUTOSAR Studio Project is written with Web Technologies (HTML,CSS,JavaScript) and also electron framework to make it as Desktop Application

The aim of the software is to
Design Software Components Model and Change it to ARXML files (SWCs.ARXML ,DataTypeAndInterface.ARXML)

AUTOSAR Studio will try to extract the following information:

-  Software Components Standard Tags (AUTOSAR Release 4.3.0)
-  Composition DataTypeAndInterface Tags (AUTOSAR Release 4.3.0)

## Setup

Clone this repository on your machine.

    git clone https://github.com/MinaMourice/AsuSAR-Stack-19.git
Open your terminal and navigate to the repo's directory.

    cd AsuSAR-Stack-19/AsuSAR-Stack-19
Run electron installation command:    
    
    npm install --save-dev electron
    
Run start command to run the application:

    npm start
    

## Knowledge 
- What is AUTOSAR ?
    - AUTOSAR – AUTomotive Open Systems ARchitecture
        Middleware and system-level standard, jointly developed by
        automobile manufacturers, electronics and software suppliers
        and tool vendors.
    - It pursues the objective of creating and establishing an open and standardized software architecture for automotive electronic    control units
    - **“cooperate on standards, compete on implementations”**
- What is the software component (SWC)?
    
  - The software component is a piece of code that carries out an application or part of an application. In AUTOSAR, software components        are not limited to the application layer, i.e. they also exist in the RTE and BSW layer.
  - The AUTOSAR Software Components encapsulate an application which runs on the AUTOSAR infrastructure.
  
 - What is the basic structure of SWC?
    - Software Component Description
        * Ports
            * P-Ports: Provide Ports
            * R-Ports: Require Ports
            * PR-Ports: Provide Require Ports
        * Internal Behavior 
            * Runnables
            * Events
    - Implementation.
    
  - What are the ports’ interfaces?
    - Client-Server: The server provides services while one or more clients may use its services to carry out tasks when the operation invoked on a server uses arguments supplied by a client to perform the requested task.
    - Sender-Receiver: this way of communicating allows one receiver to get information from multiple senders or a sender to send information to an arbitrary number of receivers.
    
  - What is the runnable?
    - A runnable entity is the smallest code fragment inside a SWC. It is these Runnables that are mapped to OS tasks and will execute the behavior of the SWC. 
        
  - What is ARXML?
    - ARXML files are a type of files used across AUTOSAR, to author and configure the AUTOSAR software.
    - ARXML stands for AUTOSAR XML, which is nothing but a schema with certain parameters, this schema is provided by AUTOSAR to standardize the process & increase portability.
    
## Software Component ARXML Elements

- AUTOSAR Tags

    - Define Autosar XML schema version
    
          <AUTOSAR 
                xsi:schemaLocation="http://autosar.org/schema/r4.0 AUTOSAR_4-3-0.xsd" 
                xmlns="http://autosar.org/schema/r4.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
                <AR-PACKAGES>
                        ....
                </AR-PACKAGES>
          </AUTOSAR>
         
- Top Level Packages (AR-PACKAGES)

    - This element is the container of all AUTOSAR packages that are added into the file.
    
            <AR-PACKAGES>
                <AR-PACKAGE>
                </AR-PACKAGE>
                <AR-PACKAGE>
                </AR-PACKAGE>
                .
                .
                .
            </AR-PACKAGES>
- AR-PACKAGE 

   - AUTOSAR Package containing package name , Software components and Their structure  
        
            <AR-PACKAGE>
                <SHORT-NAME>PackageName</SHORT-NAME>
                <ELEMENTS>
                    <APPLICATION-SW-COMPONENT-TYPE>
                        .......
                    </APPLICATION-SW-COMPONENT-TYPE>
                    <SWC-IMPLEMENTATION>
                        .......
                    </SWC-IMPLEMENTATION>
                 </ELEMENTS>
            </AR-PACKAGE>
- Application Software Component

    - This element describes the software component and its ports.
        
            <APPLICATION-SW-COMPONENT-TYPE>
                <SHORT-NAME>SWC_Name</SHORT-NAME>
                <PORTS>
                    .......
                </PORTS>
                <INTERNAL-BEHAVIORS>
                    .......
                </INTERNAL-BEHAVIORS>
            </APPLICATION-SW-COMPONENT-TYPE>
            
    - Ports Types
        
         – PPort (provided port) or RPort (required port)
        
         – Interface provided (provided interface) or (required interface)
    
    
                <PORTS>
                    <P-PORT-PROTOTYPE>
                        <PROVIDED-COM-SPECS>
                            .....
                        </PROVIDED-COM-SPECS>
                    </P-PORT-PROTOTYPE>   
                    .
                    .
                    .
                    <R-PORT-PROTOTYPE>
                        <REQUIRED-COM-SPECS>
                            .......
                        </REQUIRED-COM-SPECS>
                    </R-PORT-PROTOTYPE>       
                    .
                    .
                    .
                    .
                </PORTS>
                
     - Internal Behavior
     
        - This element describes the behavior of the software component, including its Runnables and its events
        
        
               <INTERNAL-BEHAVIORS>
                    <SWC-INTERNAL-BEHAVIOR>
                        <SHORT-NAME>SWC_InternalBehaviorName</SHORT-NAME>
                            <EVENTS>
                                ......
                            </EVENTS>
                            <RUNNABLES>
                                .......
                            </RUNNABLES>
                     </SWC-INTERNAL-BEHAVIOR>   
                </INTERNAL-BEHAVIORS>
             
             
          - Events
                We implement Five event types ( Init , Timing , Data Recieved , Data Recieved Error , Operation Invoked )
                    that trig a runnable
                    
                    <EVENTS>
                          <INIT-EVENT>
                          </INIT-EVENT>
                          <TIMING-EVENT>
                          </TIMING-EVENT>
                          <DATA-RECEIVED-EVENT>
                          </DATA-RECEIVED-EVENT>
                          <DATA-RECEIVE-ERROR-EVENT>
                          </DATA-RECEIVE-ERROR-EVENT>
                          <OPERATION-INVOKED-EVENT>
                          </OPERATION-INVOKED-EVENT>
                    </EVENTS>
            
          - Runnables
                
                    <RUNNABLE-ENTITY>
                        <SHORT-NAME>RunnableName</SHORT-NAME>
                        <DATA-SEND-POINTS>
                        </DATA-SEND-POINTS>
                        <DATA-WRITE-ACCESSS>
                        </DATA-WRITE-ACCESSS>
                        <SERVER-CALL-POINTS>
                        </SERVER-CALL-POINTS>
                    </RUNNABLE-ENTITY>
## ToDo

Frontend
* [x] Make Intropage.
* [x] Make Drawing Block.
* [x] Enter Data Type and Interfaces.
* [x] Add more UI Features.
* [x] Software Component Properties

Backend
* [x] Generate basic ARXML Prototype.
* [x] Generate SWCs.ARXML Files as Autosar standard.
* [x] Generate DataTypeAndInterface.ARXML Files as Autosar standard.
