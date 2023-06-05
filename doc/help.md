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

### Fonctions

Les fonctions de manipulation de ces bornes sont les suivantes:

```C
borne *borne_create(int id, int pdc, int power, double latitude, double longitude);
```

Cette fonction alloue la mémoire pour une borne, puis peuple ses champs avec les valeurs données en entrée.

```C
void borne_destroy(borne *b);
```

Cette fonction libère la mémoire associée à la borne.

**Toutes les fonctions `borne_get_*` retournent la valeur du champ correspondant de la borne.**

```C
bool borne_equals(borne *b1, borne *b2);
```

Cette fonction retourne `true` si toutes les valeurs des deux bornes sont égales, `false` sinon.

```C
void borne_print(borne *b);
```

Cette fonction affiche les valeurs des champs de la borne sous la forme : `Borne id, pdc, power, latitude, longitude`.
