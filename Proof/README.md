# Preuve avec Lean 4

## Configuration pour Lean 4
Pour participer à cette compétition, vous devez installer `Lean 4`

Pour ce faire, installez d'abord `elan`, le gestionnaire de versions de `lean4`. 

Je recommande également d'installer l'[extension VSCode](https://marketplace.visualstudio.com/items?itemName=leanprover.lean4) pour `lean4` afin de pouvoir compiler automatiquement ce projet et avoir un aperçu.

Ensuite, installez `Lean 4` en utilisant cette commande :

```bash
elan toolchain install leanprover/lean4:v4.27.0
elan default leanprover/lean4:v4.27.0
```

Ensuite, exécutez la commande suivante dans le répertoire `Csgames/` pour installer les dépendances du projet :

```bash
lake update
```

# Pour compléter le défi, référez-vous aux fichiers dans le dossier CsGames