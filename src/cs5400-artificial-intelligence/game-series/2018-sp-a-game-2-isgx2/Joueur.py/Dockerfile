FROM siggame/joueur:py-onbuild as build

FROM python:alpine

COPY --from=build /usr/src/client /client
WORKDIR /client

ENTRYPOINT ["python", "-u", "main.py", GAME_NAME]
