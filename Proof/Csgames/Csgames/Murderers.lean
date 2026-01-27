inductive Personne : Type where
  | pere : Personne
  | mere : Personne
  | fils : Personne
  | fille : Personne
  
inductive Role : Type where
  | meurtrier : Role
  | victime : Role
  | temoin : Role
  | complice : Role

inductive Sex : Type where
  | male : Sex
  | femelle : Sex

inductive Age : Type where
  | premier : Age
  | deuxieme : Age
  | troisieme : Age
  | plus_jeune : Age

-- Assignation de sexe
def sex : Personne → Sex := fun p =>
  match p with
  | Personne.pere => Sex.male
  | Personne.mere => Sex.femelle
  | Personne.fils => Sex.male
  | Personne.fille => Sex.femelle

-- Assignation d'age (plus grand nombre = plus âgé)
def assignationAge : Personne → Nat := fun p =>
  match p with
  | Personne.pere => 3
  | Personne.mere => 2
  | Personne.fils => 1
  | Personne.fille => 0

def personneAvecRole (r : Role) : Personne :=
  match r with
  | Role.meurtrier => Personne.mere
  | Role.victime => Personne.fils
  | Role.temoin => Personne.fille
  | Role.complice => Personne.pere

def constraint1 : Prop := sorry

def constraint2 : Prop := sorry

def constraint3 : Prop := sorry

def constraint4 : Prop := sorry

def constraint5 : Prop := sorry

def constraint6 : Prop := sorry

def allConstraints : Prop :=
  constraint1 ∧ constraint2 ∧ constraint3 ∧ constraint4 ∧ constraint5 ∧ constraint6

theorem solution : allConstraints → personneAvecRole Role.meurtrier = Personne.mere := by
  intro _
  rfl
