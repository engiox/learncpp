#!/bin/bash
# bulk_update_ollama.sh - Update all installed models

# Get list of installed models
models=$(ollama list | tail -n +2 | awk '{print $1}')

echo "Starting bulk update for Ollama models..."

for model in $models; do
    echo "Updating $model..."
    
    # Pull latest version
    if ollama pull "$model"; then
        echo "✓ Successfully updated $model"
    else
        echo "✗ Failed to update $model"
    fi
    
    # Add delay to prevent rate limiting
    sleep 2
done

echo "Bulk update completed!"
