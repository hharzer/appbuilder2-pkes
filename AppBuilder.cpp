#include "AppBuilder.h"


AppBuilder::AppBuilder(byte num_com, byte _num_callback, String handshake, int _attempts)
{
    is_connected = 0;
    onconnect = 0;
    ondisconnect = 0;
    num_components = num_com;
    num_callbacks = _num_callback;
    current_cursor = 0;

    components = new int[num_components];
    for (byte i = 0; i < num_components; i++)
    {
        components[i] = 0;
    }

    callback_index = 0;

    handshake_phrase = handshake;
    attempts = _attempts;

    callbacks.id = new uid8[num_callbacks];
    callbacks.callback = new gen_callback[num_callbacks];

    for (byte i = 0; i < num_callbacks; i++)
    {
        callbacks.id[i] = 0;
        callbacks.callback[i] = 0;
    }
}

void AppBuilder::flush_buffer(char *buffer, byte size)
{
    for (byte i = 0; i < size; i++)
    {
        buffer[i] = 0;
    }
}

void AppBuilder::execute_callbacks()
{
    if (callback_stack != 0)
    {
        uid8 first_id = callback_stack >> 8; //Extract first id from stack, id is 1 byte
        uid8 second_id = callback_stack; //Extract second id from stack
        byte index = 0; //Index to see how many callback have already been checked
        byte already_one_executed = (second_id & first_id) ? 0 : 1; // variable to ask if one callback was already executed so you can end the search if the second one was found
        callback_stack = 0; // Reset to indicate that the callbacks were already executed

        while (index < callback_index)
        {
            if (callbacks.id[index] == first_id)
            {
                callbacks.callback[index](first_id, serial_buffer);
                if (already_one_executed)
                    return; // if one callback was already executed, both now should've been executed, thus making it unneccessary to check other callbacks
                already_one_executed = 1;
            }
            if (callbacks.id[index] == second_id)
            {
                callbacks.callback[index](second_id, serial_buffer);
                if (already_one_executed)
                    return; // s.a.
                already_one_executed = 1;
            }
            index++;
        }


    }

}

uid8 AppBuilder::add_callback(uid8 id, gen_callback callback)
{
    if (callback_index < num_callbacks)
    {
        callbacks.id[callback_index] = id;
        callbacks.callback[callback_index] = callback;
        callback_index++;
        // Serial.println(id);
        // Serial.println(callbacks.id[callback_index - 1]);
        return id;

    }
    return 0;
}

void AppBuilder::set_onconnect(gen_callback onc)
{
    onconnect = onc;
}

void AppBuilder::set_ondisconnect(gen_callback ondc)
{
    ondisconnect = ondc;
}

void AppBuilder::serial_event()
{
    char temp_c = 0;
    // delay(2);
    while (Serial.available())
    {
        temp_c = Serial.read();
        if (temp_c == '!') // only a callback, no text
        {
            delay(2);
            callback_stack = callback_stack << 8; //make room on stack
            temp_c = Serial.read() - 48; // transform from a written character (ascii) to a number
            callback_stack |= temp_c; // "push" on stack
        }
        else if (temp_c == '?') //callback with text, e.g. input
        {
            callback_stack <<= 8; //make room on stack
            temp_c = Serial.read() - 48; // Transormation from characters ('A') to actual uids
            callback_stack |= temp_c;

            // additional processing to capture the string that was sent

            temp_c = 0;
            flush_buffer(serial_buffer, 32); //prepare buffer
            delay(2); // wait for serial buffer(arduino) to get ready again
            while (Serial.available())
            {
                if (temp_c < 32)
                {
                    serial_buffer[temp_c] = Serial.read(); //save character in buffer
                    temp_c++;
                }
                else
                {
                    return;
                }
                delay(2); // wait for serial to get ready again
            }

        }
    }
}

bool AppBuilder::handshake()
{
    // Serial.println("Handshake 1");
    int unsuccessful_attempts = 0;
    flush_buffer(serial_buffer, 32);

    byte index = 0;

    while (unsuccessful_attempts < attempts)
    {
        Serial.println(handshake_phrase);
        while (Serial.available() && index < 31)
        {
            if (index < 31)
            {
                serial_buffer[index] = Serial.read();
                delay(2);
                index++;
            }
        }
        serial_buffer[index] = '\0';
        String temp_phrase = String(serial_buffer);
        if (handshake_phrase.equals(temp_phrase))
            return true;
        //unsuccessful_attempts++;
    }

    return false;
}

void AppBuilder::refresh()
{
    //Serial.println("hier");

    delay(2);

    if (!Serial)
    {
        if (is_connected)
        {
            ondisconnect(0, 0);
            is_connected = 0;
        }
    }
    else
    {
        if (!is_connected)
        {
            // Serial.println("Handshake 0");
            if (handshake())
            {

                onconnect(0, 0);
                // Serial.println("SUCCESS");
                is_connected = 1;
            }
        }
        else
        {
            // if connected and he knows it ...
            // Serial.println(callback_stack);
            execute_callbacks();
        }
    }

}

void AppBuilder::send_components()
{

    char temp_compoment [3]; // Save a component (type, id) and terminate it with a \0

    temp_compoment[0] = '#'; //Start of protocol
    temp_compoment[1] = '\0';//current_cursor + 48; //Num of components // Obsolete because of change
    temp_compoment[2] = '\0'; //End
    Serial.print(temp_compoment);

    for (int i = 0; i < current_cursor; i ++) //For each component
    {
        temp_compoment[0] = (components[i] >> 8); //Type
        temp_compoment[1] =  components[i];//ID
        temp_compoment[2] = '\0';//End
        Serial.print(temp_compoment);
    }

    Serial.println('#');

}

uid8 AppBuilder::add_component(uid8 type)
{
    if (current_cursor < num_components)
    {
        components[current_cursor] = type << 8;
        components[current_cursor] |= current_cursor + 48; // Transforms Index to a real character, eg 0 -> 49('0')
        return current_cursor++ ;
    }
}

uid8 AppBuilder::add_component(uid8 type, uid8 id)
{
    if (current_cursor < num_components)
    {
        components[current_cursor] = type << 8;
        components[current_cursor] |= id + 48;
        current_cursor++;
        return id;
    }
}

uid8 AppBuilder::end_layout(uid8 layout)
{
    return add_component('L', layout);
}

uid8 AppBuilder::start_layout()
{
    return add_component('L');
}

uid8 AppBuilder::add_button()
{
    return add_component('B');
}

uid8 AppBuilder::add_input()
{
    return add_component('I');
}

uid8 AppBuilder::add_label()
{
    return add_component('T');
}

uid8 AppBuilder::set_text(uid8 id, char *text)
{
    Serial.print('+');
    Serial.print(id);
    Serial.print(text);
    Serial.println('+');
    return id;
}