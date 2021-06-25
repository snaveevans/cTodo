#include "todo.h"
#include "cJSON/cJSON.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>

Todo *create_todo(char *name) {
  Todo *todo = calloc(1, sizeof(Todo));
  if (todo == NULL) {
    return NULL;
  }

  todo->name = calloc(strlen(name) + 1, sizeof(char));
  if (todo->name == NULL) {
    return NULL;
  }

  Guid *guid = new_guid();
  if (guid == NULL) {
    return NULL;
  }

  todo->id = guid;
  strcpy(todo->name, name);
  return todo;
}

Todo *_recreate_todo(char *name, char *id) {
  Todo *todo = calloc(1, sizeof(Todo));
  if (todo == NULL) {
    return NULL;
  }

  todo->name = calloc(strlen(name) + 1, sizeof(char));
  if (todo->name == NULL) {
    return NULL;
  }

  Guid *guid = _recreate_guid(id);
  if (guid == NULL) {
    return NULL;
  }
  todo->id = guid;
  strcpy(todo->name, name);
  return todo;
}

cJSON *_get_todo_storage() {
  int length = 0;
  char *buffer = NULL;
  cJSON *todoStorage = NULL;
  FILE *file = get_todo_file("r");
  if (file == NULL) {
    return NULL;
  }

  if (file) {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if (buffer) {
      fread(buffer, 1, length, file);
    }
    fclose(file);
  }

  if (buffer) {
    todoStorage = cJSON_Parse(buffer);
    free(buffer);
  }

  return todoStorage;
}

int get_todos_length() {
  cJSON *todoCjson = NULL;
  cJSON *todosCjson = NULL;
  cJSON *todoStorage = _get_todo_storage();
  if (todoStorage == NULL) {
    return -1;
  }

  todosCjson = cJSON_GetObjectItemCaseSensitive(todoStorage, "todos");
  if (todosCjson == NULL) {
    return -1;
  }

  int length = 0;
  cJSON_ArrayForEach(todoCjson, todosCjson) { length = length + 1; }

  cJSON_Delete(todoStorage);
  return length;
}

int get_todos(Todo **todos, int length) {
  cJSON *id = NULL;
  cJSON *name = NULL;
  cJSON *todoCjson = NULL;
  cJSON *todosCjson = NULL;
  cJSON *todoStorage = _get_todo_storage();
  if (todoStorage == NULL) {
    return -1;
  }

  todosCjson = cJSON_GetObjectItemCaseSensitive(todoStorage, "todos");
  if (todosCjson == NULL) {
    return -1;
  }

  int pos = 0;
  cJSON_ArrayForEach(todoCjson, todosCjson) {
    id = cJSON_GetObjectItemCaseSensitive(todoCjson, "id");
    name = cJSON_GetObjectItemCaseSensitive(todoCjson, "name");

    Todo *todo = _recreate_todo(name->valuestring, id->valuestring);
    todos[pos] = todo;
    pos++;
    if (pos == length) {
      goto end;
    }
  }

end:
  cJSON_Delete(todoStorage);
  return 0;
}

int write_todo(Todo *todo) {
  char *string = NULL;
  cJSON *todos = NULL;
  cJSON *todoCjson = NULL;
  cJSON *name = NULL;
  cJSON *id = NULL;

  cJSON *todoStorage = cJSON_CreateObject();
  if (todoStorage == NULL) {
    goto end;
  }

  todos = cJSON_CreateArray();
  if (todos == NULL) {
    goto end;
  }
  cJSON_AddItemToObject(todoStorage, "todos", todos);

  todoCjson = cJSON_CreateObject();
  if (todoCjson == NULL) {
    goto end;
  }
  cJSON_AddItemToArray(todos, todoCjson);

  name = cJSON_CreateString(todo->name);
  if (name == NULL) {
    goto end;
  }
  cJSON_AddItemToObject(todoCjson, "name", name);

  id = cJSON_CreateString(todo->id->value);
  if (id == NULL) {
    goto end;
  }
  cJSON_AddItemToObject(todoCjson, "id", id);

  string = cJSON_PrintUnformatted(todoStorage);
  if (string != NULL) {
    FILE *file = get_todo_file("w");
    fprintf(file, "%s\n", string);
  }
end:
  return 0;
}

void free_todo(Todo *todo) {
  free(todo->id->value);
  free(todo->id);
  free(todo->name);
  free(todo);
}

void free_todos(Todo **todos, int length) {
  for (int pos = 0; pos < length; pos++) {
    free_todo(todos[pos]);
  }
  free(todos);
}
