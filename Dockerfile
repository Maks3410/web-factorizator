FROM node:latest

COPY . /app

RUN cd /app && npm install # установка зависимостей
RUN cd /app && npm run build # сборка

CMD ["node", "/SERVER/server.js"]

EXPOSE 3000