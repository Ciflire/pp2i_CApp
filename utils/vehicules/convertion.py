# This file contains the functions to convert the data from txt to csv
def parse_txt(origin_txt_autonomie,origin_txt_charge, destination):
    f = open(origin_txt_autonomie, "r")
    g=open(origin_txt_charge,"r")
    csv = open(destination, "w")
    k = 0
    voitures=[]
    for x in f:
        L = x.strip().split(' ')
        s = ""
        for y in L[:-2]:
            s += y+" "
        voitures.append([str(k),s+L[-2],L[-1]])
        k+=1
    for x in g:
        L = x.strip().split(' ')
        name=""
        for y in L[:-2]:
            name += y+" "
        name+=L[-2]
        for i in range(len(voitures)):
            if voitures[i][1]==name:
                voitures[i].append(L[-1])
    for x in voitures[:-1]:
        if len(x)==4:
            csv.write(x[0]+","+x[1]+","+x[2]+","+x[3]+"\n")
    csv.write(voitures[-1][0]+","+voitures[-1][1]+","+voitures[-1][2]+","+voitures[-1][3])
    csv.close
    f.close
    g.close


parse_txt("data/données_distance.txt","data/données_batterie.txt",
          "data/Vehicules.csv")
