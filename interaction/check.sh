#!/bin/sh -e

RESULT=$(echo "1adam" | nc -q 1 "$1" "$2")
echo "$RESULT" | grep "Secure Coding is hard!"
echo "$RESULT" | grep "Choose something."
echo "$RESULT" | grep "1, 2, 3, 4, or 5"
echo "$RESULT" | grep "Need a name"
echo "$RESULT" | grep "I DID IT"

RESULT=$(echo "1aaaaaaaaaaaaaaaaaaaaaaa2message" | nc -q 1 "$1" "$2")
echo "$RESULT" | grep "Need a message"
echo "$RESULT" | grep "says"
