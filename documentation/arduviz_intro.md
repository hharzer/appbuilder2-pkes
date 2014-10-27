# Introduction
[ArduViz](@ref ArduViz) is a python script to enable the visualisation of received layouts and the flow of data from an arduino. Furthermore it is the counterpart to the [AppBuilder](@ref AppBuilder) library.

Currently supported are the following functions:
- Connection to a selected port (if the port can't be accessed you get an error message)
- Two different connection modes:
	+ simple connection (connect to port, at disconnect return to the main menu)
	+ connection with autoreconnect (connect to port, at disconnect wait for a new available connection on that port and then reconnect.)
- Receiving different layouts and display them. The layouts can include:
	+ Buttons
	+ Labels
	+ TextInputs
	+ Other nested layouts
- Flexible and fast interaction with your arduino by callbacks
- Connecting multiple arduinos with one host device
- Cross-platform (Windows, Linux, MacOS, Android *under development*)

# Usage

[ArduViz](@ref ArduViz)' usage is intended to be as straightforward as possible. You simply have to follow the given [instructions](md_documentation_installation.html) on how to install all needed packages and you're ready to go. 

You'll be greeted by the main menu.

![Main menu](menu.png)

Here you can select the port (depending on your operating system) and select a connection mode.

- `Connect`
	+ The client makes an attempt to connect to the specified port. If the connection isn't available or otherwise not usable, the attempt will fail and you'll return to the main menu.
- `Connect with auto reconnection`
	+ Use this mode when you are going to do several using the exact same port. This, however, will block the serial connection. 


That's it. The ArduViz script will do the rest for you like:
- Connecting and handshake
- Reading input, displaying elements
- Sending and receiving data.

If you seek a deeper understanding of how the script works, take a look at the ArduViz dokumentation.
You will also find possibilites for how and where to extend the code, e.g. for a diagram.

