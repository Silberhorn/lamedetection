#ifndef LANECALCULATION_H_
#define LANECALCULATION_H_

using namespace std;
using namespace cv;
using namespace boost::geometry::model::d2;

class lanecalculation
{
private:
	// Vektoren fuer erkannte Koordinaten
	Vec4i left;
	Vec4i right;

	// Steigungen
	double steigung_left;
	double y_achsenabschnitt_left;
	double x_Schnitt_left;
	double steigung_right;
	double y_achsenabschnitt_right;
	double x_Schnitt_right;

	// Distanz zum Fahrbahnrand
	int distance_L;
	int distance_R;

public:
	lanecalculation(Vec4i, Vec4i);
    ~lanecalculation();

	int getDistanceLeft();
	int getDistanceRight();

	string getStringDistance();
};

#endif	// LANECALCULATION_H_
