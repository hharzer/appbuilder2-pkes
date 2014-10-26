# Introduction

[AppBuilder](@ref AppBuilder) is a library that's designed to communicate with a compatible counterpart, e.g. a computer, an android phone or even another arduino handset.

Currently supported are the following functions:
-  Connection detection (disconnction detection isn't currently supported due to restriction from arduino's serial library)
-  Handshake to ensure that you're connected to a compatible and trustworhty counterpart
-  Building layouts and sending them (You can nested layouts etc. The view, though, depends on your counterpart)
-  Setting, receiving and executing callback for both buttons and textinputs (the latter also receives the string that as inside the textinput)
-  Setting text

There are several features still to be implemented like creating diagrams and sending data continously. The latter can be emulated by sending text.

# Usage

The library was designed to be as straighforward as possible, so all names should be self-explanatory and easy to understand. Nonetheless, a tutorial on how to use the library will beneift your understanding.

**Please refrain from using Serial while also using the client software.**

## Getting started

### Initializing

[AppBuilder](@ref AppBuilder)'s constructor is defined as follows:

~~~~~~~~~~~~~~~{.cpp}
AppBuilder(byte num_com, byte num_callbacks, String handshake, int attempts);
~~~~~~~~~~~~~~~

The arguments explained:
* `num_com` is the _number of components_ you want to use
* `num_callbacks` is the _number of callbacks_ you want to use
* `handshake` is the _handshake phrase_ that's used to connect to a counterpart
* `attempts` is the _number of attempts_ made at doing a handshake

An exmaple for initializing your [AppBuilder](@ref AppBuilder) object would look like this:

~~~~~~~~~~~~~~~{.cpp}
AppBuilder appb(12, 5, String("AVH\0"), 2048);
~~~~~~~~~~~~~~~

You can store _12_ components that have _5_ callbacks. The connection phrase would be _AVH_ (ArduinoVizHandshake) and the number for attempts _2048_.

Next thing you need would be a function that's called when you're connected. That's probably your first encounter with `gen_callback`. It will be explained later on.

The signature of `gen_callback` is defined as follows:
~~~~~~~~~~~~~~~{.cpp}
typedef void (*gen_callback)(uid8, char *);
~~~~~~~~~~~~~~~

Since there's no uid or character array involved, you can safely ignore both arguments. When your function gets called, you'll be able to create your layout.

### Building a layout

Currently, there are four different UI elements available:
* Layout
* Label
* Button
* Text input

The last two offer a callback functionality which will be explained later on. For now, though, we want to create an UI and send it to the counterpart.

First of all, we need a layout that acts as a container for the UI. The layout also specifies how all elements are sorted and arranged. However, the client organizes this for now. After we created a layout, we can add other components such as buttons and label. There's also the possibily of nesting layout to group and arrange them.

~~~~~~~~~~~~~~~{.cpp}
uid8 l = appb.start_layout();
t2 = appb.add_label();
uid8 b3 = appb.add_button();
uid8 b2 = appb.add_button();
uid8 t1 = appb.add_input();
uid8 b = appb.add_button();
b4 = appb.add_label();
appb.end_layout(l);
~~~~~~~~~~~~~~~

Since you want to change properties and add callbacks later, you need to save all uids of component you want to modify. All function that add components to the layout will return the uid of the created element if it was successfull, otherwise ( for example when you've already added the specified amount of components ) it will return 0.

Also, you probably noticed that, when you call `end_layout`, you have to pass a uid, namely the one of the layout you actually want to close. 

After you created all components and saved all necessary uids, you can send them:

~~~~~~~~~~~~~~~{.cpp}
appb.send_components();
~~~~~~~~~~~~~~~

## Setting properties

### Setting the text of somehting 

To change the text of any component (except the layout, everyone has a caption), you simply need to call `set_text` and pass the uid and the text.

A call could look like this:

~~~~~~~~~~~~~~~{.cpp}
appb.set_text(t2, "Sample Text 1");
appb.set_text(b, "on");
appb.set_text(b2, "off");
appb.set_text(b3, "Sample Text 2");
appb.set_text(b4, "Sample Text 3");
~~~~~~~~~~~~~~~

## Setting and receiving callbacks

To be able to react to callbacks, you need to assign ceratin components certain function. 

To set such a function, it is important to comply to `gen_callback`. The arguments are the id of the element that initiated the callback and a possible character array with the contents of an input. A function may look like this:

~~~~~~~~~~~~~~~{.cpp}
void turn_on(uid8 id, char *string)
{
    digitalWrite(13, HIGH);
}

void turn_off(uid8 id, char *string)
{
    digitalWrite(13, LOW);
}
~~~~~~~~~~~~~~~

As you probably noticed, this functions toggle the built-in led. we want to assign them to the buttons labeled _on_ and _off_. Their ids are stored in `b` and `b2`.

~~~~~~~~~~~~~~~{.cpp}
appb.add_callback(b, turn_on);
appb.add_callback(b2, turn_off);
~~~~~~~~~~~~~~~

Now, when you click the corresponding buttons you'll notice that you can now turn the led on and off. A text callback would look similarly:

~~~~~~~~~~~~~~~{.cpp}
void text_callback(uid8 id, char *string)
{
    appb.set_text(b4, string);
}
~~~~~~~~~~~~~~~

Keep in mind that the passed string is only valid within your callback. It is possible that it gets invalidated after leaving the function.

~~~~~~~~~~~~~~~{.cpp}
appb.add_callback(t1, text_callback);
~~~~~~~~~~~~~~~

# Callbacks explained

You need to be aware of certain facts regarding callback handling. One of them was already mentioned above: strings are only valid wihtin the function. But there are other things you have to keep in mind.

## When to expect them

Callbacks can only be recognized when you're arduino executes `serial_event`. Because of that, there's the possibility that callbacks get dropped if your computation take too long and you're sending too many callbacks from the client. 

![Callback cycle](Callback_Ablauf.png)

The callback stack can hold up to _two_ callbacks at the same time.

# General sequence of events

![General process](Allgemeiner_Ablauf.png)
