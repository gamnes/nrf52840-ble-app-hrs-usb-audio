
# nRF52840-ble-app-hrs-usb-audio-teensy

This repository contains example source code that can be used together with a nRF52840-DK
to interface and use a Teensy SGTL5000 Audio adapter board along with transferring USB Audio 
data through the USB interface, while at the same time running BLE APP HRS. 
A Teensy Arduino Shield Adapter with some modifications are used to connect the audio board to the DK. 
A standard MIC input microphone, or a LINEIN MEMs microphone is used for microphone input for testing purposes.

To see the setup of the Teensy Audio Board as well as the shield adapter and DK preprations, please have a look 
at the nRF52-teensy-sgtl5000-audio GitHub repository. This demo is using the exact same setup as that example. 
There are some modifications in this examples with respect to the SGTL5000 driver source. This example has the 
nRF configured as a I2S Slave, while the PLL is used on the SGTL5000 and it acts as the I2S Master. The sample playback 
feature has also been removed from the source in this repo. 

## Comments
<dl>
  <dt>Please note:</dt>
    <dd> 
      This demo will only run on the nRF52840-DK! The other nRF52-series SoCs do not have a USB interface.
    </dd>
  <dt>I2S MCLK Frequency</dt>
    <dd> 
      The nRF52840 is set up to run I2S as a Slave at 8MHz, which is above the defined maximum I2S speed of the nRF52840
      in its specification. This has been tested and works for this demo purpose, but for an actual product you might want 
      to stay within the specified limits of the SoC as well as the audio device that you are going to use.
    </dd>

  <dt>Audio Volume</dt>
    <dd> 
      The volume output of this demo could be fairly HIGH depending on the microphone/speakers
      that are being used. Please be aware of this and don't put your headphones into your ears before you 
      have tested the output volume level!
    </dd>
</dl>



## Running the example

Please note the volume level warning as noted earlier. Depending on your microphone and speakers, 
certain dB settings in the header/source driver files might have to be changed to provide an acceptable 
volume level. 

### HW Setup
To run this example on the nRF52840-DK, please follow the setup as explained in the nRF52-teensy-sgtl5000-audio repository.
I would also recommend you run the SDK v15.0.0 'USB Audio Class Example' to get familiar with how the USB works.

### Run the example
One all the modification are done (Audio board, Teensy Shield, and nRF52840-DK), you are ready to test this! 

#### Assembly and flashing
- Connect the SGTL5000 Audio board to the Teensy Shield
- Connect the Teensy Shield to the nRF52-DK
- Connect a speaker or headphone to the jack plug on the audio board
- Upload precompiled .hex file found in the repository, "nrf52840-ble-app-hrs-usb-audio-teensy_app_s140.hex", to the nRF52840-DK
- Connect a micro USB cable between the PC and the 'nRF USB' on the long edge of the DK (you probably now also have the normal 
USB micro cable connected to the short edge, that is fine and it can be used to see the UART logging). Reset the DK.


#### What to expect
When the application is running, and after a reset, your PC might automatically detect the nRF USB Audio streams - input and output.
My PC swaps automatically over to using the "Headphones (nRF52 USB Audio Demo)" output, as well as the nRF52 USB input. After your PC is
configured to use the nRF52 "Headphones", play your favorite youtube video or something else that has audio, and the audio should be played on the 
headphones/speaker that is connected to the Teensy Audio Board. Success!:D You should now also be able to connect to the BLE HRS using nRF Connect 
on your phone or the PC using a Dongle. 

If you are having issues getting the headphones/speakers to work, I suggest you modify the source code to enable Microphone
playback loop `drv_sgtl5000_start_mic_loopback()` in `main()` and make sure that works before you try to play the USB audio.
If this does not work either, I suggest going back to the standalone Teensy Audio Board example and make sure that runs before
testing this demo.



## Compiling and Developing
This example is built with SDK v15.0.0. This can be downloaded here: http://developer.nordicsemi.com/nRF5_SDK/. 

The example assumes a location of this repository matching the following path for this readme.
```
...\nRF5_SDK_15.0.0_a53641a\examples\peripheral\nrf52840-ble-app-hrs-usb-audio-teensy\README.md
```


### Development Environment
There is both Keil and SES project files that can be used for development. Please note that if you use one for 
development and not the other, I would recommend deleting the one that is not used to avoid confusion at a later 
stage when you might think both projects in the repository are up to date - but in fact they are not.


## FW Overview
This example works by forwarding the received USB audio data in `hp_audio_user_ev_handler()` to a application 
event handler. The event used for this is named `AUA_EVENT_USB_USER_EVT_RX_DONE`. The application then takes this 
USB audio data and puts it into a queue, this is done in `application_usb_audio_callback()`. The I2S callback function,
`i2s_sgtl5000_driver_evt_handler()`, which is basically the I2S peripheral library requesting data from the application, 
checks this same queue, and if there are any frames to be played, it will pop them off and play it.

## TODO Add more documentation.

