

/*
 * ====================== WARNING ======================
 *
 * THE CONTENTS OF THIS FILE HAVE BEEN AUTO-GENERATED.
 * DO NOT MODIFY IN ANY WAY.
 *
 * ====================== WARNING ======================
 */

/**
 *
 * This API is used by the controller to control the flow of the application. Certain arguments are
 *  passed from the command line to the application using the controller and the functions
 *  provided by this API.
 * <HR>
 *
 * Copyright (C) Sierra Wireless Inc.
 */

#ifndef CTRLVC_INTERFACE_H_INCLUDE_GUARD
#define CTRLVC_INTERFACE_H_INCLUDE_GUARD


#include "legato.h"


//--------------------------------------------------------------------------------------------------
/**
 * Type for handler called when a server disconnects.
 */
//--------------------------------------------------------------------------------------------------
typedef void (*ctrlVC_DisconnectHandler_t)(void *);

//--------------------------------------------------------------------------------------------------
/**
 *
 * Connect the current client thread to the service providing this API. Block until the service is
 * available.
 *
 * For each thread that wants to use this API, either ConnectService or TryConnectService must be
 * called before any other functions in this API.  Normally, ConnectService is automatically called
 * for the main thread, but not for any other thread. For details, see @ref apiFilesC_client.
 *
 * This function is created automatically.
 */
//--------------------------------------------------------------------------------------------------
void ctrlVC_ConnectService
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 *
 * Try to connect the current client thread to the service providing this API. Return with an error
 * if the service is not available.
 *
 * For each thread that wants to use this API, either ConnectService or TryConnectService must be
 * called before any other functions in this API.  Normally, ConnectService is automatically called
 * for the main thread, but not for any other thread. For details, see @ref apiFilesC_client.
 *
 * This function is created automatically.
 *
 * @return
 *  - LE_OK if the client connected successfully to the service.
 *  - LE_UNAVAILABLE if the server is not currently offering the service to which the client is
 *    bound.
 *  - LE_NOT_PERMITTED if the client interface is not bound to any service (doesn't have a binding).
 *  - LE_COMM_ERROR if the Service Directory cannot be reached.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_TryConnectService
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Set handler called when server disconnection is detected.
 *
 * When a server connection is lost, call this handler then exit with LE_FATAL.  If a program wants
 * to continue without exiting, it should call longjmp() from inside the handler.
 */
//--------------------------------------------------------------------------------------------------
void ctrlVC_SetServerDisconnectHandler
(
    ctrlVC_DisconnectHandler_t disconnectHandler,
    void *contextPtr
);

//--------------------------------------------------------------------------------------------------
/**
 *
 * Disconnect the current client thread from the service providing this API.
 *
 * Normally, this function doesn't need to be called. After this function is called, there's no
 * longer a connection to the service, and the functions in this API can't be used. For details, see
 * @ref apiFilesC_client.
 *
 * This function is created automatically.
 */
//--------------------------------------------------------------------------------------------------
void ctrlVC_DisconnectService
(
    void
);


//--------------------------------------------------------------------------------------------------
/**
 ** Get the phone number specified on the command line and start voice call to the destination number.
 **
 ** @return
 **      - LE_OK              If voice call can be successfully made to the destination.
 **      - LE_BUSY            If there is already an active voice call.
 **      - LE_FAULT           If not able to initiate voice call.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_MakeCall
(
    const char* LE_NONNULL argPtr
        ///< [IN]
);

//--------------------------------------------------------------------------------------------------
/**
 ** This function changes the path to the .wav file to the specified path on the command line.
 ** If user specifies "default", path is reset to the default piano.wav included with the app.
 **
 ** @return
 **      - LE_OK              If wav file exists and path to audio file is successfully changed.
 **      - LE_FAULT           If path was not changed.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_SetWav
(
    const char* LE_NONNULL argPtr,
        ///< [IN]
    bool setAudioToDefaultFlag
        ///< [IN]
);

//--------------------------------------------------------------------------------------------------
/**
 ** End any active voice call. Also ends incoming or outgoing calls which are not yet connected.
 **
 ** @return
 **       - LE_OK             If call is successfully ended.
 **       - LE_NOT_FOUND      If the voice call object reference is not found.
 **       - LE_FAULT          If end call cannot be processed.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_HangupCall
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 ** Answer an incoming call.
 **
 ** @return
 **       - LE_OK             If incoming call is successfully connected.
 **       - LE_NOT_FOUND      Incoming voice call object reference is not found.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_AnswerCall
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 ** Call the last dialed number.
 **
 ** @return
 **      - LE_OK              If redial is processed successfully.
 **      - LE_FAULT           If not able to perform redial.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_Redial
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 ** Place the active call on hold by disabling all audio input from mic and connecting input stream
 ** to the file pointed to by AudioFilePath
 **
 ** @return
 **      - LE_OK              If hold is processed successfully.
 **      - LE_FAULT           If hold is not possible.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_HoldCall
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 ** Unhold the active call which is currently on hold by disconnecting the .wav file from the
 ** input stream and connecting the mic to the input stream.
 **
 ** @return
 **      - LE_OK              If unhold is processed successfully.
 **      - LE_FAULT           If unhold is not possible.
 */
//--------------------------------------------------------------------------------------------------
le_result_t ctrlVC_UnholdCall
(
    void
);

#endif // CTRLVC_INTERFACE_H_INCLUDE_GUARD