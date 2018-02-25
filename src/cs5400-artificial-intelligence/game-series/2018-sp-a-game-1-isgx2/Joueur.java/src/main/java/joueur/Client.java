package joueur;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.Stack;
import org.json.*;

public class Client {
    // region Singleton pattern setup
    private static Client instance = null;

    protected Client() {
        // Exists only to defeat instantiation.
    }

    public static Client getInstance() {
        if (instance == null) {
            instance = new Client();
        }

        return instance;
    }

    // endregion

    private String hostname = null;
    private int port = 0;
    private boolean printIO = false;
    private boolean started = false;
    private static final String EOT_CHAR = "" + (char) 4;
    private static final int BUFFER_SIZE = 1024;
    private BaseAI ai = null;
    private BaseGameObject aisPlayer = null;
    public GameManager gameManager;
    private Socket socket;
    private PrintWriter socketOut;
    private BufferedReader socketIn;
    private Stack<ServerEvent> eventsStack;
    private String receivedBuffer = "";

    public void connect(String hostname, int port, boolean printIO) {
        if (hostname.isEmpty()) {
            hostname = "localhost";
        }

        if (port <= 0) {
            port = 3000;
        }

        this.hostname = hostname;
        this.port = port;
        this.printIO = printIO;
        this.eventsStack = new Stack<ServerEvent>();

        System.out.println(
                ANSIColorCoder.FG_CYAN.apply() + "Connecting to: " + hostname + ":" + port + ANSIColorCoder.reset());

        this.socket = null;
        this.socketIn = null;
        this.socketOut = null;

        try {
            this.socket = new Socket(this.hostname, this.port);
            this.socketOut = new PrintWriter(this.socket.getOutputStream(), true);
            this.socketIn = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
            this.socket.setTcpNoDelay(true);
        } catch (IOException e) {
            this.handleError(e, ErrorCode.COULD_NOT_CONNECT,
                    "Couldn't create the socket for the connection to: " + hostname + ":" + port);
        }
    }

    public void setup(BaseGame game, BaseAI ai) {
        this.ai = ai;
        this.gameManager = new GameManager(game);
    }

    public void start() {
        this.started = true;
    }

    public String lowercaseFirst(String str) {
        return str.substring(0, 1).toLowerCase() + str.substring(1);
    }

    public void send(String eventName, Object data) {
        JSONObject send = new JSONObject(data);
        send.put("event", eventName);
        if (data != null) {
            send.put("data", data);
        }

        send.put("sentTime", System.currentTimeMillis());

        String str = send.toString() + Client.EOT_CHAR;

        if (this.printIO) {
            System.out.println(ANSIColorCoder.FG_MAGENTA.apply() + "TO SERVER <-- " + str + ANSIColorCoder.reset());
        }

        this.socketOut.println(str);
        //this.socketOut.flush();
    }

    public void disconnect() {
        this.handleError(null, ErrorCode.NONE, null);
    }

    public void handleError(Exception e, ErrorCode errorCode, String errorMessage) {
        try {
            this.socketOut.close();
            this.socketIn.close();
            this.socket.close();
        } catch (Exception err) {
            // whatever, we are disconnecting anyways
        }

        ErrorCode.handleError(e, errorCode, errorMessage);
    }

    public void play() {
        System.out.println(ANSIColorCoder.FG_GREEN.apply() + "Game is starting." + ANSIColorCoder.reset());
        this.waitForEvent(null);
    }

    public Object waitForEvent(String eventName) {
        while (true) {
            this.waitForEvents();

            while (!this.eventsStack.isEmpty()) {
                ServerEvent serverEvent = this.eventsStack.pop();
                if (eventName != null && serverEvent.event.equals(eventName)) {
                    return serverEvent.data;
                } else {
                    this.autoHandle(serverEvent.event, serverEvent.data);
                }
            }
        }
    }

    private void waitForEvents() {
        if (!this.eventsStack.isEmpty()) {
            return; // as we already have events to handle, no need to wait for more
        }

        while (true) {
            char[] chars = null;
            int charsRead = -2;
            try {
                chars = new char[Client.BUFFER_SIZE];
                charsRead = this.socketIn.read(chars);
            } catch (SocketTimeoutException e) {
                if (this.started) { // then the server is probably frozen :(
                    this.handleError(e, ErrorCode.SERVER_TIMEOUT, "Timed out from server, it probably froze.");
                } else {
                    continue; // because we should be lobbied and will wait for it to start
                }
            } catch (IOException e) {
                this.handleError(e, ErrorCode.CANNOT_READ_SOCKET, "Error with reading socket: " + e.getMessage());
            }

            String responseData = null;
            if (charsRead != -2) {
                if (charsRead == -1) { // then there was still more to read, so it filled the whole buffer
                    charsRead = Client.BUFFER_SIZE;
                }

                if (chars != null) {
                    responseData = new String(chars, 0, charsRead);
                }
            }
            if (responseData == null || responseData.isEmpty()) {
                continue;
            }

            if (this.printIO) {
                System.out.println(
                        ANSIColorCoder.FG_MAGENTA.apply() + "FROM SERVER -->" + responseData + ANSIColorCoder.reset());
            }

            String total = this.receivedBuffer + responseData;
            String[] split = total.split("[" + Client.EOT_CHAR + "]", -1);

            this.receivedBuffer = split[split.length - 1]; // this is either an empty string because of the EOT_CHAR split, or an incomplete json string so store it in the buffer

            for (int i = split.length - 2; i >= 0; i--) { // iterate through in reverse, skipping the over the very last item because we stored it in the receivedBuffer
                String str = split[i];
                JSONObject deserialized = new JSONObject(str);
                ServerEvent serverEvent = new ServerEvent(deserialized.getString("event"), deserialized.opt("data"));
                this.eventsStack.push(serverEvent);
            }

            if (!this.eventsStack.isEmpty()) {
                return;
            }
        }
    }

