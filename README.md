# PIA_bouncingLogo
This program replicates the bouncing DVD logo screensaver.

<br/>
<p align="center">
  <img src="https://media1.giphy.com/media/02fzO2B9FwQ1GHD5I5/giphy.gif" />
</p>

## Description
After start, user is asked to choose which simulation mode will be enetered. Options are terminal or allegro.
#### Mode Terminal:
If user input is ***terminal*** short vizualization in terminal is started. No other user inputs are required.
#### Mode Allegro:
If user input is ***allegro*** the vizualization will be in new display window. User is asked to set width and then height of display screen. If no integer value is typed, recommended 800x600 disaplay is used.
Vizualization in display starts right after the user input. Information about ***How many bounces with walla does it take to hit the first corner*** is printed in terminal.
#### Invalid input:
If user input is not ***terminal*** or ***allegro*** program ends.

## How to run
This program uses the allegro5 library. We will install the allegro5 library using vcpkg.
### Install vcpkg:
Clone the vcpkg repository: git clone https://github.com/Microsoft/vcpkg.git \
First, make sure you are in the directory where you want to install the tool.
### Run the boot script to build vcpkg:
In the directory where you have installed vcpkg, run Powershell and type the command:  **.\vcpkg\bootstrap-vcpkg.bat**
### Install libraries for your project:
To install the allegro5 library type the command: **.\vcpkg install allegro5**

Next, enter the command: **.\vcpkg integrate install**
**Powershell will print the command, which you will copy to the Nuget Package Manager Console.**

(See tutorial for Visual Studio https://www.youtube.com/watch?v=0h1lC3QHLHU&t=187s&ab_channel=TroubleChute)
