# DevOps (Github Actions)

Vous devrez bâtir une pipeline CI/CD pour un projet de Python afin de répondre à différents besoin de l'équipe de développement.

Veuillez consulter le `README.md` du projet pour avoir plus d'infos sur le stack utilisé et comment initialiser le serveur.

## Étape 1

Créer un nouveau repo Github avec tous les fichiers du dossier `fastapi-app`. Assurez-vous que le contenu du dossier `fastapi-app` soit à la racine du repo pour que les pipelines Github Actions fonctionnent adéquatement.

**Assurez-vous de créer un repo public pour la correction**

## Étape 2 (CI)

Ajoutez au projet un workflow Github Actions (`cicd.yml`) qui roule à chaque création de PR, et à chaque push dans une PR existante. Le workflow devra réaliser les actions suivantes:

### 2.1 Linter

Rouler tous les Linters pour vérifier la syntaxe du code.

### 2.2 Tests

Rouler tous les tests du projet **avec coverage**. Le workflow doit échouer si un test échoue.

**Attention ! Veillez à ce que 2 runs différentes de `cicd.yml` ne roule jamais les tests simultanément ! J'ai entendu dire que les `concurrency groups` de Github Actions pourrait aider.**

### 2.3 Build

Build le projet avec Poetry pour vérifier que le projet ne crash pas. Le workflow doit échouer si le build échoue.

### 2.4 Tag
Créer un tag de version

Prérequis:
- Relié à Main ET/OU flag d'exécution "IMAGE" à True

Pour ce faire:
- Ce tag doit suivre la nomenclature SEMVER
- L'utilisation d'outil de tagging est permis, tel que https://github.com/semantic-release/semantic-release
- Ce tag doit être appliqué sur le commit correspondant et doit idéalement créer une variable d'environnement pour les autres workflow "SEM_VERSION"

## Étape 3 (Job)

Ajoutez au projet un workflow Github Actions (`job.yml`) qui roule à chaque heure automatiquement. Le workflow devra réaliser les actions suivantes:

### 3.1 Date

Afficher la date actuelle dans la console avec le format suivant: `YYYY-MM-DD`
