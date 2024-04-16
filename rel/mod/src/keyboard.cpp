#include "keyboard.hpp"

#include <dolphin/si.h>

#include <cstring>

namespace mod {

Keyboard::Keyboard(int channel)
{
	setChannel(channel);
}

void Keyboard::setChannel(int channel)
{
	// Disconnect if necessary
	if (mConnected)
	{
		disconnect();
	}

	// Set new channel
	mChannel = channel;

	// Reconnect
	connect();
}

bool Keyboard::connect()
{
	if (SIProbe(mChannel) != 0x08200000)
	{
		// No keyboard in that slot
		return false;
	}
	
	// Enable polling from device
	SIEnablePolling(1 << (31 - mChannel));
	
	mConnected = true;
	return true;
}

void Keyboard::disconnect()
{
	// Flush response
	uint64_t message;
	SIGetResponse(mChannel, &message);
	
	// Disable polling
	SIDisablePolling(1 << (31 - mChannel));
	mConnected = false;
}

void Keyboard::update()
{
	if (!mConnected && !connect())
	{
		return;
	}
	
	// Poll next state
	SISetCommand(mChannel, 0x00540000);
	SITransferCommands();
	
	// Read data
	uint64_t message;
	if (!SIGetResponse(mChannel, &message) || message & (1LL << 63))
	{
		// Failed to receive response or ERRSTAT is set
		disconnect();
	}
	
	// Save last key state
	mKeysPrevCount = mKeysDownCount;
	memcpy(mKeysPrev, mKeysDown, sizeof(mKeysPrev));
	
	// Read new keys
	mKeysDownCount = 0;
	for (int i = 0; i < cMaxKeysPressed; ++i)
	{
		KeyCode code = static_cast<KeyCode>((message >> (i * 8 + 8)) & 0xFF);

		if (code == KeyCode::kInvalid)
		{
			continue;
		}

		mKeysDown[mKeysDownCount++] = code;
	}
	
	// Check released keys
	mKeysReleasedCount = 0;
	for (int i = 0; i < mKeysPrevCount; ++i)
	{
		bool released = true;
		for (int j = 0; j < mKeysDownCount; ++j)
		{
			if (mKeysPrev[i] == mKeysDown[j])
			{
				released = false;
			}
		}
		if (released)
		{
			mKeysReleased[mKeysReleasedCount++] = mKeysPrev[i];
		}
	}
	
	// Check pressed keys
	mKeysPressedCount = 0;
	for (int i = 0; i < mKeysDownCount; ++i)
	{
		bool pressed = true;
		for (int j = 0; j < mKeysPrevCount; ++j)
		{
			if (mKeysDown[i] == mKeysPrev[j])
			{
				pressed = false;
			}
		}
		if (pressed)
		{
			mKeysPressed[mKeysPressedCount++] = mKeysDown[i];
		}
	}
}

}
