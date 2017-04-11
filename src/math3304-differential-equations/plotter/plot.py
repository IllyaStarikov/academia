import matplotlib.pyplot as plt


def step(t_0, t):
    results = []
    for unit in t:
        results += [1 if unit > t_0 else 0]

    return results


def plot(t, s, bounds, chapterNumber, sectionNumber, problemNumber):
    plt.plot(t, s)

    plt.xlabel('t')
    plt.ylabel('y(t)')

    plt.grid(True)
    plt.ylim(bounds)

    plt.savefig("images/{0}.{1}-problem-{2}.eps".format(chapterNumber, sectionNumber, problemNumber), format='eps', dpi=1000)
    plt.show()
