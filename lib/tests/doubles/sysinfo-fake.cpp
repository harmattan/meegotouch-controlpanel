#include <sysinfo.h>

#include <string.h>

int sysinfo_init (struct system_config **)
{
    return 0;
}

void sysinfo_finish (struct system_config *)
{
}

int sysinfo_get_value (struct system_config *,
                       const char *, uint8_t **val_out,
                       unsigned long *len_out)
{
    static const char* id = "XXX-DEVICE";
    *val_out = (uint8_t*) strdup (id);
    *len_out = strlen (id);
    return 0;
}

