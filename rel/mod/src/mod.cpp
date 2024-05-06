#include "mod.hpp"
#include "patch.hpp"

#include <drv/dispdrv.h>
#include <mgr/fontmgr.h>
#include <system.h>
#include <pmario_sound.h>

#include <cstdio>
#include <cstring>

ModInitFunction *ModInitFunction::sFirst = nullptr;
ModUpdateFunction *ModUpdateFunction::sFirst = nullptr;

namespace mod {

Mod *gMod = nullptr;

void main()
{
	Mod *mod = new Mod();
	mod->init();
}

Mod::Mod()
{
	
}

void Mod::init()
{
	gMod = this;

	mPFN_makeKey_trampoline = patch::hookFunction(makeKey, []()
	{
		gMod->updateEarly();
	});

	// Initialize typesetting early
	fontmgrTexSetup();
	patch::hookFunction(fontmgrTexSetup, [](){});

	mConsole.init();

	// Run spread initializations
	for (ModInitFunction *p = ModInitFunction::sFirst; p; p = p->next)
	{
		p->initFunction();
	}

  psbgmlist[1] = BGMList {
    "BGM_EVT_DANGER5",
    0x80000000,
    "sound/stream/evt_kik5_32k",
    80,
    64,
    0,
    1,
  };
}

void Mod::updateEarly()
{
	// Run spread update functions
	for (ModUpdateFunction *p = ModUpdateFunction::sFirst; p; p = p->next)
	{
		p->updateFunction();
	}

	// Register draw command
	dispEntry(CameraId::CAMERA_DEBUG_3D, 1, 0.f, [](CameraId layerId, void *user)
	{
		reinterpret_cast<Mod *>(user)->draw();
	}, this);

	mConsole.update();

	// Call original function
	mPFN_makeKey_trampoline();
}

void Mod::draw()
{

}

}
