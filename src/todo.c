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

cJSON *_get_todo_storageJson() {
  int length = 0;
  char *buffer = NULL;
  cJSON *todostorageJson = NULL;
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
    todostorageJson = cJSON_Parse(buffer);
    free(buffer);
  }

  return todostorageJson;
}

int get_storage(cJSON **storageJson, cJSON **todosJsonArray) {
  int result = 0;
  *storageJson = _get_todo_storageJson();

  if (storageJson == NULL) {
    // no file create storageJson and todosArray
    goto create;
  }

  *todosJsonArray = cJSON_GetObjectItemCaseSensitive(*storageJson, "todos");
  if (todosJsonArray == NULL) {
    // file exists but no todos, create storageJson and todosArray
    goto create;
  }
  goto end;

create:
  *storageJson = cJSON_CreateObject();
  if (storageJson == NULL) {
    // unexpected error
    result = 1;
    goto end;
  }

  *todosJsonArray = cJSON_CreateArray();
  if (todosJsonArray == NULL) {
    // unexpected error
    result = 2;
    goto end;
  }
  cJSON_AddItemToObject(*storageJson, "todos", *todosJsonArray);

end:
  if (result >= 2) {
    cJSON_Delete(*storageJson);
    storageJson = NULL;
  }
  return result;
}

Todo **get_todos(int *length) {
  int result = 0;
  int position = 0;
  Todo **todos = NULL;
  cJSON *idJson = NULL;
  cJSON *nameJson = NULL;
  cJSON *todoJson = NULL;
  cJSON *storageJson = NULL;
  cJSON *todosJsonArray = NULL;

  if (get_storage(&storageJson, &todosJsonArray) != 0) {
    result = 1;
    goto end;
  }

  cJSON_ArrayForEach(todoJson, todosJsonArray) {
    idJson = cJSON_GetObjectItemCaseSensitive(todoJson, "id");
    nameJson = cJSON_GetObjectItemCaseSensitive(todoJson, "name");

    Todo *todo = _recreate_todo(nameJson->valuestring, idJson->valuestring);
    int size = (position + 1) * sizeof(Todo);
    todos = realloc(todos, size);
    todos[position] = todo;
    position = position + 1;
  }

end:
  if (result != 0) {
    return NULL;
  }
  cJSON_Delete(storageJson);
  *length = position;
  return todos;
}

int add_to_json_array(Todo *todoObj, cJSON *todosJsonArray) {
  int result = 0;
  cJSON *todoJson = NULL;
  cJSON *nameJson = NULL;
  cJSON *idJson = NULL;
  todoJson = cJSON_CreateObject();

  if (todoJson == NULL) {
    result = 1;
    goto end;
  }
  cJSON_AddItemToArray(todosJsonArray, todoJson);

  nameJson = cJSON_CreateString(todoObj->name);
  if (nameJson == NULL) {
    result = 2;
    goto end;
  }
  cJSON_AddItemToObject(todoJson, "name", nameJson);

  idJson = cJSON_CreateString(todoObj->id->value);
  if (idJson == NULL) {
    result = 3;
    goto end;
  }
  cJSON_AddItemToObject(todoJson, "id", idJson);

end:
  // TODO should we clear on 0
  // if so add cJSON_Delete for idJson
  if (result >= 2) {
    cJSON_Delete(todoJson);
    todoJson = NULL;
  }
  if (result >= 3) {
    cJSON_Delete(nameJson);
    nameJson = NULL;
  }
  return result;
}

int append_todo(Todo *todo) {
  int result = 0;
  char *string = NULL;
  FILE *file = NULL;
  cJSON *storageJson = NULL;
  cJSON *todosJsonArray = NULL;

  if (get_storage(&storageJson, &todosJsonArray) != 0) {
    result = 1;
    goto end;
  }

  if (add_to_json_array(todo, todosJsonArray) != 0) {
    result = 2;
    goto end;
  }

  string = cJSON_PrintUnformatted(storageJson);
  if (string == NULL) {
    result = 3;
    goto end;
  }
  file = get_todo_file("w");
  fprintf(file, "%s\n", string);
end:
  // cleanup
  if (result >= 2 || result == 0) {
    cJSON_Delete(storageJson);
    storageJson = NULL;
    todosJsonArray = NULL;
  }
  if (result == 0) {
    free(string);
    fclose(file);
    string = NULL;
    file = NULL;
  }
  return result;
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
