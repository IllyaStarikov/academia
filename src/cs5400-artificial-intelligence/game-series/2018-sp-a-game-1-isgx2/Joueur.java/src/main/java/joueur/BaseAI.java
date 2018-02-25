package joueur;

import java.lang.reflect.Method;
import java.util.HashMap;

import org.json.JSONArray;

public abstract class BaseAI {
    private HashMap<String, String> _settings;

    protected BaseAI() {
        this._settings = new HashMap<String, String>();
    }

    public String getName() {
        return "Java Player";
    }

    public void start() {
        // the inheriting AI can add code to this inherited function
    }

    public void ended(boolean won, String reason) {
        // the inheriting AI can add code to this inherited function
    }

    public void invalid(String message) {
        // the inheriting AI can add code to this inherited function
        System.err.println(ANSIColorCoder.FG_YELLOW.apply() + "Invalid: " + message + ANSIColorCoder.reset());
    }

    public void gameUpdated() {
        // the inheriting AI can add code to this inherited function
    }

    public Object doOrder(String order, JSONArray jsonArray) {
        GameManager gameManager = Client.getInstance().gameManager;
        Object[] unserializedArgs = null;
        Method method = null;

        try {
            Method[] methods = this.getClass().getDeclaredMethods();
            for (int i = 0; i < methods.length; i++) {
                if (methods[i].getName().equals(order)) {
                    method = methods[i];
                    break;
                }
            }

            int len = jsonArray.length();
            unserializedArgs = new Object[len];
            for (int i = 0; i < len; i++) {
                unserializedArgs[i] = gameManager.unserialize(jsonArray.get(i));
            }
        } catch (IllegalArgumentException | SecurityException e) {
            Client.getInstance().handleError(e, ErrorCode.REFLECTION_FAILED,
                    "Could not find method '" + order + "' in AI to do order.");
            return null;
        }

        try {
            Object returned = method.invoke(this, unserializedArgs);
            return returned;
        } catch (Exception e) {
            // assume any exception is their fault, if it was a reflection error it probably was already caught above
            Client.getInstance().handleError(e, ErrorCode.AI_ERRORED,
                    "AI threw exception when executing order '" + order + "'.");
        }

        return null; // should not be reached
    }

    public void setSettings(String aiSettings) {
        if (aiSettings != null && !aiSettings.equals("")) {
            String[] split = aiSettings.split("&");
            for (int i = 0; i < split.length; i++) {
                String[] kv = split[i].split("=");
                String value = "";
                if (kv.length > 1) {
                    value = kv[1];
                }

                this._settings.put(kv[0], value);
            }
        }
    }

    /**
    * Gets an AI setting passed to the program via the `--aiSettings` flag. If the flag was set it will be returned as a string value, null otherwise.
    *
    * @param key The key of the setting you wish to get the value for
    * @return A string representing the value set via command line, or null if the key was not set
    */
    protected String getSetting(String key) {
        if (this._settings.containsKey(key)) {
            return this._settings.get(key);
        }

        return null;
    }
}
