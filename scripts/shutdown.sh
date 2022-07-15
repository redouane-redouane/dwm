#!/bin/bash
[ $(echo -e "No\nYes" | dmenu -i -p "Shutdown ?") == "Yes" ] && shutdown now
