The vt_sound library places code and data into sections "code_user" and "data_user".

We'd like to move that to "BANK_6" so that AY code exists in a separate memory bank.
This is done by getting zobjcopy to rename the sections in the "vt_sound.lib" file.

zobjcopy vt_sound.lib --section code_user=BANK_6 --section data_user=BANK_6 --global "VT_INIT" --global "VT_MUTE" --global "_vt_play" --global "_vt_play_isr_enabled" vt_sound_6.lib

Linking the program against "vt_sound_6.lib" will now place all AY-related code into
BANK_6.
