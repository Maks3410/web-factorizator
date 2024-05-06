FROM nginx:latest

WORKDIR /app
COPY nginx.conf /etc/nginx/nginx.conf
COPY index.html .
COPY ./js ./js

EXPOSE 8000

CMD ["nginx", "-g", "daemon off;"]
