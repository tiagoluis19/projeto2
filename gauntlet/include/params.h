
/*
    Copyright 2020-2023 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

    // keyword = hey turret
    // UUID = 3d 57 62 c4 31 ad ae 85

static const uint8_t KEYWORD_ARRAY[] = {
        0xf8, 0x7b, 0x91, 0xd1, 0x38, 0xad, 0x21, 0xba, 0x76, 0xc3, 0x9b, 0x2d, 0x76, 0x75, 0xc1, 0xfe, 0x7d, 0x35,
        0x3e, 0x78, 0x94, 0x64, 0x87, 0x68, 0x8c, 0x43, 0x50, 0x53, 0xbc, 0x53, 0x37, 0xf8, 0x2e, 0xd4, 0xc1, 0x64,
        0x3e, 0xda, 0xa1, 0xc8, 0xaf, 0x0c, 0x07, 0x0f, 0x78, 0xe8, 0x6b, 0xb6, 0xe4, 0x67, 0xa4, 0xda, 0x87, 0x73,
        0x60, 0xc9, 0x31, 0xc3, 0x16, 0xd1, 0xcd, 0xce, 0x98, 0x1c, 0x64, 0x8d, 0x15, 0x66, 0x99, 0xae, 0x61, 0x60,
        0xd1, 0x22, 0x30, 0x80, 0x8c, 0xfe, 0xd8, 0x99, 0x91, 0x04, 0xab, 0x9a, 0x4a, 0x08, 0xf2, 0x71, 0xd3, 0x57,
        0x92, 0xab, 0xfc, 0xd8, 0x20, 0xf3, 0x73, 0xc4, 0x3c, 0xbe, 0xec, 0x43, 0x85, 0x62, 0xcb, 0xe9, 0x7e, 0x8d,
        0xb8, 0xe8, 0x19, 0x40, 0x60, 0xed, 0xa9, 0x9e, 0xac, 0x85, 0x3d, 0x25, 0x25, 0x0a, 0xf4, 0x0f, 0x26, 0xe2,
        0x7b, 0xb8, 0x93, 0xf3, 0xe1, 0xce, 0x32, 0x2e, 0x1d, 0x73, 0x2a, 0xcb, 0xb7, 0xd6, 0x36, 0x0a, 0x96, 0xd7,
        0x87, 0x4d, 0x65, 0x70, 0x71, 0xe4, 0x8f, 0xaf, 0xfb, 0xd3, 0xd6, 0xd3, 0x57, 0xa4, 0x0f, 0xc5, 0x70, 0x4a,
        0x5b, 0x59, 0x18, 0xc1, 0xb5, 0x6b, 0xad, 0x7d, 0x2d, 0x5f, 0x73, 0x58, 0x7d, 0x58, 0x19, 0xab, 0x34, 0xe4,
        0x20, 0x33, 0x7c, 0x7c, 0x57, 0x4b, 0xdd, 0xbf, 0xc7, 0x7f, 0x1d, 0xad, 0xd9, 0x16, 0x89, 0xf0, 0x9b, 0x8f,
        0x0c, 0x36, 0x32, 0x52, 0xf1, 0x02, 0x49, 0xe8, 0x68, 0x51, 0x37, 0xcf, 0x87, 0x50, 0x6e, 0x27, 0x75, 0x93,
        0x20, 0xf8, 0x53, 0x89, 0xb0, 0x04, 0xce, 0xeb, 0x96, 0x13, 0x72, 0x51, 0xba, 0x88, 0x13, 0x7c, 0x0d, 0x9d,
        0x31, 0x54, 0xa3, 0x2d, 0x34, 0xfc, 0x6f, 0x86, 0x4a, 0x70, 0x17, 0xa9, 0x3b, 0x5a, 0x26, 0xd1, 0xf0, 0x55,
        0x88, 0x57, 0xf4, 0xde, 0xd3, 0x84, 0x2a, 0x51, 0x74, 0x68, 0x00, 0xb6, 0x0c, 0x77, 0x27, 0xc8, 0x13, 0x4d,
        0x64, 0x3d, 0x6e, 0x7d, 0x42, 0x17, 0xd0, 0x27, 0xbc, 0x79, 0x6f, 0x47, 0x5d, 0x26, 0xd7, 0x16, 0xb1, 0x39,
        0xb8, 0x4b, 0x88, 0xce, 0xbf, 0x2a, 0x9e, 0x80, 0x55, 0x2b, 0xd8, 0xdf, 0x81, 0xb0, 0xaf, 0xb3, 0x87, 0xbd,
        0x91, 0xfa, 0x6f, 0x4d, 0x2f, 0xaf, 0x60, 0xe9, 0xb6, 0x17, 0xf2, 0x26, 0xa3, 0xea, 0x6b, 0x82, 0x6b, 0x18,
        0x2f, 0xfa, 0x00, 0x59, 0x41, 0x37, 0x9f, 0x05, 0x44, 0xc7, 0x13, 0xa1, 0x31, 0x11, 0xde, 0x7e, 0x6d, 0xc1,
        0x65, 0xe7, 0x4c, 0x78, 0x64, 0xf5, 0xa8, 0x25, 0x54, 0x1b, 0x6e, 0x12, 0xc4, 0xdb, 0xbb, 0xb9, 0x27, 0xa7,
        0x1e, 0xa1, 0x22, 0x0f, 0xd8, 0x2b, 0x5e, 0xbe, 0xca, 0x21, 0x70, 0x49, 0x4c, 0x7c, 0xb3, 0xa8, 0x6c, 0xff,
        0x88, 0x2c, 0xa7, 0xf7, 0x92, 0x10, 0x02, 0xb5, 0xd4, 0xf4, 0x69, 0x26, 0xbf, 0x79, 0xda, 0xe0, 0xde, 0x07,
        0x7e, 0xdc, 0xbf, 0x06, 0x14, 0x22, 0x14, 0x98, 0x7f, 0xe3, 0xf1, 0x32, 0x87, 0x5e, 0xb6, 0x5c, 0xc9, 0x02,
        0xe4, 0xa4, 0x1c, 0x12, 0xb2, 0xb9, 0xed, 0x4b, 0x9d, 0x80, 0xcb, 0xb3, 0x1d, 0xd8, 0x51, 0x55, 0xf9, 0x80,
        0x87, 0xa4, 0xc2, 0x14, 0x67, 0x78, 0x40, 0x19, 0xb1, 0x85, 0xa5, 0xa7, 0x38, 0x3f, 0x87, 0xa9, 0xf8, 0x0e,
        0x23, 0xf9, 0xff, 0xf5, 0x4e, 0xa0, 0x28, 0x8e, 0xdf, 0x1d, 0xfc, 0x3b, 0xf0, 0x7c, 0x38, 0xbe, 0xcf, 0x10,
        0x3c, 0xb3, 0x46, 0x4e, 0xb3, 0x4d, 0xf8, 0x89, 0xa4, 0x99, 0x82, 0x2f, 0x5b, 0xdf, 0x3d, 0x2a, 0x00, 0x3d,
        0x6c, 0xd8, 0xfb, 0x6c, 0x64, 0x94, 0xca, 0xcb, 0x84, 0x0c, 0x3c, 0x66, 0x95, 0xa4, 0x3a, 0x28, 0x4c, 0xe3,
        0x57, 0x9b, 0x93, 0x1e, 0x43, 0x49, 0xf8, 0xcc, 0x64, 0xb4, 0x36, 0x93, 0x69, 0x23, 0x21, 0x78, 0xbe, 0x7f,
        0x53, 0x87, 0x17, 0xda, 0xd7, 0x0e, 0x7f, 0x52, 0x0e, 0x39, 0x62, 0x04, 0x9d, 0x4d, 0x6f, 0xd3, 0xfc, 0x3f,
        0x25, 0x67, 0x04, 0x8a, 0x3c, 0x21, 0x82, 0x49, 0x92, 0x3a, 0xc0, 0x3c, 0xd8, 0xe6, 0xad, 0x35, 0x3d, 0x77,
        0x34, 0xfa, 0xe2, 0xc5, 0xb5, 0x41, 0xb1, 0xe0, 0x0e, 0x65, 0xb5, 0x0d, 0xca, 0x4c, 0x9c, 0x3b, 0x27, 0x18,
        0x93, 0xf0, 0x1b, 0x48, 0x40, 0x41, 0x0e, 0x3e, 0xd6, 0x29, 0x71, 0x64, 0x8c, 0x6e, 0x54, 0x31, 0xac, 0x30,
        0x88, 0x2c, 0xbf, 0x06, 0xce, 0xc7, 0x63, 0xf1, 0xc8, 0xed, 0x9a, 0xb8, 0xb2, 0xb5, 0xca, 0x9f, 0x2a, 0x60,
        0x13, 0xb3, 0xcc, 0x09, 0x95, 0xc4, 0xed, 0x61
};



// context = turretcontrol
static const uint8_t CONTEXT_ARRAY[3960] __attribute__ ((aligned (16))) = {
        0x72, 0x68, 0x69, 0x6e, 0x6f, 0x33, 0x2e, 0x30, 0x2e, 0x30, 0x08, 0x00, 0x00, 0x00, 0x3d, 0x57, 0x62, 0xc4,
        0x31, 0xad, 0xae, 0x85, 0x65, 0x6e, 0x00, 0x13, 0x00, 0x00, 0x00, 0x47, 0x69, 0x74, 0x48, 0x75, 0x62, 0x4f,
        0x49, 0x44, 0x43, 0x5f, 0x39, 0x37, 0x36, 0x33, 0x38, 0x33, 0x30, 0x32, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0f, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x63, 0x6f, 0x6e, 0x74,
        0x65, 0x78, 0x74, 0x3a, 0x0a, 0x20, 0x20, 0x65, 0x78, 0x70, 0x72, 0x65, 0x73, 0x73, 0x69, 0x6f, 0x6e, 0x73,
        0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x70, 0x65, 0x6e, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x3a, 0x0a,
        0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x24, 0x6f, 0x70, 0x65, 0x6e, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0x3a, 0x6f,
        0x70, 0x65, 0x6e, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x63, 0x61, 0x6b, 0x65, 0x69,
        0x73, 0x61, 0x6c, 0x69, 0x65, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x64, 0x6f, 0x20, 0x79, 0x6f,
        0x75, 0x20, 0x68, 0x61, 0x74, 0x65, 0x20, 0x6d, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x6f, 0x64, 0x65,
        0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x28, 0x40, 0x73, 0x79, 0x6e, 0x6f, 0x6e, 0x79, 0x6d, 0x73,
        0x29, 0x20, 0x66, 0x69, 0x72, 0x65, 0x20, 0x6d, 0x6f, 0x64, 0x65, 0x20, 0x28, 0x74, 0x6f, 0x29, 0x20, 0x28,
        0x66, 0x75, 0x6c, 0x6c, 0x29, 0x20, 0x24, 0x66, 0x69, 0x72, 0x65, 0x6d, 0x6f, 0x64, 0x65, 0x3a, 0x66, 0x69,
        0x72, 0x65, 0x6d, 0x6f, 0x64, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x73, 0x69, 0x6e, 0x67, 0x3a, 0x0a, 0x20,
        0x20, 0x20, 0x20, 0x2d, 0x20, 0x27, 0x40, 0x73, 0x69, 0x6e, 0x67, 0x73, 0x20, 0x24, 0x6d, 0x75, 0x73, 0x69,
        0x63, 0x5f, 0x73, 0x65, 0x6c, 0x3a, 0x6d, 0x75, 0x73, 0x69, 0x63, 0x5f, 0x73, 0x65, 0x6c, 0x20, 0x28, 0x66,
        0x6f, 0x72, 0x29, 0x20, 0x28, 0x6d, 0x65, 0x29, 0x27, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x61, 0x69, 0x6e,
        0x74, 0x65, 0x6e, 0x61, 0x6e, 0x63, 0x65, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x6d, 0x61, 0x69,
        0x6e, 0x74, 0x65, 0x6e, 0x61, 0x6e, 0x63, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x72, 0x61, 0x74, 0x65, 0x6f,
        0x66, 0x66, 0x69, 0x72, 0x65, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x28, 0x40, 0x73, 0x79, 0x6e,
        0x6f, 0x6e, 0x79, 0x6d, 0x73, 0x29, 0x20, 0x66, 0x69, 0x72, 0x65, 0x20, 0x72, 0x61, 0x74, 0x65, 0x20, 0x28,
        0x74, 0x6f, 0x29, 0x20, 0x24, 0x66, 0x69, 0x72, 0x65, 0x72, 0x72, 0x61, 0x74, 0x65, 0x3a, 0x66, 0x69, 0x72,
        0x65, 0x72, 0x72, 0x61, 0x74, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x73, 0x61, 0x66, 0x65, 0x74, 0x79, 0x3a,
        0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x28, 0x40, 0x73, 0x79, 0x6e, 0x6f, 0x6e, 0x79, 0x6d, 0x73, 0x29,
        0x20, 0x73, 0x61, 0x66, 0x65, 0x74, 0x79, 0x20, 0x24, 0x6f, 0x6e, 0x6f, 0x66, 0x66, 0x3a, 0x6f, 0x6e, 0x6f,
        0x66, 0x66, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6f, 0x76, 0x72, 0x3a,
        0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x28, 0x6d, 0x61, 0x6e, 0x75, 0x61, 0x6c, 0x29, 0x20, 0x6f, 0x76,
        0x65, 0x72, 0x72, 0x69, 0x64, 0x65, 0x20, 0x28, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x73, 0x29, 0x0a,
        0x20, 0x20, 0x20, 0x20, 0x66, 0x65, 0x65, 0x64, 0x62, 0x61, 0x63, 0x6b, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20,
        0x2d, 0x20, 0x28, 0x67, 0x69, 0x76, 0x65, 0x29, 0x20, 0x66, 0x65, 0x65, 0x64, 0x62, 0x61, 0x63, 0x6b, 0x0a,
        0x20, 0x20, 0x20, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x61, 0x75, 0x74, 0x6f, 0x3a, 0x0a, 0x20, 0x20,
        0x20, 0x20, 0x2d, 0x20, 0x28, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x29, 0x20, 0x28, 0x74, 0x6f, 0x29, 0x20,
        0x61, 0x75, 0x74, 0x6f, 0x6e, 0x6f, 0x6d, 0x6f, 0x75, 0x73, 0x20, 0x6d, 0x6f, 0x64, 0x65, 0x0a, 0x20, 0x20,
        0x73, 0x6c, 0x6f, 0x74, 0x73, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x70, 0x65, 0x6e, 0x63, 0x6c, 0x6f,
        0x73, 0x65, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x64, 0x65, 0x70, 0x6c, 0x6f, 0x79, 0x0a, 0x20,
        0x20, 0x20, 0x20, 0x2d, 0x20, 0x72, 0x65, 0x74, 0x72, 0x61, 0x63, 0x74, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d,
        0x20, 0x72, 0x65, 0x74, 0x72, 0x61, 0x63, 0x74, 0x20, 0x77, 0x69, 0x6e, 0x67, 0x73, 0x0a, 0x20, 0x20, 0x20,
        0x20, 0x2d, 0x20, 0x64, 0x65, 0x70, 0x6c, 0x6f, 0x79, 0x20, 0x77, 0x69, 0x6e, 0x67, 0x73, 0x0a, 0x20, 0x20,
        0x20, 0x20, 0x66, 0x69, 0x72, 0x65, 0x6d, 0x6f, 0x64, 0x65, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20,
        0x73, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x62, 0x75, 0x72, 0x73, 0x74,
        0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x61, 0x75, 0x74, 0x6f, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x75,
        0x73, 0x69, 0x63, 0x5f, 0x73, 0x65, 0x6c, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x73, 0x74, 0x69,
        0x6c, 0x6c, 0x20, 0x61, 0x6c, 0x69, 0x76, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x74, 0x75, 0x72,
        0x72, 0x65, 0x74, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x70, 0x6f,
        0x72, 0x74, 0x61, 0x6c, 0x20, 0x72, 0x61, 0x64, 0x69, 0x6f, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x66, 0x69, 0x72,
        0x65, 0x72, 0x72, 0x61, 0x74, 0x65, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x6d, 0x65, 0x64, 0x69,
        0x75, 0x6d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x66, 0x61, 0x73, 0x74, 0x0a, 0x20, 0x20, 0x20, 0x20,
        0x2d, 0x20, 0x73, 0x6c, 0x6f, 0x77, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x6f, 0x6e, 0x6f, 0x66, 0x66, 0x3a, 0x0a,
        0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x6f, 0x66, 0x66, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x6f, 0x6e,
        0x0a, 0x20, 0x20, 0x6d, 0x61, 0x63, 0x72, 0x6f, 0x73, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x73, 0x79, 0x6e,
        0x6f, 0x6e, 0x79, 0x6d, 0x73, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x73, 0x65, 0x74, 0x0a, 0x20,
        0x20, 0x20, 0x20, 0x2d, 0x20, 0x63, 0x68, 0x61, 0x6e, 0x67, 0x65, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x73, 0x69,
        0x6e, 0x67, 0x73, 0x3a, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x2d, 0x20, 0x70, 0x6c, 0x61, 0x79, 0x0a, 0x20, 0x20,
        0x20, 0x20, 0x2d, 0x20, 0x73, 0x69, 0x6e, 0x67, 0x0a, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x26, 0x00,
        0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00,
        0x4b, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00, 0x5e, 0x00,
        0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x6f, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x00,
        0x80, 0x00, 0x00, 0x00, 0x85, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x95, 0x00,
        0x00, 0x00, 0x9a, 0x00, 0x00, 0x00, 0xa7, 0x00, 0x00, 0x00, 0xac, 0x00, 0x00, 0x00, 0xba, 0x00, 0x00, 0x00,
        0xc2, 0x00, 0x00, 0x00, 0xc9, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0xdb, 0x00,
        0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe5, 0x00, 0x00, 0x00, 0xf1, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x00, 0x00, 0x05, 0x01, 0x00, 0x00, 0x61, 0x75, 0x74, 0x6f, 0x6e, 0x6f, 0x6d, 0x6f, 0x75, 0x73,
        0x00, 0x61, 0x75, 0x74, 0x6f, 0x00, 0x62, 0x75, 0x72, 0x73, 0x74, 0x00, 0x63, 0x68, 0x61, 0x6e, 0x67, 0x65,
        0x00, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x73, 0x00, 0x64, 0x65, 0x70, 0x6c, 0x6f, 0x79, 0x20, 0x77,
        0x69, 0x6e, 0x67, 0x73, 0x00, 0x64, 0x65, 0x70, 0x6c, 0x6f, 0x79, 0x00, 0x64, 0x6f, 0x00, 0x66, 0x61, 0x73,
        0x74, 0x00, 0x66, 0x65, 0x65, 0x64, 0x62, 0x61, 0x63, 0x6b, 0x00, 0x66, 0x69, 0x72, 0x65, 0x00, 0x66, 0x6f,
        0x72, 0x00, 0x66, 0x75, 0x6c, 0x6c, 0x00, 0x67, 0x69, 0x76, 0x65, 0x00, 0x68, 0x61, 0x74, 0x65, 0x00, 0x6d,
        0x61, 0x69, 0x6e, 0x74, 0x65, 0x6e, 0x61, 0x6e, 0x63, 0x65, 0x00, 0x6d, 0x61, 0x6e, 0x75, 0x61, 0x6c, 0x00,
        0x6d, 0x65, 0x64, 0x69, 0x75, 0x6d, 0x00, 0x6d, 0x65, 0x00, 0x6d, 0x6f, 0x64, 0x65, 0x00, 0x6f, 0x66, 0x66,
        0x00, 0x6f, 0x6e, 0x00, 0x6f, 0x76, 0x65, 0x72, 0x72, 0x69, 0x64, 0x65, 0x00, 0x70, 0x6c, 0x61, 0x79, 0x00,
        0x70, 0x6f, 0x72, 0x74, 0x61, 0x6c, 0x20, 0x72, 0x61, 0x64, 0x69, 0x6f, 0x00, 0x72, 0x61, 0x74, 0x65, 0x00,
        0x72, 0x65, 0x74, 0x72, 0x61, 0x63, 0x74, 0x20, 0x77, 0x69, 0x6e, 0x67, 0x73, 0x00, 0x72, 0x65, 0x74, 0x72,
        0x61, 0x63, 0x74, 0x00, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x00, 0x73, 0x61, 0x66, 0x65, 0x74, 0x79, 0x00,
        0x73, 0x65, 0x74, 0x00, 0x73, 0x69, 0x6e, 0x67, 0x6c, 0x65, 0x00, 0x73, 0x69, 0x6e, 0x67, 0x00, 0x73, 0x6c,
        0x6f, 0x77, 0x00, 0x73, 0x74, 0x69, 0x6c, 0x6c, 0x20, 0x61, 0x6c, 0x69, 0x76, 0x65, 0x00, 0x74, 0x6f, 0x00,
        0x74, 0x75, 0x72, 0x72, 0x65, 0x74, 0x20, 0x6f, 0x70, 0x65, 0x72, 0x61, 0x00, 0x79, 0x6f, 0x75, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00,
        0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x15, 0x00,
        0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1f, 0x00,
        0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00,
        0x25, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x29, 0x00,
        0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1b, 0x00,
        0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00,
        0x35, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x40, 0x00,
        0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00,
        0x55, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00, 0x00, 0x6c, 0x00,
        0x00, 0x00, 0x6f, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x75, 0x00, 0x00, 0x00,
        0x7b, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x89, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 0x97, 0x00,
        0x00, 0x00, 0x9e, 0x00, 0x00, 0x00, 0xa3, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x00, 0x00, 0xad, 0x00, 0x00, 0x00,
        0xb0, 0x00, 0x00, 0x00, 0xb6, 0x00, 0x00, 0x00, 0xb9, 0x00, 0x00, 0x00, 0xbc, 0x00, 0x00, 0x00, 0xc4, 0x00,
        0x00, 0x00, 0xc6, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0xca, 0x00, 0x00, 0x00, 0xd2, 0x00, 0x00, 0x00,
        0xd9, 0x00, 0x00, 0x00, 0xdb, 0x00, 0x00, 0x00, 0x04, 0x1f, 0x01, 0x17, 0x03, 0x16, 0x03, 0x1d, 0x04, 0x1f,
        0x19, 0x07, 0x0c, 0x1d, 0x1f, 0x08, 0x0d, 0x17, 0x13, 0x14, 0x03, 0x17, 0x1f, 0x1c, 0x19, 0x15, 0x26, 0x09,
        0x11, 0x1b, 0x15, 0x1a, 0x24, 0x11, 0x18, 0x26, 0x09, 0x11, 0x1b, 0x15, 0x1a, 0x09, 0x22, 0x0e, 0x02, 0x1d,
        0x1f, 0x0e, 0x12, 0x09, 0x07, 0x02, 0x14, 0x0e, 0x06, 0x0c, 0x0e, 0x06, 0x1c, 0x0e, 0x04, 0x1c, 0x0e, 0x0c,
        0x0e, 0x1c, 0x0c, 0x0e, 0x21, 0x15, 0x0f, 0x11, 0x23, 0x10, 0x0d, 0x1f, 0x16, 0x0d, 0x17, 0x1f, 0x03, 0x17,
        0x03, 0x17, 0x1d, 0x16, 0x0d, 0x17, 0x1f, 0x17, 0x03, 0x17, 0x1d, 0x16, 0x02, 0x17, 0x25, 0x22, 0x03, 0x15,
        0x16, 0x12, 0x09, 0x12, 0x03, 0x16, 0x16, 0x12, 0x16, 0x19, 0x09, 0x04, 0x0e, 0x01, 0x17, 0x04, 0x17, 0x19,
        0x23, 0x0c, 0x1c, 0x06, 0x09, 0x1b, 0x15, 0x0d, 0x1b, 0x04, 0x1c, 0x1f, 0x03, 0x15, 0x1c, 0x0d, 0x09, 0x12,
        0x19, 0x1c, 0x0d, 0x1f, 0x1c, 0x12, 0x1f, 0x1c, 0x02, 0x14, 0x1f, 0x24, 0x11, 0x18, 0x26, 0x1c, 0x12, 0x1f,
        0x1c, 0x02, 0x14, 0x1f, 0x1c, 0x11, 0x1f, 0x0c, 0x17, 0x1c, 0x12, 0x1f, 0x0c, 0x17, 0x1d, 0x0d, 0x0e, 0x1f,
        0x12, 0x1d, 0x0b, 0x1f, 0x1d, 0x11, 0x18, 0x0f, 0x03, 0x15, 0x1d, 0x11, 0x18, 0x1d, 0x15, 0x19, 0x1d, 0x1f,
        0x11, 0x15, 0x03, 0x15, 0x06, 0x23, 0x1f, 0x03, 0x1f, 0x11, 0x1f, 0x22, 0x1f, 0x0c, 0x03, 0x1f, 0x01, 0x1b,
        0x1c, 0x03, 0x1f, 0x0c, 0x1f, 0x01, 0x1b, 0x1c, 0x03, 0x25, 0x22, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
        0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00,
        0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
        0x18, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x1c, 0x00,
        0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
        0x21, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
        0x21, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x14, 0x00,
        0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x09, 0x00,
        0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
        0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00,
        0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
        0x23, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x17, 0x00,
        0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
        0x1d, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x2f, 0x00,
        0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00,
        0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x38, 0x00,
        0x00, 0x00, 0x39, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00,
        0x3d, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x41, 0x00,
        0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x66, 0x69, 0x72, 0x65, 0x6d, 0x6f, 0x64, 0x65, 0x00, 0x66, 0x69, 0x72,
        0x65, 0x72, 0x72, 0x61, 0x74, 0x65, 0x00, 0x6d, 0x75, 0x73, 0x69, 0x63, 0x5f, 0x73, 0x65, 0x6c, 0x00, 0x6f,
        0x6e, 0x6f, 0x66, 0x66, 0x00, 0x6f, 0x70, 0x65, 0x6e, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00,
        0x23, 0x00, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00, 0x30, 0x00,
        0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
        0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0x00,
        0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00,
        0x3e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x42, 0x00,
        0x00, 0x00, 0x66, 0x69, 0x72, 0x65, 0x6d, 0x6f, 0x64, 0x65, 0x00, 0x66, 0x69, 0x72, 0x65, 0x72, 0x72, 0x61,
        0x74, 0x65, 0x00, 0x6d, 0x75, 0x73, 0x69, 0x63, 0x5f, 0x73, 0x65, 0x6c, 0x00, 0x6f, 0x6e, 0x6f, 0x66, 0x66,
        0x00, 0x6f, 0x70, 0x65, 0x6e, 0x63, 0x6c, 0x6f, 0x73, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00,
        0x2b, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 0x51, 0x00,
        0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x5d, 0x00, 0x00, 0x00, 0x63, 0x61, 0x6b, 0x65, 0x69, 0x73, 0x61, 0x6c,
        0x69, 0x65, 0x00, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6f, 0x76, 0x72, 0x00, 0x66, 0x65, 0x65, 0x64,
        0x62, 0x61, 0x63, 0x6b, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x74, 0x65, 0x6e, 0x61, 0x6e, 0x63, 0x65, 0x00, 0x6d,
        0x6f, 0x64, 0x65, 0x00, 0x6f, 0x70, 0x65, 0x6e, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x72, 0x61, 0x74,
        0x65, 0x6f, 0x66, 0x66, 0x69, 0x72, 0x65, 0x00, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 0x61, 0x75, 0x74, 0x6f,
        0x00, 0x73, 0x61, 0x66, 0x65, 0x74, 0x79, 0x00, 0x73, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0e, 0x00, 0x00, 0x00,
        0x48, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0xe0, 0x02,
        0x00, 0x00, 0x40, 0x03, 0x00, 0x00, 0x50, 0x03, 0x00, 0x00, 0x74, 0x03, 0x00, 0x00, 0xac, 0x03, 0x00, 0x00,
        0xd0, 0x03, 0x00, 0x00, 0xf4, 0x03, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x78, 0x04, 0x00, 0x00, 0xb0, 0x04,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x6c, 0x00,
        0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
        0x80, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00,
        0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00,
        0x00, 0x00, 0xbc, 0x00, 0x00, 0x00, 0xbc, 0x01, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x70, 0x01, 0x00, 0x00, 0xbc, 0x00,
        0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00,
        0x3c, 0x01, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0xff, 0xff,
        0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x2c, 0x01, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00,
        0x0b, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x01, 0x00, 0x00, 0x08, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x0b, 0x00,
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x50, 0x01, 0x00, 0x00, 0x3c, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0x88, 0x01, 0x00, 0x00, 0xac, 0x01, 0x00, 0x00, 0x70, 0x01,
        0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x9c, 0x01, 0x00, 0x00,
        0x88, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x01,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00,
        0x15, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xd0, 0x01, 0x00, 0x00, 0xbc, 0x01,
        0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x09, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0x94, 0x02,
        0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00,
        0x14, 0x02, 0x00, 0x00, 0x60, 0x02, 0x00, 0x00, 0x84, 0x02, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0x16, 0x00,
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0x2c, 0x02, 0x00, 0x00, 0x50, 0x02, 0x00, 0x00,
        0x14, 0x02, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x40, 0x02,
        0x00, 0x00, 0x2c, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01,
        0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x74, 0x02, 0x00, 0x00,
        0x60, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00,
        0x13, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, 0xac, 0x02, 0x00, 0x00, 0xd0, 0x02,
        0x00, 0x00, 0x94, 0x02, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
        0xc0, 0x02, 0x00, 0x00, 0xac, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x94, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xf4, 0x02,
        0x00, 0x00, 0xe0, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x0c, 0x03, 0x00, 0x00, 0x30, 0x03, 0x00, 0x00, 0xf4, 0x02, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x09, 0x00,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x02, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x09, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00,
        0x00, 0x00, 0x64, 0x03, 0x00, 0x00, 0x50, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00,
        0x00, 0x00, 0x88, 0x03, 0x00, 0x00, 0x74, 0x03, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x9c, 0x03, 0x00, 0x00, 0x88, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0xac, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
        0x01, 0x00, 0x00, 0x00, 0xe4, 0x03, 0x00, 0x00, 0xd0, 0x03, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x00,
        0x00, 0x00, 0x1c, 0x04, 0x00, 0x00, 0x54, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00,
        0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x1c, 0x04, 0x00, 0x00, 0x05, 0x00,
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x44, 0x04, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x05, 0x00,
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x68, 0x04, 0x00, 0x00, 0x54, 0x04, 0x00, 0x00,
        0x11, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00,
        0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x8c, 0x04, 0x00, 0x00, 0x78, 0x04, 0x00, 0x00,
        0x05, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xa0, 0x04, 0x00, 0x00, 0x8c, 0x04,
        0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x05, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xc4, 0x04, 0x00, 0x00, 0xb0, 0x04,
        0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



#endif // PARAMS_H
    