    private void autoHandle(String eventName, Object data) {
        try {
            Method method = this.getClass().getDeclaredMethod(
                    "autoHandle" + eventName.substring(0, 1).toUpperCase() + eventName.substring(1), Object.class);
            method.setAccessible(true);
            method.invoke(this, data);
        } catch (IllegalAccessException | IllegalArgumentException | InvocationTargetException | NoSuchMethodException
                | SecurityException e) {
            this.handleError(e, ErrorCode.REFLECTION_FAILED, "could not auto handle event '" + eventName + "'");
        }
    }

    @SuppressWarnings("unused") // because it can be invoked via reflection
    private void autoHandleDelta(Object data) {
        this.gameManager.deltaUpdate((JSONObject) data);

        if (this.aisPlayer == null) {
            try {
                this.aisPlayer = (BaseGameObject) this.ai.getClass().getField("player").get(this.ai);
            } catch (IllegalArgumentException | IllegalAccessException | NoSuchFieldException | SecurityException e) {
                this.handleError(e, ErrorCode.REFLECTION_FAILED, "Could not get the AI's Player");
            }
        }

        if (this.aisPlayer != null) {
            try {
                this.ai.gameUpdated();
            } catch (Exception e) {
                this.handleError(e, ErrorCode.AI_ERRORED, "AI.gameUpdated() errored");
            }
        }
    }

    @SuppressWarnings("unused") // because it can be invoked via reflection
    private void autoHandleInvalid(Object data) throws Exception {
        JSONObject jsonObject = (JSONObject) data;
        try {
            this.ai.invalid(jsonObject.getString("message"));
        } catch (Exception e) {
            this.handleError(e, ErrorCode.AI_ERRORED, "AI.invalid() errored");
        }
    }

    @SuppressWarnings("unused") // because it can be invoked via reflection
    private void autoHandleFatal(Object data) throws Exception {
        JSONObject jsonObject = (JSONObject) data;
        this.handleError(null, ErrorCode.FATAL_EVENT, "Got fatal error: " + jsonObject.getString("message"));
    }

    @SuppressWarnings("unused") // because it can be invoked via reflection
    private void autoHandleOver(Object data) {
        JSONObject overData = (JSONObject) data;
        boolean won = false;
        String reason = "";

        if (this.aisPlayer != null) {
            try {
                won = this.aisPlayer.getClass().getField("won").getBoolean(this.aisPlayer);
                reason = (String) this.aisPlayer.getClass().getField(won ? "reasonWon" : "reasonLost")
                        .get(this.aisPlayer);
            } catch (IllegalArgumentException | IllegalAccessException | NoSuchFieldException | SecurityException e) {
                this.handleError(e, ErrorCode.REFLECTION_FAILED, "Cannot get if play won or lost when game is over");
            }
        }

        try {
            try {
                this.ai.ended(won, reason);
            } catch (Exception e) {
                this.handleError(e, ErrorCode.AI_ERRORED, "AI threw exception during AI.ended()");
            }
        } catch (Exception e) {
            this.handleError(e, ErrorCode.AI_ERRORED, "AI errored in AI.ended(won, reason)");
        }

        System.out.println(ANSIColorCoder.FG_GREEN.apply() + "Game is over. " + (won ? "I Won!" : "I Lost :(")
                + " because " + reason + ANSIColorCoder.reset());

        String message = overData.optString("message");
        if (message != null && !message.equals("")) {
            message = message.replace("__HOSTNAME__", this.hostname);
            System.out.println(ANSIColorCoder.FG_CYAN.apply() + message + ANSIColorCoder.reset());
        }

        this.disconnect();
    }

    @SuppressWarnings("unused") // because it can be invoked via reflection
    private void autoHandleOrder(Object data) {
        JSONObject orderData = (JSONObject) data;

        String order = null;
        int index = -1;
        try {
            order = orderData.getString("name");
            index = orderData.getInt("index");
        } catch (Exception e) {
            this.handleError(e, ErrorCode.REFLECTION_FAILED, "Order data malformed, missing name or index: ");
        }

        Object returned = ai.doOrder(order, orderData.optJSONArray("args"));

        JSONObject finishedData = new JSONObject();
        finishedData.put("orderIndex", index);
        finishedData.put("returned", returned);
        this.send("finished", finishedData);
    }

    public Object runOnServer(BaseGameObject caller, String functionName, JSONObject args) {
        JSONObject runData = new JSONObject();
        runData.put("caller", this.gameManager.serializeGameObject(caller));
        runData.put("functionName", functionName);
        if (args != null) {
            runData.put("args", args);
        }

        this.send("run", runData);

        Object ranData = this.waitForEvent("ran");

        if (ranData != null) {
            ranData = this.gameManager.unserialize(ranData);
        }

        return ranData;
    }
}
