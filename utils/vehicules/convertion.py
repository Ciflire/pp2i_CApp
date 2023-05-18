# This file contains the functions to convert the data from txt to csv
def parse_txt(origin_txt, destination):
    f = open(origin_txt, "r")
    csv = open(destination, "a")
    k = 0
    for x in f:
        L = x.strip().split(' ')
        s = ""
        for y in L[:-2]:
            s += y+" "
        csv.write(str(k) + "," + s + str(L[-2]) + "," + str(L[-1]) + '\n')
    csv.close
    f.close


parse_txt('utils/vehicules/données_distance.txt',
          'utils/vehicules/Vehicules.csv')
