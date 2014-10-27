# Introduction
[ArduViz](@ref ArduViz) is a python script, consisting of several classes to enable the visualisation of a received layout and the flow of data from an arduino. Furthermore it is the counterpart to the 
[AppBuilder](@ref AppBuilder) library.

Currently supported are the following functions:
- Connection to a selected port (if the port can't be accessed you get an error message)

- Two different connection modes:
	+ simple connection (connect to port, at disconnect return to the main menue)
	+ connection with autoreconnect (connect to port, at disconnect wait for a new available connection on that port and then reconnect.)

- Receiving different layouts and display them. The layouts can include:
	+ Buttons
	+ Labels
	+ TextInputs
	+ Other Layouts

- Nested layouts, because layouts can contain layouts itself too

- Flexibly and fast interaction with your arduion by callbacks

- Running multiple arduinos on one host device

- Cross platform (Windows,Linux,MacOS, Android under development)

# Usage

The [ArduViz](@ref ArduViz) usage is hold very easy, if you followed the installation instructions. Just execute the [main.py](@ref ) and you will get to the main menue.

![](menu.png)

Here you can select the port (depending on your os) and select a connection mode.
That are the both already explained in the introduction.

- "Connect."
	+ The "Connect" button is a good choice if you are unsure which port your arduino is connected to.You can also use this mode, if you want to load a new sketch to your arduino, after the connection.
	So it is useful if you are currently working with your sketch. And just need a one time test.
- "Connect with auto reconnection."
	+ Use this mode when you are going to do several tests with the same code. You are able to test different actions of your system, just by turn out your usb wire and stuck it in again. The port will keep the same and ArduViz will connect to it again automatically.


That's it. The ArduViz script will do the rest for you like:
- Connecting
- Parsing
- Displaying the widget tree.

If you seek a deeper understanding of how the script works take a look at the ArduViz dokumentation.
You will also find possibilites for how and where to extend the code, e.g. for a diagram.

