getFillitFiles="true"
makeTests="true"
fillitPath="../fillit"
fillitPathIsCustom="false"

function print_help
{
read -r -d '' HELP_TEXT << EOM
DESCRIPTION:
Recupere et compile fillit pour les tests de test-fillit..

LISTE DES COMMANDES:
<chemin_vers_fillit>      Specifie le chemin vers fillit (le dossier contenant
                          le Makefile et les sources etc).
                          Ne peut etre specifie qu'une seule fois, autrement une erreur se produit.
--nogetfillit             Ne recupere pas les fichiers du dossier fillit.
--nomake                  N'execute pas make a la fin du script.
-h / --help               Affiche cette page d'aide.
EOM

echo "$HELP_TEXT"
}

for param in "$@"; do
	if [[ "$param" =~ ^--.* ]]; then
		if [[ "$param" == "--nogetfillit" ]]; then
			getFillitFiles="false"
		elif [[ "$param" == "--nomake" ]]; then
			makeTests="false"
		elif [[ "$param" == "--help" ]]; then
			print_help
			exit 0
		else
			echo "Erreur: parametre $param inconnu. Utilisez --help pour afficher l'aide."
			exit 0
		fi
	elif [[ "$param" =~ ^-.* ]]; then
		if [[ "$param" == "-h" ]]; then
			print_help
			exit 0
		else
			echo "Erreur: parametre $param inconnu. Utilisez --help pour afficher l'aide."
			exit 0
		fi
	fi
done

for param in "$@"; do
	if [[ ! "$param" =~ ^-.* ]]; then
		if [[ "$fillitPathIsCustom" == "false" ]]; then
			fillitPath="$param"
			fillitPathIsCustom="true"
		else
			echo "Trop d'arguments, le chemin de fillit ne peut etre initialise qu'une fois. Utilisez --help pour afficher l'aide."
			exit 0
		fi
	fi
done

if [[ "$getFillitFiles" == "true" ]]; then
	rm -r "fillit"
	cp -R "${fillitPath}" "fillit"
	make -C fillit
fi
if [[ "$makeTests" == "true" ]]; then
	make -j4
fi
