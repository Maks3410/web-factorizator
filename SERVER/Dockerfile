FROM node:latest
WORKDIR /app
COPY /package*.json ./

RUN npm install
RUN apt install g++

COPY . .
RUN g++ -o poly.exe factorization.cpp

RUN chmod +x ./poly.exe

EXPOSE 3000
CMD [ "node", "server.js" ]

