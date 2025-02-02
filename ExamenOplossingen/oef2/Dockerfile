FROM pxlsystemsadvanced/pxl-c-sdk:v1 AS base

WORKDIR /app

COPY . .

RUN gcc -static my_app.c -o my_app

FROM alpine:3.20

WORKDIR /app

COPY --from=base /app/my_app /app/

CMD [ "/app/my_app" ]