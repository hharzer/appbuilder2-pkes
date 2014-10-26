#ifndef __APPBUI_HELPER__
#define __APPBUI_HELPER__

#include "arduino.h"




typedef unsigned char uid8;
typedef unsigned char byte;
typedef unsigned int twobytes;
typedef void (*gen_callback)(uid8, char *);

struct callback_dictionary
{
    uid8 *id;
    gen_callback *callback;
};

struct handshake_informations {
	char* phrase;
	byte attempts;
};

#endif