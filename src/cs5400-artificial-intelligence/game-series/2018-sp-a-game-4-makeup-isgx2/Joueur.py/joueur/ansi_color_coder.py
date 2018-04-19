_style = {
    "none": 0,
    "bold": 1,
    "underline": 4,
    "blink": 5,
    "inverse": 7,
    "hidden": 8
}

_text = {
    "black": 30,
    "red": 31,
    "green": 32,
    "yellow": 33,
    "blue": 34,
    "magenta": 35,
    "cyan": 36,
    "white": 37,
    "default": 39
}

_background = {
    "black": 40,
    "red": 41,
    "green": 42,
    "yellow": 43,
    "blue": 44,
    "magenta": 45,
    "cyan": 46,
    "white": 47,
    "default": 49
}


def ansi(num):
    return "\033[{}m".format(num)


def style(key="default"):
    return ansi(_style[key])


def text(key="default"):
    return ansi(_text[key])


def background(key="default"):
    return ansi(_background[key])


def reset():
    return ansi(0)
