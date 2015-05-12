Zonifieur est une IA codée en moins de 36 heures lors de l'édition Prologin de 2015.

Pour la tester il faut suivre les instructions de https://bitbucket.org/prologin/stechec2 pour lancer des parties sur le jeu prologin2015.

L'IA tente à chaque tour de se déplacer vers un portail estimé optimal de le capturer et de créer une bonne disposition de lien à partir de là.
Elle essaye d'éviter au possible les boucles perdantes via LoopAvoider.
Pour déterminer si un portail est intéressant on lui calcule une valeur heuristique en fonction de ce qu'on pourra faire perdre ou qu'on pourra gagner avec.
On place systématiquement 2 boucliers après capture qu'on renforce si on a des PA en fin d'action.
Pour créer les liens on s'arrange pour essayer d'avoir des patterns qui maximisent la réutilisation d'une même aire.

Au final cette IA est arrivée 8ème au classement général.

L'ensemble de son code à l'exception des fichiers prologin.hh, prologin.cc et Makefile (sous GPLv2) est sous license CC-BY-NC.