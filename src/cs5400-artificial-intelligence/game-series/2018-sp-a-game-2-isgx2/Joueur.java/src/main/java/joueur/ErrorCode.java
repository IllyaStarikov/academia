package joueur;

public enum ErrorCode {
    NONE(0),
    INVALID_ARGS(20),
    COULD_NOT_CONNECT(21),
    DISCONNECTED_UNEXPECTEDLY(22),
    CANNOT_READ_SOCKET(23),
    DELTA_MERGE_FAILURE(24),
    REFLECTION_FAILED(25),
    UNKNOWN_EVENT_FROM_SERVER(26),
    SERVER_TIMEOUT(27),
    FATAL_EVENT(28),
    GAME_NOT_FOUND(29),
    MALFORMED_JSON(30),
    UNAUTHENTICATED(31),

    AI_ERRORED(42);

    private int returnNumber;

    private ErrorCode(int returnNumber) {
        this.returnNumber = returnNumber;
    }

    public static void handleError(Exception e, ErrorCode errorCode, String errorMessage) {
        if(errorCode != NONE) {
            System.err.println(ANSIColorCoder.FG_RED.apply() + "---\nError: " + errorCode.name());

            if (errorMessage != null) {
                System.err.println("\n" + errorMessage);
            }

            if(e != null) {
                System.err.println("---\n" + e.getMessage() + "\n---");
                e.printStackTrace();
            }

            System.err.println("---" + ANSIColorCoder.reset());
        }

        System.exit(errorCode.returnNumber);
    }
}
