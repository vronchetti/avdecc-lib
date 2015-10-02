/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2014 AudioScience Inc.
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
 * stream_output_descriptor_response_imp.h
 *
 * STREAM OUTPUT descriptor response implementation class
 */

#pragma once
#include <iostream>
#include <map>
#include <string>
using namespace std;

#include "jdksavdecc_acmp.h"
#include "stream_output_descriptor_response.h"
#include "jdksavdecc_aem_descriptor.h"
#include "descriptor_response_base_imp.h"

namespace avdecc_lib
{
    class stream_output_descriptor_response_imp : public stream_output_descriptor_response, public virtual descriptor_response_base_imp
    {
    private:
        std::map <string, int> stream_info_flags;
        struct stream_output_desc_stream_flags
        {
            bool clock_sync_source;
            bool class_a;
            bool class_b;
            bool supports_encrypted;
            bool primary_backup_supported;
            bool primary_backup_valid;
            bool secondary_backup_supported;
            bool secondary_backup_valid;
            bool tertiary_backup_supported;
            bool tertiary_backup_valid;
        };
        struct stream_output_desc_stream_flags stream_output_flags;
        
        std::vector<uint64_t> stream_formats_vec; //store supported stream formats
    public:
        stream_output_descriptor_response_imp(const uint8_t *frame, size_t frame_len, ssize_t pos);
        virtual ~stream_output_descriptor_response_imp();

        uint8_t * STDCALL object_name();
        uint16_t STDCALL localized_description();
        uint16_t STDCALL clock_domain_index();
        uint16_t STDCALL stream_flags();
        bool STDCALL stream_flags_clock_sync_source();
        bool STDCALL stream_flags_class_a();
        bool STDCALL stream_flags_class_b();
        bool STDCALL stream_flags_supports_encrypted();
        bool STDCALL stream_flags_primary_backup_supported();
        bool STDCALL stream_flags_primary_backup_valid();
        bool STDCALL stream_flags_secondary_backup_supported();
        bool STDCALL stream_flags_secondary_backup_valid();
        bool STDCALL stream_flags_tertiary_backup_supported();
        bool STDCALL stream_flags_tertiary_backup_valid();
        const char * STDCALL current_format();
        uint16_t formats_offset();
        uint16_t STDCALL number_of_formats();
        uint64_t STDCALL backup_talker_entity_id_0();
        uint16_t STDCALL backup_talker_unique_0();
        uint64_t STDCALL backup_talker_entity_id_1();
        uint16_t STDCALL backup_talker_unique_1();
        uint64_t STDCALL backup_talker_entity_id_2();
        uint16_t STDCALL backup_talker_unique_2();
        uint64_t STDCALL backedup_talker_entity_id();
        uint16_t STDCALL backedup_talker_unique();
        uint16_t STDCALL avb_interface_index();
        uint32_t STDCALL buffer_length();
        bool STDCALL get_stream_info_flag(const char *flag);
        uint64_t STDCALL get_stream_format_by_index(size_t stream_format_index);
    private:
        /**
         * Store the stream flags componenets of the STREAM INPUT descriptor object in a vector.
         */
        void stream_flags_init();
        
        /**
         * Store the supported stream formats of the STREAM OUTPUT descriptor object in a vector.
         */
        void stream_formats_init(const uint8_t *frame);
    };
}
