Sorting Simulator
==========================
How to Compile and Build
==========================
 1. Qt Framework was used for this project. You might need to download Qt Creator to run the code. It can be downloaded here: https://www.qt.io/download-open-source/
 2. Once you have Qt installed and the code pulled in your local directory, you will need to make a few changes. You need to know the working directory of the project code and change that in the .cpp files. The files DataSet.cpp, tracereader.cpp, tracewriter.cpp, genealgorithm.cpp, and mainwindow.cpp all set up a private data member localDataPath. You will need to manually change its value to match your local project path. For example, if the project code is in a directory called /Users/firstlastname/simulator/, then you should make sure the "localDataPath" variable is set to "/Users/firstlastname/simulator/" in all of these classes' constructors.
 3. After those changes are made, just click on the run button on the lower left corner of the Qt creater.

==============================
How to use our program
==============================
-There are two sets of radio buttons: Algorithms and Data
-The set of radio buttons under the header Algorithms represents the options of algorithms you can choose from to simulate
      Note: These include Insertion Sort, Merge Sort, and Selection Sort
-The set of radio buttons under the header Data represents the different types of data sets you can choose to sort 
      Note: These include Inverse and Random
-In order to use the program, you must first select the sorting algorithm you want to use, as well as the data set you want to sort for the simulation
      Note: The default sorting algorithm is Insertion Sort and the default data set type is Inverse
-Once you have selected the algorithm and data set, you may use the simulation toolbar at the top left of the GUI window to run the simulation. The four buttons correspond to four different simulation actions:
      1. |<  The simulation will step back through the algorithm from its current position to the initial start of the   
             algorithm
      2.  <  The simulation will step back one step in the algorithm from its current position
      3.  >  The simulation will step forward one step in the algorithm from its current position
      4. >|  The simulation will step forward through the algorithm from its current position to the end of the algorithm
