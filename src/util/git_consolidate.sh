#!/bin/bash

set -e

# Check for uncommitted changes
if ! git diff-index --quiet HEAD --; then
    echo "Error: You have uncommitted changes. Please commit or stash them first."
    echo "Run: git add . && git commit -m 'Save changes' or git stash"
    exit 1
fi

# Find all git repositories and get their first commit dates
echo "Finding git repositories..."
repos=()
while IFS= read -r -d '' git_dir; do
    repo_path="${git_dir%/.git}"
    if [ -f "$git_dir/config" ]; then
        cd "$repo_path"
        first_commit_date=$(git log --reverse --pretty=format:"%ct" | head -n 1)
        cd - > /dev/null
        repos+=("$first_commit_date:$repo_path")
    fi
done < <(find src -type d -name ".git" -print0 2>/dev/null)

if [ ${#repos[@]} -eq 0 ]; then
    echo "No git repositories found in src/"
    exit 1
fi

echo "Found ${#repos[@]} repositories"

# Sort by first commit date
IFS=$'\n' sorted_repos=($(sort -n <<<"${repos[*]}"))
unset IFS

# Create temporary backup directory
temp_backup="/tmp/academia_backup_$(date +%s)"
mkdir -p "$temp_backup"

# Process each repository in chronological order
for repo_entry in "${sorted_repos[@]}"; do
    repo_path="${repo_entry#*:}"
    # Use the relative path from src/ to preserve directory structure
    target_dir="${repo_path#src/}"
    
    echo "Processing $repo_path..."
    
    # Move existing non-git content to backup if it exists
    if [ -d "$repo_path" ] && [ -n "$(find "$repo_path" -type f ! -path "*/.git/*" 2>/dev/null)" ]; then
        echo "📦 Backing up existing content from $target_dir"
        mkdir -p "$temp_backup/$target_dir"
        # Move only non-git files to backup
        find "$repo_path" -mindepth 1 -maxdepth 1 ! -name ".git" -exec mv {} "$temp_backup/$target_dir/" \;
    fi
    
    # Generate patch
    cd "$repo_path"
    git log \
        --pretty=email \
        --patch-with-stat \
        --reverse \
        --full-index \
        --binary \
        -m \
        --first-parent \
        > /tmp/patch
    cd - > /dev/null
    
    # Apply patch to the existing directory structure (preserve src/ prefix)
    if git am --committer-date-is-author-date --directory "$repo_path" < /tmp/patch; then
        echo "✓ Applied $target_dir"
    else
        echo "⚠️  Conflict in $target_dir, trying with 3-way merge..."
        git am --abort 2>/dev/null || true
        
        # Try again with 3-way merge and ignore whitespace
        if git am --committer-date-is-author-date --directory "$repo_path" --3way --ignore-whitespace < /tmp/patch; then
            echo "✓ Applied $target_dir with 3-way merge"
        else
            echo "⚠️  Failed to apply $target_dir, skipping remaining patches"
            git am --abort 2>/dev/null || true
        fi
    fi
done

rm -f /tmp/patch
echo "Done! All repositories consolidated."
echo "📦 Backup of original files stored at: $temp_backup"

# Show consolidation summary
echo
echo "📊 Consolidation Summary:"
echo "  Total repositories processed: ${#sorted_repos[@]}"
total_commits=$(git rev-list --count HEAD)
echo "  Total commits in consolidated repo: $total_commits"
echo
echo "💡 Tip: Run 'git log --oneline | wc -l' to see commit count"
echo "💡 Tip: Run 'git-fame .' to see author statistics"