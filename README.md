# ft_containers
recoding some continers of c++
Implémentez les containers suivants et rendez les fichiers <container>.hpp correspondants :
• vector
Vous n’avez pas à faire la spécialisation vector<bool>.
• map
• stack
Elle utilisera votre classe vector comme container sous-jacent par défaut. Cependant, elle restera compatible avec les autres containers, ceux de la STL inclus.
Vous pouvez valider ce projet sans la stack (80/100).
Cependant, si vous voulez faire la partie bonus, il faudra avoir
réalisé les 3 containers obligatoires.
Vous devez aussi implémenter :
• iterators_traits
• reverse_iterator
• enable_if
Oui, il s’agit de C++11 mais vous saurez le refaire en C++98.
Le but est de vous faire découvrir SFINAE.
• is_integral
• equal et/ou lexicographical_compare
• std::pair
• std::make_pair
5
ft_containers Les containers C++, tout simplement
III.1 Prérequis
• Le namespace doit être ft.
• La structure de données interne utilisée pour chacun de vos containers doit être
cohérente et justifiable (utiliser juste un tableau pour map n’est donc pas accepté).
• Vous ne pouvez pas implémenter plus de fonctions publiques que ne possèdent
les containers standards. Toute autre fonction supplémentaire doit être privée ou
protégée. Chaque fonction et chaque variable publique doit être justifiée.
• Toutes les fonctions membres, les fonctions non-membres et les surcharges d’un
container sont attendues.
• Vous devez vous conformer au nommage original. Faites attention aux détails.
• Si le container possède un système d’itérateur, vous devez l’implémenter.
• Vous devez utiliser std::allocator.
• Pour les surcharges non-membres, le mot-clé friend est autorisé. Chaque utilisation de friend doit être justifiée et sera vérifiée en évaluation.
• Bien entendu, pour implémenter map::value_compare, le mot-clé friend est autoris
