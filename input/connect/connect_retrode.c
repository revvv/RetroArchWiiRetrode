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

struct hidpad_retrode_data
{
   struct pad_connection* connection;
   uint8_t data[64];
   uint32_t slot;
   uint32_t buttons;
};

static void* hidpad_retrode_init(void *data, uint32_t slot, hid_driver_t *driver)
{
   struct pad_connection* connection = (struct pad_connection*)data;
   struct hidpad_retrode_data* device    = (struct hidpad_retrode_data*)
      calloc(1, sizeof(struct hidpad_retrode_data));

   if (!device)
      return NULL;

   if (!connection)
   {
      free(device);
      return NULL;
   }

   device->connection   = connection;
   device->slot         = slot;

   return device;
}

static void hidpad_retrode_deinit(void *data)
{
   struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;

   if (device)
      free(device);
}

static void hidpad_retrode_get_buttons(void *data, input_bits_t *state)
{
	struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;
	if (device)
   {
		BITS_COPY16_PTR(state, device->buttons);
	}
   else
		BIT256_CLEAR_ALL_PTR(state);

	RARCH_LOG("XXX Retrode hack BTN val=%d / %d\n", state, device->buttons);
}

static int16_t hidpad_retrode_get_axis(void *data, unsigned axis)
{
   int val;
   struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;

   if (!device || axis >= 2)
      return 0;

   val = device->data[2 + axis];
   //RARCH_LOG("Retrode DPAD val=0x%02X\n", val);

   // map Retrode values to a known gamepad (VID=0x0079, PID=0x0011)
   if (val == 0x9C)
   {
	   // axis=0 left, axis=1 up
	   val = 0x00;
   }
   else if (val == 0x64)
   {
	   // axis=0 right, axis=1 down
	   val = 0xFF;
   }
   else
   {
	   val = 0x7F; // no button pressed
   }

   val = (val << 8) - 0x8000;

   return (abs(val) > 0x1000) ? val : 0;
}

static void hidpad_retrode_packet_handler(void *data, uint8_t *packet, uint16_t size)
{
   uint32_t i, pressed_keys;
   static const uint32_t button_mapping[8] =
   {
		   RETRO_DEVICE_ID_JOYPAD_B,
		   RETRO_DEVICE_ID_JOYPAD_Y,
		   RETRO_DEVICE_ID_JOYPAD_SELECT,
		   RETRO_DEVICE_ID_JOYPAD_START,
		   RETRO_DEVICE_ID_JOYPAD_A,
		   RETRO_DEVICE_ID_JOYPAD_X,
		   RETRO_DEVICE_ID_JOYPAD_L,
		   RETRO_DEVICE_ID_JOYPAD_R
   };
   struct hidpad_retrode_data *device = (struct hidpad_retrode_data*)data;

   if (!device)
      return;

   // Retrode: Add this to only support controller 1 (also required for heldButton state)
   if (packet[1] != 1)
   	   return;

   memcpy(device->data, packet, size);

   device->buttons = 0;

   pressed_keys = device->data[4];

   for (i = 0; i < 8; i ++)
      if (button_mapping[i] != NO_BTN)
         device->buttons |= (pressed_keys & (1 << i)) ? (1 << button_mapping[i]) : 0;
}

static void hidpad_retrode_set_rumble(void *data,
      enum retro_rumble_effect effect, uint16_t strength)
{
	(void)data;
	(void)effect;
   (void)strength;
}

const char * hidpad_retrode_get_name(void *data)
{
	(void)data;
	/* For now we return a single static name */
	return "Retrode";
}

pad_connection_interface_t pad_connection_retrode = {
   hidpad_retrode_init,
   hidpad_retrode_deinit,
   hidpad_retrode_packet_handler,
   hidpad_retrode_set_rumble,
   hidpad_retrode_get_buttons,
   hidpad_retrode_get_axis,
   hidpad_retrode_get_name,
};
