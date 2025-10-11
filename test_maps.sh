#!/bin/bash

# Script to test all .cub map files in the maps directory
# Usage: ./test_maps.sh [all | valid | invalid]
#   all     - Test all maps (default)
#   valid   - Test only valid maps
#   invalid - Test only invalid maps

# Configuration
BIN="./cub3D"
OUTPUT_FILE="map_test_results.txt"

# Colors for terminal output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Parse command line argument
MODE="${1:-all}"

case "$MODE" in
    all)
        MAPDIR="maps"
        TEST_TYPE="All Maps"
        ;;
    valid)
        MAPDIR="maps/valid_maps"
        TEST_TYPE="Valid Maps"
        ;;
    invalid)
        MAPDIR="maps/invalid_maps"
        TEST_TYPE="Invalid Maps"
        ;;
    *)
        echo -e "${RED}Error: Invalid argument '$MODE'${NC}"
        echo "Usage: $0 [all | valid | invalid]"
        echo "  all     - Test all maps (default)"
        echo "  valid   - Test only valid maps"
        echo "  invalid - Test only invalid maps"
        exit 1
        ;;
esac

# Clear or create output file
> "$OUTPUT_FILE"

# Check if binary exists
if [ ! -f "$BIN" ]; then
    echo -e "${RED}Error: $BIN not found. Please compile the project first.${NC}"
    exit 1
fi

# Check if maps directory exists
if [ ! -d "$MAPDIR" ]; then
    echo -e "${RED}Error: $MAPDIR directory not found.${NC}"
    exit 1
fi

# Find all .cub files recursively
MAPS=($(find "$MAPDIR" -type f -name "*.cub" | sort))

if [ ${#MAPS[@]} -eq 0 ]; then
    echo -e "${RED}No .cub files found in $MAPDIR${NC}"
    exit 1
fi

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Testing Mode: $TEST_TYPE${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}Found ${#MAPS[@]} map files to test${NC}"
echo "Results will be saved to: $OUTPUT_FILE"
echo ""
echo "======================================" | tee -a "$OUTPUT_FILE"
echo "Map Testing Started: $(date)" | tee -a "$OUTPUT_FILE"
echo "Test Mode: $TEST_TYPE" | tee -a "$OUTPUT_FILE"
echo "Directory: $MAPDIR" | tee -a "$OUTPUT_FILE"
echo "======================================" | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Counters
TOTAL=0
SUCCESS=0
FAILED=0

# Test each map
for map in "${MAPS[@]}"; do
    TOTAL=$((TOTAL + 1))

    echo -e "${YELLOW}Testing [$TOTAL/${#MAPS[@]}]: $map${NC}"

    # Separator in output file
    echo "======================================" >> "$OUTPUT_FILE"
    echo "Map: $map" >> "$OUTPUT_FILE"
    echo "Time: $(date)" >> "$OUTPUT_FILE"
    echo "--------------------------------------" >> "$OUTPUT_FILE"

    # Run the program and capture output (both stdout and stderr)
    # No timeout - wait for program to finish naturally
    "$BIN" "$map" > /tmp/cub3d_output.txt 2>&1
    EXIT_CODE=$?

    # Read the output
    OUTPUT=$(cat /tmp/cub3d_output.txt)

    # Check exit code and output
    if [ $EXIT_CODE -eq 0 ]; then
        echo -e "${GREEN}  ✓ SUCCESS${NC}"
        echo "Status: SUCCESS (exit code: 0)" >> "$OUTPUT_FILE"
        SUCCESS=$((SUCCESS + 1))
    else
        echo -e "${RED}  ✗ FAILED (exit code: $EXIT_CODE)${NC}"
        echo "Status: FAILED (exit code: $EXIT_CODE)" >> "$OUTPUT_FILE"
        FAILED=$((FAILED + 1))
    fi

    # Save output to file if there's any
    if [ -n "$OUTPUT" ]; then
        echo "" >> "$OUTPUT_FILE"
        echo "Program Output:" >> "$OUTPUT_FILE"
        echo "$OUTPUT" >> "$OUTPUT_FILE"
    else
        echo "No output captured" >> "$OUTPUT_FILE"
    fi

    echo "" >> "$OUTPUT_FILE"
    echo "" # Blank line for readability

    # Small delay between tests
    sleep 0.1
done

# Summary
echo "======================================" | tee -a "$OUTPUT_FILE"
echo "Testing Completed: $(date)" | tee -a "$OUTPUT_FILE"
echo "======================================" | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"
echo "Summary ($TEST_TYPE):" | tee -a "$OUTPUT_FILE"
echo "  Total maps tested: $TOTAL" | tee -a "$OUTPUT_FILE"
echo -e "  ${GREEN}Successful: $SUCCESS${NC}" | tee -a "$OUTPUT_FILE"
echo -e "  ${RED}Failed: $FAILED${NC}" | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Cleanup
rm -f /tmp/cub3d_output.txt

echo -e "${GREEN}Full results saved to: $OUTPUT_FILE${NC}"