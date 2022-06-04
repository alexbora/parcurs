#!/usr/bin/env sh

######################################################################
# @author      : alex (alex@mac.local)
# @file        : mail
# @created     : Joi Iun 02, 2022 22:54:41 EEST
#
# @description : 
######################################################################


#!/bin/bash

sesAccess='t400.linux@gmail.com'
sesSecret='Cragger2011'   
sesFromName="alex"
sesFromAddress="t400.linux@gmail.com"
sesToName="alex"
sesToAddress="alexandru.bora@renault-trucks.com"
sesSubject="Test"
sesSMTP="smtp.gmail.com"
sesPort="465"
sesMessage=$''
sesFile="$1"
sesMIMEType=`file --mime-type "$sesFile" | sed 's/.*: //'`

curl -v --url smtps://$sesSMTP:$sesPort --ssl-reqd  --mail-from $sesFromAddress --mail-rcpt $sesToAddress  --user $sesAccess:$sesSecret -F '=(;type=multipart/mixed' -F "=$sesMessage;text/plain" -F "file=@$sesFile;type=$sesMIMEType;encoder=base64" -F '=)' -H "Subject: $sesSubject" -H "From: $sesFromName <$sesFromAddress>" -H "To: $sesToName <$sesToAddress>"
