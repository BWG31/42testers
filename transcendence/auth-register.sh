#!/bin/bash

# Auth Registration Script
# Usage: ./auth-register.sh

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Load environment variables
if [ ! -f .env ]; then
    echo -e "${RED}Error: .env file not found${NC}"
    exit 1
fi

source .env

# Check if AUTH_HOST and AUTH_PORT are set
if [ -z "$AUTH_HOST" ] || [ -z "$AUTH_PORT" ]; then
    echo -e "${RED}Error: AUTH_HOST or AUTH_PORT not set in .env${NC}"
    exit 1
fi

# Prompt for user inputs
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${YELLOW}Register New User${NC}"
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo ""

echo -ne "${BLUE}Email:${NC} "
read -r email

echo -ne "${BLUE}Username:${NC} "
read -r username

echo -ne "${BLUE}Password:${NC} "
read -rs password
echo ""

echo ""
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"

# Build URL
URL="http://${GATEWAY_HOST}:${GATEWAY_PORT}/api/auth/register"

# Build JSON body
JSON_BODY=$(cat <<EOF
{
  "email": "$email",
  "username": "$username",
  "password": "$password"
}
EOF
)

# Print request info
echo -e "${BLUE}Method:${NC}  POST"
echo -e "${BLUE}URL:${NC}     $URL"
echo -e "${BLUE}Body:${NC}    $JSON_BODY"
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo ""

# Make request
RESPONSE=$(curl -s -w "\n%{http_code}" -X POST \
    -H "Content-Type: application/json" \
    -d "$JSON_BODY" \
	-c "cookies.txt"\
    "$URL")

# Extract status code and body
HTTP_CODE=$(echo "$RESPONSE" | tail -n1)
BODY=$(echo "$RESPONSE" | sed '$d')

# Color status code based on value
if [ "$HTTP_CODE" -ge 200 ] && [ "$HTTP_CODE" -lt 300 ]; then
    STATUS_COLOR=$GREEN
elif [ "$HTTP_CODE" -ge 300 ] && [ "$HTTP_CODE" -lt 400 ]; then
    STATUS_COLOR=$CYAN
elif [ "$HTTP_CODE" -ge 400 ] && [ "$HTTP_CODE" -lt 500 ]; then
    STATUS_COLOR=$YELLOW
else
    STATUS_COLOR=$RED
fi

# Print status
echo -e "${STATUS_COLOR}Status: $HTTP_CODE${NC}"
echo ""

# Pretty print JSON response if possible
if command -v jq &> /dev/null; then
    echo -e "${BLUE}Response:${NC}"
    echo "$BODY" | jq '.' 2>/dev/null || echo "$BODY"
else
    echo -e "${BLUE}Response:${NC}"
    echo "$BODY"
fi

echo ""
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
