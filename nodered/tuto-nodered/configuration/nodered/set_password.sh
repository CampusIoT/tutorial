#!/bin/bash

MAIN_ADMIN_TOKEN=$1
MAIN_USER_PASSWORD=$2

cp /data/settings.TMPL.js /data/settings.js
# Set admin password

HASH_PASSWORD=$(echo "$MAIN_ADMIN_TOKEN" | node_modules/node-red-admin/node-red-admin.js hash-pw | head -1 | awk '{print $2}') \
  && echo HASH_PASSWORD=$HASH_PASSWORD \
  && sed -i "s|__HASH_ADMIN_PASSWORD__|$HASH_PASSWORD|g" /data/settings.js

# Set user password
HASH_USER_PASSWORD=$(echo "$MAIN_USER_PASSWORD" | node_modules/node-red-admin/node-red-admin.js hash-pw | head -1 | awk '{print $2}') \
  && echo HASH_USER_PASSWORD=$HASH_USER_PASSWORD \
  && sed -i "s|__HASH_USER_PASSWORD__|$HASH_USER_PASSWORD|g" /data/settings.js
