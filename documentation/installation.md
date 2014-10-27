## At first

If you don't have it yet, download the arduino USB driver (for example with the arduino IDE)
[Download page](http://arduino.cc/en/Main/Software)

## Windows

1. Install all files from the package/Windows 
    - python2.7
    - pySerial
    - pygame
2. Setting the environment variables:
    - My Computer > Properties > Advanced System Settings > Environment Variables
    - Add as seen below
3. For Kivy follow the instructions on [Kivy Installation](http://kivy.org/docs/installation/installation-windows.html)
4. Start the `main.py` via the `kivy.bat`
5. Run the application

| variable     | value                                     |
|--------------|-------------------------------------------|
| `PYTHONHOME` | Your python directory (e.g. `C:\Python27` |
| `PYTHONPATH` | `yourdir\Lib`                             |
| `Path`       | PYTHONHOME;PYTHONPATH					   |

## Linux / MacOS

_The following may require root rights:_

1. If not already installed, setup [python](https://www.python.org/download/) or with your packet manager
2. Download [pySerial](https://pypi.python.org/pypi/pyserial)
3. Change your directory to the extracted folder and run: `python setup.py install`
4. Setup [Kivy](http://kivy.org/#download) (you will find detailed installation guides on this side)
5. Run the python client with: 
    - `python main.py` for Linux
    - `kivy main.py` for MacOS

If there are still questions or hints to improve this tutorial, don't hesitate to let us know. Thank you.