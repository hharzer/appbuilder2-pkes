#include "AppBuilder.h"

AppBuilder appb(12, 5, String("AVH\0"), 2048);


int mydelay = 0;
uid8 t2 = 0, b4 = 0, disconnected = 0;

void turn_on(uid8 id, char *string)
{
    digitalWrite(13, HIGH);
}

void turn_off(uid8 id, char *string)
{
    digitalWrite(13, LOW);
}

void hallo2(uid8 id, char *string)
{
    appb.set_text(b4, string);
}

void serialEvent()
{
    appb.serial_event();
}

void onconnect (uid8 id, char *unwichtig)
{

    uid8 l = appb.start_layout();
    t2 = appb.add_label();
    uid8 b3 = appb.add_button();
    uid8 b2 = appb.add_button();
    uid8 l2 = appb.start_layout();
    uid8 t1 = appb.add_input();
    uid8 b = appb.add_button();
    b4 = appb.add_label();
    appb.end_layout(l2);
    appb.end_layout(l);

    appb.send_components();
    //appb.sendappb();
    //Serial.println("Hallo Welt");
    appb.set_text(t2, "jojo");
    appb.set_text(b, "on");
    appb.set_text(b2, "off");
    appb.set_text(b3, "WOW");
    appb.set_text(b4, "rekd");

    appb.add_callback(b, turn_on);
    appb.add_callback(b2, turn_off);
    appb.add_callback(t1, hallo2);

    digitalWrite(13, LOW);
}

void ondisconnect (uid8 id, char *unwichtig)
{
    //mydelay = 1000;
    digitalWrite(13, HIGH);
    disconnected = 1;
}

// the setup function runs once when you press reset or power the board
void setup()
{
    // initialize digital pin 13 as an output.
    // Serial.println("INITIALIZING");
    pinMode(13, OUTPUT);

    digitalWrite(13, HIGH);

    appb.set_onconnect(onconnect);
    appb.set_ondisconnect(ondisconnect);

    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
    appb.refresh();

    if (!disconnected)
    {
        char mydelaystr[32];
        String(mydelay).toCharArray(mydelaystr, 32);
        appb.set_text(t2, mydelaystr);
        mydelay++;
    }
    else
    {
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(mydelay);              // wait for a second
        digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
        delay(mydelay);              // wait for a second
    }

}
