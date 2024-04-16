#include <mgr/evtmgr.h>
extern int aaa_00_init_evt[];
static int mapdraw(EventEntry* event, bool isFirstCall);
static void draw(CameraId cameraId, void* param);
static USERFUNC_DEF(check_name);
static USERFUNC_DEF(decrypt_flag1);
static USERFUNC_DEF(release_memory);

void mapdelete(void);
