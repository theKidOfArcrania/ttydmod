#include <platform.h>
#include <mgr/evtmgr_cmd.h>

typedef struct TreeData {
  int has_more;
  const char *ki_hit_obj;
  const char *miki; // Tree trunk?
  const char *ha_temae; // Leaves in front
  const char *ha_usiro; // Leaves in the back
  Bytecode *callback;
} TreeData;

typedef struct KusaData {
  int has_more;
  const char *kusa_hit_obj;
  const char *map_obj;
  int *callback;
} KusaData;
