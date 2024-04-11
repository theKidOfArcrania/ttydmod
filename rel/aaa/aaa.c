#include <mgr/evtmgr_cmd.h>
#include <mapdata.h>
#include <placeholder.h>
#include "aaa.h"
#include "aaa_00.h"
static char negone_one__374[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static float neg_one__382 = -1.0;
static float __local_PI__383 = 3.1415927;
static float __local_3PIO2__385[] = { 4.712389, 0.0 };
static char one_negone__373[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static float __local_PIO2__384 = 1.5707964;
static float one__381 = 1.0;
static char negone_one__360[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static float neg_one__365 = -1.0;
static float __local_PI__366 = 3.1415927;
static float __local_3PIO2__368[] = { 4.712389, 0.0 };
static char one_negone__359[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static float __local_PIO2__367 = 1.5707964;
static float one__364 = 1.0;
static double _three__localstatic4__sqrtf = 3.0;
static double _half__localstatic3__sqrtf = 5e-1;

typedef void (*EntryFunction)(void);

SECTION(".ctors") static const EntryFunction init[1] = { NULL };
SECTION(".dtors") static const EntryFunction fini[1] = { NULL };

void _unresolved() {

}

EvtReturnCodes __break__(EventEntry *evt, bool a) {
  (*(int*)evt->args[0]) = 0;
  return EVT_RETURN_DONE;
}

void _epilog(void) {
    const EntryFunction *dtor;
    mapdelete();
    for (dtor = fini; *dtor; dtor++) {
        (*dtor)();
    }
}
void _prolog(void) {
    const EntryFunction *ctor;
    for (ctor = init; *ctor; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("aaa_00", aaa_00_init_evt);
}
