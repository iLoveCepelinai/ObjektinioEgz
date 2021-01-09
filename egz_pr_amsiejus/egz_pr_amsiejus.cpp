/*
Matas Amðiejus
VU, DM2 2 kursas
2021 01 09
*/

#include "egz_pr_bib.h"

int main() {

    map<string, zodis> zodziai;

    skaitymas(zodziai);

    nuorodos(zodziai);

    spausdinimas(zodziai);

	system("pause");
	return 0;
}


