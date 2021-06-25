#ifndef GUID_H_
#define GUID_H_

typedef struct {
  char *value;
} Guid;

Guid *new_guid();
Guid *_recreate_guid(char *id);

#endif
