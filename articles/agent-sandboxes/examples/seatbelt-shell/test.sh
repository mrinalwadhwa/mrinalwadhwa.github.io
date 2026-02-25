#!/bin/bash
# test.sh - Test the Seatbelt sandbox

set -e

WORKSPACE="/tmp/workspace"
PROFILE="$(dirname "$0")/sandbox-profile.sb"

echo "=== Seatbelt Sandbox Test ==="
echo ""

# Setup
rm -rf "$WORKSPACE"
mkdir -p "$WORKSPACE"

echo "1. Testing write to workspace (should succeed)..."
sandbox-exec -f "$PROFILE" /bin/bash -c "echo hello > $WORKSPACE/test.txt && echo  PASS: wrote to workspace"

echo ""
echo "2. Testing read from workspace (should succeed)..."
sandbox-exec -f "$PROFILE" /bin/bash -c "cat $WORKSPACE/test.txt && echo  PASS: read from workspace"

echo ""
echo "3. Testing write outside workspace (should fail)..."
if sandbox-exec -f "$PROFILE" /bin/bash -c "echo hello > /tmp/outside.txt" 2>/dev/null; then
    echo "   FAIL: write outside workspace succeeded (should have failed)"
    exit 1
else
    echo "   PASS: write outside workspace blocked"
fi

echo ""
echo "4. Testing read from system files (should succeed)..."
sandbox-exec -f "$PROFILE" /bin/bash -c "head -1 /etc/passwd > /dev/null && echo  PASS: read /etc/passwd"

echo ""
echo "5. Testing network access (should fail)..."
if sandbox-exec -f "$PROFILE" /bin/bash -c "curl -s --connect-timeout 2 https://example.com > /dev/null" 2>/dev/null; then
    echo "   FAIL: network access succeeded (should have failed)"
else
    echo "   PASS: network access blocked"
fi

echo ""
echo "=== All tests passed ==="
