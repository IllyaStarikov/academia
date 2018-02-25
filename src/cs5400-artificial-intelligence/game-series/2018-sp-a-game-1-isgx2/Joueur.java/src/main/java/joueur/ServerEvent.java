package joueur;

public class ServerEvent {
    public String event;
    public Object data;

    public ServerEvent(String event, Object data) {
        this.event = event;
        this.data = data;
    }
}
