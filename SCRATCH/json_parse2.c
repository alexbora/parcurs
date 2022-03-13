/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : json_parse
 * @created     : duminică mar 06, 2022 14:29:55 EET
 */

#include "json-c/json_types.h"
#include <json-c/json.h>
#include <stdio.h>

int main() {
  char *string =
      "{ \"name\": \"xxxxx\", \"Id\": 101, \"Voting_eligible\": true }";
  char *string2 = "{ \"name\": \"21/01/2022\",  \"name\": \"31/01/2022\" }";

  json_object *jobj = json_tokener_parse(string2);
  json_object_object_foreach(jobj, key, val) {
    printf("%s\n", key);
    printf("%s\n", json_object_to_json_string(val));
  }
}
