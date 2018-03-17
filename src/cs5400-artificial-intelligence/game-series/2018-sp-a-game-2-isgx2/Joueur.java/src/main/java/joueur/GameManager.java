package joueur;
import java.lang.reflect.Field;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import org.json.JSONObject;

public class GameManager {
    private Client client;
    private BaseGame game;
    private Map<String, BaseGameObject> gameObjects;
    private String gameFolder;
    private String DELTA_LIST_LENGTH; // not a final because it is set AFTER the constructor
    private String DELTA_REMOVED;

    public GameManager(BaseGame game) {
        this.game = game;
        this.client = Client.getInstance();
        this.gameObjects = game.gameObjects;
        this.gameFolder = Client.getInstance().lowercaseFirst(this.game.name);
    }

    public void setConstants(JSONObject constants) {
        this.DELTA_LIST_LENGTH = constants.getString("DELTA_LIST_LENGTH");
        this.DELTA_REMOVED = constants.getString("DELTA_REMOVED");
    }

    public void deltaUpdate(JSONObject delta) {
        this.initGameObjects(delta);

        this.deltaMerge(delta, this.game);
    }

    private void initGameObjects(JSONObject delta) {
        JSONObject jsonGameObjects = delta.optJSONObject("gameObjects");
        if (jsonGameObjects != null) {
            Iterator<?> keys = jsonGameObjects.keys();
            while (keys.hasNext()) {
                String key = (String)keys.next();
                Object value = jsonGameObjects.get(key);

                if (value instanceof JSONObject && !this.gameObjects.containsKey(key)) { // then this is the first time we've seen this game object, so create it.
                    JSONObject jsonGameObject = (JSONObject)value;
                    this.gameObjects.put(key, this.createGameObject(jsonGameObject.getString("gameObjectName")));
                }
            }
        }
    }

    @SuppressWarnings("rawtypes")
    private BaseGameObject createGameObject(String className) {
        try {
            Class gameObjectClass = Class.forName("games." + this.gameFolder + "." + className);
            Constructor<?> constructor = gameObjectClass.getDeclaredConstructors()[0];
            constructor.setAccessible(true);
            return (BaseGameObject)constructor.newInstance();
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | InvocationTargetException e) {
            this.client.handleError(e, ErrorCode.DELTA_MERGE_FAILURE, "Error: could not create base game object of Class '" + className + "'");
        }

        return null;
    }

    @SuppressWarnings("rawtypes")
    private Object deltaMerge(Object delta, Object state) {
        if (delta instanceof JSONObject) {
            JSONObject jsonObject = (JSONObject)delta;

            if (this.isGameObjectReference(jsonObject)) {
                return this.gameObjects.get(jsonObject.getString("id"));
            }

            if (this.isDeltaList(jsonObject)) {
                return this.deltaMergeList((List)state, jsonObject);
            }

            if (state != null && (state instanceof BaseGameObject || state instanceof BaseGame)) {
                return this.deltaMergeClass(state, jsonObject);
            }

            // else it should be a dictionary (which the delta looks identical to a game object, hence why we needed to check for that first).
            return this.deltaMergeMap((Map)state, jsonObject);
        }
        else { // if it's not an object it SHOULD be a string, integer, float, boolean, etc. (some primitive)
            if (this.isDeltaRemoved(delta) || JSONObject.NULL.equals(delta)) {
                return null;
            }
            return delta;
        }
    }

    private Object deltaMergeClass(Object state, JSONObject delta) {
        Iterator<?> keys = delta.keys();
        while (keys.hasNext()) {
            String key = (String)keys.next();

            try {
                Field field = state.getClass().getField(key);
                Object value = this.deltaMerge(delta.get(key), field.get(state));
                field.set(state, value);
            } catch (NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException e) {
                this.client.handleError(e, ErrorCode.DELTA_MERGE_FAILURE, "Error: could not merge field '" + key + "'");
            }
        }

        return state;
    }

    @SuppressWarnings({ "rawtypes", "unchecked" })
    private List deltaMergeList(List list, JSONObject delta) {
        int listLength = delta.getInt(this.DELTA_LIST_LENGTH);

        delta.remove(this.DELTA_LIST_LENGTH);

        while (list.size() < listLength) {
            list.add(null);
        }

        while (list.size() > listLength) {
            list.remove(list.size() - 1);
        }

        Iterator<?> keys = delta.keys();
        while (keys.hasNext()) {
            String key = (String)keys.next();
            int index = Integer.parseInt(key);

            if (index >= 0 && index < listLength) {
                list.set(index, this.deltaMerge(delta.get(key), list.get(index)));
            } // otherwise it's out of range of the list, and probably the DELTA_REMOVED value, which we removed with the above list resizing anyways
        }

        return list;
    }

    @SuppressWarnings({ "unchecked", "rawtypes" })
    private Map deltaMergeMap(Map map, JSONObject delta) {
        Iterator<?> keys = delta.keys();
        while (keys.hasNext()) {
            Object key = keys.next();
            Object deltaValue = delta.get((String)key);

            if (this.isDeltaRemoved(deltaValue)) {
                map.remove(key);
            }
            else {
                map.put(key, this.deltaMerge(deltaValue, map.get(key)));
            }
        }

        return map;
    }

    private boolean isGameObjectReference(JSONObject jsonObject) {
        if (jsonObject != null && jsonObject.length() == 1 && jsonObject.has("id")) {
            String id = jsonObject.optString("id");
            if (id != null && !id.isEmpty()) {
                return true;
            }
        }

        return false;
    }

    private boolean isDeltaList(JSONObject jsonObject) {
        if (jsonObject != null && jsonObject.has(this.DELTA_LIST_LENGTH)) {
            int deltaLength = jsonObject.optInt(this.DELTA_LIST_LENGTH);
            if (deltaLength >= 0) {
                return true;
            }
        }
        return false;
    }

    private boolean isDeltaRemoved(Object obj) {
        return this.DELTA_REMOVED.equals(obj);
    }

    public Map<String, String> serializeGameObject(BaseGameObject baseGameObject) {
        HashMap<String, String> map = new HashMap<String, String>();
        map.put("id", baseGameObject.id);
        return map;
    }

    public Object serializeSafe(Object obj) {
        if (obj instanceof BaseGameObject) {
            return this.serializeGameObject((BaseGameObject)obj);
        }

        return obj;
    }

    public Object unserialize(Object obj) {
        return this.deltaMerge(obj, null);
    }
}
