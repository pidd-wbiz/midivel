# midivel
MIDI velocity modifier

For Raspberry Pi Pico

Modifies MIDI velocity data eg to enable fine tuning of touch sensitive keyboards. Everything apart from velocity is passed straight through.

Uses polling and fifo buffers for uart, it is assumed there will be no data overun.

Tested on.....

  Raspberry Pi Pico 

  Alto Proffesional Live 61 Keyboard
  CME UF8 keyboard
  Yamaha SHS-10S keytar
  
  Roland SC-7 Sound Module
  Yamaha EMT-10 AWM Sound Expander

  Datapoint Midi Serial Interface Rev 2.0 (3.3V)
