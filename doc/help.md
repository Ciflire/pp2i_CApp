# Aide

## Bornes

### Structure de borne

La structure des bornes est la suivante :
Type| Nom de variable
-|-
int|id
int|pdc
int|power
double|latitude
double|longitude

### Fonctions de borne.c

Les fonctions de manipulation de ces bornes sont les suivantes:

```C
borne *borne_create(int id, int pdc, int power, double latitude, double longitude);
```

Cette fonction alloue la mémoire pour une borne, puis peuple ses champs avec les valeurs données en entrée.

```C
void borne_destroy(borne *b);
```

Cette fonction libère la mémoire associée à la borne.

> **Toutes les fonctions `borne_get_*` retournent la valeur du champ correspondant de la borne.**

```C
bool borne_equals(borne *b1, borne *b2);
```

Cette fonction retourne `true` si toutes les valeurs des deux bornes sont égales, `false` sinon.

```C
void borne_print(borne *b);
```

Cette fonction affiche les valeurs des champs de la borne sous la forme : `Borne id, pdc, power, latitude, longitude`.

---

### Structure de liste de bornes

La structure des listes de bornes est une **liste doublement chainée cyclique** la suivante :
Type| Nom de variable
-|-
borne*|borne
int|index
borne_list*|next
borne_list*|prev

### Fonctions de borne_list.c

Les fonctions de manipulation de listes de bornes sont les suivantes:

```C
borne_list *borne_list_create(void);
```

Cette fonction alloue la mémoire pour une liste, elle est initialisée avec des pointeurs `next` et `prev` vers elle-même et une borne `NULL`.

```C
void borne_list_destroy(borne_list *list);
```

Cette fonction libère la mémoire associée à la liste de bornes en appelant `borne_destroy` successivement sur toute les bornes.

```C
void borne_list_append(borne_list *list, borne *b);
```

Cette fonction ajoute une borne à la liste de bornes à son bout.

> **Toutes les fonctions `borne_list_get*` retournent la valeur du champ correspondant de la borne.**

```C
int *borne_list_length(borne_list *list);
```

Retourne la longeur de la liste, celle-ci étant la valeur du champ `index` de la dernière borne  

```C
bool borne_list_isBorneInList(borne_list *list, borne *b);
```

Cette fonction retourne `true` si la borne `b` est dans la liste `list`, `false` sinon.

```C
borne *borne_list_print(borne_list *list);
```

Cette fonction affiche les valeurs des champs de la liste de bornes sous la forme : `Borne id, pdc, power, latitude, longitude`.

---

### Structure de voiture

La structure des voitures (nommée "car") est la suivante :
Type| Nom de variable
-|-
char*|Modèle
int|id
double|autonomie (en km)
double|capacité de charge (en kWh)

### Fonctions de car.c

Les fonctions de manipulation de ces cars sont les suivantes:

```C
car *car_create(int id, int pdc, int power, double latitude, double longitude);
```

Cette fonction alloue la mémoire pour une car, puis peuple ses champs avec les valeurs données en entrée.

```C
void car_destroy(car *b);
```

Cette fonction libère la mémoire associée à la car.

> **Toutes les fonctions `car_get_*` retournent la valeur du champ correspondant de la car.**

```C
bool car_equals(car *b1, car *b2);
```

Cette fonction retourne `true` si toutes les valeurs des deux cars sont égales, `false` sinon.

```C
void car_print(car *b);
```

Cette fonction affiche les valeurs des champs de la car sous la forme : `modèle, indice, autonomie, capacité de charge`.

---

### Stucture de liste de voitures

Elle est sensiblement la même que celle des listes de bornes, mais avec des cars à la place des bornes.
