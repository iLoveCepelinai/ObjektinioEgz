#include "egz_pr_bib.h"

//funkcija skirta sutalpinti zodzius kompiuterio atmintyje skaitomus nuo failo
void skaitymas(map<string, zodis>& zodziai) {
    std::ifstream failas;
    string failoPav = "tekstas.txt";

    string eilute;
    vector<string> eilutesZodziai;
    string tempZodis;

    vector<string> skirtukai;
    skirtukai.push_back("; ");
    skirtukai.push_back(", ");
    skirtukai.push_back(". ");
    skirtukai.push_back(": ");
    skirtukai.push_back("? ");
    skirtukai.push_back("! ");
    skirtukai.push_back("- ");
    skirtukai.push_back("> ");
    skirtukai.push_back("< ");
    skirtukai.push_back("\" ");
    skirtukai.push_back(" ");   //paskutinis turi buti tarpas


    int kelintaEil = 0;
    int pos = 0;
    int posVal = 0;

    failas.open(failoPav);

    try {
        if (!failas.good()) {
            throw failoPav;
        }

        //einame per visas eilutes tekstiniame faile
        while (std::getline(failas, eilute)) {
            kelintaEil++;
            pos = 0;

            if (eilute.empty() == false) {
                while ((pos = eilute.find("\t")) != std::string::npos) {
                    eilute.replace(pos, 1, " ");
                }

                //i eilutes vektoriu surasomi visi zodziai (nesvarus)
                while ((pos = eilute.find(skirtukai.back())) != std::string::npos) {
                    tempZodis = eilute.substr(0, pos + skirtukai.back().length());
                    if (tempZodis != " " || tempZodis.empty() == false) {
                        eilutesZodziai.push_back(tempZodis);
                    }
                    eilute.erase(0, pos + skirtukai.back().length());
                }
                //irasome paskutini zodi
                if (eilute.empty() == false) {
                    eilutesZodziai.push_back(eilute);
                }

                //vektoriuje talpinami zodziai "apvalomi" pagal skirtukus
                for (auto& zodelis : eilutesZodziai) {
                    for (auto skirtukas : skirtukai) {
                        posVal = zodelis.find(skirtukas);
                        if (posVal != std::string::npos) {
                            tempZodis = zodelis.substr(0, posVal);
                            zodelis = tempZodis;
                        }
                    }
                    //papildomas valymas, jei sakinio gale yra ? , .
                    if (zodelis.back() == '.' || zodelis.back() == ',' || zodelis.back() == '?' || zodelis.back() == ')'
                        || zodelis.back() == '!' || zodelis.back() == '\"') {
                        tempZodis = zodelis.substr(0, zodelis.size() - 1);
                        zodelis = tempZodis;
                    }
                    //isskirtiniai "prilipe variantai"
                    if (zodelis.front() == '\"' || zodelis.front() == '(') {
                        tempZodis = zodelis.substr(1, zodelis.size());
                        zodelis = tempZodis;
                    }
                    std::transform(zodelis.begin(), zodelis.end(), zodelis.begin(),
                        [](unsigned char c) { return std::tolower(c); });
                }

                //siuo metu turime nuskaite svaria eilute (be skirtuku)

                //talpiname "svarius" zodzius musu map'e
                for (auto& zodelis : eilutesZodziai) {
                    if (zodziai.find(zodelis) != zodziai.end()) {   //jei zodis jau egzistuoja map'e
                        zodziai[zodelis].counter += 1;
                        zodziai[zodelis].eilutes.push_back(kelintaEil);
                    }
                    else if (zodelis.empty() == false) {             //jei zodzio dar nera map'e
                        zodis temp = { 1, {kelintaEil} };
                        zodziai[zodelis] = temp;
                    }
                }
                eilutesZodziai.clear();                             //paruosiame vektoriu kitai eilutei
            }
        }
        skirtukai.clear();  //atlaisviname atminti
        failas.close();
    }
    catch (string pav) {
        cout << pav << " failas neegzistuoja arba jo nepavyko atidaryti\n";
    }
}

void nuorodos(map<string, zodis>& zodziai) {
    cout << "Nuorodos" << endl;
    for (auto zodelis : zodziai) {
        if (zodelis.first.length() > 16) {
            if (zodelis.first.substr(0, 12) == "https://www." && (zodelis.first.substr(zodelis.first.length() - 5, 5) == ".com/" ||
                zodelis.first.substr(zodelis.first.length() - 4, 4) == ".lt/")) {
                cout << zodelis.first << "\n";
            }
        }
        if (zodelis.first.length() > 15) {
            if (zodelis.first.substr(0, 11) == "http://www." && (zodelis.first.substr(zodelis.first.length() - 5, 5) == ".com/" ||
                zodelis.first.substr(zodelis.first.length() - 4, 4) == ".lt/")) {
                cout << zodelis.first << "\n";
            }
        }
        if (zodelis.first.length() > 4) {
            if (zodelis.first.substr(0, 4) == "www." && (zodelis.first.substr(zodelis.first.length() - 4, 4) == ".com" ||
                zodelis.first.substr(zodelis.first.length() - 3, 3) == ".lt")) {
                cout << zodelis.first << "\n";
            }
        }
    }
}

void spausdinimas(map<string, zodis>& zodziai) {
    cout << setw(30) << "ZODIS" << "\t Kiek" << "\t Vietos eilutese" << endl;
    for (auto const& pair : zodziai) {
        if (pair.second.counter > 1) {
            cout << setw(30) << pair.first << "\t" << pair.second.counter << "\t{ ";
            for (auto& eil : pair.second.eilutes) {
                cout << eil << " ";
            }
            cout << "};" << "\n";
        }
    }
}