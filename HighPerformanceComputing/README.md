# High Performance Computing avec CubeCl (Rust)

Pour ce défi, vous allez devoir implémenter un algorithme connu qui va rouler sur votre GPU!

## But du défi

Implémenter l'algorithme [Bailey–Borwein–Plouffe](https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula) en Rust en utilisant CubeCl pour paralléliser le calcul.
$$\pi = \sum_{k=0}^{\infty} \left[ \frac{1}{16^k} \left( \frac{4}{8k+1} - \frac{2}{8k+4} - \frac{1}{8k+5} - \frac{1}{8k+6} \right) \right]$$
Cet algorithme permet de calculer le n-ième chiffre hexadécimal de Pi et est une sommation de plusieurs termes.
Le calcul de chaque terme est indépendant des autres, il est donc possible de paralléliser le calcul.


## Instructions

Pour compiler le projet:
1. Installer Rust https://www.rust-lang.org/tools/install
1. Changer de répertoire pour être dans le dossier `CubeCl/`
1. Lancer le projet avec la commande `cargo run`

Dans votre programme, je vous recommande d'utiliser un terme de vectorisation pas plus haut que 4 pour commencer.
Par exemple, pour l'itération `n`, calculer et enregistrer le n-ième nombre à la position 0. 
Ensuite le (n+1)-ième à la position 1, etc.


## Exemple pour vous aider à démarrer
Exemple de code: https://github.com/tracel-ai/cubecl/tree/main/examples

## Pour changer le "backend" utilisé

Il est également possible de changer la méthode d'accélération de calcul que `CubeCl` utilise.
Pour ce faire, il suffit de lancer la commande `cargo run --features <backend>`.
Les backends disponibles sont:
- `wgpu`: (Par défaut) Fonctionne avec n'importe quelle carte graphique.
- `cuda`: Fonctionne uniquement avec les cartes graphiques NVIDIA.

---

# High Performance Computing avec Burn (Rust)

Pour ce deuxième défi, vous allez devoir implémenter les fonctions pour faire fonctionner un perceptron!

Un perceptron est un seul "neurone" utilisé dans les modèles d'intelligence artificielle. 
Avec seulement un perceptron, il est possible d'approximer des fonctions linéaires, ce qui va être votre objectif.

La fonction en question est **y = 2x + 20**

Dans ce défi, vous allez devoir finir l'implémentation des fonctions suivantes:

- `feed_forward(&self, inputs: &[f32]) -> i32`: Fonction permettant de calculer la valeur produite par le perceptron selon des données en entrée (une liste du format [x,y])
- `activate(s: f32) -> i32`: La fonction d'activation
- `train(&mut self, inputs: &[f32], desired: i32)`: La fonction qui permet d'entraîner le perceptron afin de trouver les bonnes valeurs de `weights`.

## Instructions

Pour compiler le projet:
1. Installer Rust https://www.rust-lang.org/tools/install
1. Changer de répertoire pour être dans le dossier `burn/`
1. Lancer le projet avec la commande `cargo run`

## Référence
Voici la documentation de [Burn](https://burn.dev/docs/burn/)

Et cet article expliquant l'implémentation d'un perceptron: https://medium.com/@irisjohn/training-a-single-perceptron-neural-networks-358680ddb33a