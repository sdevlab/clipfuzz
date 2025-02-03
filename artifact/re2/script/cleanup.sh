#!/bin/bash

while true; do
  find .. -type d -name 'artifact' -exec sh -c "rm -rf {}/*" \;
  sleep 600
done
