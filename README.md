# DiIconTool
Icon files creating/unpacking tool.
Created using DiLib : https://github.com/JohnDBV/DiLib

Version : 1.0.0

# Build instructions : 

1. Clone the repo(DiLib will already be added as a project dependency)
2. Open a git shell and change the directory to the "DiIconTool" sources directory
3. Execute : git clone https://github.com/JohnDBV/DiLib.git
4. Build and run !

# The help contains the following info : 

![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/06e2e951-229e-4ce6-88c5-1ee9ac2c5d30)

# Complex use-case : 

Conducting tests on Windows, x64, inside the 'C:\test' folder(as example), we have the following folder structure : 
![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/384a2722-7a45-4fe8-ae5b-57e53070806b)

1. Generate a sample icon file if you don't have any using : DiIconTool create-sample
A new file will appear, and no output will be displayed (yet) :
![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/8df23f1e-f6d2-4c55-870e-601e4bd6e459)

2. Let's unpack the icon file, to get access to the "inside images" using : DiIconTool unpack SampleIconPngFormat.ico

The output is : 
![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/878be642-96ec-4cbf-b738-c3d87a414e36)

A few more files will appear as a result : 
![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/9ce01411-00b7-4f9f-acf7-c01496108dd9)

3. Considering we want to create a new icon file called "NewIconFileWithThreeImages.ico", containing the first 3 generated images, we have to run : 
DiIconTool pack NewIconFileWithThreeImages.ico image1.png image2.png image3.png

The output is : 
![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/16905a1a-a3b4-4b2a-9183-932ca2364e9e)

As a result, the "NewIconFileWithThreeImages.ico" file is also generated, as we can see below :
![image](https://github.com/JohnDBV/DiIconTool/assets/36071862/1818c166-8d0e-4a59-ba36-00580bcfb96a)

Hope the app will prove itself useful, and C# interop will come soon for the DiLib IconFile.
Enjoy !
