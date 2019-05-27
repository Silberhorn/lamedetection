#ifndef LANECALCULATION_H
#define LANECALCULATION_H

class lanecalculation
{
private:
	// Vektoren für erkannte Koordinaten
	Vec4i left;
	Vec4i right;

	// Steigungen
	double steigung_left;
	double y_achsenabschnitt_left;
	double x_Schnitt_left;
	double steigung_right;
	double y_achsenabschnitt_right;
	double x_Schnitt_right;
	
	int counter_left;
	int counter_right;
	
	// Distanz zum Fahrbahnrand
	int distance_L;
	int distance_R;
	
public:
	lanecalculation(Vec4i left, Vec4i right);
    ~lanecalculation();

	string getStringDistance();
};

#endif	// LANECALCULATION_H