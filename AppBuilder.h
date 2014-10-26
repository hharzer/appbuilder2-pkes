#ifndef __APPBUI___
#define __APPBUI___
#include "helper.h"



class AppBuilder


{

private:

    //! True if connected via specified medium (Serial) or not
    char is_connected; /*!<  */
    //! Function that's called after the connection was established (After handshake)
    gen_callback onconnect; /*!<  */
    //! Function that's called immediatly after the notice that the connection wa slost (e.g. cable unplugged)
    gen_callback ondisconnect; /*!<  */

    //! Number of components that have to be stored
    byte num_components; /*!<  */

    byte current_cursor;

    //! Number of callbacks that have to be stored
    byte num_callbacks; /*!<  */

    //! The current index of added callbacks
    byte callback_index; /*!<  */

    //! A buffer to read from the serial input.
    char serial_buffer[32]; /*!<  */

    //! The phrase that's used to do a handshake
    String handshake_phrase; /*!<  */
    //! Attempts that are made before giving up connecting
    int attempts; /*!<  */

    //! An array to store the added components. Size depends on
    int *components; /*!<  */
    twobytes callback_stack; // stores two bytes (uid8s) for callbacks /*!<  */
    struct callback_dictionary callbacks; /*!<  */

    struct handshake_informations handshake_information; /*!<  */

    /**
     * @brief Executes incoming callbacks
     * @details Executes incoming callbacks that are stored in callback_stack and resets it
     */
    void execute_callbacks(); /*!<  */

    /**
     * @brief Flushes any given (char) buffer
     * @details Flushes the buffer and sets everything to 0
     *
     * @param buffer A pointer to the buffer that has to flushed
     * @param size The size of the given buffer
     */
    void flush_buffer(char *buffer, byte size);/*!<  */

    /**
     * @brief Handshake for connection
     * @details Ensures that the connection is only established if the counterpart is eligible
     * @return True if connected, false otherwise
     */
    bool handshake();/*!<  */

    /**
     * @brief Adds a component to the array so it can be sent
     * @details Universal function to add any type of components to the components array
     *
     * @param comp type of the component
     * @return uid8 on succes, otherwise 0
     */
    uid8 add_component(uid8 type);

    /**
     * @brief Adds a component with specified id
     * @details Universal function to add any type of components to the components array. The uid of the added one will be id
     *
     * @param type The type of the components
     * @param id The id of the component
     *
     * @return uid of added component (id), 0 otherwise
     */
    uid8 add_component(uid8 type, uid8 id);



public:

    /**
     * @brief Constructor of AppBuilder
     * @details Don't forget to start the Serial connection before using AppBuilder (e.g. Serial.begin(9600))
     *
     * @param num_com Number of components that will be used
     * @param num_callbacks Number of callbacks that will be used
     * @param handshake The phrase that's used for handshakes
     * @param attempts Attempts that are made to connect to the computer (not implemented yet)
     */
    AppBuilder(byte num_com, byte num_callbacks, String handshake, int attempts);

    /**
     * @brief Function that processes the incoming bytes of the serial connection
     * @details Has to be added to ensure that AppBuilder can process incoming callbacks
     */
    void serial_event();

    /**
     * @brief Refreshes the state of AppBuilder, e.g. executing callbacks, connecting to the client
     * @details If AppBuilder isn't connected to a client, but a Serial connection is established, it tries to do the handshake, thus blocking further calculations. Be aware of this fact
     */
    void refresh();

    /**
     * @brief Sets the function that's called when you're successfully connection
     * @details This includes performing the handshake. Nothing will happen if the AppBuilder::handshake wasn't successful
     *
     * @param onc The function that will be called on connection.
     */
    void set_onconnect(gen_callback onc);

    /**
     * @brief Sets the function that's called when the connection is lost.
     *
     * @param ondc The function that will be called on disconnection
     */
    void set_ondisconnect(gen_callback ondc);

    /**
     * @brief Sends components to client
     * @details Sends the array according to the protocol to the client
     */
    void send_components();

    /**
     * @brief Starts a new layout for components
     * @details Encapsulates components on a new layout
     * @return The id of the created layout, 0 otherwise
     */
    uid8 start_layout();

    /**
     * @brief Ends the given layout
     * @details Closes the layout with the given id
     *
     * @param layout The id of the layout that is to be closed
     * @return id on success, 0 otherwise
     */
    uid8 end_layout(uid8 layout);

    /**
     * @brief Adds a button
     * @details Adds a button, return id on succes
     * @return id on success, 0 otherwise
     */
    uid8 add_button();
    /**
     * @brief Adds a label
     * @details Adds a label, return id on succes
     * @return id on success, 0 otherwise
     */
    uid8 add_label();
    /**
     * @brief Adds a text input
     * @details Adds a text input, return id on succes
     * @return id on success, 0 otherwise
     */
    uid8 add_input();

    /**
     * @brief Sets the text of a given components
     * @details Sends text to client synchronous
     *
     * @param id id of the widget
     * @param text The new text
     *
     * @return id on succes, 0 otherwise
     */
    uid8 set_text(uid8 id, char *text);

    /**
     * @brief Adds a callback to a component
     * @details
     *
     * @param id The component
     * @param callback The corresponding component
     *
     * @return id on success, 0 otherwise
     */
    uid8 add_callback(uid8 id, gen_callback callback);

};

#endif