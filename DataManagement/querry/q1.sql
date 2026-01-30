-- Trouver seulement le tire et le genre des jeux qui sont plus vieux que 1987
-- J'
SELECT J.nom as 'title', J.genre as 'genre' FROM Jeu as J JOIN Sortie AS S ON J.jeuID == S.sortieId WHERE S.annee < 1987;