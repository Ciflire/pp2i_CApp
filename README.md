# ppii2-STTV

## Pour lancer le projet
  
Copiez-collez la commande dans votre terminal. Celà va cloner le fichier git dans votre répertoire courrant, puis executer une série de commandes afin de générer les fichiers nécessaires au bon fonctionnement du projet. En il lancera l'application.
```bash
git clone https://gitlab.telecomnancy.univ-lorraine.fr/ppii2_2223/ppii2-grp_18 &&\\ 
cd ppii2-grp_18 && \\
mkdir bin && \\
python3 utils/vehicules/convertion.py && \\
python3 utils/bornes/bornes_cleanup.py && \\
make remake && \\ 
./bin/path
```

Une fois l'application lancée, il vous sera demander de rentrer l'ID de votre voiture. L'application va générer un graphe d'adjacence dépendant de l'autonomie de votre voiture. Il faudra par la suite rentrer l'ID de la borne de départ est d'arrivée, l'autonomie minimale en dessous de laquelle vous ne souhaitez pas descendre, le temps d'attente et le temps de chargement que vous ne souhaitez pas dépasser. L'application vous retournera la suite de bornes à emprunter pour arriver à destination.
