#include "console.hpp"
#include <cstdio>

#include <mario/mario.h>
#include <eff/eff_fukidashi.h>


namespace mod {



void CC_effect(const char *args) {
  uint32_t sound;
  uint32_t icon;
  if (sscanf(args, "%d %d", &sound, &icon) != 2) {
    gConsole->logInfo("Expected two integer arguments: [sound] [icon]");
  }

  auto height = marioGetPtr()->wPlayerCollisionBox.y;
  auto eff = effFukidashiEntry(icon, sound, (void*)-1, 0.0,
      (3.0 * height) / 2.0, 0.0, height / 3.0, 0.0, 60 /* duration */);
}

ConCommand effect("effect", CC_effect);

}
