DROP TABLE IF EXISTS Sortie CASCADE;
DROP TABLE IF EXISTS Personnage CASCADE;
DROP TABLE IF EXISTS Jeu CASCADE;
DROP TABLE IF EXISTS Console CASCADE;
DROP TABLE IF EXISTS PersonnageJeux CASCADE;
DROP TABLE IF EXISTS Developpeur CASCADE;

CREATE TABLE Developpeur (
    developpeurID INT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    pays VARCHAR(50) NOT NULL
);

CREATE TABLE Jeu (
    jeuID INT PRIMARY KEY,
    titre VARCHAR(100) NOT NULL,
    genre VARCHAR(50) NOT NULL,
    note DECIMAL(3,1) NOT NULL,
    developpeurID INT,
    FOREIGN KEY (developpeurID) REFERENCES Developpeur(developpeurID)
);

CREATE TABLE Console (
    consoleID INT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    annee INT NOT NULL,
    fabricant VARCHAR(100) NOT NULL
);

CREATE TABLE Personnage (
    personnageID INT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL
);

CREATE TABLE PersonnageJeux (
    personnageJeuxID INT PRIMARY KEY,
    personnageID INT,
    jeuID INT NOT NULL,
    FOREIGN KEY (jeuID) REFERENCES Jeu(jeuID)
);

CREATE TABLE Sortie (
    sortieID INT PRIMARY KEY,
    jeuID INT NOT NULL,
    consoleID INT NOT NULL,
    annee INT NOT NULL,
    FOREIGN KEY (jeuID) REFERENCES Jeu(jeuID),
    FOREIGN KEY (consoleID) REFERENCES Console(consoleID)
);

-- Classic Game Developers
INSERT INTO Developpeur VALUES (401, 'Nintendo', 'Japan');
INSERT INTO Developpeur VALUES (402, 'Atari', 'USA');
INSERT INTO Developpeur VALUES (403, 'Sega', 'Japan');
INSERT INTO Developpeur VALUES (404, 'Capcom', 'Japan');
INSERT INTO Developpeur VALUES (405, 'PlayStation', 'USA');
INSERT INTO Developpeur VALUES (406, 'Rare', 'UK');

-- Retro Game Consoles
INSERT INTO Console VALUES (501, 'NES', 1983, 'Nintendo');
INSERT INTO Console VALUES (502, 'Atari 2600', 1977, 'Atari');
INSERT INTO Console VALUES (503, 'Sega Genesis', 1988, 'Sega');
INSERT INTO Console VALUES (504, 'Super Nintendo', 1990, 'Nintendo');
INSERT INTO Console VALUES (505, 'PlayStation 1', 1994, 'Sony');
INSERT INTO Console VALUES (506, 'Nintendo 64', 1996, 'Nintendo');
INSERT INTO Console VALUES (507, 'Game Boy', 1989, 'Nintendo');
INSERT INTO Console VALUES (508, 'Sega Master System', 1985, 'Sega');

-- Classic Games
INSERT INTO Jeu VALUES (1, 'Super Mario Bros',  'Platformer', 9.3, 401);
INSERT INTO Jeu VALUES (2, 'Pac-Man',  'Arcade', 8.9, 402);
INSERT INTO Jeu VALUES (3, 'The Legend of Zelda',  'Adventure', 9.1, 401);
INSERT INTO Jeu VALUES (4, 'Sonic the Hedgehog',  'Platformer', 8.7, 403);
INSERT INTO Jeu VALUES (5, 'Donkey Kong',  'Arcade', 8.8, 401);
INSERT INTO Jeu VALUES (6, 'Mega Man',  'Platformer', 8.5, 404);
INSERT INTO Jeu VALUES (7, 'Mega Man X',  'Platformer', 8.5, 404);
INSERT INTO Jeu VALUES (8, 'Final Fantasy VII',  'Platformer', 9.5, 405);
INSERT INTO Jeu VALUES (9, 'GoldenEye 007',  'Shooter', 9.0, 406);
INSERT INTO Jeu VALUES (10, 'Tetris',  'Puzzle', 9.2, 402);
INSERT INTO Jeu VALUES (11, 'Super Mario Kart',  'Racing', 9.6, 401);

-- Game Characters
INSERT INTO Personnage VALUES (1, 'Mario');
INSERT INTO Personnage VALUES (2, 'Luigi');
INSERT INTO Personnage VALUES (3, 'Pac-Man');
INSERT INTO Personnage VALUES (4, 'Miss Pac-Man');
INSERT INTO Personnage VALUES (5, 'Link');
INSERT INTO Personnage VALUES (6, 'Sonic');
INSERT INTO Personnage VALUES (7, 'Doctor Eggman');
INSERT INTO Personnage VALUES (8, 'Donkey Kong');
INSERT INTO Personnage VALUES (9, 'Donkey Kong Jr');
INSERT INTO Personnage VALUES (10, 'Mega Man');
INSERT INTO Personnage VALUES (11, 'Cloud Strife');
INSERT INTO Personnage VALUES (12, 'James Bond');
INSERT INTO Personnage VALUES (13, 'Tetris Block');
INSERT INTO Personnage VALUES (14, 'Proto Man');

-- Character Appearances in Games
INSERT INTO PersonnageJeux VALUES (1, 1, 1); 
INSERT INTO PersonnageJeux VALUES (2, 2, 1);
INSERT INTO PersonnageJeux VALUES (3, 3, 2); 
INSERT INTO PersonnageJeux VALUES (4, 4, 2); 
INSERT INTO PersonnageJeux VALUES (5, 5, 3);
INSERT INTO PersonnageJeux VALUES (6, 6, 4); 
INSERT INTO PersonnageJeux VALUES (7, 7, 4); 
INSERT INTO PersonnageJeux VALUES (8, 8, 5); 
INSERT INTO PersonnageJeux VALUES (9, 9, 5); 
INSERT INTO PersonnageJeux VALUES (10, 10, 6);  
INSERT INTO PersonnageJeux VALUES (11, 10, 7);  
INSERT INTO PersonnageJeux VALUES (12, 11, 8);
INSERT INTO PersonnageJeux VALUES (13, 12, 9);
INSERT INTO PersonnageJeux VALUES (14, 13, 10);
INSERT INTO PersonnageJeux VALUES (15, 1, 11); 
INSERT INTO PersonnageJeux VALUES (16, 2, 11);
INSERT INTO PersonnageJeux VALUES (17, 8, 11);
INSERT INTO PersonnageJeux VALUES (18, 9, 11);
INSERT INTO PersonnageJeux VALUES (19, 14, 6);  
INSERT INTO PersonnageJeux VALUES (20, 14, 7);  


-- Game Releases
INSERT INTO Sortie VALUES (601, 1, 501, 1985);
INSERT INTO Sortie VALUES (602, 2, 502, 1980);
INSERT INTO Sortie VALUES (603, 3, 501, 1986);
INSERT INTO Sortie VALUES (604, 4, 503, 1991);
INSERT INTO Sortie VALUES (605, 5, 502, 1981);
INSERT INTO Sortie VALUES (606, 6, 501, 1987);
INSERT INTO Sortie VALUES (607, 7, 501, 1993);
INSERT INTO Sortie VALUES (608, 8, 504, 1997);
INSERT INTO Sortie VALUES (609, 9, 506, 1997);
INSERT INTO Sortie VALUES (610, 10, 501, 1984);
INSERT INTO Sortie VALUES (611, 11, 504, 1992);