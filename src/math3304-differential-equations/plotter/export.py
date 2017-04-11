import glob
import re


def importFromFile(filename):
    filehandler = open(filename)
    contents = filehandler.readlines()
    filehandler.close()

    return contents


def exportToFile(filename, contents):
    filehandler = open(filename, 'w+')
    filehandler.writelines(contents)
    filehandler.close()


def appendToFile(filename, contents):
    filehandler = open(filename, 'a+')
    filehandler.writelines(contents)
    filehandler.close()


# returns an array of images of the form (filename, chapter number, section number, problem number)
def getAllImageFiles():
    files = []

    regex = '(\d)\.(\d)-problem-(\d)\..*'
    pattern = re.compile(regex)

    for file in glob.glob('./images/*'):
        if pattern.search(file):
            matches = pattern.search(file)
            files += [[matches.group(0), matches.group(1), matches.group(2), matches.group(3)]]

    return files


def bodyString(imageFile):
    return [
        '\setcounter{{section}}{{{0}}}\n'.format(imageFile[1]),
        '\setcounter{{subsection}}{{{0}}}\n'.format(imageFile[2]),
        '\subsection{{Problem \#{0}}}\n'.format(imageFile[3]),
        '\\begin{center}\n',
        '    \includegraphics[width=\\textwidth]{{./plotter/images/{{{0}}}}}\n'.format(imageFile[0]),
        '\end{center}\n'
    ]


def exportToLaTeX(filename, header, footer, imageFiles):
    exportToFile(filename, "")
    appendToFile(filename, header)

    for imageFile in imageFiles:
        appendToFile(filename, bodyString(imageFile))

    appendToFile(filename, footer)


header = importFromFile("./latex-boilerplate/header.tex")
footer = importFromFile("./latex-boilerplate/footer.tex")

images = getAllImageFiles()

exportToLaTeX("assignment.tex", header, footer, images)
