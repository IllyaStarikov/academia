import matplotlib.pyplot as plt
import numpy as np


def step(t_0, t):
    results = []
    for unit in t:
        results += [1 if unit > t_0 else 0]

    return results


chapterNumber = 6
sectionNumber = 5
problemNumber = 1

bounds = [-200, 200]  # y-axis bounds
t = np.arange(-30.0, 30.0, 0.01)  # x-axis bounds
s = np.exp(-t) * np.cos(t) - 3 * np.exp(-t) * np.sin(t) + step(np.pi, t) * np.exp(-t + np.pi) * np.sin(t - np.pi)  # equation of t

plt.plot(t, s)

plt.xlabel('t')
plt.ylabel('y(t)')
plt.title("Section {0}.{1}, Problem #{2}".format(chapterNumber, sectionNumber, problemNumber))

plt.grid(True)
plt.ylim(bounds)

plt.savefig("images/{0}.{1}-problem-{2}.eps".format(chapterNumber, sectionNumber, problemNumber), format='eps', dpi=1000)
plt.show()
