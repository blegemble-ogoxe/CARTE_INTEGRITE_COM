

/*
 * ====================== WARNING ======================
 *
 * THE CONTENTS OF THIS FILE HAVE BEEN AUTO-GENERATED.
 * DO NOT MODIFY IN ANY WAY.
 *
 * ====================== WARNING ======================
 */


#ifndef CTRLVC_INTERFACE_H_INCLUDE_GUARD
#define CTRLVC_INTERFACE_H_INCLUDE_GUARD


#include "legato.h"


//--------------------------------------------------------------------------------------------------
/**
 * Get the server service reference
 */
//--------------------------------------------------------------------------------------------------
le_msg_ServiceRef_t ctrlVC_GetServiceRef
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Get the client session reference for the current message
 */
//--------------------------------------------------------------------------------------------------
le_msg_SessionRef_t ctrlVC_GetClientSessionRef
(
    void
);

//--------------------------------------------------------------------------------------------------
/**
 * Initialize the server and advertise the service.
 */
//--------------------------------------------------------------------------------------------------
void ctrlVC_AdvertiseService
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