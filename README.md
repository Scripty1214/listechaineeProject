# Projet Listechainee

Ce projet a été réalisé par Ys, Erwan Laniray et Mathieu Hacquard. Nous avons trouvé notre inspiration à partir du projet de notre professeur rcoscali sur GitHub. Ce projet consiste en la manipulation de listes chaînées en langage C.

# Difficultés rencontrées
Nous avons rencontré plusieurs difficultés tout au long du projet. L'un des principaux obstacles était lié à la réinitialisation automatique de notre liste curlist après l'utilisation d'une fonctionnalité pour manipuler les listes chaînées. Nous avons passé plusieurs jours à essayer de résoudre ce problème sans succès.

Une autre difficulté majeure que nous avons rencontrée concernait l'implémentation de la fonction insert_elem_into_list. Nous n'avions pas de stratégie claire sur la manière de la mettre en œuvre efficacement. D'ailleurs, cette fonction a toujours un problème, nous ne pouvons pas inserer d'éléments en dessous de 0. Nous n'avons pas réussi a implémenter cela dans la fonction.

Enfin, lorsque nous faisons append, prepend ou remove, les fonctions marchent très bien et les valeurs sont bien ajouté et supprimés mais visuellement, le système nous sort plusieurs fois le message d'erreur que l'on a défini. Nous n'avons pas réussi a corriger cela mais le code marche tout aussi bien, c'est juste moche visuellement.

# Stratégie adoptée
Après avoir bloqué pendant un certain temps, nous avons décidé de changer d'approche. Nous avons opté pour une méthode de sauvegarde et de mise à jour de la liste curlist dans un fichier texte après chaque opération. Pour cela, nous avons utilisé la fonction save_list.

De plus, pour résoudre le problème de l'insertion d'éléments dans la liste, nous avons décidé de demander à l'utilisateur l'index et l'élément à insérer dans la liste. Cette approche a été appliquée à chaque fonctionnalité du projet.

# Utilisation du menu interactif
Nous avons rencontré des difficultés pour implémenter un menu interactif par nous-mêmes. Finalement, nous avons intégré le menu interactif développé par notre professeur de langage C (rcoscali sur GitHub) pour assurer une meilleure expérience utilisateur.

Ce projet nous a permis de mieux comprendre les concepts des listes chaînées et de renforcer nos compétences en programmation en langage C.

# Apprentissages
Ce projet nous a appris à penser différemment lors de la résolution des problèmes. Nous avons réalisé l'importance d'examiner objectivement notre code afin de détecter les erreurs et de les corriger, même si cela devait nous prendre beaucoup de temps.

Nous avons également rencontré des petits problèmes par-ci par-là dans notre code, mais cela nous a permis de consolider nos compétences en programmation et de mieux comprendre les concepts des listes chaînées.

Ce module nous a offert une expérience enrichissante qui a contribué à notre développement professionnel en tant que programmeurs en herbe. Notre programme peut surement etre optimisé voir amélioré mais nous sommes fier d'avoir fait tout cela meme si notre code est un peu bancal.

# Utilisation

- Cloner le repo:
git clone https://github.com/Scripty1214/listechaineeProject.git

- Aller dans le dosser puis entrer dans le dossier build:
cd listechaineeProject/build

- Executer Ninja:
ninja

- Executer le projet suivi de l'option demandée:
./listechainee -h



# Voici les commandes supportés par notre projet listechainee (et tout marche):

Help menu:
    Options:
        -h : Display help menu
        -v : Increase verbosity
        -d : Display the current list
        -i : Initialize the list
        -l <filename> : Load a list from a file
        -s <filename> : Save the current list to a file
        -t <element> : Test if an element is in the list
        -A <element> : Append an element to the list
        -P <element> : Prepend an element to the list
        -I : Insert an element at the specified index
        -x : Delete the head of the list
        -X : Delete the end of the list
        -r <element> : Remove an element from the list
        -N : Enter interactive mode
