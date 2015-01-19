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
    uid8 *id; //! The id of the element
    gen_callback *callback; //! The corresponding callback
};

//! Informations for the handshake
struct handshake_informations
{
    char *phrase; //! The actual handshake phrase
    byte attempts; //! Num of attempts
};

#endif