#!/bin/bash

echo "Is it morning? Please answer yes or no."
read YES_OR_NO

case "$YES_OR_NO" in
		yes|y|Yes|YES)
			echo "Good morning!";;
		[nN]*)
			echo "Good Afternoon!";;
		*)
			echo "Sorry,not recognized."
esac
