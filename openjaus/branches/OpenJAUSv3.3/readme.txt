RELEASE NOTES: OpenJAUSv3.3 beta (04/15/08)
==========================================



Target Operating Environment:
-----------------------------

This software is designed to be cross platform compatible. The code base has
been tested on a variety of operating systems and development environments
including: Linux (Ubuntu & Fedora Core) w/gnu toolchain, Windows w/MS Visual 
Studio 2005, and Windows w/ MinGW. All test machines have been little endian
byte order based. 


Installation (GNU Toolchain):
-----------------------------

Execute the make command in the following directories:

OpenJAUSv3.3/libjaus/ 
OpenJAUSv3.3/libopenJaus/ 

Currently the software must be installed with root privileges. This is important 
as the installation scripts attempt to write to the /usr/lib and /usr/include 
directories.

Extract the software to a folder in the /opt directory called "CIMAR". This should 
leave a folder containing the Core CIMAR libraries in the path (/opt/CIMAR/Core).

To install the software, run the make command in the /opt/CIMAR/Core directory. 
This will call the install script which will compile and install each library 
sequentially. Upon successful completion, the libraries files and associated header 
files will be copied to the appropriate directories.

*Note: The default installations of the libraries include all symbols and debug 
information within the shared object (.so) files. This is to facilitate efficient 
development and use of a run-time debugger. To reduce the size of the installed 
libraries, the information can be removed by using the "strip" command. 


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
4. Make sure the component is compiled first by running the "make" command.
5. Execute the component via the relative path. (./bin/cmpt) 
	
Custom or Experimental Message Implementation:
	
The Open JAUS library in C contains template message files "skeletonMessage.c" 
and "skeletonMessage.h." These files are designed to be easily cast (using a 
simple find and replace tool) into a specific message that can be included with 
the library upon reinstallation. They are located in the root message directories 
in their respective /src and /include folders within the /libjausC directory. 
		
The general way to implement a new message based on these templates is as follows:

1. Copy the "skeleton" templates into their proper directories (/command, 
   /experimental, etc...) based on the content of the intended message.

2. Rename the "skeleton" files to the intended specific JAUS message name. 
   ex: rename "skeletonMessage.c" to "myExperimentalMessage.c".

3. Change the contents of the header file (previously "skeletonMessage.h") to 
   reflect the correct JAUS message names.
   ex: Rename all "xXxX" to the proper JAUS message name.
   (Don't forget this process is CaSe SENsitive!)

4. Add to the message data structure in the header file the variables which are 
   defined for each of the fields in your JAUS message. The variables should be 
   of the correct JAUS type, and their names should correspond with that of the 
   field names in the JAUS document. (All scaled integer values should be of type 
   JausDouble within the message data structure).

5. Change the contents of the source file to reflect the correct JAUS message names
   ex: Rename all "xXxX" to the proper JAUS message name.
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
   comments should be referred to the openjaus.com discussion boards.

*  There is no standalone API documentation, which describes all data structures, 
   functions, or default behavior.

*  This implementation of the standard JAUS message set library does not contain 
   any of the Planning Subgroup messages.

*  A "ToString" method for each JAUS message and data structure is lacking from 
   this implementation and thus makes displaying critical information to the user 
   more cumbersome.
