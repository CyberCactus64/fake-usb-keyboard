#!/bin/bash

# upload this script to a fresh debian based server and run it as root

# 1. update + NGINX
sudo apt update && sudo apt install -y nginx curl ufw

# 2. payload expected at /var/www/html/utility.exe

# 3. config NGINX (only for utility.exe)
cat > /etc/nginx/sites-available/utility << 'EOF'
server {
    listen 80;
    root /var/www/html;
    server_name _;
    
    location = /utility.exe {
        add_header Content-Type application/octet-stream;
        types { } default_type application/octet-stream;
    }
    
    location / {
        deny all;
    }
}
EOF

# 4. activate config + restart NGINX
sudo ln -sf /etc/nginx/sites-available/utility /etc/nginx/sites-enabled/
sudo rm -f /etc/nginx/sites-enabled/default
sudo nginx -t && sudo systemctl restart nginx

# 5. firewall (solo 80 + 22)
sudo ufw reset
sudo ufw allow 22/tcp
sudo ufw allow 80/tcp
sudo ufw --force enable

# 6. check
IP=$(curl -s ifconfig.me)
echo "Your payload URL is: http://$IP/utility.exe"