#pragma once

#include <cstdint>
#include <dolphin/os/OSExi.h>

namespace mod {

/// Checks if there is a USB Gecko on EXI channel `chan`
bool ugProbe(EXIChannel chan);

/// Try to send `len` bytes from `data` via the USB Gecko on channel `chan`.
/// Returns number of bytes sent or negative on error.
int ugSend(EXIChannel chan, const void *data, int len);

/// Try to receive `len` bytes into `data` via the USB Gecko on channel `chan`.
/// Returns number of bytes received or negative on error.
int ugRecv(EXIChannel chan, void *data, int len);

}
