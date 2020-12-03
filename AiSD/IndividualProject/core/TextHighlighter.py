import os

os.system("")


class styleOfHighlight:
    ERROR = "E"
    WARNING = "W"
    SUCCESS = "S"
    NORMAL = ""


class colors:
    HEADER = '\033[95m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'


def coloredPrint(text: str, style: styleOfHighlight, addLineAtEnd=False, addLineAtBeginning=False):
    if addLineAtBeginning:
        print("")

    if style is None:
        print(text)

    if style == "E":
        print(colors.FAIL + text + colors.ENDC)

    if style == "S":
        print(colors.OKGREEN + text + colors.ENDC)

    if style == "W":
        print(colors.WARNING + text + colors.ENDC)

    if style == "H":
        print(colors.HEADER + text + colors.ENDC)

    if addLineAtEnd:
        print("")
