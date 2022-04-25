/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : json_opt2
 * @created     : Duminică Mar 06, 2022 07:50:00 EET
 */

#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  /*Declaring the json data's in json format*/
  char buf[] =
      "{ \"Name\": \"xxxxx\", \"Id\": 101, \"Voting_eligible\": true }";

  /*Declaring the Json_object.To pass the Json string to the newly created
   * Json_object*/
  json_object* new_obj = json_tokener_parse(buf);

  /*To get the data's then we have to get to the specific node by using the
   * below function*/

  json_object*
      obj_Name;  // Declaring the object to get  store the value of the Name
  obj_Name = json_object_object_get(
      new_obj,
      "Name");  // This in-built func used to traverse through specific node

  json_object*
      obj_Id;  // Declaring the object to get  store the value of the Id
  obj_Id = json_object_object_get(
      new_obj,
      "Id");  // This in-built func used to traverse through specific node

  json_object*
      obj_Vote;  // Declaring the object to get  store the value of the  Vote
  obj_Vote = json_object_object_get(
      new_obj, "Voting_eligible");  // This in-built func used to traverse
                                    // through specific node

  /* To store the values we use temp char */
  char* Name = json_object_get_string(
      obj_Name);  // This is in-built func to get the string(value) from
                  // "json_object_object_get()"
  char* Id = json_object_get_string(obj_Id);
  char* Vote = json_object_get_string(obj_Vote);

  /* we can also use like this statement directly to reduce the pgm size */
  //  printf("Name :
  //  %s\n",json_object_get_string(json_object_object_get(new_obj, "Name")));
  //  printf("Id : %s\n",json_object_get_string(json_object_object_get(new_obj,
  //  "Id"))); printf("Voting_eligible :
  //  %s\n",json_object_get_string(json_object_object_get(new_obj,
  //  "Voting_eligible")));

  printf("Name : %s\n", Name);
  printf("Id : %s\n", Id);
  printf("Voting_eligible : %s\n", Vote);

  json_object_put(new_obj);  // to return the pointer to its originalobjects
}
