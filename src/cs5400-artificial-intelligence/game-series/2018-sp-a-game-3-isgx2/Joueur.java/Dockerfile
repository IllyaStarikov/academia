FROM siggame/joueur:java-onbuild as build

FROM java:jre-alpine

WORKDIR /client
COPY --from=build /usr/src/client/target/java-client-jar-with-dependencies.jar \
                  /client/java-client.jar

ENTRYPOINT ["java", "-jar", "java-client.jar", Chess]
