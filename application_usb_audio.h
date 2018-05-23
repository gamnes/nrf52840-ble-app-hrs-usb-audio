#ifndef __APPLICATION_USB_AUDIO_H
#define __APPLICATION_USB_AUDIO_H

#include <stdint.h>

typedef enum 
{
    AUA_EVENT_USB_POWER_DETECTED = 0,
    AUA_EVENT_USB_POWER_REMOVED,
    AUA_EVENT_USB_POWER_READY,
    AUA_EVENT_USB_USER_EVT_RX_DONE
} application_usb_audio_event_type_t;

typedef struct
{
    application_usb_audio_event_type_t event_type;
    int16_t *   temp_buffer;
    uint32_t    temp_buffer_size;
} application_usb_audio_event_t;

typedef void (*application_usb_audio_callback_t)(application_usb_audio_event_t *event);

typedef struct
{
     application_usb_audio_callback_t event_handler;
}application_usb_audio_config_t;

#define USBD_AUDIO_SAMPLE_FREQ  48000
#define USBD_AUDIO_CHANNELS     2
#define USBD_AUDIO_RESOLUTION   16

uint32_t application_usb_audio_init(application_usb_audio_config_t *config);
uint32_t application_usb_audio_events_enable(void);
uint32_t application_usb_audio_process_events(void);

#endif
