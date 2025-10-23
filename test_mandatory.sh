#!/bin/bash

BIN="./cub3D"
MAPDIR="maps"
VALDIR="maps/valid_maps"
INVALDIR="maps/invalid_maps"
DELAY=0.3  # 300ms between tests (0.5s might be too high)

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

# Check if binary exists
if [ ! -f "$BIN" ]; then
	echo "Error: $BIN not found. Run 'make' first."
	exit 1
fi

# Select which maps to test based on argument
case "$1" in
    valid)
        MAPS=($(find "$VALDIR" | sort))
        HEADER="${GREEN}Testing ${#MAPS[@]} valid bonus maps${NC}"
        ;;
    invalid)
        MAPS=($(find "$INVALDIR" | sort))
        HEADER="${RED}Testing ${#MAPS[@]} invalid bonus maps${NC}"
        ;;
    all|"")
        MAPS=($(find "$MAPDIR" | sort))
        HEADER="${BLUE}Testing ${#MAPS[@]} all bonus maps${NC}"
        ;;
    *)
        echo "Usage: $0 [valid|invalid|all]"
        exit 1
        ;;
esac

if [ ${#MAPS[@]} -eq 0 ]; then
	echo "No files found for selection"
	exit 1
fi

echo -e "${BLUE}========================================${NC}"
echo -e "$HEADER"
echo -e "${BLUE}========================================${NC}"

COUNT=0
for map in "${MAPS[@]}"; do
    COUNT=$((COUNT + 1))
	if [[ "$map" == *"$VALDIR"* ]]; then
		COLOR=$GREEN
	elif [[ "$map" == *"$INVALDIR"* ]]; then
		COLOR=$RED
	else
		COLOR=$BLUE
	fi
	echo -e "${COLOR}[$COUNT/${#MAPS[@]}] Testing: $map${NC}"

	"$BIN" "$map"

	# Buffer time between tests
	sleep $DELAY
done

echo -e "${GREEN}All tests completed!${NC}"