#!/bin/bash

# Check if email parameter is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <email-to-replace> [replacement-email]"
    echo "Example: $0 illya@starikov.co"
    echo "Example: $0 illya@starikov.co newuser@company.com"
    echo ""
    echo "If replacement-email is not provided, defaults to: REDACTED@example.com"
    exit 1
fi

EMAIL_TO_REPLACE="$1"
REPLACEMENT_EMAIL="${2:-REDACTED@example.com}"  # Use 2nd param or default

echo "Replacing email: $EMAIL_TO_REPLACE -> $REPLACEMENT_EMAIL"
echo "Warning: This will rewrite git history. Make sure you have a backup!"
read -p "Continue? (y/N): " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo "Aborted."
    exit 1
fi

# Step 1: Replace email in author and committer fields
echo "Step 1: Replacing email in author and committer fields..."
git filter-repo --force --email-callback "
  return email.replace(b\"$EMAIL_TO_REPLACE\", b\"$REPLACEMENT_EMAIL\")
"

# Step 2: Replace email everywhere (metadata, messages, and file contents)
echo "Step 2: Replacing email in all content..."
git filter-repo --force --replace-text <(echo "$EMAIL_TO_REPLACE==>$REPLACEMENT_EMAIL")

echo "Email replacement complete!"
echo "Replaced: $EMAIL_TO_REPLACE -> $REPLACEMENT_EMAIL"
echo ""
echo "Don't forget to force push if you need to update a remote repository:"
echo "git push --force-with-lease origin --all"

