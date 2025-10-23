#!/bin/bash

BIN="./cub3D"
MAPDIR="maps"
VALDIR="maps/valid_maps"
INVALDIR="maps/invalid_maps"
OUTPUT="valgrind_mandatory.log"
DELAY=0.3

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

# Check if binary exists
if [ ! -f "$BIN" ]; then
    echo "Error: $BIN not found. Run 'make' first."
    exit 1
fi

# Clear output file
> "$OUTPUT"

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
    echo "No .cub files found in $MAPDIR"
    exit 1
fi

echo -e "${BLUE}========================================${NC}"
echo -e "${HEADER}"
echo -e "${BLUE}Output: $OUTPUT${NC}"
echo -e "${BLUE}========================================${NC}"

{
    echo "========================================"
    echo "Valgrind Mandatory Testing"
    echo "Started: $(date)"
    echo "========================================"
    echo ""
} | tee -a "$OUTPUT"

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

    {
        echo "========================================"
        echo "Map [$COUNT/${#MAPS[@]}]: $map"
        echo "Time: $(date)"
        echo "----------------------------------------"
        echo ""
    } >> "$OUTPUT"

    valgrind --leak-check=full --track-origins=yes \
             --log-file="${OUTPUT}.tmp" \
             "$BIN" "$map" 2>&1

    # Append valgrind output
    cat "${OUTPUT}.tmp" >> "$OUTPUT"
    echo "" >> "$OUTPUT"
    echo "" >> "$OUTPUT"

    rm -f "${OUTPUT}.tmp"
	sleep $DELAY
done

{
    echo "========================================"
    echo "Completed: $(date)"
    echo "========================================"
} >> "$OUTPUT"

echo -e "${YELLOW}Results saved to: $OUTPUT${NC}"