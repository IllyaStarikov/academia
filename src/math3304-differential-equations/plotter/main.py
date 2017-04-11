import numpy as np

from plot import plot, step
from export import importFromFile, getAllImageFiles, exportToLaTeX


def main():
    # The bounds for all the equations
    t = [
        np.arange(-30.0, 30.0, 0.01),
        np.arange(-10, 10, 0.01)
    ]

    # The equations to graph take the form
    # [[ chapterNumber, sectionNumber, problemNumber,
    # equation of t,
    # y-axis bounds], ...]

    graphs = [
        [
            6, 5, 1,
            np.exp(-t[0]) * np.cos(t[0]) - 3 * np.exp(-t[0]) * np.sin(t[0]) + step(np.pi, t[0]) * np.exp(-t[0] + np.pi) * np.sin(t[0] - np.pi),
            [-200, 200]
        ],
        [
            6, 5, 7,
            step(2 * np.pi, t[1]) * np.sinh(t[1]),
            [-2000, 2000]
        ]
    ]

    for graph, tValues in zip(graphs, t):
        plot(tValues, graph[3], graph[4], graph[0], graph[1], graph[2])

    header = importFromFile('./latex-boilerplate/header.tex')
    footer = importFromFile('./latex-boilerplate/footer.tex')

    files = getAllImageFiles()
    exportToLaTeX('assignment.tex', header, footer, files)


if __name__ == "__main__":
    main()
