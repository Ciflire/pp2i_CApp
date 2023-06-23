import numpy as np
import matplotlib.pyplot as plt


def heatmap():
    a = np.loadtxt("data/borne_cleaned.csv", skiprows=1, delimiter=',')

    with open('data/response_pdc.txt', 'r') as f:
        data = f.readlines()
        print(len(data))

    usage = np.zeros((len(a), 300))

    i = 0
    j = 0
    for pdc in a[:, 2]:
        i += 1
        for _ in range(int(pdc)):
            if j >= len(data):
                break
            liste = eval(data[j][:-1])
            chemin = np.array(liste)
            j += 1
            for ah in chemin:
                usage[i][ah[0] // 10: ah[1] // 10] += 1

    fig = plt.figure(figsize=(40, 40))
    plt.scatter(a[:, 0], a[:, 1], c='#d44', s=1, figure=fig)
    plt.scatter(a[:, 0], a[:, 1], cmap=plt.cm.summer, c=usage.sum(
        axis=1)/a[:, 2], s=usage.sum(axis=1)*100/a[:, 2], figure=fig)

    fig.savefig('static/images/bornes.png')

    fig1 = plt.figure(figsize=(40, 40))
    plt.imshow(usage, interpolation='nearest',
               cmap=plt.cm.Greens, aspect='auto')
    fig1.savefig('static/images/heatmap.png')

    np.savetxt('data/usage.csv', usage, delimiter=',', fmt='%d')


heatmap()
