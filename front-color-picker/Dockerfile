FROM node:latest

WORKDIR /container/app

COPY bin bin
COPY public public
COPY routes routes
COPY app.js app.js
COPY package.json package.json

RUN npm install

ENTRYPOINT ["npm", "start"]
