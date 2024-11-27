FROM eclipse-temurin:17-jdk-jammy AS build_env

WORKDIR /app

COPY . /app

RUN ./mvnw dependency:resolve
RUN ./mvnw spring-boot:run -Dspring-boot.run.profiles=mysql

FROM eclipse-temurin:17-jre-jammy

WORKDIR /app

COPY --from=build_env /app/target/*.jar .

RUN ./mvnw package

CMD [ "java", "-Djava.security.egd=file:/dev/./urandom", "-jar /spring-petclinic.jar" ]
