Sorting Simulator
==========================
How to Compile and Build
==========================
1. Qt Framework was used for this project. You might need to download Qt Creator to run the code. It can be downloaded here: https://www.qt.io/download-open-source/
2. Once you have Qt installed and the code pulled in your local directory, you will need to make a few changes. You need to know the working directory of the project code and change that in the .cpp files. The files DataSet.cpp, tracereader.cpp, tracewriter.cpp, genealgorithm.cpp, and mainwindow.cpp all set up a private data member localDataPath. You will need to manually change its value to match your local project path. For example, if the project code is in a directory called /Users/firstlastname/simulator/, then you should make sure the "localDataPath" variable is set to "/Users/firstlastname/simulator/" in all of these classes' constructors.
3. After those changes are made, just click on the run button on the lower left corner of the Qt creater.


==============================
How to use our program
================================
