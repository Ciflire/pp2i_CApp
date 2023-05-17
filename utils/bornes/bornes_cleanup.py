import pandas as pd

from haversine import haversine_vector
import time

import matplotlib.pyplot as plt
import numpy as np

def timeit(method):
    def timed(*args, **kw):
        ts = time.time()
        result = method(*args, **kw)
        te = time.time()
        if 'log_time' in kw:
            name = kw.get('log_name', method.__name__.upper())
            kw['log_time'][name] = int((te - ts) * 1000)
        else:
            print ('%r  %2.2f ms' % \
                  (method.__name__, (te - ts) * 1000))
        return result
    return timed


@timeit
def cleanup():
    A= pd.read_csv("./schema.csv") #ouverture du CSV

    coords = A["coordonneesXY"] #traitement des coordonnees
    XandY = [eval(smth) for smth in coords.values]
    XandY = pd.DataFrame(XandY, columns=["X","Y"])#separation des X et Y
    XandY = XandY.round(4)# Passage de precision à 75m près

    XYP = XandY.join(A["puissance_nominale"])# ajout des puissances

    XYPN = XYP.join(A["nbre_pdc"])# ajout du nombre de bornes

    XYPN = XYPN.groupby(["X","Y","puissance_nominale"]).max()# somme des bornes par coordonnes et puissance
    XYPN = XYPN.reset_index()# retour a 4 colonnes

    # latitude et longitude bornees
    minXY=[-4.902,42.28]
    maxXY=[8.221,51.24]

    XYPN = XYPN.drop(XYPN[XYPN["X"] > maxXY[0]].index)
    XYPN = XYPN.drop(XYPN[XYPN["X"] < minXY[0]].index)
    XYPN = XYPN.drop(XYPN[XYPN["Y"] > maxXY[1]].index)
    XYPN = XYPN.drop(XYPN[XYPN["Y"] < minXY[1]].index)

    #Verification de l'unité de puissance (kW) par borne
    XYPN['puissance_nominale'] = np.where(XYPN['puissance_nominale'] >= 1000, XYPN['puissance_nominale'] // 1000, XYPN['puissance_nominale'])
    XYPN['puissance_nominale'] = np.where(XYPN['puissance_nominale'] >= 250, XYPN['puissance_nominale'] // 2, XYPN['puissance_nominale'])

    XYPN = XYPN.drop(XYPN[XYPN["puissance_nominale"] <= 1.7].index)

    # XYPN.to_csv("./bornes.csv", index=False, header=False)
  
    L = np.zeros((len(XYPN.index)*(len(XYPN.index)-1)//2,1))
    
    L_index = 0
    for i in range(len(XYPN.index)-1):
        L[L_index:L_index+len(XYPN.index)-1-i]=haversine_vector(XYPN[["X","Y"]].iloc[i], XYPN[["X","Y"]].iloc[i+1:], comb=True, check=False) 
        L_index+=len(XYPN.index)-1-i
    
    # np.savetxt("adjacence.csv", L, delimiter=",")
    # print("done")

    # plot des bornes
    plt.figure(0, figsize=[50,50])
    plt.scatter(XYPN["X"].values,XYPN["Y"].values, c=XYPN["puissance_nominale"].values, s=10*XYPN["nbre_pdc"].values, cmap="plasma")
    # plt.xlim(2,3)
    # plt.ylim(48,49)

    # plot des puissances de chaque borne
    # plt.figure(1)
    # plt.plot(XYPN["nbre_pdc"],'.')

    plt.savefig('bornes.png')

cleanup()