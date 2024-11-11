FROM mcr.microsoft.com/dotnet/sdk:7.0 AS build_stage

WORKDIR /app

COPY ./ContosoPizza/ .

RUN dotnet publish -c Release -o ./publish

EXPOSE 5000


FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS prod_stage

COPY --from=Build_stage /app/publish /app

ENTRYPOINT [ "dotnet", "ContosoPizzaSite.dll" ]