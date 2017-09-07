/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2013 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * controller.h
 *
 * Public Controller interface class
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include "avdecc-lib_build.h"
#include "net_interface.h"

class net_interface;

namespace avdecc_lib
{
class end_station;
class configuration_descriptor;

class controller
{
public:
    ///
    /// Call destructor for Controller used for destroying objects
    ///
    AVDECC_CONTROLLER_LIB32_API virtual void STDCALL destroy() = 0;

    ///
    /// \return The current AVDECC Controller build release version.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual const char * STDCALL get_version() const = 0;

    ///
    /// \return The total number of End Stations connected.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual size_t STDCALL get_end_station_count() = 0;
    
    ///
    /// \return The entity id of the controller.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual uint64_t STDCALL get_entity_id() = 0;
    
    ///
    /// Set the entity id of the controller.
    ///
    /// This API should only be used if an application wishes to modify the default
    /// controller entity - generated from the selected network interface MAC EUI.
    ///
    /// The controller entity id must not be modified after the system process start point.
    /// \see process_start()
    ///
    AVDECC_CONTROLLER_LIB32_API virtual void STDCALL set_entity_id(uint64_t entity_id) = 0;
    
    ///
    /// Set the maximum number of inflight READ_DESCRIPTOR commands allowed.
    ///
    /// This API should only be used if an application wishes to limit the number
    /// of READ_DESCRIPTOR commands enqueued.  If unused, the controller will queue up
    /// to the descriptor count.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual void STDCALL set_max_num_read_desc_cmd_inflight(int max_num_read_desc_cmd_inflight) = 0;

    ///
    /// \return The corresponding End Station by index.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual end_station * STDCALL get_end_station_by_index(size_t end_station_index) = 0;

    ///
    /// \return Find an endstation's index by Entity ID.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual bool STDCALL is_end_station_found_by_entity_id(uint64_t entity_entity_id, uint32_t & end_station_index) = 0;

    ///
    /// \return Find an endstation's index by MAC Address.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual bool STDCALL is_end_station_found_by_mac_addr(uint64_t mac_addr, uint32_t & end_station_index) = 0;

    ///
    /// \return The corresponding CONFIGURATION descriptor by index.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual configuration_descriptor * STDCALL get_current_config_desc(size_t end_station_index, bool report_error = true) = 0;

    ///
    /// \return The corresponding CONFIGURATION descriptor by Entity ID.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual configuration_descriptor * STDCALL get_config_desc_by_entity_id(uint64_t end_station_entity_id, uint16_t entity_index, uint16_t config_index) = 0;

    ///
    /// Update the base log level for messages to be logged by the post_log_msg callback.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual void STDCALL set_logging_level(int32_t new_log_level) = 0;

    ///
    /// Apply filters required to be true for an end station to be enumerated.
    ///
    /// The required filters are passed in.  If any of the required entity, talker,
    /// or listener flags are not true for an end station, the end station is not enumerated.
    ///
    /// \param entity_capabilities_flags avdecc_lib::end_station_entity_capabilities_flags
    /// \param talker_capabilities_flags avdecc_lib::end_station_talker_capabilities_flags
    /// \param listener_capabilities_flags avdecc_lib::end_station_listener_capabilities_flags
    ///
    AVDECC_CONTROLLER_LIB32_API virtual void STDCALL apply_end_station_capabilities_filters(uint32_t entity_capabilities_flags,
                                                                                            uint32_t talker_capabilities_flags,
                                                                                            uint32_t listener_capabilities_flags) = 0;

    ///
    /// \return The number of missed notifications that exceeds the notification buffer count.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual uint32_t STDCALL missed_notification_count() = 0;

    ///
    /// \return The number of missed logs that exceeds the log buffer count.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual uint32_t STDCALL missed_log_count() = 0;

    ///
    /// Send a CONTROLLER_AVAILABLE command to verify that the AVDECC Controller is still there.
    ///
    AVDECC_CONTROLLER_LIB32_API virtual int STDCALL send_controller_avail_cmd(void * notification_id, uint32_t end_station_index) = 0;
};

///
/// Create a public AVDECC Controller object with a network interface object, notification and post_log_msg callback functions used for accessing from outside the library.
///
/// \param netif A network interface object created in the application level using the public network interface API provided.
/// \param notification_user_obj A void pointer used to store any helpful C++ class object.
/// \param notification_type The type of notification that the callback function is called with. (Refer to notifications enumeration included in the library for a list of notification types supported.)
/// \param entity_id An unique identifier of the End Station the command is targeted to.
/// \param cmd_type The type of the AEM command used in the command data to be sent.
/// \param desc_type The type of the AEM descriptor used in the command data to be sent.
/// \param desc_index The index associated with the corresponding descriptor type used in the command data to be sent.
/// \param notification_id A void pointer to the unique identifier for each notification message.
///
/// \param log_user_obj A void pointer used to store any helpful class object.
/// \param log_level The log level that the callback function is called with. (Refer to logging levels enumeration included in the library for a list of log levels supported.)
/// \param log_msg A message containing additional information to be logged.
/// \param time_stamp_ms The time in milliseconds indicating when the message is logged.
///
extern "C" AVDECC_CONTROLLER_LIB32_API controller * STDCALL create_controller(net_interface * netif,
                                                                              void (*notification_callback)(void * notification_user_obj,
                                                                                                            int32_t notification_type, uint64_t entity_id,
                                                                                                            uint16_t cmd_type, uint16_t desc_type,
                                                                                                            uint16_t desc_index, uint32_t cmd_status,
                                                                                                            void * notification_id),
                                                                              void (*acmp_notification_callback)(void *, int32_t, uint16_t,
                                                                                                                 uint64_t, uint16_t, uint64_t,
                                                                                                                 uint16_t, uint32_t, void *),
                                                                              void (*log_callback)(void * log_user_obj, int32_t log_level,
                                                                                                   const char * log_msg, int32_t time_stamp_ms),
                                                                              int32_t initial_log_level);
}
