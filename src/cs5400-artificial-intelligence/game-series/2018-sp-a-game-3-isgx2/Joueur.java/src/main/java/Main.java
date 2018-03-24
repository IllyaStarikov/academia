
// Please do not modify this file.
// Instead have a look at `README.md` for how to start writing you AI.

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import org.json.JSONObject;

import joueur.BaseAI;
import joueur.BaseGame;
import joueur.Client;
import joueur.ErrorCode;
import joueur.ANSIColorCoder;
import net.sourceforge.argparse4j.ArgumentParsers;
import net.sourceforge.argparse4j.impl.Arguments;
import net.sourceforge.argparse4j.inf.ArgumentParser;
import net.sourceforge.argparse4j.inf.ArgumentParserException;
import net.sourceforge.argparse4j.inf.Namespace;

class JoueurJava {
    public static void main(String[] args) throws IOException {
        ArgumentParser parser = ArgumentParsers.newArgumentParser("Joueur.Java")
                .description("Runs the Java client with options. Must a provide a game name to play on the server.");
        parser.addArgument("game").dest("game").required(true)
                .help("the name of the game you want to play on the server");
        parser.addArgument("-s", "--server").dest("server").setDefault("localhost")
                .help("the hostname or the server you want to connect to e.g. locahost:3000");
        parser.addArgument("-p", "--port").dest("port").type(Integer.class).setDefault(3000)
                .help("the port to connect to on the server. Can be defined on the server arg via server:port");
        parser.addArgument("-n", "--name").dest("playerName").help(
                "the name you want to use as your AI\'s player name. This over-rides the name you set in your code");
        parser.addArgument("-i", "--index").dest("index").type(Integer.class).setDefault(-1)
                .help("the player number you want to be, with 0 being the first player");
        parser.addArgument("-w", "--password").dest("password")
                .help("the password required for authentication on official servers");
        parser.addArgument("-r", "--session").dest("session").setDefault("*")
                .help("the requested game session you want to play on the server");
        parser.addArgument("--aiSettings").dest("aiSettings")
                .help("Any settings for the AI. Delimit pairs by an ampersand (key=value&otherKey=otherValue)");
        parser.addArgument("--gameSettings").dest("gameSettings").help(
                "Any settings for the game server to force. Must be url parms formatted (key=value&otherKey=otherValue)");
        parser.addArgument("--printIO").dest("printIO").action(Arguments.storeTrue())
                .help("(debugging) print IO through the TCP socket to the terminal");

        String gameAlias = "", server = "localhost", requestedSession = "*", playerName = "Java Player",
                password = null, aiSettings = null, gameSettings = null;
        int port = 3000, playerIndex = -1;
        boolean printIO = false;

        try {
            Namespace parsedArgs = parser.parseArgs(args);
            gameAlias = parsedArgs.getString("game");
            server = parsedArgs.getString("server");
            requestedSession = parsedArgs.getString("session");
            playerName = parsedArgs.getString("playerName");
            playerIndex = parsedArgs.getInt("index");
            password = parsedArgs.getString("password");
            port = parsedArgs.getInt("port");
            printIO = parsedArgs.getBoolean("printIO");
            aiSettings = parsedArgs.getString("aiSettings");
            gameSettings = parsedArgs.getString("gameSettings");
        } catch (ArgumentParserException e) {
            ErrorCode.handleError(e, ErrorCode.INVALID_ARGS, "Invalid Args");
        }

        if (server.contains(":")) {
            String[] split = server.split(":");
            server = split[0];
            port = Integer.parseInt(split[1]);
        }

        Client client = Client.getInstance();
        client.connect(server, port, printIO);
        client.send("alias", gameAlias);
        String gameName = (String) client.waitForEvent("named");

        BaseGame game = null;
        try {
            Class<?> gameClass = Class.forName("games." + client.lowercaseFirst(gameName) + ".Game");
            Constructor<?> gameConstructor = gameClass.getDeclaredConstructors()[0];
            gameConstructor.setAccessible(true);
            game = (BaseGame) gameConstructor.newInstance(new Object[0]);
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | SecurityException
                | IllegalArgumentException | InvocationTargetException e) {
            client.handleError(e, ErrorCode.GAME_NOT_FOUND,
                    "Could not create Game via reflection for game '" + gameName + "'");
        }

        BaseAI ai = null;
        try {
            Class<?> aiClass = Class.forName("games." + client.lowercaseFirst(gameName) + ".AI");
            Constructor<?> aiConstructor = aiClass.getDeclaredConstructors()[0];
            aiConstructor.setAccessible(true);
            ai = (BaseAI) aiConstructor.newInstance(new Object[0]);
        } catch (Exception e) {
            client.handleError(e, ErrorCode.AI_ERRORED,
                    "Could not create AI via reflection for game '" + gameName + "'");
        }

        client.setup(game, ai);

        ai.setSettings(aiSettings);

        if (playerName == null || playerName.isEmpty()) {
            playerName = ai.getName();
            if (playerName == null || playerName.isEmpty()) {
                playerName = "Java Player"; // to make sure they have a name
            }
        }

        JSONObject playData = new JSONObject();
        playData.put("gameName", gameName);
        playData.put("password", password);
        playData.put("playerName", playerName);
        if (playerIndex > -1) {
            playData.put("playerIndex", playerIndex);
        }
        playData.put("requestedSession", requestedSession);
        playData.put("gameSettings", gameSettings);
        playData.put("clientType", "Java");
        client.send("play", playData);

        JSONObject lobbiedData = (JSONObject) client.waitForEvent("lobbied");

        gameName = lobbiedData.getString("gameName");
        String gameSession = lobbiedData.getString("gameSession");

        System.out.println(ANSIColorCoder.FG_CYAN.apply() + "In lobby for game '" + gameName + "' in session '"
                + gameSession + "'." + ANSIColorCoder.reset());

        JSONObject constants = lobbiedData.getJSONObject("constants");

        client.gameManager.setConstants(constants);
        JSONObject startData = (JSONObject) client.waitForEvent("start");

        // set the AI's game and player via reflection
        try {
            ai.getClass().getField("game").set(ai, game);
            ai.getClass().getField("player").set(ai, game.gameObjects.get(startData.getString("playerID")));
        } catch (IllegalArgumentException | IllegalAccessException | NoSuchFieldException | SecurityException e) {
            client.handleError(e, ErrorCode.REFLECTION_FAILED, "Could not set reflected Game and Player for AI.");
        }

        client.start();

        try {
            ai.start();
            ai.gameUpdated();
        } catch (Exception e) {
            client.handleError(e, ErrorCode.REFLECTION_FAILED, "AI threw exception during initial start");
        }

        client.play();
    }
}
