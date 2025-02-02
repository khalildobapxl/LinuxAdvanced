FROM pxlsystemsadvanced/pxl-c-sdk:v1

WORKDIR /app

COPY . .

RUN gcc -static my_app.c -o my_app

CMD [ "/app/my_app" ]