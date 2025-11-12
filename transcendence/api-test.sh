#!/bin/bash

# API Test Script
# Usage: ./api-test.sh <method> <service> <endpoint> [-h] [-b]
# Example: ./api-test.sh GET auth /health
#          ./api-test.sh POST auth /login -h -b

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

# Check arguments
if [ $# -lt 3 ]; then
    echo -e "${YELLOW}Usage: $0 <method> <service> <endpoint> [-h] [-b]${NC}"
    echo ""
    echo -e "${CYAN}Methods:${NC}"
    echo "  GET, POST, PUT, PATCH, DELETE"
    echo ""
    echo -e "${CYAN}Services:${NC}"
    echo "  auth     - Auth service"
    echo "  user     - User service"
    echo "  game     - Game service"
    echo "  gateway  - API Gateway"
    echo ""
    echo -e "${CYAN}Options:${NC}"
    echo "  -h       - Add custom headers (prompts for key-value pairs)"
    echo "  -b       - Add JSON body (prompts for key-value pairs)"
    echo ""
    echo -e "${CYAN}Examples:${NC}"
    echo "  $0 GET auth /health"
    echo "  $0 POST auth /login -h -b"
    echo "  $0 DELETE user /users/123 -h"
    exit 1
fi

METHOD=$1
SERVICE=$2
ENDPOINT=$3
shift 3

# Validate HTTP method
case "$METHOD" in
    GET|POST|PUT|PATCH|DELETE)
        ;;
    *)
        echo -e "${RED}Error: Invalid HTTP method '$METHOD'${NC}"
        echo -e "${YELLOW}Valid methods: GET, POST, PUT, PATCH, DELETE${NC}"
        exit 1
        ;;
esac

# Initialize arrays for headers and body
declare -a CUSTOM_HEADERS
ADD_HEADERS=false
ADD_BODY=false

# Parse options
while [ $# -gt 0 ]; do
    case "$1" in
        -h)
            ADD_HEADERS=true
            shift
            ;;
        -b)
            ADD_BODY=true
            shift
            ;;
        *)
            echo -e "${RED}Error: Unknown option '$1'${NC}"
            exit 1
            ;;
    esac
done

# Prompt for headers if -h flag is present
if [ "$ADD_HEADERS" = true ]; then
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}Enter headers (press Enter with empty key to finish):${NC}"
    while true; do
        echo -ne "${BLUE}Header key:${NC} "
        read -r key
        if [ -z "$key" ]; then
            break
        fi
        echo -ne "${BLUE}Header value:${NC} "
        read -r value
        CUSTOM_HEADERS+=("-H" "$key: $value")
    done
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
fi

# Prompt for body if -b flag is present
BODY_JSON=""
if [ "$ADD_BODY" = true ]; then
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${YELLOW}Enter JSON body key-value pairs (press Enter with empty key to finish):${NC}"
    JSON_PAIRS=()
    while true; do
        echo -ne "${BLUE}Key:${NC} "
        read -r key
        if [ -z "$key" ]; then
            break
        fi
        echo -ne "${BLUE}Value:${NC} "
        read -r value
        # Escape quotes in value
        value=$(echo "$value" | sed 's/"/\\"/g')
        JSON_PAIRS+=("\"$key\":\"$value\"")
    done
    
    if [ ${#JSON_PAIRS[@]} -gt 0 ]; then
        BODY_JSON=$(IFS=,; echo "{${JSON_PAIRS[*]}}")
        # Add Content-Type header if not already present
        HAS_CONTENT_TYPE=false
        for header in "${CUSTOM_HEADERS[@]}"; do
            if [[ "$header" =~ ^Content-Type: ]]; then
                HAS_CONTENT_TYPE=true
                break
            fi
        done
        if [ "$HAS_CONTENT_TYPE" = false ]; then
            CUSTOM_HEADERS+=("-H" "Content-Type: application/json")
        fi
    fi
    echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
fi

# Determine host and port based on service
case "$SERVICE" in
    auth)
        HOST=$AUTH_HOST
        PORT=$AUTH_PORT
        ;;
    user)
        HOST=$USER_HOST
        PORT=$USER_PORT
        ;;
    game)
        HOST=$GAME_HOST
        PORT=$GAME_PORT
        ;;
    gateway)
        HOST=$GATEWAY_HOST
        PORT=$GATEWAY_PORT
        ;;
    *)
        echo -e "${RED}Error: Invalid service '$SERVICE'${NC}"
        echo -e "${YELLOW}Valid services: auth, user, game, gateway${NC}"
        exit 1
        ;;
esac

# Build URL
URL="http://${HOST}:${PORT}${ENDPOINT}"

# Print request info
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo -e "${BLUE}Method:${NC}  $METHOD"
echo -e "${BLUE}Service:${NC} $SERVICE"
echo -e "${BLUE}URL:${NC}     $URL"
if [ ${#CUSTOM_HEADERS[@]} -gt 0 ]; then
    echo -e "${BLUE}Headers:${NC}"
    for ((i=0; i<${#CUSTOM_HEADERS[@]}; i+=2)); do
        echo "  ${CUSTOM_HEADERS[i+1]}"
    done
fi
if [ -n "$BODY_JSON" ]; then
    echo -e "${BLUE}Body:${NC}    $BODY_JSON"
fi
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
echo ""

# Build curl command
CURL_CMD=(curl -s -w "\n%{http_code}" -X "$METHOD")

# Add custom headers
if [ ${#CUSTOM_HEADERS[@]} -gt 0 ]; then
    CURL_CMD+=("${CUSTOM_HEADERS[@]}")
fi

# Add body if present
if [ -n "$BODY_JSON" ]; then
    CURL_CMD+=(-d "$BODY_JSON")
fi

# Add URL
CURL_CMD+=("$URL")

# Execute request
RESPONSE=$("${CURL_CMD[@]}")

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
    echo ""
    echo -e "${YELLOW}Tip: Install 'jq' for pretty JSON output${NC}"
fi

echo ""
echo -e "${CYAN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
