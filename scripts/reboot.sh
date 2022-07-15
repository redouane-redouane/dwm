#!/bin/bash
[ $(echo -e "No\nYes" | dmenu -i -p "Reboot ?") == "Yes" ] && reboot
