@echo off

#!/bin/bash

# Lấy URL remote hiện tại (origin)
REMOTE_URL=$(git config --get remote.origin.url)

if [ -z "$REMOTE_URL" ]; then
  echo "❌ Không tìm thấy remote origin. Hãy clone từ GitHub rồi chạy lại script."
  exit 1
fi

echo "✅ Remote URL: $REMOTE_URL"

# Xóa thư mục .git cũ
rm -rf .git

# Tạo repo mới
git init
git add .
git commit -m "Reset clean repo"

# Gắn lại remote cũ
git remote add origin "$REMOTE_URL"

# Đặt branch main
git branch -M main

# Push đè lên GitHub
git push --force origin main

echo "🎉 Repo đã được reset sạch và push lại thành công!"
