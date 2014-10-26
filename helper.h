#ifndef __APPBUI_HELPER__
#define __APPBUI_HELPER__

#include "arduino.h"



//! Typedef for an universial id 
typedef unsigned char uid8;

//! Simplification
typedef unsigned char byte;

//! Show that the stack's two bytes long
typedef unsigned int twobytes;

//! A generic callback used for everything, e.g. connect, disconnect, etc.
typedef void (*gen_callback)(uid8, char *);


//! Structure to save callbacks by id
struct callback_dictionary
{
    uid8 *id;
    gen_callback *callback;
};

//! Informations for the handshake
struct handshake_informations {
	char* phrase;
	byte attempts;
};

#endif