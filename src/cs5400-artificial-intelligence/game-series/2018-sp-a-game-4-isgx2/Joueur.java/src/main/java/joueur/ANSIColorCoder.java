package joueur;

public enum ANSIColorCoder {
    NONE(0),
    BOLD(1),
    UNDERLINE(4),
    BLINK(5),
    INVERSE(7),
    HIDDEN(8),

    FG_BLACK(30),
    FG_RED(31),
    FG_GREEN(32),
    FG_YELLOW(33),
    FG_BLUE(34),
    FG_MAGENTA(35),
    FG_CYAN(36),
    FG_WHITE(37),
    FG_DEFAULT(39),

    BG_BLACK(40),
    BG_RED(41),
    BG_GREEN(42),
    BG_YELLOW(43),
    BG_BLUE(44),
    BG_MAGENTA(45),
    BG_CYAN(46),
    BG_WHITE(47),
    BG_DEFAULT(49);

    public int value;

    private ANSIColorCoder(int val) {
        this.value = val;
    }

    private static String ansi(int num) {
        return "" + ((char)27) + "[" + num + "m";
    }

    public String apply() {
        return ansi(this.value);
    }

    public static String reset() {
        return ansi(0);
    };
}
