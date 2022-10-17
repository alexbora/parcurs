#!/usr/bin/env sh

######################################################################
# @author      : alex (alex@mac.local)
# @file        : tino
# @created     : Luni Oct 17, 2022 17:58:54 EEST
#
# @description : 
######################################################################


#!/bin/bash
echo Content-type: text/html
echo ""
## make POST and GET stings
## as bash variables available
if [ ! -z $CONTENT_LENGTH ] && [ "$CONTENT_LENGTH" -gt 0 ] && [ $CONTENT_TYPE != "multipart/form-data" ]; then
read -n $CONTENT_LENGTH POST_STRING <&0
eval `echo "${POST_STRING//;}"|tr '&' ';'`
fi
eval `echo "${QUERY_STRING//;}"|tr '&' ';'`

echo  "<!DOCTYPE html>"
echo  "<html>"
echo  "<head>"
echo  "</head>"

if [[ "$vote" = "a" ]];then
echo "you pressed A"
  sudo /usr/local/bin/run_a.sh
elif [[ "$vote" = "b" ]];then
echo "you pressed B"
  sudo /usr/local/bin/run_b.sh
fi

echo  "<body>"
echo  "<div id=\"content-container\">"
echo  "<div id=\"content-container-center\">"
echo  "<form id=\"choice\" name='form' method=\"POST\" action=\"/\">"
echo  "<button id=\"a\" type=\"submit\" name=\"vote\" class=\"a\" value=\"a\">A</button>"
echo  "<button id=\"b\" type=\"submit\" name=\"vote\" class=\"b\" value=\"b\">B</button>"
echo  "</form>"
echo  "<div id=\"tip\">"
echo  "</div>"
echo  "</div>"
echo  "</div>"
echo  "</div>"
echo  "</body>"
echo  "</html>"
