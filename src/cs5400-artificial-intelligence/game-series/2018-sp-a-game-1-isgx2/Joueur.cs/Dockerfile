FROM siggame/joueur:cs-onbuild as build

FROM microsoft/dotnet:runtime-deps

WORKDIR /client
COPY --from=build /usr/src/client/build /client

ENTRYPOINT ["./cs-client", GAME_NAME]
