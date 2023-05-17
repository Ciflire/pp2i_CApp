f = open("Données distance.txt", "r")
longueur = len(open("Données distance.txt", "r").readlines())
json = open("Vehicules.json", "w")


k = 0
json.write("[\n")
for x in f:
    json.write('\t{\n \t"id" : ' + str(k) + ',\n\t "name" : "')
    flag = False
    for i in x:
        if i == "\t":
            json.write('", \n\t "distance" : ')
            flag = True
        if i == "A" and flag:
            break  # permet d'enlever "Average" des données
        json.write(i)
    k += 1
    if k == longueur:
        # j'ai pas trouvé mieux pour enlever la virgule à la fin
        json.write('\n\t}\n')
    else:
        json.write('\n\t},\n')
json.write("]")


json.close
f.close
