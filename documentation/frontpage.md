# Introduction

ArduViz and AppBuilder are libraries intended to provide an easy way of vizualizing data and informations from your arduino with the help of your PC or Android phone (coming soon!). Additionally, you can interact with your arduino via GUI - inlcuding buttons, text inputs and labels - and send it commands or even control it.

At its core, AppBuilder and ArduViz are designed to be as versatile as possible. It runs on any platform (Windows, Mac, Linux) and supports most arduinos. Furthermore, you're theoretically able to customize both libraries to your liking, e.g. adding, altering or removing elements at whim.

This documentation is centered around the use of the serial connection between arduino and client.

<img src="ArduViz_Mac.png" style="float: left; height: 15em; margin-right: 1%; margin-bottom: 0.5em;">
<img src="ArduViz_Win.png" style="float: left; height: 15em; margin-right: 1%; margin-bottom: 0.5em;">
<img src="ArduViz_Linux.png" style="float: left; height: 15em; margin-right: 1%; margin-bottom: 0.5em;">

<p style="clear: both;">

The layout of your biult app will always look the same, regardless of your operating system. (Tested on Windows 7, Mac OS 10.10, Ubuntu 14.04)

Also, the handling and usage will not differ between these platforms. However, you have to have the same preconidtions (listed below) installed on every system. The tutorial will explain what you need and where to get it.																						

## Features
- GUI powered by the [Kivy](http://kivy.org) library (with huge potential of extensions, e.g.: diagram,progressbar ,pictures,...)
- Two connection modes: connection and auto reconnection
- Connect multiple arduinos to one PC
- Multi-platform (Linux,Windows,Mac OS)
- Well documented
- Easily extensible
- Fast start tutorial


## What you need to start
- Python 2.7
- [Kivy](http://kivy.org)
- [pySerial](http://pyserial.sourceforge.net)

We have also made a detailed installtion guide [here](md_documentation_appb_intro.html).


###AppBuilder:
The functionality of the AppBuilder (arduino library) can be found [here](md_documentation_installation.html).

###ArduViz:
The functionality of the ArduViz application (client) can be found [here](md_documentation_arduviz_intro.html).
