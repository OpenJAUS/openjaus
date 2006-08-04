Open JAUS Project Release Notes
Version: 3.2
Last Revised: 08/04/06

1. Development Group Information

The majority of this software was developed by Tom Galluzzo, Danny Kent, and 
Bob Touchton at the University of Florida's Center for Intelligent Machines and 
Robotics (CIMAR). This JAUS implementation was used by Team CIMAR for the 2005 
DARPA Grand Challenge. The primary purpose of the software was to use a 
standardized messaging architecture on Team CIMAR's vehicle, The NaviGator. 
Each source file contains within the header comments the names of the 
developer(s), in order to establish proper ownership where appropriate.

Contact information:

Center for Intelligent Machines and Robotics (CIMAR)
	Director: Dr. Carl Crane
	phone: 352-392-9461
	email: ccrane AT ufl DOT edu

Tom Galluzzo:
	phone: 352-870-2230
	email: galluzzt AT gmail DOT com

Danny Kent:
	phone: 386-451-3802
	email: jaus AT dannykent DOT com

Bob Touchton:
	phone: 904-612-9370
	email: btouch AT comcast DOT net

2. Target Operating Environment

This software is designed and intended to be used on a Linux or Unix like 
operating system, and has been run successfully on several different makes of 
i386 machines running a Redhat or Fedora distribution of Linux. If the target 
distribution has a significantly different directory structure, the install may 
need to be modified to accommodate. 

This JAUS implementation has two primary code bases written in separate languages:

First, the CIMAR Node Manager and its referenced JAUS message library are written 
in Java. The Java JAUS message library contains a subset of the complete standard 
JAUS message set, mostly containing only those messages which are needed by the 
Node Manager (some others have been implemented to aid future development of a 
complete library in Java).

Second, a JAUS message and data structure library is written in C. This library 
is complete with the exception of the Manipulator Subgroup messages. Also 
written in C is an interface to the CIMAR Node Manager, and a Template Component. 
The Template Component is designed to use the C Node Manager interface to connect 
to the CIMAR Node Manager and exchange JAUS messages.

The dependencies for using both code bases are as follows:

Requirements:
1. gcc (http://gcc.gnu.org/) 
2. make (http://www.gnu.org/software/make/)
3. ant (http://ant.apache.org/)
4. Java SDK with a Java Run Time Environment (RTE) 
   (version 1.4 or higher) (http://java.sun.com/)
5. curses (Required for Template Component’s user interface) 
   (http://www.gnu.org/software/ncurses/ncurses.html)
	
3. Installation

Currently the software must be installed with root privileges. This is important 
as the installation scripts attempt to write to the /usr/lib and /usr/include 
directories.

Extract the software to a folder in the /opt directory called “CIMAR”. This should 
leave a folder containing the Core CIMAR libraries in the path (/opt/CIMAR/Core).

To install the software, run the make command in the /opt/CIMAR/Core directory. 
This will call the install script which will compile and install each library 
sequentially. Upon successful completion, the libraries files and associated header 
files will be copied to the appropriate directories.

*Note: The default installations of the libraries include all symbols and debug 
information within the shared object (.so) files. This is to facilitate efficient 
development and use of a run-time debugger. To reduce the size of the installed 
libraries, the information can be removed by using the “strip” command. 

4. Method of Operation

Running the Node Manager:

When the Node Manager is installed, it copies a script called NM to the 
/usr/local/bin. This script will run the Node Manager assuming it is in the 
default location of /opt/CIMAR/Core/nodeManager/. The Node Manager has a 
configuration file called nodeManager.conf which controls the functionality of 
the Node Manager. Documentation for the various parameters in this file is 
included within the comments contained therein.
	
Running the Template Component:

1. From a command prompt, execute a single instance of the CIMAR Node Manager.
2. Start a new terminal session.
3. Enter the root directory of the component (i.e. the directory containing the 
   components Makefile)
4. Make sure the component is compiled first by running the “make” command.
5. Execute the component via the relative path. (./bin/cmpt) 
	
Custom or Experimental Message Implementation:
	
The Open JAUS library in C contains template message files "skeletonMessage.c" 
and "skeletonMessage.h." These files are designed to be easily cast (using a 
simple find and replace tool) into a specific message that can be included with 
the library upon reinstallation. They are located in the root message directories 
in their respective /src and /include folders within the /libjausC directory. 
		
The general way to implement a new message based on these templates is as follows:

1. Copy the “skeleton” templates into their proper directories (/command, 
   /experimental, etc...) based on the content of the intended message.

2. Rename the “skeleton” files to the intended specific JAUS message name. 
   ex: rename "skeletonMessage.c" to "myExperimentalMessage.c".

3. Change the contents of the header file (previously "skeletonMessage.h") to 
   reflect the correct JAUS message names.
   ex: Rename all “xXxX” to the proper JAUS message name.
   (Don’t forget this process is CaSe SENsitive!)

4. Add to the message data structure in the header file the variables which are 
   defined for each of the fields in your JAUS message. The variables should be 
   of the correct JAUS type, and their names should correspond with that of the 
   field names in the JAUS document. (All scaled integer values should be of type 
   JausDouble within the message data structure).

5. Change the contents of the source file to reflect the correct JAUS message names
   ex: Rename all “xXxX” to the proper JAUS message name.
   (Again, this process is CaSe SENsitive!)

6. Add any initialization code to the dataInitialize() function.

7. Add the FromBuffer() parsing code to the source file. (Remember to test for 
   presence vector bit indicators, if there is a presence vector, and remember 
   that scaled integer values must be transformed from and to their floating point 
   form during these processes.)

8. Add the ToBuffer() packing code to the source file. (Remember to test for 
   presence vector bit indicators, if there is a presence vector, and remember 
   that scaled integer values must be transformed from and to their floating 
   point form during these processes.)

9. If any data members of the message have been dynamically allocated destroy 
   them in the dataDestroy() function.

10. Recompile the library and correct all warnings or errors.

11. Reinstall the library

5. Known Issues

*  There is a general lack of documentation within the code, any questions or 
   comments should be referred to the appropriate author.

*  There is no standalone API documentation, which describes all data structures, 
   functions, or default behavior.

*  This implementation of the standard JAUS message set library does not contain 
   any of the Manipulator Subgroup messages (Codes 4600h - 47FFh).

*  A method that iteratively or recursively computes the size, in bytes, of a 
   serialized or "packed" JAUS message has not been implemented. This functionality 
   would allow for the appropriate sizing of memory buffers when packing and 
   parsing JAUS messages to and from a data stream.

*  A "ToString" method for each JAUS message and data structure is lacking from 
   this implementation and thus makes displaying critical information to the user 
   more cumbersome.
   
   
   