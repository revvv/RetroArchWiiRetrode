/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2013-2014 - Jason Fetters
 *  Copyright (C) 2011-2017 - Daniel De Matteis
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <boolean.h>
#include "joypad_connection.h"

#include "../input_defines.h"

struct hidpad_xbox360_data
{
   struct pad_connection* connection;
   hid_driver_t *driver;
   uint8_t data[64];
   uint32_t slot;
   uint32_t buttons;
};

static void* hidpad_xbox360_init(void *data, uint32_t slot, hid_driver_t *driver)
{
   struct pad_connection* connection = (struct pad_connection*)data;
   struct hidpad_xbox360_data* device    = (struct hidpad_xbox360_data*)
      calloc(1, sizeof(struct hidpad_xbox360_data));

   if (!device)
      return NULL;

   if (!connection)
   {
      free(device);
      return NULL;
   }

   device->connection   = connection;
   device->slot         = slot;
   device->driver       = driver;

   /* turn on LED */
   if (slot < 4)
   {
       uint8_t ATTRIBUTE_ALIGN(32) buf[] = { WIIUSB_SC_INTMSG, 0x01, 0x03, 0x06 + slot };
       device->driver->send_control(device->connection, buf, sizeof(buf));
   }

   return device;
}

static void hidpad_xbox360_deinit(void *data)
{
    struct hidpad_xbox360_data *device = (struct hidpad_xbox360_data*)data;

    if (device)
        free(device);
}

static void hidpad_xbox360_get_buttons(void *data, input_bits_t *state)
{
    struct hidpad_xbox360_data *device = (struct hidpad_xbox360_data*)data;
    if (device)
    {
        BITS_COPY16_PTR(state, device->buttons);
    }
    else
        BIT256_CLEAR_ALL_PTR(state);
}

static int16_t hidpad_xbox360_get_axis(void *data, unsigned axis)
{
    struct hidpad_xbox360_data *device = (struct hidpad_xbox360_data*)data;

    if (!device || axis >= 4)
        return 0;

    /* return value within [-32768, 32767] */
    if (axis == 0)
        return (device->data[10] << 8) | device->data[9];
    else if (axis == 1)
        return (device->data[8]  << 8) | device->data[7];
    else if (axis == 2)
        return (device->data[14] << 8) | device->data[13];
    else if (axis == 3)
        return (device->data[12] << 8) | device->data[11];

    return 0;
}

static void hidpad_xbox360_packet_handler(void *data, uint8_t *packet, uint16_t size)
{
    struct hidpad_xbox360_data *device = (struct hidpad_xbox360_data*)data;

    if (!device)
        return;

    memcpy(device->data, packet, size);

    device->buttons = 0;

    device->buttons |= ((device->data[3] & 0x01) == 0x01) ? (1 << RETRO_DEVICE_ID_JOYPAD_UP)     : 0;
    device->buttons |= ((device->data[3] & 0x02) == 0x02) ? (1 << RETRO_DEVICE_ID_JOYPAD_DOWN)   : 0;
    device->buttons |= ((device->data[3] & 0x04) == 0x04) ? (1 << RETRO_DEVICE_ID_JOYPAD_LEFT)   : 0;
    device->buttons |= ((device->data[3] & 0x08) == 0x08) ? (1 << RETRO_DEVICE_ID_JOYPAD_RIGHT)  : 0;
    device->buttons |= ((device->data[3] & 0x10) == 0x10) ? (1 << RETRO_DEVICE_ID_JOYPAD_START)  : 0;
    device->buttons |= ((device->data[3] & 0x20) == 0x20) ? (1 << RETRO_DEVICE_ID_JOYPAD_SELECT) : 0; /* XBOX360 back button maps to select */
    device->buttons |= ((device->data[3] & 0x40) == 0x40) ? (1 << RETRO_DEVICE_ID_JOYPAD_L3)     : 0;
    device->buttons |= ((device->data[3] & 0x80) == 0x80) ? (1 << RETRO_DEVICE_ID_JOYPAD_R3)     : 0;
    device->buttons |= ((device->data[4] & 0x10) == 0x10) ? (1 << RETRO_DEVICE_ID_JOYPAD_B)      : 0; /* XBOX360 A button maps to B */
    device->buttons |= ((device->data[4] & 0x20) == 0x20) ? (1 << RETRO_DEVICE_ID_JOYPAD_A)      : 0; /* XBOX360 B button maps to A */
    device->buttons |= ((device->data[4] & 0x40) == 0x40) ? (1 << RETRO_DEVICE_ID_JOYPAD_Y)      : 0; /* XBOX360 X button maps to Y */
    device->buttons |= ((device->data[4] & 0x80) == 0x80) ? (1 << RETRO_DEVICE_ID_JOYPAD_X)      : 0; /* XBOX360 Y button maps to X */
    device->buttons |= ((device->data[4] & 0x01) == 0x01) ? (1 << RETRO_DEVICE_ID_JOYPAD_L)      : 0;
    device->buttons |= ((device->data[4] & 0x02) == 0x02) ? (1 << RETRO_DEVICE_ID_JOYPAD_R)      : 0;

    /* XBOX360 button unused */
    /* device->buttons |= ((device->data[4] & 0x04) == 0x04) ? ... : 0; */

    /* triggers */
    device->buttons |= (device->data[5] > 128) ? (1 << RETRO_DEVICE_ID_JOYPAD_L2) : 0; /* [0, 255] */
    device->buttons |= (device->data[6] > 128) ? (1 << RETRO_DEVICE_ID_JOYPAD_R2) : 0; /* [0, 255] */
}

static void hidpad_xbox360_set_rumble(void *data,
      enum retro_rumble_effect effect, uint16_t strength)
{
    struct hidpad_xbox360_data *device = (struct hidpad_xbox360_data*)data;
    u8 left, right;

    if (!device)
        return;

    left = (effect == RETRO_RUMBLE_STRONG) ? 100 : 50;
    right = (effect == RETRO_RUMBLE_STRONG) ? 100 : 50;

    uint8_t ATTRIBUTE_ALIGN(32) buf[] = { WIIUSB_SC_INTMSG, 0x00, 0x08, 0x00, left, right, 0x00, 0x00, 0x00 };
    device->driver->send_control(device->connection, buf, sizeof(buf));
}

const char * hidpad_xbox360_get_name(void *data)
{
    (void)data;
    /* For now we return a single static name */
    return "XBOX360";
}

pad_connection_interface_t pad_connection_xbox360 = {
   hidpad_xbox360_init,
   hidpad_xbox360_deinit,
   hidpad_xbox360_packet_handler,
   hidpad_xbox360_set_rumble,
   hidpad_xbox360_get_buttons,
   hidpad_xbox360_get_axis,
   hidpad_xbox360_get_name,
};

